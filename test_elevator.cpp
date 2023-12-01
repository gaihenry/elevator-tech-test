/*
 * A test simulator of the elevator system
 * */
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include "elevator.h"
#include "elevatorcall.h"
#include "dispatcher.h"
#include "simulator.h"

using namespace std;

int main(int argc, char *argv[]) {	
	std::cout << "\nTesting has started...\n";
	//Get the singleton instance
	Dispatcher *disp = Dispatcher::getInstance();
	
	//Start up the dispatching thread
	std::thread worker(Dispatcher::run);
	
	//Add elevator calls
	vector<ElevatorCall> calls;
	ElevatorCall call(1, 3, 2);
	calls.push_back(call);
	disp->processCalls(calls);
	int n = calls.size();
	std::this_thread::sleep_for(std::chrono::seconds(1));

	ElevatorCall call2(10, 5, 1);
	ElevatorCall call3(90, 1, 2);
	calls.push_back(call2);
	calls.push_back(call3);
	disp->processCalls(calls);
	std::this_thread::sleep_for(std::chrono::seconds(1));

	//Stats
	Stats stat = disp->getStats();
	std::cout << "\nStats for this run\n";
	std::cout << "\tAverage Time Waiting: " << stat.totalWait / n << std::endl;
	std::cout << "\tAverage Time Inside: " << stat.totalInside / n << std::endl;
	std::cout << "\tAverage Time Total: " << (stat.totalWait + stat.totalInside ) / n << std::endl;
	std::cout << "\tThe Min Time Waiting: " << stat.minWait << std::endl;
	std::cout << "\tThe MAX Time Waiting: " << stat.maxWait << std::endl;

	//Use simulator to produce calls
	vector<ElevatorCall> calls2;
	Simulator::generateCalls(calls2);
	//Join the thread
	Dispatcher::stop();
	worker.join();
	
	//Clean up
	cout << "\nCalling delete instance...\n";
	Dispatcher::deleteInstance();
	cout << "\nEND of the test\n";;

	return 0;
}

