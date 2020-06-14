#pragma once
#include "List.h"

class Assoñ_arr
{
public:
	List list[5];
	Assoñ_arr();
	HANDLE hThread;
	HANDLE hEventBufEmpty;
	HANDLE hEventBufFull;
	std::string buf1;
	std::string buf2;
	void asyncAdd(const std::string& key, const std::string& value);
	void add(const std::string& key, const std::string& value);
	void del(const std::string& key);
	static int hashCode(const std::string& value);
	void write(HANDLE structFile);
	void read(HANDLE structFile);

};
inline std::ostream& operator <<(std::ostream& os, const Assoñ_arr& arr)
{
	for (int i = 0; i < 5; i++)
		os << arr.list[i] << "\t\n";
	return os;
}
