/*
 * simulator.cpp
 * ************************
 * @author Henry Gai
 *************************/
#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "simulator.h"
////////////////////////////////////////////////////////
Simulator::Simulator() 
{
}
//
Simulator::~Simulator()
{
}
////////////////////////////////////////////////////////
void Simulator::generateCalls(std::vector<ElevatorCall> &calls, int n)
{
	//
	std::vector<int> floors;
	std::vector<int> dest;
	std::vector<int> numOfPassenger;
	//Except for lobby
	//Another option for the seed is std::mt19937 rng(time(NULL));
	const unsigned int seed = (unsigned int)time(0);
	for (int i = 0; i < n; i++) {
		floors.push_back(uniform_dist(seed, 2, 100));
	}
	for (int i = 0; i < n; i++) {
		dest.push_back(uniform_dist(seed, 1, 100));
	}
	for (int i = 0; i < n; i++) {
		//mean = 2.5, SD = 2.5 for x = [0, 5]
		numOfPassenger.push_back(lognormal_dist(2.5, 2.5));
	}
	//Generate calls
	for (int i = 0; i < n; i++) {
		calls.push_back({floors[i], dest[i], numOfPassenger[i]});
	}
	
}

int Simulator::uniform_dist(const unsigned int seed, int min, int max)
{
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> floor_dist(min,max);
	return floor_dist(generator);
}
int Simulator::lognormal_dist(double m, double s)
{
	//std::random_device rd;
    	//std::mt19937 generrator(rd());
	std::default_random_engine generator;
  	std::lognormal_distribution<double> log_dist(m,s);
	return std::round(log_dist(generator));
}
