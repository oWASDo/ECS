#include "../Heder/ECS_Context.h"


ECS_Context::ECS_Context()
{

}

ECS_Context::~ECS_Context()
{
	entities.clear();
	typeMaps.clear();
	typeSizes.clear();
	typeNumberElement.clear();
	typrOrder.clear();
	datas.clear();
}


Entity* ECS_Context::CreateAndAddEntity() {

	//create new entity and adde to the Entities vector
	entities.push_back(Entity());
	std::vector <Entity>::iterator it = entities.begin();
	Entity* p = &(*it);
	return p;
}


Indicies ECS_Context::GetIdexes(const std::string nameAsString, Entity* entity) {
	size_t index = 0;
	size_t indexXX = 0;
	int indexType = typeMaps[nameAsString];
	int arrayPosition = entity->GetIndexByType(indexType) - 1;

	for (std::string orderedName : typrOrder) {
		size_t size = typeSizes[orderedName];
		int numofElements = typeNumberElement[orderedName] +
			(orderedName == nameAsString ? -1 : 0);

		size_t numOfElements2 =
			typeNumberElement[orderedName];

		index += size * numofElements;
		if (orderedName == nameAsString)
		{
			indexXX += arrayPosition;
			break;
		}
		indexXX += numOfElements2;
	}
	return Indicies(index, indexXX);
}

bool ECS_Context::GetFalseInAtype(const std::string nameAsString, int& index) {
	size_t start = 0;
	size_t end = 0;
	int indexType = typeMaps[nameAsString];

	for (std::string orderedName : typrOrder) {

		size_t numOfElement = typeNumberElement[orderedName];
		end += numOfElement;

		if (orderedName == nameAsString)
		{

			break;
		}
		start += numOfElement;
	}

	if (actives.size() != 0/* || actives.size() != 0*/)
	{
		auto f = actives.begin() + start;
		auto l = actives.begin() + end;
		std::vector<bool> vecs = { f, l };
		bool a = std::find(std::begin(vecs), std::end(vecs), true) == std::end(vecs);
		int ind = 0;
		for (bool b : vecs) {
			if (!b)
			{
				index = ind + start;
				return true;
			}
			ind++;
		}
	}

	return false;
}



