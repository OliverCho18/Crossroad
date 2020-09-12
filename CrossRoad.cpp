// Author: Arda Basaran, Nicholas Biffis, Oliver Cho
// Date: 16 December 2017
// File description: This is the class file for the CrossRoad class

#include "CrossRoad.h"
#include "Section.h"
#include <vector>
#include <iostream>

using namespace std;

/*
* Default constructor of the class
*/
CrossRoad::CrossRoad() :
north(), south(), east(), west()
{
	length = 0;
}

/*
* Custom constructor that creates a crossroad, with each lane with the given lenght
*
* @param
*	lengthSim Length of each lane
*/
CrossRoad::CrossRoad(int lengthSim) : length(lengthSim)
{
	vector<Section*> n, e, w, s;

	// CREATE SECTIONS FROM START TO INTERSECTION
	for(int i = 0; i < (lengthSim-2)/2; i++)
	{
		Section* leftEntry = new Section();
		Section* rightEntry = new Section();
		Section* northEntry = new Section();
		Section* southEntry = new Section();

		// make connections to previous sections
		if(i != 0)
		{
			n[i-1]->setUp(northEntry);
			e[i-1]->setUp(rightEntry);
			w[i-1]->setUp(leftEntry);

			s[i-1]->setDown(southEntry);
			e[i-1]->setDown(rightEntry);
			w[i-1]->setDown(leftEntry);
			

			n[i-1]->setLeft(northEntry);
			w[i-1]->setLeft(leftEntry);
			s[i-1]->setLeft(southEntry);

			n[i-1]->setRight(northEntry);
			e[i-1]->setRight(rightEntry);
			s[i-1]->setRight(southEntry);
		}

		// add sections to the lane
		n.push_back(northEntry);
		e.push_back(rightEntry);
		s.push_back(southEntry);
		w.push_back(leftEntry);
		
	}

	//INIT INTERSECTIONS
	Section* bl = new Section();
	Section* br = new Section();
	Section* tl = new Section();
	Section* tr = new Section();

	bl->setIntersection(true);
	br->setIntersection(true);
	tl->setIntersection(true);
	tr->setIntersection(true);



	//CONNECT INTERSECTIONS TO FIRST HALF OF THE LANE
	int tempIndex = (lengthSim-2)/2-1;
	n[tempIndex]->setUp(br);
	n[tempIndex]->setLeft(br);
	n[tempIndex]->setRight(br);

	s[tempIndex]->setDown(tl);
	s[tempIndex]->setLeft(tl);
	s[tempIndex]->setRight(tl);

	w[tempIndex]->setUp(tr);
	w[tempIndex]->setDown(tr);
	w[tempIndex]->setLeft(tr);

	e[tempIndex]->setUp(bl);
	e[tempIndex]->setRight(bl);
	e[tempIndex]->setDown(bl);

	// add intersections to the lanes
	n.push_back(br);
	n.push_back(tr);

	e.push_back(bl);
	e.push_back(br);

	w.push_back(tr);
	w.push_back(tl);

	s.push_back(tl);
	s.push_back(bl);



	tempIndex += 3; 

	// CREATE SECTIONS FROM INTERSECTION TO THE END
	for(int i = 0; i < (lengthSim-2)/2; i++)
	{
		Section* leftEntry = new Section();
		Section* rightEntry = new Section();
		Section* northEntry = new Section();
		Section* southEntry = new Section();

		// make connections to previous sections
		n[tempIndex+i-1]->setUp(northEntry);
		e[tempIndex+i-1]->setRight(rightEntry);
		w[tempIndex+i-1]->setLeft(leftEntry);
		s[tempIndex+i-1]->setDown(southEntry);
		
	

		// add sections to the lane
		n.push_back(northEntry);
		e.push_back(rightEntry);
		s.push_back(southEntry);
		w.push_back(leftEntry);
	}

	

	// connect intersection sections to each other
	br->setUp(tr);
	br->setRight(e[tempIndex]);
	br->setLeft(tr);

	bl->setDown(s[tempIndex]);
	bl->setRight(br);
	bl->setUp(br);

	tr->setUp(n[tempIndex]);
	tr->setLeft(tl);
	tr->setDown(tl);

	tl->setDown(bl);
	tl->setRight(bl);
	tl->setLeft(w[tempIndex]);




	// set crossroad lanes to created lanes
	north = n;
	east = e;
	west = w;
	south = s;
}

/*
* Destructor of the class.
*/
CrossRoad::~CrossRoad()
{
	for(int i = 0; i < length; i++)
	{
		delete north[i];
		delete south[i];
		if(i != (length-2)/2 && i != (length-2)/2+1)
		{
			delete east[i];
			delete west[i];
		}
	}
}


/*
* Accessor method for the north bound.
*
* @return
*	A vector of section representing the north bound.
*/
vector<Section*> CrossRoad::getNorth()
{
	return north;
}


/*
* Accessor method for the south bound.
*
* @return
*	A vector of section representing the south bound.
*/
vector<Section*> CrossRoad::getSouth()
{
	return south;
}

/*
* Accessor method for the west bound.
*
* @return
*	A vector of section representing the west bound.
*/
vector<Section*> CrossRoad::getWest()
{
	return west;
}

/*
* Accessor method for the east bound.
*
* @return
*	A vector of section representing the east bound.
*/
vector<Section*> CrossRoad::getEast()
{
	return east;
}

/*
* This method prints the crossroad to the standard output.
*/
void CrossRoad::printCrossRoad()
{
	// print the upper half of the north and south bounds
	for(int i=0; i < (length-2)/2; i++)
	{
		for(int j = 0; j < (length-2)/2; j++)
			cout << " ";

		cout << getSouth()[i]->getVehicleType();
		cout << getNorth()[length-1-i]->getVehicleType();
		cout << endl;
	}


	// print the west bound
	for(int j = length-1; j >= 0; j--)
	{
		cout << getWest()[j]->getVehicleType();
	}
	cout << endl;

	// print the east bound
	for(int j = 0; j < length; j++)
	{
		cout << getEast()[j]->getVehicleType();
	}
	cout << endl;



	

	int temp = (length-2)/2+2;

	// print the lower half of the north and south bounds
	for(int i=0; i < (length-2)/2; i++)
	{
		for(int j = 0; j < (length-2)/2; j++)
			cout << " ";

		cout << getSouth()[temp+i]->getVehicleType();
		cout << getNorth()[length-1-temp-i]->getVehicleType();
		cout << endl;
	}

	cout << endl;
}



