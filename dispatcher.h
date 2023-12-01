/* 
 * dispatcher.h
 * ************************
 * An Elevator dispatcher with the following functionalities:
 *   - maintain a pool of Elevators (3 by default)
 *   - maintain a queue of ElevatorCall requests
 *   - dispatch calls to an elevator with minimal travel time (waiting + door open + car travel)
 *  
 * @Usage:
 * 	See test_dispatch.cpp for sample
 * @author Henry Gai
 *************************/
#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <deque>
#include <vector>

#include "elevator.h"
#include "elevatorcall.h"

struct Stats
{
        int totalWait;
        int totalInside;
        int minWait;
        int maxWait;
};

class Dispatcher
{
	public:
		//Disable clients to create object
		Dispatcher(Dispatcher &other) = delete;
		void operator=(const Dispatcher &) = delete;
		//Clients use this to get a handle
		static Dispatcher* getInstance();
		static void deleteInstance();
		static void run();
		static void stop();
		bool processCalls(std::vector<ElevatorCall> &calls);
		Stats getStats();
	private:
		Dispatcher();
		~Dispatcher();
		static std::deque<ElevatorCall> *m_queue;
		static std::vector<Elevator> *m_elevators;
		static Dispatcher *g_instance;
		static bool stopFlag;
		//
		static void dispatchCalls();
		static void assignElevator(ElevatorCall &call);

};
#endif
