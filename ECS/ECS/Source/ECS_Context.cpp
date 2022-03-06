#include "../Heder/ECS_Context.h"

ECS_Context::ECS_Context()
{
}

ECS_Context::~ECS_Context()
{
	entities.clear();
	for (auto data : vectorOfDatasOfDatas) {
		data->clear();
		data->shrink_to_fit();
		delete data;

	}
	for (auto actives : vectorOfActivesOfActives) {
		actives->clear();
		actives->shrink_to_fit();
		delete actives;
	}
	vectorOfDatasOfDatas.clear();
	vectorOfDatasOfDatas.shrink_to_fit();

	vectorOfActivesOfActives.clear();
	vectorOfActivesOfActives.shrink_to_fit();

	typeOrder.clear();
	typeOrder.shrink_to_fit();

	componentsNameCode.clear();
	componentsSize.clear();
	nuberOfElementPerComponentType.clear();

}


int ECS_Context::CreateAndAddEntity() {

	entities.emplace(entities.end(), Entity());

	return 0;
}


bool ECS_Context::NameCodeContainsKey(std::string stringToCheck)
{

	return !NotExistKeyInMap(componentsNameCode, stringToCheck);
}

size_t ECS_Context::NameCodeGetCode(std::string stringToCheck)
{
	if (NameCodeContainsKey(stringToCheck))
	{
		//return nameCode[stringToCheck];
		return componentsNameCode.at(stringToCheck);
	}
	return 10000000000;
}

int ECS_Context::GetLogicIndexFromName(std::string nameAsString)
{
	int dataTypeAsNuber = 0;
	for (auto t : typeOrder)
	{
		if (t == nameAsString)
		{
			break;
		}
		dataTypeAsNuber++;
	}
	return dataTypeAsNuber;

}



