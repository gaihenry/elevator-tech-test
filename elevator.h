/* 
 * elevator.h
 * ************************
 * An Elevator with properties:
 *   - max capacity
 *   - current number of passengers loaded
 *   - current state: idle, UP, DN
 *   - current floor
 *   - current destinations
 *   - actions: DROP, PICKUP
 * Only one public interface:
 *  
 * @Usage:
 * 	.
 * @author Henry Gai
 *************************/
#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <list>
#include <vector>
#include <string>
#include "elevatorcall.h"

#define LOBBY_DOOR 30
#define DOOR_TIME 5
#define FLOOR_TIME 1

class Elevator
{
	public:
		Elevator(int MaxCapacity = 10, std::string name = "Elevator");
		~Elevator();
		std::vector<ElevatorCall> destinations;
		int floor;//current floor
		int num; //current num of passengers
		std::string name;

		bool isFull(int n) { 
			return num + n > maxCapacity;
		}
	private:
		int maxCapacity;
		bool parse();
};
#endif
