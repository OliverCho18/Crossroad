// Author: Arda Basaran, Nicholas Biffis, Oliver Cho
// Date: 16 December 2017
// File description: This is the header file for the CrossRoad class

#ifndef __crossroad_h__
#define __crossroad_h__

#include "Section.h"
#include <vector>

using namespace std;

/*
* This class uses instances of Section class to implement lanes and intersections for
* the simulation.
*/
class CrossRoad
{
	private:
		// length of one lane
		int length;

		// lanes stored as vectors of Section instances
		vector<Section*> north;
		vector<Section*> south;
		vector<Section*> east;
		vector<Section*> west;

	public:
		/*
		* Default constructor of the class
		*/
		CrossRoad();

		/*
		* Custom constructor that creates a crossroad, with each lane with the given lenght
		*
		* @param
		*	lengthSim Length of each lane
		*/
		CrossRoad(int lengthSim);

		/*
		* Destructor of the class.
		*/
		~CrossRoad();

		/*
		* Accessor method for the north bound.
		*
		* @return
		*	A vector of section representing the north bound.
		*/
		vector<Section*> getNorth();

		/*
		* Accessor method for the south bound.
		*
		* @return
		*	A vector of section representing the south bound.
		*/
		vector<Section*> getSouth();

		/*
		* Accessor method for the east bound.
		*
		* @return
		*	A vector of section representing the east bound.
		*/
		vector<Section*> getEast();

		/*
		* Accessor method for the west bound.
		*
		* @return
		*	A vector of section representing the west bound.
		*/
		vector<Section*> getWest();

		/*
		* This method prints the crossroad to the standard output.
		*/
		void printCrossRoad();

};

#endif
