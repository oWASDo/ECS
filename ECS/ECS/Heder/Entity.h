#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class Entity
{
public:
	Entity();
	~Entity();


	//void AddType(std::string type, int index);
	void AddType(int type, int index);
	bool HasType(int type);

private:
	//map<std::string, long long > components;
	//std::vector<std::string> types;
	std::vector<int> types;
	std::vector<int> typesIndex;

};

