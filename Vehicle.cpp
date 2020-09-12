// Author: Arda Basaran, Nicholas Biffis, Oliver Cho
// Date: 16 December 2017
// File description: This is the class file for the Vehicle class

#include "Vehicle.h"
#include "Section.h"
#include <string>
#include <iostream>

using namespace std;

/*
* Default constructor.
*/
Vehicle::Vehicle() 
{
	length = 0;
	direction = 0;
	turn = "";
	type = "";
	spawnTime = 0;
	waitIntersection = 0;
	waitCrossRoad = 0;
	spawnLane = 0;
	for(int i = 0; i < 5; i++)
		tiles[i] = NULL;
}

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
Vehicle::Vehicle(string t, int dir, Section* laneFirst, int sLane, string turnDir, int time)
{
	spawnLane = sLane;
	type = t;
	turn = turnDir;
	if(t == "car")
	{
		length = 2;
	}
	if(t == "truck")
	{
		length = 4;
	}
	else if(t == "suv")
	{
		length = 3;
	}

	direction = dir;


	tiles[0] = laneFirst;
	tiles[0]->setOccupied(true, type[0]);

	//cout << type[0] << endl;
	//cout << tiles[0]->getVehicleType() << endl;
	//cout << type << " " << tiles[0]->getVehicleType() << endl;


	for(int i = 1; i < 5; i++)
		tiles[i] = NULL;

	spawnTime = time;
	waitIntersection = 0;
	waitCrossRoad = 0;
}

/*
* Destructor for the class
*/
Vehicle::~Vehicle() {}

/*
* Accessor method for the type of the vehicle
*
* @return
*	Type of the vehicle
*/
string Vehicle::getType()
{
	return type;
}


/*
* Accessfor method for the direction of the vehicle
*
* @return
*	Direction of the vehicle
*/
int Vehicle::getDirection()
{
	return direction;
}


/*
* Accessor method for the location indicating head of the vehicle
*
* @return
*	Section that the head of the vehicle is at
*/
Section* Vehicle::getLocation()
{
	return tiles[0];
}


/*
* Accessor method for the length of the vehicle
*
* @return
*	Length of the vehicle
*/
int Vehicle::getLength()
{
	return length;
}



/*
* Accessor method for the turn of the vehicle
*
* @return
*	Turn of the vehicle
*/
string Vehicle::getTurn()
{
	return turn;
}


/*
* This method updates the vehicle to move one unit in the direction and turn it has.
* (Assume the vehicle can move)
*/
void Vehicle::update()
{
	// move from the tail to the head
	for(int i = length-1; i > 0; i--)
	{
		// set tail section to not occupied
		if(i == length-1 && tiles[i] != NULL)
			tiles[i]->setOccupied(false, 'O');

		//move the tile
		tiles[i] = tiles[i-1];

	}

	// move head
	tiles[0] = tiles[0]->getNext(direction);

	//if head is not null, occupy the next section
	if(tiles[0] != NULL)
		tiles[0]->setOccupied(true,type[0]);
}


/*
* This method checks whether the vehicle has made to the end of the cross road.
*
* @return
*	Boolean value indicating whether the vehicle has made to the end of the cross road.
*/
bool Vehicle::isGone()
{

	// if the next section is not null, return false
	if(tiles[0] != NULL && tiles[0]->getNext(direction) != NULL)
		return false;

	// set all tiles to not occupied
	for(int i = 0; i < length; i++)
		tiles[i]->setOccupied(false,'O');
		
	return true;
}


/*
* Accessor method for the lane of the vehicle
*
* @return
*	Lane of the vehicle
*/
int Vehicle::getSpawnLane()
{
	return spawnLane;
}

/*
* Accessor method for the spawn time of the vehicle
*
* @return
*	Spawn time of the vehicle
*/
double Vehicle::getSpawnTime()
{
	return spawnTime;
}

/*
* Accessor method for the total time the vehicle waits to enter the intersection.
*
* @return
*	Total time the vehicle waits to enter the intersection.
*/
double Vehicle::getWaitIntersection()
{
	return waitIntersection;
}

/*
* This method increases the time the vehicle waits to enter the intersection.
*/
void Vehicle::addWaitIntersection()
{
	waitIntersection += 1;
}


/*
* Accessor method for the total time the vehicle waits except when it
* waits to enter the intersection.
*
* @return
*	Total time the vehicle waits except when it waits to enter the intersection.
*/
double Vehicle::getWaitCrossRoad()
{
	return waitCrossRoad;
}


/*
* This method increases the time the vehicle waits except when it waits to
* enter the intersection.
*/
void Vehicle::addWaitCrossRoad()
{
	waitCrossRoad += 1;
}

