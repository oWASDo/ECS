#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../Heder/Macros.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	void print() {

		//std::cout << this << std::endl;

		/*for (size_t i = 0; i < types.size(); i++)
		{
			std::vector <int>::iterator it = types.begin() + i;
			int* p = &(*it);
			std::cout << p << std::endl;

		}

		for (size_t i = 0; i < typesIndex.size(); i++)
		{
			std::vector <int>::iterator it = types.begin() + i;
			int* p = &(*it);
			std::cout << p << std::endl;

		}*/
		/*for (size_t i = 0; i < 5; i++)
		{
			auto a = &type_[i];
			std::cout << a << std::endl;

		}
		for (size_t i = 0; i < 5; i++)
		{
			auto a = &free_[i];
			std::cout << a << std::endl;

		}
		for (size_t i = 0; i < 5; i++)
		{
			auto a = &typeIndex_[i];
			std::cout << a << std::endl;

		}
		std::cout << "" << std::endl;
		*/
	}

	/*
	* Get phisical index by given struct number.
	* If entity do not have any struct type return -1
	* @param type: as number.
	* @param index: logical index.
	*/
	void AddType(int type, int index);

	void RemoveType(int type);

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


	int  type_[MaxComponentPeEntyty];
	bool free_[MaxComponentPeEntyty];
	int  typeIndex_[MaxComponentPeEntyty];
	
};

