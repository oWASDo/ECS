#include "../Heder/Entity.h"


Entity::Entity()
{
}

Entity::~Entity()
{
	types.clear();
	typesIndex.clear();
}

void Entity::AddType(int type, int index) {

	types.push_back(type);
	typesIndex.push_back(index);
}
bool Entity::HasType(int type) {

	int i = 0;
	bool result = false;
	if (std::find(types.begin(), types.end(), type) != types.end())
	{
		result = true;
	}
	return result;
}
int Entity::GetIndexByType(int type) {
	int index = 0;
	for (int i : types) {
		if (i == type)
		{
			return typesIndex[index];
		}
		index++;
	}
	return -1;
}
