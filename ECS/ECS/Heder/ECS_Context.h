#pragma once
#include "Entity.h"
#include <vector>
#include <map>
#include <list>
#include <string>
#include <stdexcept>
#include <memory>
#include"Component.h"
//using namespace std;

class ECS_Context
{
public:

	ECS_Context();
	virtual ~ECS_Context();

	/*
	* EntityCration
	* @return retun entity pointer.
	*/
	Entity* CreateAndAddEntity();

	/*
	* Link component to entity
	* @param entity: entity to link.
	* @param baseData: inizialization data.
	*/
	template<typename T>
	void AddComponentToEntity(Entity* entity, T baseData);

	/*
	* Unlink component to entity
	* @param entity: entity to unlink.
	*/
	template<typename T>
	void RemoveComponentToEntity(Entity* entity);

#pragma region getter
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

#pragma endregion

private:

	std::vector<Entity> entities;
	std::map<std::string, int> typeMaps;
	std::map<std::string, int> typeSizes;
	std::map<std::string, int> typeNumberElement;
	std::vector<std::string> typrOrder;
	std::vector<char> datas;
	std::vector<bool> actives;

	/*
	* Get phisical index by given struct number.
	* If entity do not have any struct type return -1
	* @param nameAsString: name type to Check.
	* @param entity: entity linked where get indicies.
	* @return Indexes calss with logical index and phisical index.
	*/
	Indicies GetIdexes(const std::string nameAsString, Entity* entity);


	/*
	* Get phisical index by given struct number.
	* If entity do not have any struct type return -1
	* @param nameAsString: name type to Check.
	* @param index: return logical index.
	* @return true-> memory free in type | false-> memory not free in type.
	*/
	bool GetFalseInAtype(const std::string nameAsString, int& index);
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
void ECS_Context::AddComponentToEntity(Entity* entity, const T baseData) {

	int dataSize = sizeof(T);

	//get name data name
	const char* name = typeid(T).name();
	std::string nameAsString = std::string(name);

	//entity already has this component
#pragma region Check if entity already has this component
	int typeAsInteger = typeMaps.size() + 1;

	if (entity->HasType(typeAsInteger))
	{
		throw "This entity already has this component ->" + nameAsString;
	}
#pragma endregion

	//Check if is a struct
#pragma region Check if is a struct

	if (nameAsString.find("struct"))
	{
		throw "T type is not a struct";
	}
#pragma endregion

	int unactiveDataIndex;
	bool haveHataNull = GetFalseInAtype(nameAsString, unactiveDataIndex);

	//Check is there is already this struct registered
	auto haveThisComponentAlready = typeMaps.find(nameAsString);
	if (haveThisComponentAlready == typeMaps.end()) // not exist
	{
		//exist
		typeMaps.insert(std::pair<std::string, int >(nameAsString, typeAsInteger));
		typeSizes.insert(std::pair<std::string, int >(nameAsString, sizeof(T)));
		typeNumberElement.insert(std::pair<std::string, int >(nameAsString, 1));
		typrOrder.push_back(nameAsString);
	}
	else if (haveHataNull == false) //exist
	{
		typeNumberElement[nameAsString]++;
	}

	//Link entity to data
	entity->AddType(typeMaps[nameAsString], typeNumberElement[nameAsString]);


	//check if there is a free data
	auto indxes = GetIdexes(nameAsString, entity);
	if (haveHataNull)
	{
		actives[unactiveDataIndex] = true;
		char* charPtr = datas.data();
		std::memcpy(charPtr + indxes.Ind1(), &baseData, dataSize);

	}
	else
	{

		auto indexIt = datas.begin() + indxes.Ind1();
		char zeroDatas[sizeof(T)] = {};

		std::memcpy(&zeroDatas, &baseData, dataSize);

		auto iter = actives.begin();

		actives.insert(iter, true);
		datas.insert(indexIt, zeroDatas, zeroDatas + sizeof(T));

	}

}
template<typename T>
inline void ECS_Context::RemoveComponentToEntity(Entity* entity)
{
	int dataSize = sizeof(T);

	//get name data name
	const char* name = typeid(T).name();
	std::string nameAsString = std::string(name);

	//find pointer of data to set free
	auto indxes = GetIdexes(nameAsString, entity);

	//copy new data
	actives[indxes.Ind2()] = false;
	char zeroDatas[sizeof(T)] = {};
	std::memcpy(&datas[indxes.Ind1()], &zeroDatas, dataSize);

}
