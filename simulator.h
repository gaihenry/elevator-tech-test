/* 
 * simulator.h
 * ************************
 * An Elevator call request simulator with a time series:
 *   - uniform distribution of calls and frequency
 *   - lognormal dist. of number of passengers per call, [0, 5]
 * @Usage:
 * 	vector<ElevatorCall> calls;
 * 	Simulator::generateCalls(calls);
 * @author Henry Gai
 *************************/
#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>

#include "elevatorcall.h"

class Simulator
{
	public:
		//n - number of calls to generate
		static void generateCalls(std::vector<ElevatorCall> &calls, int n);
	private:
		Simulator();
		~Simulator();
		//For calling floor and frequency of calls, [1, 100] for floors
		static int uniform_dist(const unsigned int seed, int min, int max);
		//For number of passengers per call, [0, 5]
		static int lognormal_dist(double m, double s);

};
#endif
