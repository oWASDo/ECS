// ECS.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <vector>
#include "Heder/ECS_Context.h"
#include "Heder/Component.h"

using namespace std;

int main()
{
	size_t entttSNumber = 5000;

	//Create ECS context
	ECS_Context* context = new ECS_Context();




	Entity* entf = nullptr;

	for (size_t i = 0; i < entttSNumber; i++)
	{
		//Create entity
		Entity* ent = context->CreateAndAddEntity();

		//Link component to entity
		context->AddComponentToEntity<Integet>(ent, Integet());
		context->AddComponentToEntity<Boolean>(ent, Boolean());

		if (i == 1)
		{
			entf = ent;

		}
	}

	//Remove liked component to entity
	context->RemoveComponentToEntity<Integet>(entf);

	//Link new component to entity
	context->AddComponentToEntity<Integet>(entf, Integet(454));

	//Delete context
	delete context;
}