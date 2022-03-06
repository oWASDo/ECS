// ECS.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include <iostream>
#include <vector>
#include <time.h>
#include "Heder/ECS_Context.h"
#include "Heder/Component.h"

class ClassTest
{
public:
	ClassTest();
	~ClassTest();
	void Adding() {
		inttt += 5;


	}

private:
	int inttt;
};

ClassTest::ClassTest()
{
	inttt = 5;
}

ClassTest::~ClassTest()
{
}




using namespace std;

int main() {

	size_t entttSNumber = 5;

	//Create ECS context
	ECS_Context* context = new ECS_Context();


	for (int i = 0; i < entttSNumber; i++)
	{
		//Create entity
		context->CreateAndAddEntity();

		//Link component to entity
		context->AddComponentToEntity<Integer>(context->GetEntity(i), Integer(0));
		if (i % 2)
		{
			context->AddComponentToEntity<Boolean>(context->GetEntity(i), Boolean());

		}
	}

	context->RemoveComponentToEntity<Integer>(context->GetEntity(3));
	context->AddComponentToEntity<Integer>(context->GetEntity(3), Integer(0));


	{
		std::vector< Integer*> ii;

		context->GetTypes<Integer>(ii);

		//___________________________________________________________
		clock_t begin_time = clock();

		for (size_t j = 0; j < ii.size(); j++)
		{
			ii[j]->integer += 5;

		}
		std::cout << "ecs time " << clock() - begin_time << std::endl;
		std::cout << "ecs time " << float(clock() - begin_time) << std::endl;
		ii.clear();
		ii.shrink_to_fit();
		//___________________________________________________________

		std::list<ClassTest*> v;
		for (size_t i = 0; i < entttSNumber; i++)
		{
			v.emplace(v.end(), new ClassTest());
		}
		clock_t begin_time0 = clock();
		for (auto vEl : v)
		{
			vEl->Adding();
		}
		std::cout << "class time " << clock() - begin_time << std::endl;
		std::cout << "class time " << float(clock() - begin_time0) << std::endl;;
		//___________________________________________________________
		for (auto vEl : v)
		{
			delete vEl;
		}
		v.clear();

		delete context;

	}
}