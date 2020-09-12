// Author: Arda Basaran, Nicholas Biffis, Oliver Cho
// Date: 16 December 2017
// File description: This is the header file for the Statistics class

#ifndef __statistics_h__
#define __statistics_h__

#include "Vehicle.h"

/*
* This class implements a container for the different statistics which will be collected
* during the simulation.
*/
class Statistics{
	private:
		double carSpawned;
		double truckSpawned;
		double suvSpawned;

		double vehicleNotSpawned;

		// number of vehicles that got erased from the simulation
		double carGone;
		double truckGone;
		double suvGone;

		// average time a vehicle spends in the simulation before
		// getting erased
		double carLifeSpan;
		double suvLifeSpan;
		double truckLifeSpan;

		// average time a vehicle waits to enter the intersection
		double carIntersectionWait;
		double suvIntersectionWait;
		double truckIntersectionWait;


		// average time a vehicle waits at anywhere else
		double carCrossRoadWait;
		double suvCrossRoadWait;
		double truckCrossRoadWait;

	public:
		/*
		* Default constructor
		*/
		Statistics();

		/*
		* Destructor of the class
		*/
		~Statistics();

		/*
		* Given the current time and a vehicle, this method collects its stats.
		*
		* @param
		* 	vehicle A vehicle whose stats will be collected
		*	t Current integer time
		*/
		void recordStats(Vehicle vehicle, int t);

		/*
		* This method stores the collected statistics to the given array.
		* 
		* @param
		*	arr A double array which will store the statistics
		* @return
		*	A double array that stores the statistics
		*/
		double* getStats(double* arr);

		/*
		* This method increases the number of spawned cars.
		*/
		void addCarSpawned();

		/*
		* This method increases the number of spawned trucks.
		*/
		void addTruckSpawned();

		/*
		* This method increases the number of spawned SUVs.
		*/
		void addSUVSpawned();

		/*
		* This method increases the number of vehicles that are not spawned.
		*/
		void addVehicleNotSpawned();
};

#endif