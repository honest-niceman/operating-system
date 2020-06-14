#include "List.h"

List::List()
{
	first = nullptr;
}
List :: ~List() {}

void List::add(const std::string& key, const std::string& value)
{
	if (!first)
	{
		first = new Node(key, value);
	}
	else
	{
		Node* p = first;
		first = new Node(key, value);
		first->next = p;
	}
}

void List::del(const std::string& key)
{
	if (first->key == key)
	{
		Node* p = first;
		first->next = first->next->next;
	}
	else
	{
		Node* p = first;
		while (p->next && p->next->key != key)
		{
			p = p->next;
		}
		if (!p->next) return;
		Node* n = p->next;
		p->next = p->next->next;
		delete n;
	}
}
