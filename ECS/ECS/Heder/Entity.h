#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


class Entity
{
public:
	Entity();
	virtual ~Entity();


	/*
	* Get phisical index by given struct number.
	* If entity do not have any struct type return -1
	* @param type: as number.
	* @param index: logical index.
	*/
	void AddType(int type, int index);

	/**
	* Check if entity already have given type.
	* @param type: type as number.
	* @param index: struct number.
	* @return true-> have | false->not have.
	*/
	bool HasType(int type);

	/**
	* Get phisical index by given struct number.
	* If entity do not have any struct type return -1
	* @param index: type as number.
	* @return phisical index.
	*/
	int GetIndexByType(int type);

private:

	std::vector<int> types;
	std::vector<int> typesIndex;

};

