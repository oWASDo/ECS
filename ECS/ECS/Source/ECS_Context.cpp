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


std::shared_ptr<Entity> ECS_Context::AddEntity() {

	std::shared_ptr<Entity> sharedPointer = std::make_shared<Entity>();
	entities.push_back(sharedPointer);
	return sharedPointer;
}


Indexes ECS_Context::GetIdexes(const std::string nameAsString, Entity* entity) {
	size_t index = 0;
	size_t indexXX = 0;
	int indexType = typeMaps[nameAsString];
	int arrayPosition = entity->GetIndexByType(indexType) - 1;

	for (std::string orderedName : typrOrder) {
		size_t size = typeSizes[orderedName];
		size_t numofElements =
			typeNumberElement[orderedName] +
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
	return Indexes(index, indexXX);
}

bool ECS_Context::GetFalseInAtype(const std::string nameAsString, int& index) {
	size_t start = 0;
	size_t end = 0;
	int indexType = typeMaps[nameAsString];

	for (std::string orderedName : typrOrder) {

		//size_t size = typeSizes[orderedName];
		size_t numOfElement = typeNumberElement[orderedName];
		end += numOfElement;

		/*size_t numofElements =
			typeNumberElement[orderedName] +
			(orderedName == nameAsString ? -1 : 0);

		index += size * numofElements;*/

		if (orderedName == nameAsString)
		{

			break;
		}
		start += numOfElement;

	}

	if (actives.size() != 0 || actives.size() != 0)
	{

		auto f = actives.begin() + start;
		auto l = actives.begin() + end;
		//std::vector<bool> vecs(f, l);
		//std::vector<bool> vecs(&actives[start], &actives[end]);
		std::vector<bool> vecs = { f,l };
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


	//actives.

	return false;
}



