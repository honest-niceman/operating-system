#pragma once
#include <iostream>
#include <string>

class List
{
public:
	struct Node {
		std::string key;
		std::string value;
		Node(const std::string& k, const std::string& v)
		{
			key = k;
			value = v;
			next = nullptr;
		}
		Node* next;
		~Node() {}
	};
	Node* first;
	void add(const std::string& key, const std::string& value);
	void del(const std::string& key);
	List();
	~List();
};
inline std::ostream& operator << (std::ostream& os, const List& list)
{
	auto* p = list.first;
	while (p != nullptr)
	{
		os << p->key << " - " << p->value << "\t\n";
		p = p->next;
	}
	return os;
}
