// Author: Arda Basaran, Nicholas Biffis, Oliver Cho
// Date: 16 December 2017
// File description: This is the header file for the Section class

#ifndef __section_h__
#define __section_h__

/*
* Section class implements small sections of the lanes. Once they are linked appropriately
* they create a cross road (see class CrossRoad) for vehicles to simulate on.
*/
class Section 
{
	private:
		// indicates whether the section is occupied or not
		bool occupied;

		// indicates whether the section is intersection or not
		bool intersection;

		// indicates the type of vehicle that occupies this section
		// 'c': car, 's': suv, 't': truck, 'O': unoccupied
		char vehicleType;

		// provides links to next sections according to direction
		Section* up;
		Section* down;
		Section* left;
		Section* right;

	public:

		/*
		* Default constructor of the class
		*/
		Section();

		/*
		* Destructor of the class
		*/
		~Section();

		/*
		* This method changes the occupation of the section with given boolean value
		* and given vehicle type indicator
		* 
		* @param 
		*	value Boolean value to set
		*	c 	  Char value indicating the type of the vehicle
		*/
		void setOccupied(bool value, char c);

		/*
		* Accessor method for "occupied"
		*
		* @return
		* 	Boolean value indicating whether the section is occupied
		*/
		bool isOccupied();

		/*
		* Mutator method for "intersection"
		*
		* @param
		* 	value Boolean value to set
		*/
		void setIntersection(bool value);

		/*
		* Accessor method for "intersection"
		*
		* @return
		* 	Boolean value indicating whether the section is an intersection
		*/
		bool isIntersection();

		/*
		* Accessor method for "vehicleType"
		*
		* @return
		*	Char value indicating the type of the vehicle
		*/
		char getVehicleType();

		/*
		* Mutator method for section link to the up
		*
		* @param
		* 	section The section that will be linked to the up
		*/
		void setUp(Section* section);

		/*
		* Accessor method for for section link to the up
		* 
		* @return
		*	The section that is linked to the up
		*/
		Section* getUp();


		/*
		* Mutator method for section link to the down
		*
		* @param
		* 	section The section that will be linked to the down
		*/
		void setDown(Section* section);

		/*
		* Accessor method for for section link to the down
		* 
		* @return
		*	The section that is linked to the down
		*/
		Section* getDown();


		/*
		* Mutator method for section link to the left
		*
		* @param
		* 	section The section that will be linked to the left
		*/
		void setLeft(Section* section);

		/*
		* Accessor method for for section link to the left
		* 
		* @return
		*	The section that is linked to the left
		*/
		Section* getLeft();


		/*
		* Mutator method for section link to the right
		*
		* @param
		* 	section The section that will be linked to the right
		*/
		void setRight(Section* section);

		/*
		* Accessor method for for section link to the right
		* 
		* @return
		*	The section that is linked to the right
		*/
		Section* getRight();


		/*
		* Given a direction, this method returns the next section in that direction.
		*
		* @param
		* 	dir The integer indicating the direction
		* @return
		* 	The next section in the given direction
		*/
		Section* getNext(int dir);

};

#endif