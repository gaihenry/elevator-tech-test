/* 
 * elevatorcall.h
 * ************************
 * An Elevator call request with the following properties:
 *   - current floor
 *   - destination floor
 *   - number of passengers together
 * Only one public interface:
 *  
 * @Usage:
 * 	.
 * @author Henry Gai
 *************************/
#ifndef ELEVATORCALL_H
#define ELEVATORCALL_H

#include <list>

class ElevatorCall
{
	public:
		ElevatorCall(int floor, int dest, int num);
		~ElevatorCall();
		int floor;//current calling floor
		int dest; //destination floor
		int num; //number of passengers together
		int waiting;//waiting time for pickup
	private:
};
#endif
