// Author: Arda Basaran, Nicholas Biffis, Oliver Cho
// Date: 16 December 2017
// File description: This is the class file for the StopLight class

#include "StopLight.h"
#include <string>

using namespace std;

/*
* Default constructor of the class
*/
StopLight::StopLight()
{
	greenTime = 0;
	redTime = 0;
	yellowTime = 0;
	color = 0;
	lastChange = 0;
}

/*
* Constructor with values for the class variables also with a start color
*
* @param
*	rt Integer value indicating the red time
*	yt Integer value indicating the yellow time
*	gt Integer value indicating the green time
*	startColor Integer value indicating the start color
*/
StopLight::StopLight(int rt, int yt, int gt, int startColor)
{
	greenTime = gt;
	redTime = rt;
	yellowTime = yt;
	color = startColor;
	lastChange = 0;
} 

/*
* Destructor of the class
*/
StopLight::~StopLight() {}


/*
* This method updates the stoplight according to the given time
*
* @param
*	t Integer value indicating the current time
*/
void StopLight::update(int t)
{
	if(color == 1 && t - lastChange >= redTime)
	{
		color = 3;
		lastChange = t;
	}
	if(color == 2 && t - lastChange >= yellowTime)
	{
		color = 1;
		lastChange = t;
	}
	if(color == 3 && t - lastChange >= greenTime)
	{
		color = 2;
		lastChange = t;
	}
}


/*
* This method returns the integer value indicating the current color
* on the stoplight. (1: red, 2: yellow, 3: green)
*
* @return
* 	Integer value indicating the current color of the stoplight
*/
int StopLight::getColor()
{
	return color;
}


/*
* This method returns the ticks remaining to next color change on the stoplight
* with respect to given current time.
*
* @param t
*	t Integer value indicating the current time
* @return
*	Number of ticks left to the next color change.
*/
int StopLight::ticksLeft(int t)
{
	if(color == 1)
	{
		return redTime - (t-lastChange);
	}
	if(color == 2)
	{
		return yellowTime - (t-lastChange);
	}
	else
	{
		return greenTime - (t-lastChange);
	}
}

