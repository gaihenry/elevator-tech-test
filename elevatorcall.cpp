/*
 * elevatorcall.cpp
 * ************************
 * @author Henry Gai
 *************************/
#include "elevatorcall.h"


ElevatorCall::ElevatorCall(int current, int dest, int num) : 
	floor(current),
	dest(dest),
	num(num),
	waiting(0)
{
}
//////////
ElevatorCall::~ElevatorCall()
{
}

/////////
bool ElevatorCall::parse()
{
	return true;
}
