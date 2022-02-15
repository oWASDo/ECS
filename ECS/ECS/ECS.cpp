// ECS.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <vector>
#include "Heder/ECS_Context.h"
#include "Heder/Component.h"

//using namespace std;

int main()
{
	size_t entttSNumber = 5000;

	ECS_Context* context = new ECS_Context();



	//content->func<Integet, Integet, Boolean>(1, 1 /*Integet*/, 5/*Boolean*/);
	//content->GetTypes<Integet, Integet, Boolean>();


	for (size_t i = 0; i < entttSNumber; i++)
	{
		std::shared_ptr<Entity> ent = context->AddEntity();

		context->AddComponentToEntity<Integet>(ent.get(), Integet());
		context->AddComponentToEntity<Boolean>(ent.get(), Boolean());
		//context->AddComponentToEntity(ent.get());
	}

	delete context;



}