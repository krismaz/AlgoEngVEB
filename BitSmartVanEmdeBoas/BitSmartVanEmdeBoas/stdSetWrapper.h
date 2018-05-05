#pragma once
#include <set>
class stdSetWrapper
{
private:
	std::set<unsigned long> set;
public:
	unsigned int Min() { return *set.begin(); }
	unsigned int Max() { return *set.rbegin(); }
	stdSetWrapper() {};
	~stdSetWrapper() {};
	bool Contains(unsigned int key) { return set.find(key) != set.end(); }
	unsigned int Predecessor(unsigned int key) { return *(--set.lower_bound(key)); }
	unsigned int Successor(unsigned int key) { return *set.upper_bound(key); };
	void Insert(unsigned int key) { set.insert(key); }
	void Delete(unsigned int key) { set.erase(key); }
};