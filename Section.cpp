// Author: Arda Basaran, Nicholas Biffis, Oliver Cho
// Date: 16 December 2017
// File description: This is the class file for the Section class

#include "Section.h"

/*
* Accessor method for for section link to the up
* 
* @return
*	The section that is linked to the up
*/
Section::Section()
{
	vehicleType = 'O';
	occupied = false;
	intersection = false;
	up = 0;
	down = 0;
	left = 0;
	right = 0;
}

/*
* Destructor of the class
*/
Section::~Section() {}


/*
* This method changes the occupation of the section with given boolean value
* and given vehicle type indicator
* 
* @param 
*	value Boolean value to set
*	c 	  Char value indicating the type of the vehicle
*/
void Section::setOccupied(bool value, char c)
{
	occupied = value;
	vehicleType = c;
}


/*
* Accessor method for "occupied"
*
* @return
* 	Boolean value indicating whether the section is occupied
*/
bool Section::isOccupied()
{
	return occupied;
}


/*
* Mutator method for "intersection"
*
* @param
* 	value Boolean value to set
*/
void Section::setIntersection(bool value)
{
	intersection = value;
}


/*
* Accessor method for "intersection"
*
* @return
* 	Boolean value indicating whether the section is an intersection
*/
bool Section::isIntersection()
{
	return intersection;
}


/*
* Accessor method for "vehicleType"
*
* @return
*	Char value indicating the type of the vehicle
*/
char Section::getVehicleType()
{
	return vehicleType;
}


/*
* Mutator method for section link to the up
*
* @param
* 	section The section that will be linked to the up
*/
void Section::setUp(Section* section)
{
	up = section;
}


/*
* Accessor method for for section link to the up
* 
* @return
*	The section that is linked to the up
*/
Section* Section::getUp()
{
	return up;
}


/*
* Mutator method for section link to the down
*
* @param
* 	section The section that will be linked to the down
*/
void Section::setDown(Section* section)
{
	down = section;
}


/*
* Accessor method for for section link to the down
* 
* @return
*	The section that is linked to the down
*/
Section* Section::getDown()
{
	return down;
}


/*
* Mutator method for section link to the left
*
* @param
* 	section The section that will be linked to the left
*/
void Section::setLeft(Section* section)
{
	left = section;
}


/*
* Accessor method for for section link to the left
* 
* @return
*	The section that is linked to the left
*/
Section* Section::getLeft()
{
	return left;
}


/*
* Mutator method for section link to the right
*
* @param
* 	section The section that will be linked to the right
*/
void Section::setRight(Section* section)
{
	right = section;
}


/*
* Accessor method for for section link to the right
* 
* @return
*	The section that is linked to the right
*/
Section* Section::getRight()
{
	return right;
}


/*
* Given a direction, this method returns the next section in that direction.
*
* @param
* 	dir The integer indicating the direction
* @return
* 	The next section in the given direction
*/
Section* Section::getNext(int dir)
{
	if(dir == 1)
	{
		return getUp();
	}
	else if(dir == 2)
	{
		return getLeft();
	}
	else if(dir == 3)
	{
		return getRight();
	}
	else
	{
		return getDown();
	}
}

