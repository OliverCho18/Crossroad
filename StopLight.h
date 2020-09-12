// Author: Arda Basaran, Nicholas Biffis, Oliver Cho
// Date: 16 December 2017
// File description: This is the header file for the StopLight class

#ifndef __stoplight_h__
#define __stoplight_h__

/* 
* This class implements the stoplights that will control the crossroad, the
* simulation checks instances of this stoplight class to determine whether
* the vehicles can move through the intersections
*/
class StopLight {
	private:
		// number of ticks that the stoplight will be red
		int redTime;
		// number of ticks that the stoplight will be yellow
		int yellowTime;
		// number of ticks that the stoplight will be green
		int greenTime;

		// Integer value indicating the color of the light 
		// 1: red, 2: yellow, 3: green
		int color;

		// indicates the last time the stoplight changed color
		int lastChange;

	public:
		/*
		* Default constructor of the class
		*/
		StopLight();
		
		/*
		* Constructor with values for the class variables also with a start color
		*
		* @param
		*	rt Integer value indicating the red time
		*	yt Integer value indicating the yellow time
		*	gt Integer value indicating the green time
		*	startColor Integer value indicating the start color
		*/
		StopLight(int rt, int yt, int gt, int startColor);

		/*
		* Destructor of the class
		*/
		~StopLight();

		/*
		* This method updates the stoplight according to the given time
		*
		* @param
		*	t Integer value indicating the current time
		*/
		void update(int t);

		/*
		* This method returns the integer value indicating the current color
		* on the stoplight. (1: red, 2: yellow, 3: green)
		*
		* @return
		* 	Integer value indicating the current color of the stoplight
		*/
		int getColor();

		/*
		* This method returns the ticks remaining to next color change on the stoplight
		* with respect to given current time.
		*
		* @param t
		*	t Integer value indicating the current time
		* @return
		*	Number of ticks left to the next color change.
		*/
		int ticksLeft(int t);

};

#endif 
