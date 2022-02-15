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





