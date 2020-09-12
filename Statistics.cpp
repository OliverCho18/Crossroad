// Author: Arda Basaran, Nicholas Biffis, Oliver Cho
// Date: 16 December 2017
// File description: This is the class file for the Statistics class

#include "Statistics.h"
#include <iostream>


using namespace std;


/*
* Default constructor
*/
Statistics::Statistics()
{
	carSpawned = 0;
	truckSpawned = 0;
	suvSpawned = 0;
	vehicleNotSpawned = 0;
	carGone = 0;
	truckGone = 0;
	suvGone = 0;
	carLifeSpan = 0;
	suvLifeSpan = 0;
	truckLifeSpan = 0;
	carIntersectionWait = 0;
	suvIntersectionWait = 0;
	truckIntersectionWait = 0;
	carCrossRoadWait = 0;
	suvCrossRoadWait = 0;
	truckCrossRoadWait = 0;
}

/*
* Destructor of the class
*/
Statistics::~Statistics() {}

/*
* Given the current time and a vehicle, this method collects its stats.
*
* @param
* 	vehicle A vehicle whose stats will be collected
*	t Current integer time
*/
void Statistics::recordStats(Vehicle vehicle, int t)
{
	if(vehicle.getType() == "car")
	{
		carIntersectionWait = (vehicle.getWaitIntersection()+(carGone*carIntersectionWait))/(carGone+1);
		carCrossRoadWait = (vehicle.getWaitCrossRoad()+(carGone*carCrossRoadWait))/(carGone+1);
		carLifeSpan =  ((t - vehicle.getSpawnTime())+(carGone*carLifeSpan))/(carGone+1);
		carGone += 1;
	}

	else if(vehicle.getType() == "suv")
	{
		suvIntersectionWait = (vehicle.getWaitIntersection()+(suvGone*suvIntersectionWait))/(suvGone+1);
		suvCrossRoadWait = (vehicle.getWaitCrossRoad()+(suvGone*suvCrossRoadWait))/(suvGone+1);
		suvLifeSpan =  ((t - vehicle.getSpawnTime())+(suvGone*suvLifeSpan))/(suvGone+1);
		suvGone += 1;
		
	}

	else
	{
		truckIntersectionWait = (vehicle.getWaitIntersection()+(truckGone*truckIntersectionWait))/(truckGone+1);
		truckCrossRoadWait = (vehicle.getWaitCrossRoad()+(truckGone*truckCrossRoadWait))/(truckGone+1);
		truckLifeSpan =  ((t - vehicle.getSpawnTime())+(truckGone*truckLifeSpan))/(truckGone+1);
		truckGone += 1;
	}
}


/*
* This method stores the collected statistics to the given array.
* 
* @param
*	arr A double array which will store the statistics
* @return
*	A double array that stores the statistics
*/
double* Statistics::getStats(double *arr)
{
	
	arr[0] = carSpawned;
	arr[1] = truckSpawned;
	arr[2] = suvSpawned;

	arr[3] = carGone;
	arr[4] = truckGone;
	arr[5] = suvGone;

	arr[6] = carLifeSpan;
	arr[7] = suvLifeSpan;
	arr[8] = truckLifeSpan;


	arr[9]  = carIntersectionWait;
	arr[10] = suvIntersectionWait;
	arr[11] = truckIntersectionWait;

	arr[12] = carCrossRoadWait;
	arr[13] = suvCrossRoadWait;
	arr[14] = truckCrossRoadWait;

	arr[15] = vehicleNotSpawned;


	return arr;
}

/*
* This method increases the number of spawned cars.
*/
void Statistics::addCarSpawned()
{
	carSpawned += 1;
}

/*
* This method increases the number of spawned trucks.
*/
void Statistics::addSUVSpawned()
{
	suvSpawned += 1;
}

/*
* This method increases the number of spawned SUVs.
*/
void Statistics::addTruckSpawned()
{
	truckSpawned += 1;
}

/*
* This method increases the number of vehicles that are not spawned.
*/
void Statistics::addVehicleNotSpawned()
{
	vehicleNotSpawned += 1;
}
