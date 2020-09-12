// Author: Arda Basaran, Nicholas Biffis, Oliver Cho
// Date: 16 December 2017
// File description: This is the header file for the StopLight class

#ifndef __simulation_h__
#define __simulation_h__

#include <vector>
#include "Vehicle.h"
#include "CrossRoad.h"
#include "Statistics.h"
#include "StopLight.h"
#include "Random.h"


using namespace std;

/*
* This class is responsible for handling all the other classes, updates and spawns.
* Using the CrossRoad, Vehicle and StopLight class instances, this class simulates 
* the traffic and collects statistics with an instance of Statistics class.
*/
class Simulation
{
	private:
		// probability of vehicles making a left or right turn.
		double probLeft;
	    double probRight;

		// time for each color on the stoplight before changing to next color
	    int greenTicks;
		int yellowTicks;
		int redTicks;

	    // probability of a spawned vehicle being car, suv or truck
	    double carProb;
		double suvProb;

		// number of vehicles tried to spawn at every tick
		int spawnNum;

		// probability of a spawned vehicle being on the east/west/north/south lane
		double probLaneEast;
		double probLaneWest;
		double probLaneNorth;

		// length of each lane
		int laneLength;

		// indicates whether the simulation will print out to standard output
		int printSim;

		

		// two lights for north-south bounds and west-east bounds
		StopLight nsLight;
		StopLight weLight;

		// cross road implements lanes
		CrossRoad crossRoad;

		// vector storing the vehicles
		vector<Vehicle> vehicles;

		// to collect statistics
		Statistics stats;

		
		
	public:
		/*
		* Default constructor of the class
		*/
		Simulation();

		/*
		* Custom constructor that initializes a simulation with given parameters.
		*
		* @param
		*	probLeft Probability of each vehicle making a left turn
		*	probRight Probability of each vehicle making a right turn
		*	greenTicks Number of ticks for stoplights to be green
		*	yellowTicks Number of ticks for stoplights to be yellow
		*	redTicks Number of ticks for stoplights to be red
		*	carProb Probability of each vehicle spawned being a car
		*	suvProb Probability of each vehicle spawned being a SUV
		*	spawnNum Number of vehicles that the simulation will try to spawn at each tick
		*	probLaneEast Probability of each spawned vehicle being on the east bound.
		*	probLaneWest Probability of each spawned vehicle being on the west bound.
		*	probLaneNorth Probability of each spawned vehicle being on the west bound.
		*	laneLength Length of each lane.
		*	printSim Integer value indicating whether to print the simulation.
		*/
		Simulation(double probLeft, double probRight, int greenTicks, int yellowTicks, int redTicks,
					double carProb, double suvProb, int spawnNum, 
					double probLaneEast, double probLaneWest, double probLaneNorth,
					int laneLength, int printSim);

		/*
		* Destructor of the class.
		*/
		~Simulation();

		/*
		* This method updates the simulation using the given time. It updates
		* stoplights, vehicles and lanes according to the current state the simulation
		* is in.
		*
		* @param
		*	t Integer value indicating the current time. 
		*/
		void update(int t);

		/*
		* This method tries to spawn a new vehicle to the simulation.
		* 
		* @param
		*	t Integer value indicating curren time
		*/
		void spawnVehicle(int t);

		/*
		* This method prints statistics collected by the simulation to the standard
		* output.
		*/
		void printStats();


		/*
		* This method prints the simulation to standard output.
		*
		* @param
		* 	t Integer value indicating the current time
		*/
		void printSimulation(int t);

};

#endif