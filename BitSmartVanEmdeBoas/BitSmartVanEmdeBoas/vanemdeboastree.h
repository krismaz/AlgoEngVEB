#pragma once
template <int bits>
class VanEmdeBoasTree
{
private:
	unsigned int min;
	unsigned int max;
	void InsertEmpty(unsigned int);
public:
	unsigned int Min() { return min; }
	unsigned int Max() { return max; }
	VanEmdeBoasTree();
	~VanEmdeBoasTree();
	bool Contains(unsigned int);
	unsigned int Predecessor(unsigned int);
	void Insert(unsigned int);
	void Delete(unsigned int);
};