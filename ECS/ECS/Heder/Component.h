#pragma once


struct Indexes
{
private:
	size_t index1;
	size_t index2;
public:
	Indexes() {
		index1 = 0;
		index2 = 0;
	}
	Indexes(size_t i1, size_t i2) :index1(i1), index2(i2) {

	}

	size_t Ind1() {
		return index1;
	}
	size_t Ind2() {
		return index2;
	}
};

struct Integet
{
	Integet()
	{
		i = 454;
	}
	Integet(int j)
	{
		i = j;
	}
	int i;
};

struct Flaoting
{
	Flaoting()
	{
		f = 500.144f;
	}
	float f;
};

struct Boolean
{
	Boolean()
	{
		b = false;
	}
	Boolean(int i)
	{
		b = true;
	}
	bool b;
};


struct Vector3
{
	Vector3()
	{
			
	}
	float x;
	float y;
	float z;
};


struct Vector2
{
	Vector2()
	{
			
	}
	float x;
	float y;
};

