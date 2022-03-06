#pragma once
#include "Entity.h"
#include <vector>
#include <map>
#include <list>
#include <string>
#include <stdexcept>
#include <memory>
#include "Exeptions.h"

#include"Component.h"
#include "../Heder/Macros.h"


class ECS_Context
{
public:

	ECS_Context();
	virtual ~ECS_Context();

	/*
	* EntityCration
	* @return retun entity pointer.
	*/
	int CreateAndAddEntity();


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

	template<typename A>
	void GetTypes(std::vector<A*>& outVector);

	template<typename A, typename B>
	void GetTypes(
		std::vector<A*>& outVectorA,
		std::vector<B*>& outVectorB);

	template<typename A, typename B, typename C>
	void GetTypes(
		std::vector<A*>& outVectorA,
		std::vector<B*>& outVectorB,
		std::vector<C*>& outVectorC);

	template<typename A, typename B, typename C, typename D>
	void GetTypes(
		std::vector<A*>& outVectorA,
		std::vector<B*>& outVectorB,
		std::vector<C*>& outVectorC,
		std::vector<D*>& outVectorD
	);

	template<typename A, typename B, typename C, typename D, typename E>
	void GetTypes(
		std::vector<A*>& outVectorA,
		std::vector<B*>& outVectorB,
		std::vector<C*>& outVectorC,
		std::vector<D*>& outVectorD,
		std::vector<E*>& outVectorE
	);

	template<typename A, typename B, typename C, typename D, typename E, typename F>
	void GetTypes(
		std::vector<A*>& outVectorA,
		std::vector<B*>& outVectorB,
		std::vector<C*>& outVectorC,
		std::vector<D*>& outVectorD,
		std::vector<E*>& outVectorE,
		std::vector<F*>& outVectorF
	);

	template<typename A, typename B, typename C, typename D, typename E, typename F, typename G>
	void GetTypes(std::vector<A*>& outVectorA,
		std::vector<B*>& outVectorB,
		std::vector<C*>& outVectorC,
		std::vector<D*>& outVectorD,
		std::vector<E*>& outVectorE,
		std::vector<F*>& outVectorF,
		std::vector<G*>& outVectorG
	);

	template<typename T>
	std::string GetName()
	{
		const char* name = typeid(T).name();
		return std::string(name);
	}

	template<typename T>
	const char* GetRawName()
	{
		const char* name = typeid(T).name();
		return name;
	}
	
	Entity* GetEntity(int e) {
		std::vector <Entity>::iterator it = entities.begin() + e;
		Entity* p = &(*it);

		return p;
	}

#pragma endregion


	bool NameCodeContainsKey(std::string stringToCheck);
	size_t NameCodeGetCode(std::string stringToCheck);

private:

	std::vector<Entity> entities;
	std::vector<std::vector<bool>*> vectorOfActivesOfActives;
	std::vector<std::vector<char>*> vectorOfDatasOfDatas;
	std::vector<std::string> typeOrder;
	std::map<std::string, int> componentsNameCode;
	std::map<std::string, int> componentsSize;
	std::map<std::string, int> nuberOfElementPerComponentType;


	const std::string structChar = "struct";

	int GetLogicIndexFromName(std::string nameAsString);

};


template<typename T>
void ECS_Context::AddComponentToEntity(Entity* entity, T baseData)
{
	//get data size
	int dataSize = sizeof(T);

	//get name data name
	std::string nameAsSTDString = std::string(typeid(T).name());

	//Check if is a struct
#pragma region Check if is a struct

	if (nameAsSTDString.find(structChar) == std::string::npos)
	{
		try
		{
			throw IsNotAStruct();
		}
		catch (const IsNotAStruct& e)
		{
			throw IsNotAStruct();
		}
	}

#pragma endregion

	bool componentNameExist = false;
	for (const auto nameCode : componentsNameCode) {
		if (nameCode.first == nameAsSTDString) {
			componentNameExist = true;
			break;
		}
	}

	int typeAsInteger = componentsNameCode.size();

	if (!componentNameExist) // not exist
	{
		//exist
		componentsNameCode.insert(std::pair<std::string, int >(nameAsSTDString, typeAsInteger));
		componentsSize.insert(std::pair<std::string, int >(nameAsSTDString, dataSize));
		nuberOfElementPerComponentType.insert(std::pair<std::string, int >(nameAsSTDString, 1));
		typeOrder.emplace_back(nameAsSTDString);
		vectorOfDatasOfDatas.emplace_back(new std::vector<char>());
		vectorOfActivesOfActives.emplace_back(new std::vector<bool>());
	}


#pragma region Check if entity already has this component

	typeAsInteger = componentsNameCode.at(nameAsSTDString);
	if (entity->HasType(typeAsInteger))
	{
		try
		{
			throw ComponentAlreadyExist(/*nameAsSTDString*/);
		}
		catch (const ComponentAlreadyExist& e)
		{
			throw ComponentAlreadyExist(/*nameAsSTDString*/);
		}
	}
#pragma endregion

	int dataTypeAsNuber = GetLogicIndexFromName(nameAsSTDString);

	auto selectedActives = vectorOfActivesOfActives.at(dataTypeAsNuber);
	auto selectedDataLine = vectorOfDatasOfDatas.at(dataTypeAsNuber);

	if (std::any_of(selectedActives->begin(), selectedActives->end(), [](bool active) {return active == false; }))
	{
		for (int i = 0; i < selectedActives->size(); i++)
		{
			auto active = selectedActives->at(i);
			if (active == false)
			{
				entity->AddType(componentsNameCode.at(nameAsSTDString), i + 1);
				char zeroDatas[sizeof(T)] = {};
				std::memcpy(&zeroDatas, &baseData, dataSize);

				std::memcpy(selectedDataLine->data() + (i * dataSize), zeroDatas, dataSize);

				selectedActives->at(i) = true;

			}
		}
	}
	else
	{
		entity->AddType(componentsNameCode.at(nameAsSTDString), nuberOfElementPerComponentType.at(nameAsSTDString));

		nuberOfElementPerComponentType.at(nameAsSTDString)++;
		char zeroDatas[sizeof(T)] = {};
		std::memcpy(&zeroDatas, &baseData, dataSize);


		for (size_t i = 0; i < dataSize; i++)
		{
			selectedDataLine->emplace_back(0);

		}
		vectorOfActivesOfActives.at(dataTypeAsNuber)->emplace_back(true);

	}
}



template<typename T>
void ECS_Context::RemoveComponentToEntity(Entity* entity)
{
	int dataSize = sizeof(T);

	//get name data name
	const char* name = typeid(T).name();
	std::string nameAsString = std::string(name);

	int dataTypeAsNuber = GetLogicIndexFromName(nameAsString);


	auto selectedActives = vectorOfDatasOfDatas.at(dataTypeAsNuber);
	auto selectedDataLine = vectorOfActivesOfActives.at(dataTypeAsNuber);

	if (entity->HasType(componentsNameCode.at(nameAsString)))
	{
		int index = entity->GetIndexByType(componentsNameCode.at(nameAsString)) - 1;
		for (size_t i = 0; i < dataSize; i++)
		{
			selectedActives->at((index * dataSize) + i) = 0;

		}
		selectedDataLine->at(index) = false;

	}

	int indexType = componentsNameCode.at(nameAsString);

	entity->RemoveType(indexType);

}


template<typename A>
void ECS_Context::GetTypes(
	std::vector<A*>& outVector)
{
	const char* name = typeid(A).name();

	for (auto entity : entities)
	{
		if (entity.HasType(componentsNameCode.at(name)))
		{
			int index = entity.GetIndexByType(componentsNameCode.at(name));
			int dataTypeAsNuber = GetLogicIndexFromName(GetName<A>());

			auto selectedData = vectorOfDatasOfDatas.at(dataTypeAsNuber);

			A* datIndex = (A*)((selectedData->data() + ((index - 1) * sizeof(A))));

			outVector.emplace_back(datIndex);

		}
	}
}

template<typename A, typename B>
void ECS_Context::GetTypes(
	std::vector<A*>& outVectorA,
	std::vector<B*>& outVectorB)
{
#pragma region Name

	const char* nameA = GetRawName<A>();
	const char* nameB = GetRawName<B>();
#pragma endregion

	for (auto entity : entities)
	{
		if (entity.HasType(componentsNameCode.at(nameA)) &&
			entity.HasType(componentsNameCode.at(nameB)))
		{
#pragma region Index
			int indexA = entity.GetIndexByType(componentsNameCode.at(nameA));
			int indexB = entity.GetIndexByType(componentsNameCode.at(nameB));
#pragma endregion

#pragma region DataNuber

			int dataTypeAsNuberA = GetLogicIndexFromName(GetName<A>());
			int dataTypeAsNuberB = GetLogicIndexFromName(GetName<B>());
#pragma endregion

#pragma region Datas

			auto selectedA = vectorOfDatasOfDatas.at(dataTypeAsNuberA);
			auto selectedB = vectorOfDatasOfDatas.at(dataTypeAsNuberB);
#pragma endregion

#pragma region fill vector
			A* datIndexA = (A*)((selectedA->data() + ((indexA - 1) * sizeof(A))));
			outVectorA.emplace_back(datIndexA);

			B* datIndexB = (B*)((selectedB->data() + ((indexB - 1) * sizeof(B))));
			outVectorB.emplace_back(datIndexB);
#pragma endregion

		}
	}
}

template<typename A, typename B, typename C>
void ECS_Context::GetTypes(
	std::vector<A*>& outVectorA,
	std::vector<B*>& outVectorB,
	std::vector<C*>& outVectorC)
{
#pragma region Name

	const char* nameA = GetRawName<A>();
	const char* nameB = GetRawName<B>();
	const char* nameC = GetRawName<C>();
#pragma endregion

	for (auto entity : entities)
	{
		if (entity.HasType(componentsNameCode.at(nameA)) &&
			entity.HasType(componentsNameCode.at(nameB)) &&
			entity.HasType(componentsNameCode.at(nameC)))
		{
#pragma region Index

			int indexA = entity.GetIndexByType(componentsNameCode.at(nameA));
			int indexB = entity.GetIndexByType(componentsNameCode.at(nameB));
			int indexC = entity.GetIndexByType(componentsNameCode.at(nameC));
#pragma endregion

#pragma region DataNuber

			int dataTypeAsNuberA = GetLogicIndexFromName(GetName<A>());
			int dataTypeAsNuberB = GetLogicIndexFromName(GetName<B>());
			int dataTypeAsNuberC = GetLogicIndexFromName(GetName<C>());
#pragma endregion

#pragma region Datas

			auto selectedA = vectorOfDatasOfDatas.at(dataTypeAsNuberA);
			auto selectedB = vectorOfDatasOfDatas.at(dataTypeAsNuberB);
			auto selectedC = vectorOfDatasOfDatas.at(dataTypeAsNuberC);
#pragma endregion

#pragma region fill vector

			A* datIndexA = (A*)((selectedA->data() + ((indexA - 1) * sizeof(A))));
			outVectorA.emplace_back(datIndexA);

			B* datIndexB = (B*)((selectedB->data() + ((indexB - 1) * sizeof(B))));
			outVectorB.emplace_back(datIndexB);

			C* datIndexC = (C*)((selectedC->data() + ((indexC - 1) * sizeof(C))));
			outVectorC.emplace_back(datIndexC);
#pragma endregion

		}
	}
}

template<typename A, typename B, typename C, typename D>
void ECS_Context::GetTypes(
	std::vector<A*>& outVectorA,
	std::vector<B*>& outVectorB,
	std::vector<C*>& outVectorC,
	std::vector<D*>& outVectorD)
{
#pragma region Name

	const char* nameA = GetRawName<A>();
	const char* nameB = GetRawName<B>();
	const char* nameC = GetRawName<C>();
	const char* nameD = GetRawName<D>();
#pragma endregion

	for (auto entity : entities)
	{
		if (entity.HasType(componentsNameCode.at(nameA)) &&
			entity.HasType(componentsNameCode.at(nameB)) &&
			entity.HasType(componentsNameCode.at(nameC)) &&
			entity.HasType(componentsNameCode.at(nameD)))
		{
#pragma region Index

			int indexA = entity.GetIndexByType(componentsNameCode.at(nameA));
			int indexB = entity.GetIndexByType(componentsNameCode.at(nameB));
			int indexC = entity.GetIndexByType(componentsNameCode.at(nameC));
			int indexD = entity.GetIndexByType(componentsNameCode.at(nameD));
#pragma endregion

#pragma region DataNuber

			int dataTypeAsNuberA = GetLogicIndexFromName(GetName<A>());
			int dataTypeAsNuberB = GetLogicIndexFromName(GetName<B>());
			int dataTypeAsNuberC = GetLogicIndexFromName(GetName<C>());
			int dataTypeAsNuberD = GetLogicIndexFromName(GetName<D>());
#pragma endregion

#pragma region Datas

			auto selectedA = vectorOfDatasOfDatas.at(dataTypeAsNuberA);
			auto selectedB = vectorOfDatasOfDatas.at(dataTypeAsNuberB);
			auto selectedC = vectorOfDatasOfDatas.at(dataTypeAsNuberC);
			auto selectedD = vectorOfDatasOfDatas.at(dataTypeAsNuberC);
#pragma endregion

#pragma region fill vector

			A* datIndexA = (A*)((selectedA->data() + ((indexA - 1) * sizeof(A))));
			outVectorA.emplace_back(datIndexA);

			B* datIndexB = (B*)((selectedB->data() + ((indexB - 1) * sizeof(B))));
			outVectorB.emplace_back(datIndexB);

			C* datIndexC = (C*)((selectedC->data() + ((indexC - 1) * sizeof(C))));
			outVectorC.emplace_back(datIndexC);

			D* datIndexD = (D*)((selectedD->data() + ((indexD - 1) * sizeof(D))));
			outVectorD.emplace_back(datIndexD);
#pragma endregion

		}
	}

}

template<typename A, typename B, typename C, typename D, typename E>
void ECS_Context::GetTypes(
	std::vector<A*>& outVectorA,
	std::vector<B*>& outVectorB,
	std::vector<C*>& outVectorC,
	std::vector<D*>& outVectorD,
	std::vector<E*>& outVectorE)
{
#pragma region Name

	const char* nameA = GetRawName<A>();
	const char* nameB = GetRawName<B>();
	const char* nameC = GetRawName<C>();
	const char* nameD = GetRawName<D>();
	const char* nameE = GetRawName<E>();
#pragma endregion

	for (auto entity : entities)
	{
		if (entity.HasType(componentsNameCode.at(nameA)) &&
			entity.HasType(componentsNameCode.at(nameB)) &&
			entity.HasType(componentsNameCode.at(nameC)) &&
			entity.HasType(componentsNameCode.at(nameD)) &&
			entity.HasType(componentsNameCode.at(nameE)))
		{
#pragma region Index

			int indexA = entity.GetIndexByType(componentsNameCode.at(nameA));
			int indexB = entity.GetIndexByType(componentsNameCode.at(nameB));
			int indexC = entity.GetIndexByType(componentsNameCode.at(nameC));
			int indexD = entity.GetIndexByType(componentsNameCode.at(nameD));
			int indexE = entity.GetIndexByType(componentsNameCode.at(nameE));
#pragma endregion

#pragma region DataNuber

			int dataTypeAsNuberA = GetLogicIndexFromName(GetName<A>());
			int dataTypeAsNuberB = GetLogicIndexFromName(GetName<B>());
			int dataTypeAsNuberC = GetLogicIndexFromName(GetName<C>());
			int dataTypeAsNuberD = GetLogicIndexFromName(GetName<D>());
			int dataTypeAsNuberE = GetLogicIndexFromName(GetName<E>());
#pragma endregion

#pragma region Datas

			auto selectedA = vectorOfDatasOfDatas.at(dataTypeAsNuberA);
			auto selectedB = vectorOfDatasOfDatas.at(dataTypeAsNuberB);
			auto selectedC = vectorOfDatasOfDatas.at(dataTypeAsNuberC);
			auto selectedD = vectorOfDatasOfDatas.at(dataTypeAsNuberC);
			auto selectedE = vectorOfDatasOfDatas.at(dataTypeAsNuberE);
#pragma endregion

#pragma region fill vector

			A* datIndexA = (A*)((selectedA->data() + ((indexA - 1) * sizeof(A))));
			outVectorA.emplace_back(datIndexA);

			B* datIndexB = (B*)((selectedB->data() + ((indexB - 1) * sizeof(B))));
			outVectorB.emplace_back(datIndexB);

			C* datIndexC = (C*)((selectedC->data() + ((indexC - 1) * sizeof(C))));
			outVectorC.emplace_back(datIndexC);

			D* datIndexD = (D*)((selectedD->data() + ((indexD - 1) * sizeof(D))));
			outVectorD.emplace_back(datIndexD);

			E* datIndexE = (E*)((selectedE->data() + ((indexE - 1) * sizeof(E))));
			outVectorE.emplace_back(datIndexE);
#pragma endregion

		}
	}
}

template<typename A, typename B, typename C, typename D, typename E, typename F>
void ECS_Context::GetTypes(
	std::vector<A*>& outVectorA,
	std::vector<B*>& outVectorB,
	std::vector<C*>& outVectorC,
	std::vector<D*>& outVectorD,
	std::vector<E*>& outVectorE,
	std::vector<F*>& outVectorF)
{
#pragma region Name
	const char* nameA = GetRawName<A>();
	const char* nameB = GetRawName<B>();
	const char* nameC = GetRawName<C>();
	const char* nameD = GetRawName<D>();
	const char* nameE = GetRawName<E>();
	const char* nameF = GetRawName<F>();
#pragma endregion

	for (auto entity : entities)
	{
		if (entity.HasType(componentsNameCode.at(nameA)) &&
			entity.HasType(componentsNameCode.at(nameB)) &&
			entity.HasType(componentsNameCode.at(nameC)) &&
			entity.HasType(componentsNameCode.at(nameD)) &&
			entity.HasType(componentsNameCode.at(nameE)) &&
			entity.HasType(componentsNameCode.at(nameF)))
		{
#pragma region Index

			int indexA = entity.GetIndexByType(componentsNameCode.at(nameA));
			int indexB = entity.GetIndexByType(componentsNameCode.at(nameB));
			int indexC = entity.GetIndexByType(componentsNameCode.at(nameC));
			int indexD = entity.GetIndexByType(componentsNameCode.at(nameD));
			int indexE = entity.GetIndexByType(componentsNameCode.at(nameE));
			int indexF = entity.GetIndexByType(componentsNameCode.at(nameF));
#pragma endregion

#pragma region DataNuber

			int dataTypeAsNuberA = GetLogicIndexFromName(GetName<A>());
			int dataTypeAsNuberB = GetLogicIndexFromName(GetName<B>());
			int dataTypeAsNuberC = GetLogicIndexFromName(GetName<C>());
			int dataTypeAsNuberD = GetLogicIndexFromName(GetName<D>());
			int dataTypeAsNuberE = GetLogicIndexFromName(GetName<E>());
			int dataTypeAsNuberF = GetLogicIndexFromName(GetName<F>());
#pragma endregion

#pragma region Datas

			auto selectedA = vectorOfDatasOfDatas.at(dataTypeAsNuberA);
			auto selectedB = vectorOfDatasOfDatas.at(dataTypeAsNuberB);
			auto selectedC = vectorOfDatasOfDatas.at(dataTypeAsNuberC);
			auto selectedD = vectorOfDatasOfDatas.at(dataTypeAsNuberC);
			auto selectedE = vectorOfDatasOfDatas.at(dataTypeAsNuberE);
			auto selectedF = vectorOfDatasOfDatas.at(dataTypeAsNuberF);
#pragma endregion

#pragma region fill vector

			A* datIndexA = (A*)((selectedA->data() + ((indexA - 1) * sizeof(A))));
			outVectorA.emplace_back(datIndexA);

			B* datIndexB = (B*)((selectedB->data() + ((indexB - 1) * sizeof(B))));
			outVectorB.emplace_back(datIndexB);

			C* datIndexC = (C*)((selectedC->data() + ((indexC - 1) * sizeof(C))));
			outVectorC.emplace_back(datIndexC);

			D* datIndexD = (D*)((selectedD->data() + ((indexD - 1) * sizeof(D))));
			outVectorD.emplace_back(datIndexD);

			E* datIndexE = (E*)((selectedE->data() + ((indexE - 1) * sizeof(E))));
			outVectorE.emplace_back(datIndexE);

			F* datIndexF = (F*)((selectedF->data() + ((indexF - 1) * sizeof(F))));
			outVectorF.emplace_back(datIndexF);
#pragma endregion

		}
	}
}

template<typename A, typename B, typename C, typename D, typename E, typename F, typename G>
void ECS_Context::GetTypes(
	std::vector<A*>& outVectorA,
	std::vector<B*>& outVectorB,
	std::vector<C*>& outVectorC,
	std::vector<D*>& outVectorD,
	std::vector<E*>& outVectorE,
	std::vector<F*>& outVectorF,
	std::vector<G*>& outVectorG)
{
#pragma region Name
	const char* nameA = GetRawName<A>();
	const char* nameB = GetRawName<B>();
	const char* nameC = GetRawName<C>();
	const char* nameD = GetRawName<D>();
	const char* nameE = GetRawName<E>();
	const char* nameF = GetRawName<F>();
	const char* nameG = GetRawName<G>();
#pragma endregion

	for (auto entity : entities)
	{
		if (entity.HasType(componentsNameCode.at(nameA)) &&
			entity.HasType(componentsNameCode.at(nameB)) &&
			entity.HasType(componentsNameCode.at(nameC)) &&
			entity.HasType(componentsNameCode.at(nameD)) &&
			entity.HasType(componentsNameCode.at(nameE)) &&
			entity.HasType(componentsNameCode.at(nameF)) &&
			entity.HasType(componentsNameCode.at(nameG)))
		{
#pragma region Index
			int indexA = entity.GetIndexByType(componentsNameCode.at(nameA));
			int indexB = entity.GetIndexByType(componentsNameCode.at(nameB));
			int indexC = entity.GetIndexByType(componentsNameCode.at(nameC));
			int indexD = entity.GetIndexByType(componentsNameCode.at(nameD));
			int indexE = entity.GetIndexByType(componentsNameCode.at(nameE));
			int indexF = entity.GetIndexByType(componentsNameCode.at(nameF));
			int indexG = entity.GetIndexByType(componentsNameCode.at(nameG));
#pragma endregion

#pragma region DataNuber
			int dataTypeAsNuberA = GetLogicIndexFromName(GetName<A>());
			int dataTypeAsNuberB = GetLogicIndexFromName(GetName<B>());
			int dataTypeAsNuberC = GetLogicIndexFromName(GetName<C>());
			int dataTypeAsNuberD = GetLogicIndexFromName(GetName<D>());
			int dataTypeAsNuberE = GetLogicIndexFromName(GetName<E>());
			int dataTypeAsNuberF = GetLogicIndexFromName(GetName<F>());
			int dataTypeAsNuberG = GetLogicIndexFromName(GetName<G>());
#pragma endregion

#pragma region Datas
			auto selectedA = vectorOfDatasOfDatas.at(dataTypeAsNuberA);
			auto selectedB = vectorOfDatasOfDatas.at(dataTypeAsNuberB);
			auto selectedC = vectorOfDatasOfDatas.at(dataTypeAsNuberC);
			auto selectedD = vectorOfDatasOfDatas.at(dataTypeAsNuberC);
			auto selectedE = vectorOfDatasOfDatas.at(dataTypeAsNuberE);
			auto selectedF = vectorOfDatasOfDatas.at(dataTypeAsNuberF);
			auto selectedG = vectorOfDatasOfDatas.at(dataTypeAsNuberG);
#pragma endregion

#pragma region fill vector

			A* datIndexA = (A*)((selectedA->data() + ((indexA - 1) * sizeof(A))));
			outVectorA.emplace_back(datIndexA);

			B* datIndexB = (B*)((selectedB->data() + ((indexB - 1) * sizeof(B))));
			outVectorB.emplace_back(datIndexB);

			C* datIndexC = (C*)((selectedC->data() + ((indexC - 1) * sizeof(C))));
			outVectorC.emplace_back(datIndexC);

			D* datIndexD = (D*)((selectedD->data() + ((indexD - 1) * sizeof(D))));
			outVectorD.emplace_back(datIndexD);

			E* datIndexE = (E*)((selectedE->data() + ((indexE - 1) * sizeof(E))));
			outVectorE.emplace_back(datIndexE);

			F* datIndexF = (F*)((selectedF->data() + ((indexF - 1) * sizeof(F))));
			outVectorF.emplace_back(datIndexF);

			G* datIndexG = (G*)((selectedG->data() + ((indexG - 1) * sizeof(G))));
			outVectorG.emplace_back(datIndexG);
#pragma endregion

		}
	}
}





