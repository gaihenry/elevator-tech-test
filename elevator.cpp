/*
 * elevator.cpp
 * ************************
 * @author Henry Gai
 *************************/
#include "elevator.h"

Elevator::Elevator(int maxCapacity, std::string name) : 
	maxCapacity (maxCapacity),
	floor (1),
	num (0),
	name (name)
{
}
//////////
Elevator::~Elevator()
{
}

/////////
bool Elevator::parse()
{
	return true;
}
