#include <iostream>
#include <fstream>
#include <Windows.h>
#include "sstream"
#include "iostream"
#include "List.h"
#include "Assoc_Arr.h"

Assoñ_arr::Assoñ_arr()
{
	DWORD id;
	buf1 = "";
	buf2 = "";
	hEventBufEmpty = CreateEvent(NULL, FALSE, TRUE, NULL);
	hEventBufFull = CreateEvent(NULL, FALSE, FALSE, NULL);
	hThread = CreateThread(NULL, 0, [](PVOID s)->DWORD
		{
			Assoñ_arr* arr = (Assoñ_arr*)s;
			while (true)
			{
				WaitForSingleObject(arr->hEventBufFull, INFINITE);
				arr->add(arr->buf1, arr->buf2);
				SetEvent(arr->hEventBufEmpty);
			}
			return 0;
		}, this, 0, &id);
}

int Assoñ_arr::hashCode(const std::string& value)
{
	int res = 0;
	for (unsigned int i = 0; i < value.length(); i++)
	{
		res += value[i];
	}
	return res % 5;
}

void Assoñ_arr::asyncAdd(const std::string& key, const std::string& value)
{
	WaitForSingleObject(hEventBufEmpty, INFINITE);
	buf1 = key;
	buf2 = value;
	SetEvent(hEventBufFull);
}

void Assoñ_arr::add(const std::string& key, const std::string& value)
{
	int hashKey = hashCode(key);
	List::Node* p = list[hashKey].first;
	while (p != nullptr)
	{
		if (p->key == key)
		{
			p->value = value;
			return;
		}
		p = p->next;
	}
	if (p == nullptr)
	{
		List::Node* temp = list[hashKey].first;
		list[hashKey].first = new List::Node(key, value);
		list[hashKey].first->next = temp;
		return;
	}
}

void Assoñ_arr::del(const std::string& key)
{
	int hashKey = hashCode(key);
	List::Node* p = list[hashKey].first;
	if (p == nullptr)
		return;
	if (p->key == key)
	{
		list[hashKey].first = p->next;
		delete p;
		return;
	}
	List::Node* temp = p;
	while (p && p->key != key)
	{
		temp = p;
		p = p->next;
	}
	if (p != nullptr)
	{
		temp->next = p->next;
		delete p;
	}
}

void Assoñ_arr::write(HANDLE handle)
{
	DWORD dw;
	for (int i = 0; i < 5; i++)
	{
		List::Node* p = list[i].first;
		while (p != nullptr)
		{
			size_t buf = p->key.length();
			WriteFile(handle, &buf, sizeof size_t, &dw, nullptr);
			WriteFile(handle, p->key.c_str(), p->key.length(), &dw, nullptr);
			buf = p->value.length();
			WriteFile(handle, &buf, sizeof size_t, &dw, nullptr);
			WriteFile(handle, p->value.c_str(), p->value.length(), &dw, nullptr);
			p = p->next;
		}
	}
}
void Assoñ_arr::read(HANDLE handle)
{
	DWORD dw;
	size_t length = 5;
	ReadFile(handle, &length, sizeof(size_t), &dw, nullptr);
	std::string key(length, ' ');
	ReadFile(handle, (void*)key.c_str(), length, &dw, nullptr);
	ReadFile(handle, &length, sizeof(size_t), &dw, nullptr);
	std::string value(length, ' ');
	ReadFile(handle, (void*)value.c_str(), length, &dw, nullptr);
	while (dw != 0)
	{
		add(key, value);
		ReadFile(handle, &length, sizeof(size_t), &dw, nullptr);
		key = std::string(length, ' ');
		ReadFile(handle, (void*)key.c_str(), length, &dw, nullptr);
		ReadFile(handle, &length, sizeof(size_t), &dw, nullptr);
		value = std::string(length, ' ');
		ReadFile(handle, (void*)value.c_str(), length, &dw, nullptr);
	}
}
