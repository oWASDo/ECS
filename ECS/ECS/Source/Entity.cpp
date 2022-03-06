#include "../Heder/Entity.h"
#include <algorithm>

Entity::Entity()
{

	for (size_t i = 0; i < MaxComponentPeEntyty; i++)
	{
		free_[i] = false;
		
	}
	for (size_t i = 0; i < MaxComponentPeEntyty; i++)
	{
		type_[i] = -100;
	}
	for (size_t i = 0; i < MaxComponentPeEntyty; i++)
	{
		typeIndex_[i] = -100;
	}
}

 Entity::~Entity()
{

}


void Entity::AddType(int type, int index) {

	if (!HasType(type))
	{
		for (size_t i = 0; i < MaxComponentPeEntyty; i++)
		{
			if (free_[i] == false)
			{
				type_[i] = type;
				typeIndex_[i] = index;
				free_[i] = true;
				return;
			}
		}
		//types.push_back(type);
		//typesIndex.push_back(index);

	}
}
void Entity::RemoveType(int type) {
	if (HasType(type))
	{
		for (size_t i = 0; i < MaxComponentPeEntyty; i++)
		{
			if (free_[i] == true && type_[i] == type)
			{
				type_[i] = -100;
				typeIndex_[i] = -100;
				free_[i] = false;
				return;
			}
		}
	}

}

bool Entity::HasType(int type) {
	/*if (types.empty())
	{
		return false;
	}*/

	for (size_t i = 0; i < MaxComponentPeEntyty; i++)
	{
		if (free_[i] == true && type_[i] == type) {
			return true;
		}
	}
	return false;

	/*return	any_of(types.begin(), types.end(),
		[&type](int x) {return x == type; });*/

}
//
//int Entity::GetIndexByType(int type) {
//	int index = 0;
//
//	for (const int i : types) {
//		if (i == type)
//		{
//			return typesIndex[index];
//		}
//		index++;
//	}
//	return -1;
//}

int Entity::GetIndexByType(int type) {
	int index = 0;

	for (const int i : type_) {
		if (i == type)
		{
			return typeIndex_[index];
		}
		index++;
	}
	return -1;
}
