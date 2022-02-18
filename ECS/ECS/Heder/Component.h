#pragma once


struct Indicies
{
private:
	size_t index1;
	size_t index2;
public:
	Indicies() {
		index1 = 0;
		index2 = 0;
	}
	Indicies(size_t i1, size_t i2) :index1(i1), index2(i2) {

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
		integer = 0;
	}
	Integet(int newInt): integer(newInt)
	{

	}
	int integer;
};

struct Flaoting
{
	Flaoting()
	{
		_float = 0.0f;
	}
	Flaoting(float newFlaot) : _float(newFlaot)
	{

	}
	float _float;
};

struct Boolean
{
	Boolean()
	{
		_bool = false;
	}
	Boolean(bool newBool): _bool(newBool)
	{
		_bool = true;
	}
	bool _bool;
};


struct Vector3
{
	Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	Vector3(float newX, float newY, float newZ):x(newX),y(newY),z(newZ)
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	float x;
	float y;
	float z;
};


struct Vector2
{
	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2(float newX, float newY) :x(newX), y(newY)
	{
		x = 0.0f;
		y = 0.0f;
	}
	float x;
	float y;
};

