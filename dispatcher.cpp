/*
 * elevator.cpp
 * ************************
 * @author Henry Gai
 *************************/
#include <iostream>
#include <string>
#include <algorithm>
#include <mutex>
#include <thread>
#include <chrono>
//
#include "dispatcher.h"
#define NUM_CARS 3
//stats
int g_TotalWait = 0;
int g_TotalInside = 0;
int g_MinWait = INT_MAX;
int g_MaxWait = 0;
//
//Singleton instance
Dispatcher* Dispatcher::g_instance = nullptr;
std::vector<Elevator>* Dispatcher::m_elevators = nullptr;
std::deque<ElevatorCall>* Dispatcher::m_queue = nullptr;
std::mutex m_mutex;
bool Dispatcher::stopFlag = false;
////////////////////////////////////////////////////////
Dispatcher::Dispatcher() 
{
}
//
Dispatcher::~Dispatcher()
{
}
////////////////////////////////////////////////////////
Dispatcher* Dispatcher::getInstance()
{
	if (m_elevators == nullptr) {
		m_elevators = new std::vector<Elevator>(NUM_CARS, Elevator());
		for (int i = 0; i < m_elevators->size(); i++) {
			(*m_elevators)[i].name = "ELEVATOR" + std::to_string(i);
		}
	}
	if (m_queue == nullptr) {
		m_queue = new std::deque<ElevatorCall>();
	}
	if (g_instance == nullptr) {
		g_instance = new Dispatcher();
	}
	return g_instance;
}
//
void Dispatcher::deleteInstance()
{
	if (m_elevators != nullptr) {
		m_elevators->clear();
		delete m_elevators;
		m_elevators = nullptr;
	}
	if (m_queue != nullptr) {
		m_queue->clear();
		delete m_queue;
		m_queue = nullptr;
	}
	if (g_instance != nullptr) {
		delete g_instance;
		g_instance = nullptr;
	}
}
//////////////////////////////////////////////////
void Dispatcher::run()
{
	while (!stopFlag) {
		while (m_queue->empty()) {
			std::cout << "\nSleeping for 1 second...\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		//Keep calling it as long as there are calls
		dispatchCalls();
		std::cout << "\nInside run with queue size = " << m_queue->size();
	}
}
void Dispatcher::stop()
{ 
	stopFlag = true;
}
//Move one floor at a time. The Dispatching thread keeps calling it if non-empty queue.
//This allows the newly call requests added to the queue.
void Dispatcher::dispatchCalls()
{
	std::lock_guard<std::mutex> guard(m_mutex);
	for (auto &elevator : *m_elevators) {
		//std::lock_guard<std::mutex> guard(m_mutex);
		std::cout << "\nElevator " << elevator.name << " and dst = " <<elevator.destinations.size();
		if (!elevator.destinations.empty()) {
			std::cout << "\nElevator " << elevator.name << " is NOT idle";
			if (elevator.floor < elevator.destinations[0].floor) {
				//Move up one floor at a time
				elevator.floor++;
			}
			else if (elevator.floor > elevator.destinations[0].floor) {
				//Move down one floor
				elevator.floor--;
			}
			else {
				//We are here so remove the first dest call from this queue
				//@TODO what about multiple calls have the same dest?
				//@TODO Collect stats
				ElevatorCall data = elevator.destinations[0];
				g_TotalWait += data.waiting;
				g_TotalInside += std::abs(data.floor - data.dest);
				if (data.waiting < g_MinWait) {
					g_MinWait = data.waiting;
				}
				if (data.waiting > g_MaxWait) {
					g_MaxWait = data.waiting;
				}
				
				int num = data.num;
                		elevator.destinations.erase(elevator.destinations.begin());

                		//Update number of passengers for this elevator
                		elevator.num = std::max(0, elevator.num - num);
			}
		}
		else if (!m_queue->empty()) {
			std::cout << "\nChecking queue with size = " << m_queue->size() << std::endl;
			ElevatorCall call = m_queue->front();
			m_queue->pop_front();
			assignElevator(call);		
		}
	}
}
//
void Dispatcher::assignElevator(ElevatorCall &call)
{
	//Find the elevator taking shortest time for this call request
	int min = INT_MAX;
    	int index = 0;
	int first_not_full = -1;

    	for (int i = 0; i < m_elevators->size(); ++i) {
		Elevator &tmp = (*m_elevators)[i];
		int pickup = std::abs(tmp.floor - call.floor) * FLOOR_TIME;
		int total = pickup + (call.floor == 1) ? LOBBY_DOOR : DOOR_TIME;
        	if (total < min) {
            		min = total;
            		index = i;
        	}
		if (first_not_full < 0 && !tmp.isFull(call.num)) {
			first_not_full = i;
		}
    	}
	//Waiting time
	call.waiting = min;
	auto &dst = (*m_elevators)[index];
	if (!dst.isFull(call.num)) {
		dst.destinations.push_back(call);
		std::sort(dst.destinations.begin(), dst.destinations.end(),
              		[](const ElevatorCall& a, const ElevatorCall& b) {
                  	return a.floor < b.floor;
              });
	} else {
		//select any one that is not full
		if (first_not_full >= 0) {
			auto &dst2 = (*m_elevators)[first_not_full];
			dst2.destinations.push_back(call);
			std::sort(dst2.destinations.begin(), dst2.destinations.end(),
              			[](const ElevatorCall& a, const ElevatorCall& b) {
                  		return a.floor < b.floor;
				});
		}
	}

}
///////////////////////////////////////////////////////////////
bool Dispatcher::processCalls(std::vector<ElevatorCall> &calls)
{
	std::cout << "\nAdding calls to the queue\n";
	std::lock_guard<std::mutex> guard(m_mutex);
	for (auto &call : calls)
	{
		if (m_queue != nullptr) {
			m_queue->push_back(call);
		}
		//stats
		//g_TotalPassengers += call.num;
	}
	return true;
}
//////////////////////////////////////////////////////////////
Stats Dispatcher::getStats()
{
	return Stats(g_TotalWait, g_TotalInside, g_MinWait, g_MaxWait);
}
