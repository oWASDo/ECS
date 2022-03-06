#pragma once

#include <iostream>
#include <exception>

class IsNotAStruct : public std::exception
{
	const char* what() const throw ()
	{
		return "T type is not a struct";

	}
};

class ComponentAlreadyExist : public std::exception
{
	/*
public:
	ComponentAlreadyExist(std::string name)
	{
		nameAsString = name;
	}
	std::string nameAsString;*/

	const char* what() const throw ()
	{
		return "This entity already has this component";

		/*std::string message = std::string("This entity already has this component ->");
		message.append(nameAsString);
		return message.c_str();*/
	}
};