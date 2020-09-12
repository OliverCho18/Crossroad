// Author: Arda Basaran, Nicholas Biffis, Oliver Cho
// Date: 16 December 2017
// File description: This is the header file for the Vehicle

#ifndef __vehicle_h__
#define __vehicle_h__

#include "Section.h"
#include <string>

using namespace std;

/*
* This class implements vehicles that will be used in the simulation. Vehicles have attributes
* that determine their type, length, direction, turn. They store their location on the
* crossroad as an array of Section instances (see Section and CrossRoad classes). They also
* store some statistics for the simulation.
*/
class Vehicle {
	
	private:
		// length is 2 for cars, 3 for SUVs, and 4 for trucks
		int length;

		//indicates the direction the vehicle is going
		// 1: to north
		// 2: to west
		// 3: to east
		// 4: to south
		int direction;

		// indicates the turn the vehicle will do
		// can be "straight", "left", "right"
		string turn;

		// indicates the type of the vehicle
		// can be "car", "suv", "truck"
		string type;

		// stores the location of the vehicle
		// although the array has size 5, at most 4 is used (for trucks)
		Section* tiles[5];

		// statistics of the vehicle
		double spawnTime;
		double waitIntersection;
		double waitCrossRoad;

		// the lane the car was spawned at
		// 1: northbound
		// 2: westbound
		// 3: eastbound
		// 4: southbound
		int spawnLane;


	public:
		/*
		* Default constructor.
		*/
		Vehicle();

		/*
		* Custom constructor which creates a vehicle with a given type, direction, location,
		* and turn.
		*
		* @param t
		* 	t String that indicates vehicle type
		*	dir Integer value indicating the vehicle's direction
		*	laneFirst Section address indicating the vehicles first location
		*	sLane Integer value indicating the starting lane for the vehicle
		*	turnDir String that indicates turn of the vehicle
		*	time Integer value indicating current time
		*/
		Vehicle(string t, int dir, Section* laneFirst, int sLane, string turnDir, int time);

		/*
		* Destructor for the class
		*/
		~Vehicle();

		/*
		* Accessor method for the type of the vehicle
		*
		* @return
		*	Type of the vehicle
		*/
		string getType();

		/*
		* Accessfor method for the direction of the vehicle
		*
		* @return
		*	Direction of the vehicle
		*/
		int getDirection();

		/*
		* Accessor method for the location indicating head of the vehicle
		*
		* @return
		*	Section that the head of the vehicle is at
		*/
		Section* getLocation();

		/*
		* Accessor method for the length of the vehicle
		*
		* @return
		*	Length of the vehicle
		*/
		int getLength();

		/*
		* Accessor method for the turn of the vehicle
		*
		* @return
		*	Turn of the vehicle
		*/
		string getTurn();

		/*
		* This method updates the vehicle to move one unit in the direction and turn it has.
		* (Assume the vehicle can move)
		*/
		void update();

		/*
		* This method checks whether the vehicle has made to the end of the cross road.
		*
		* @return
		*	Boolean value indicating whether the vehicle has made to the end of the cross road.
		*/
		bool isGone();

		/*
		* Accessor method for the lane of the vehicle
		*
		* @return
		*	Lane of the vehicle
		*/
		int getSpawnLane();


		/*
		* Accessor method for the spawn time of the vehicle
		*
		* @return
		*	Spawn time of the vehicle
		*/
		double getSpawnTime();

		/*
		* Accessor method for the total time the vehicle waits to enter the intersection.
		*
		* @return
		*	Total time the vehicle waits to enter the intersection.
		*/
		double getWaitIntersection();


		/*
		* This method increases the time the vehicle waits to enter the intersection.
		*/
		void addWaitIntersection();

		/*
		* Accessor method for the total time the vehicle waits except when it
		* waits to enter the intersection.
		*
		* @return
		*	Total time the vehicle waits except when it waits to enter the intersection.
		*/
		double getWaitCrossRoad();


		/*
		* This method increases the time the vehicle waits except when it waits to
		* enter the intersection.
		*/
		void addWaitCrossRoad();
		
};

#endif