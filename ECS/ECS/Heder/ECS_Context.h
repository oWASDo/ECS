#pragma once
#include "Entity.h"
#include <vector>
#include <map>
#include <list>
#include <string>
#include <stdexcept>
#include <memory>

//using namespace std;

class ECS_Context
{
public:

	ECS_Context();
	~ECS_Context();

	std::shared_ptr<Entity> AddEntity();

	template<typename T>
	void AddComponentToEntity(Entity* entity, T baseData);


	//template<typename A>
	//int GetTypes();

	//template<typename A, typename B>
	//int* GetTypes();

	//template<typename A, typename B, typename C>
	//void GetTypes();

	//template<typename A, typename B, typename C, typename D>
	//void GetTypes();

	//template<typename A, typename B, typename C, typename D, typename E>
	//void GetTypes();

	//template<typename A, typename B, typename C, typename D, typename E, typename F>
	//void GetTypes();

	//template<typename A, typename B, typename C, typename D, typename E, typename F, typename G>
	//void GetTypes();

private:

	std::vector<std::shared_ptr<Entity>> entities;
	std::map<std::string, int> typeMaps;
	std::map<std::string, int> typeSizes;
	std::map<std::string, int> typeNumberElement;
	std::vector<std::string> typrOrder;
	std::vector<char> datas;
};




#pragma region Comment to reimplement
//template<typename A>
//int ECS_Content::GetTypes()
//{
//	const char* name = typeid(A).name();
//	std::string nameAsString = std::string(name);
//	int typeA = typeMaps[nameAsString];
//}
//template<typename A, typename B>
//int* ECS_Content::GetTypes()
//{
//	std::list<int> typeNames;
//
//	const char* name = typeid(A).name();
//	std::string nameAsString = std::string(name);
//	int numberType = typeMaps[nameAsString];
//	typeNames.push_back(numberType);
//
//	name = typeid(B).name();
//	nameAsString = std::string(name);
//	numberType = typeMaps[nameAsString];
//	if (std::find(typeNames.begin(), typeNames.end(), numberType) != typeNames.end())
//	{
//		throw "Same type insert in this function";
//	}
//	typeNames.push_back(numberType);
//
//	int arr[list.size()];
//	std::copy(list.begin(), list.end(), arr);
//}
//template<typename A, typename B, typename C>
//void ECS_Content::GetTypes()
//{
//	const char* name = typeid(A).name();
//	std::string nameAsString = std::string(name);
//	int typeA = typeMaps[nameAsString];
//
//	name = typeid(B).name();
//	nameAsString = std::string(name);
//	int typeB = typeMaps[nameAsString];
//
//	name = typeid(C).name();
//	nameAsString = std::string(name);
//	int typeC = typeMaps[nameAsString];
//}
//template<typename A, typename B, typename C, typename D>
//void ECS_Content::GetTypes()
//{
//
//}
//template<typename A, typename B, typename C, typename D, typename E>
//void ECS_Content::GetTypes()
//{
//
//}
//template<typename A, typename B, typename C, typename D, typename E, typename F>
//void ECS_Content::GetTypes()
//{
//
//}
//template<typename A, typename B, typename C, typename D, typename E, typename F, typename G>
//void ECS_Content::GetTypes()
//{
//
//}

#pragma endregion

template<typename T>
void ECS_Context::AddComponentToEntity(Entity* entity, T baseData) {

	int dataSize = sizeof(T);

	const char* name = typeid(T).name();
	std::string nameAsString = std::string(name);

	//if (entity->HasType(typeMaps[nameAsString]))
	int typeAsInteger = typeMaps.size() + 1;

	if (entity->HasType(typeAsInteger))
	{
		throw "This entity already has this component ->" + nameAsString;
	}

	if (nameAsString.find("struct"))
	{
		throw "T type is not a struct";
	}
	auto contain = typeMaps.find(nameAsString);

	if (contain == typeMaps.end())
	{
		//exist
		typeMaps.insert(std::pair<std::string, int >(nameAsString, typeAsInteger));
		typeSizes.insert(std::pair<std::string, int >(nameAsString, sizeof(T)));
		typeNumberElement.insert(std::pair<std::string, int >(nameAsString, 1));
		typrOrder.push_back(nameAsString);
	}
	else
	{
		typeNumberElement[nameAsString]++;
	}

	//entity->AddType(nameAsString, typeNumberElement[nameAsString]);
	entity->AddType(typeMaps[nameAsString], typeNumberElement[nameAsString]);

	long long index = 0;
	for (std::string orderedName : typrOrder) {
		long long size = typeSizes[orderedName];
		long long numofElements = typeNumberElement[orderedName] + (orderedName == nameAsString ? -1 : 0);

		index += size * numofElements;
		if (orderedName == nameAsString)
		{
			break;
		}
	}
	auto indexIt = datas.begin() + index;
	char zeroDatas[sizeof(T)] = {};
	std::memcpy(&zeroDatas, &baseData, dataSize);

	datas.insert(indexIt, zeroDatas, zeroDatas + sizeof(T));


}
