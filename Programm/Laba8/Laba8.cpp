#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <tchar.h>
#include "Assoc_arr.h"

#define DATA_BUFFER_SIZE 256

const TCHAR FileInMemoryName[] = TEXT("file1");
const TCHAR FileInMemoryName2[] = TEXT("file2");
HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, DATA_BUFFER_SIZE, FileInMemoryName);
HANDLE hMapFile2 = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, DATA_BUFFER_SIZE, FileInMemoryName2);


int main1() {
	Assoс_arr arr;
	auto putBufKey = (char*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, DATA_BUFFER_SIZE);
	auto putBufValue = (char*)MapViewOfFile(hMapFile2, FILE_MAP_ALL_ACCESS, 0, 0, DATA_BUFFER_SIZE);
	std::string value((int)*putBufValue, ' ');
	std::string key((int)*putBufKey, ' ');
	CopyMemory((void*)key.c_str(), (void*)(putBufKey + 1), (int)*putBufKey);
	CopyMemory((void*)value.c_str(), (void*)(putBufValue + 1), (int)*putBufValue);
	arr.add(key, value);
	std::cout << arr;
	system("pause");
	return 0;
}


int main2()
{
	std::string key = "12345";
	std::string value = "abcde";
	auto putBufKey = (char*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, DATA_BUFFER_SIZE);
	auto putBufValue = (char*)MapViewOfFile(hMapFile2, FILE_MAP_ALL_ACCESS, 0, 0, DATA_BUFFER_SIZE);
	*putBufKey = (char)key.length();
	*putBufValue = (char)value.length();
	CopyMemory((void*)(putBufKey + 1), key.c_str(), key.length());
	CopyMemory((void*)(putBufValue + 1), value.c_str(), value.length());

	HANDLE structfile;
	STARTUPINFO startupInfo;
	PROCESS_INFORMATION processInfo;
	ZeroMemory(&startupInfo, sizeof(STARTUPINFO));
	startupInfo.cb = sizeof(STARTUPINFO);
	BOOL RET = CreateProcess(L"C:\\Users\\Георгий\\Desktop\\OS\\Laba8\\Debug\\Laba8.exe", 
		NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL,NULL, &startupInfo, &processInfo);

	WaitForSingleObject(processInfo.hProcess, INFINITE);

	CloseHandle(processInfo.hProcess);
	system("pause");
	return 0;
}

int main() {
	main1();
	main2();
	return 0;
}