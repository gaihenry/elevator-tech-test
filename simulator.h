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
		static void generateCalls(std::vector<ElevatorCall> &calls);
	private:
		Simulator();
		~Simulator();

};
#endif
