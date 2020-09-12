// Author: Arda Basaran, Nicholas Biffis, Oliver Cho
// Date: 16 December 2017
// File description: This is the tester file for classes which are used by the simulation, 
// it does numerous tests on the methods of the classes to demonstrate their behavior.


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include "Simulation.h"
#include "Vehicle.h"
#include "CrossRoad.h"
#include "Statistics.h"
#include "StopLight.h"
#include "Random.h"

using namespace std;


// Setting up random generator

std::mt19937 Random::rng(123456);
std::uniform_int_distribution<int> Random::randint01(0,100);
std::uniform_real_distribution<double> Random::randdouble(0.0,1.0);


int main(int argc, char* argv[])
{
	cout << "#################################################" << endl;
	cout << "########## TESTING THE SECTION CLASS ############" << endl;
	cout << "#################################################" << endl;
    cout << endl << "Testing default constructor:" << endl;
    
    Section section1;

    cout << "\tIs occupied: "   << section1.isOccupied() << " [0]" << endl;
    cout << "\tIs intersection: "   << section1.isOccupied() << " [0]" << endl;
    cout << "\tVehicle type: "   << section1.getVehicleType() << " [O]" << endl;

    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << endl << "Testing setter & getter methods:" << endl;
    
    section1.setOccupied(true, 'c');
    section1.setIntersection(true);

    cout << "\tIs occupied: "   << section1.isOccupied() << " [1]" << endl;
    cout << "\tIs intersection: "   << section1.isOccupied() << " [1]" << endl;
    cout << "\tVehicle type: "   << section1.getVehicleType() << " [c]" << endl;

    Section section2;
    Section section3;
    Section section4;

    section1.setUp(&section2);
    section1.setDown(&section3);
    section1.setLeft(&section4);
    section1.setRight(&section2);
    cout << "\tUp: "   << section1.getUp() << " [" << &section2 << "] " << endl;
    cout << "\tDown: "   << section1.getDown() << " [" << &section3 << "] " << endl;
    cout << "\tLeft: "   << section1.getLeft() << " [" << &section4 << "] " << endl;
    cout << "(Set right same section as the up)" << endl;
    cout << "\tRight: "   << section1.getRight() << " [" << &section2 << "] " << endl;

    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << endl << "Testing getNext method:" << endl;

    cout << "\tDir 1 (up)   : "   << section1.getNext(1) << " [" << &section2 << "] " << endl;
    cout << "\tDir 2 (left) : "   << section1.getNext(2) << " [" << &section4 << "] " << endl;
    cout << "\tDir 3 (right): "   << section1.getNext(3) << " [" << &section2 << "] " << endl;
    cout << "\tDir 4 (down) : "   << section1.getNext(4) << " [" << &section3 << "] " << endl;

	cout << "#################################################" << endl;
	cout << "######## TESTING THE STOPLIGHT CLASS ############" << endl;
	cout << "#################################################" << endl;
    cout << endl << "Testing default constructor:" << endl;
    
    StopLight light1;
    
    cout << "\tColor: "   << light1.getColor() << " [0]" << endl;
    light1.update(5);
    cout << "\tupdate(5): "   << light1.getColor() << " [0]" << endl;
    cout << "\tticksLeft(0): "   << light1.ticksLeft(0) << " [0]" << endl;

    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << endl << "Testing custom constructor:" << endl;
    StopLight light2(3,1,2,1);
    StopLight light3(3,1,2,3);

    cout << "At t=0" << endl;
    cout << "\tLight 2 Color: "   << light2.getColor() << " [1]" << endl;
    cout << "\tLight 2 ticksLeft(0): "   << light2.ticksLeft(0) << " [3]" << endl;
    cout << "\tLight 3 Color: "   << light3.getColor() << " [3]" << endl;
    cout << "\tLight 3 ticksLeft(0): "   << light3.ticksLeft(0) << " [2]" << endl;

    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << endl << "Testing update/getColor/ticksLeft methods:" << endl;
    cout << "At t=4" << endl;
    light2.update(1);
    light3.update(1);
    light2.update(2);
    light3.update(2);
    light2.update(3);
    light3.update(3);
    light2.update(4);
    light3.update(4);
    cout << "\tLight 2 Color: "   << light2.getColor() << " [3]" << endl;
    cout << "\tLight 2 ticksLeft(4): "   << light2.ticksLeft(4) << " [1]" << endl;
    cout << "\tLight 3 Color: "   << light3.getColor() << " [1]" << endl;
    cout << "\tLight 3 ticksLeft(4): "   << light3.ticksLeft(4) << " [2]" << endl;

    cout << "At t=21" << endl;
    for(int i = 5; i<=21; i++)
    {
    	light2.update(i);
    	light3.update(i);
    }
    cout << "\tLight 2 Color: "   << light2.getColor() << " [3]" << endl;
    cout << "\tLight 2 ticksLeft(21): "   << light2.ticksLeft(21) << " [2]" << endl;
    cout << "\tLight 3 Color: "   << light3.getColor() << " [1]" << endl;
    cout << "\tLight 3 ticksLeft(21): "   << light3.ticksLeft(21) << " [3]" << endl;


    cout << "#################################################" << endl;
	cout << "######## TESTING THE CROSSROAD CLASS ############" << endl;
	cout << "#################################################" << endl;
    cout << endl << "Testing constructor:" << endl;
 	cout << "Cross road with lane length 8:" << endl;
    CrossRoad cr1(8);
    cr1.printCrossRoad();

    cout << "Cross road with lane length 20:" << endl;
    CrossRoad cr2(20);
    cr2.printCrossRoad();

    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << endl << "Testing intersection connections:" << endl;
    Section* temp;
    cout << "SPAWN LANE: NORTH" << endl;
    cout << "Straight" << endl;
    CrossRoad cr3(8);
    temp = cr3.getNorth()[0];
    while(temp != NULL)
    {
    	temp->setOccupied(true, 'X');
    	temp = temp->getNext(1);
    }
    cr3.printCrossRoad();

    cout << "Left" << endl;
    CrossRoad cr4(8);
    temp = cr4.getNorth()[0];
    while(temp != NULL)
    {
    	temp->setOccupied(true, 'X');
    	temp = temp->getNext(2);
    }
    cr4.printCrossRoad();

    cout << "Right" << endl;
    CrossRoad cr5(8);
    temp = cr5.getNorth()[0];
    while(temp != NULL)
    {
    	temp->setOccupied(true, 'X');
    	temp = temp->getNext(3);
    }
    cr5.printCrossRoad();


    cout << "SPAWN LANE: SOUTH" << endl;
    cout << "Straight" << endl;
    CrossRoad cr6(8);
    temp = cr6.getSouth()[0];
    while(temp != NULL)
    {
    	temp->setOccupied(true, 'X');
    	temp = temp->getNext(4);
    }
    cr6.printCrossRoad();

    cout << "Left" << endl;
    CrossRoad cr7(8);
    temp = cr7.getSouth()[0];
    while(temp != NULL)
    {
    	temp->setOccupied(true, 'X');
    	temp = temp->getNext(3);
    }
    cr7.printCrossRoad();

    cout << "Right" << endl;
    CrossRoad cr8(8);
    temp = cr8.getSouth()[0];
    while(temp != NULL)
    {
    	temp->setOccupied(true, 'X');
    	temp = temp->getNext(2);
    }
    cr8.printCrossRoad();


    cout << "SPAWN LANE: WEST" << endl;
    cout << "Straight" << endl;
    CrossRoad cr9(8);
    temp = cr9.getWest()[0];
    while(temp != NULL)
    {
    	temp->setOccupied(true, 'X');
    	temp = temp->getNext(2);
    }
    cr9.printCrossRoad();

    cout << "Left" << endl;
    CrossRoad cr10(8);
    temp = cr10.getWest()[0];
    while(temp != NULL)
    {
    	temp->setOccupied(true, 'X');
    	temp = temp->getNext(4);
    }
    cr10.printCrossRoad();

    cout << "Right" << endl;
    CrossRoad cr11(8);
    temp = cr11.getWest()[0];
    while(temp != NULL)
    {
    	temp->setOccupied(true, 'X');
    	temp = temp->getNext(1);
    }
    cr11.printCrossRoad();


    cout << "SPAWN LANE: EAST" << endl;
    cout << "Straight" << endl;
    CrossRoad cr12(8);
    temp = cr12.getEast()[0];
    while(temp != NULL)
    {
    	temp->setOccupied(true, 'X');
    	temp = temp->getNext(3);
    }
    cr12.printCrossRoad();

    cout << "Left" << endl;
    CrossRoad cr13(8);
    temp = cr13.getEast()[0];
    while(temp != NULL)
    {
    	temp->setOccupied(true, 'X');
    	temp = temp->getNext(1);
    }
    cr13.printCrossRoad();

    cout << "Right" << endl;
    CrossRoad cr14(8);
    temp = cr14.getEast()[0];
    while(temp != NULL)
    {
    	temp->setOccupied(true, 'X');
    	temp = temp->getNext(4);
    }
    cr14.printCrossRoad();
	

	cout << "#################################################" << endl;
	cout << "######### TESTING THE VEHICLE CLASS #############" << endl;
	cout << "#################################################" << endl;

	cout << endl << "Testing default constructor:" << endl;
    
    Vehicle vehicle1;

	cout << "\tLength: "   << vehicle1.getLength() << " [0]" << endl;
	cout << "\tDirection: "   << vehicle1.getDirection() << " [0]" << endl;
	cout << "\tTurn: "   << vehicle1.getTurn() << " \"\"" << endl;
	cout << "\tType: "   << vehicle1.getType() << " \"\"" << endl;
	cout << "\tSpawn Time: "   << vehicle1.getSpawnTime() << " [0]" << endl;
	cout << "\tSpawn Lane: "   << vehicle1.getSpawnLane() << " [0]" << endl;

    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << endl << "Testing custom constructor:" << endl;

    Vehicle vehicle2("car",1, &section1, 2, "left",7);
	cout << "\tLength: "   << vehicle2.getLength() << " [2]" << endl;
	cout << "\tDirection: "   << vehicle2.getDirection() << " [1]" << endl;
	cout << "\tTurn: "   << vehicle2.getTurn() << " \"left\"" << endl;
	cout << "\tType: "   << vehicle2.getType() << " \"Car\"" << endl;
	cout << "\tSpawn Time: "   << vehicle2.getSpawnTime() << " [7]" << endl;
	cout << "\tSpawn Lane: "   << vehicle2.getSpawnLane() << " [2]" << endl;
	cout << endl;

	Vehicle vehicle3("suv",2, &section2, 3, "right",5);
	cout << "\tLength: "   << vehicle3.getLength() << " [3]" << endl;
	cout << "\tDirection: "   << vehicle3.getDirection() << " [2]" << endl;
	cout << "\tTurn: "   << vehicle3.getTurn() << " \"right\"" << endl;
	cout << "\tType: "   << vehicle3.getType() << " \"suv\"" << endl;
	cout << "\tSpawn Time: "   << vehicle3.getSpawnTime() << " [5]" << endl;
	cout << "\tSpawn Lane: "   << vehicle3.getSpawnLane() << " [3]" << endl;
	cout << endl;

	Vehicle vehicle4("truck",3, &section1, 1, "straight",3);
	cout << "\tLength: "   << vehicle4.getLength() << " [4]" << endl;
	cout << "\tDirection: "   << vehicle4.getDirection() << " [3]" << endl;
	cout << "\tTurn: "   << vehicle4.getTurn() << " \"straight\"" << endl;
	cout << "\tType: "   << vehicle4.getType() << " \"truck\"" << endl;
	cout << "\tSpawn Time: "   << vehicle4.getSpawnTime() << " [3]" << endl;
	cout << "\tSpawn Lane: "   << vehicle4.getSpawnLane() << " [1]" << endl;
	cout << endl;

	cout << "(the rest will be tested with simulation class)" << endl;

	cout << "#################################################" << endl;
	cout << "######### TESTING THE SIMULATION CLASS ##########" << endl;
	cout << "#################################################" << endl;
	
	// Simulation sim(probLeft, probRight, greenTicks, yellowTicks, redTicks, carProb, 
	// 				suvProb, spawnNum, probLaneEast, probLaneWest, probLaneNorth,
	// 				laneLength, printSimulation);
	cout << "SIMULATION SETUP" << endl;
	cout << "North-South only." << endl;
	cout << "No left&right turn." << endl;
	cout << "Lights are always green" << endl;
	Simulation sim1(0, 0, 10, 0, 0, 0.3, 
					0.3, 1, 0, 0, 0.5,
					8, 0);
	for(int i = 0; i < 10000; i++)
		sim1.update(i);
	cout << "STATS AT T=10000" << endl;
	sim1.printStats();

	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

    cout << "SIMULATION SETUP" << endl;
    cout << "North-South only." << endl;
    cout << "No left&right turn." << endl;
    cout << "Lights are always green" << endl;
    Simulation sim12(0, 0, 10, 0, 0, 0.3, 
                    0.3, 1, 0, 0, 0.5,
                    8, 1);
    for(int i = 0; i < 30; i++)
        sim12.update(i);
    cout << "STATS AT T=30" << endl;
    sim12.printStats();

    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;


	cout << "SIMULATION SETUP" << endl;
	cout << "North-South only." << endl;
	cout << "No left&right turn." << endl;
	cout << "Green:5, Yellow:2, Red:7" << endl;
	Simulation sim2(0, 0, 5, 2, 7, 0.3, 
					0.3, 1, 0, 0, 0.5,
					8, 0);
	for(int i = 0; i < 10000; i++)
		sim2.update(i);
	cout << "STATS AT T=10000" << endl;
	sim2.printStats();

    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "SIMULATION SETUP" << endl;
    cout << "North-South only." << endl;
    cout << "No left&right turn." << endl;
    cout << "Green:5, Yellow:2, Red:7" << endl;
    Simulation sim21(0, 0, 5, 2, 7, 0.3, 
                    0.3, 1, 0, 0, 0.5,
                    8, 1);
    for(int i = 0; i < 20; i++)
        sim21.update(i);
    cout << "STATS AT T=20" << endl;
    sim21.printStats();

	cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "SIMULATION SETUP" << endl;
	cout << "All bounds are in use." << endl;
	cout << "No left turn." << endl;
	cout << "Green:5, Yellow:2, Red:7" << endl;
	Simulation sim3(0, 0.3, 5, 2, 7, 0.3, 
					0.3, 1, 0.25, 0.25, 0.25,
					8, 0);
	for(int i = 0; i < 10000; i++)
		sim3.update(i);
	cout << "STATS AT T=10000" << endl;
	sim3.printStats();

    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "SIMULATION SETUP" << endl;
    cout << "All bounds are in use." << endl;
    cout << "No left turn." << endl;
    cout << "Green:5, Yellow:2, Red:7" << endl;
    Simulation sim31(0, 0.3, 5, 2, 7, 0.3, 
                    0.3, 1, 0.25, 0.25, 0.25,
                    8, 1);
    for(int i = 0; i < 20; i++)
        sim31.update(i);
    cout << "STATS AT T=20" << endl;
    sim31.printStats();
	
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;


	cout << "SIMULATION SETUP" << endl;
	cout << "All bounds are in use." << endl;
	cout << "All turns are allowed." << endl;
	cout << "Green:7, Yellow:3, Red:10" << endl;
	Simulation sim4(0.3, 0.3, 7, 3, 10, 0.3, 
					0.3, 4, 0.25, 0.25, 0.25,
					20, 0);
	for(int i = 0; i < 10000; i++)
		sim4.update(i);
	cout << "STATS AT T=10000" << endl;
	sim4.printStats();
	
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;


    cout << "SIMULATION SETUP" << endl;
    cout << "All bounds are in use." << endl;
    cout << "All turns are allowed." << endl;
    cout << "Green:7, Yellow:3, Red:10" << endl;
    Simulation sim41(0.3, 0.3, 7, 3, 10, 0.3, 
                    0.3, 1, 0.25, 0.25, 0.25,
                    20, 1);
    for(int i = 0; i < 20; i++)
        sim41.update(i);
    cout << "STATS AT T=20" << endl;
    sim41.printStats();


    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++" << endl;


    cout << "SIMULATION SETUP" << endl;
    cout << "All bounds are in use." << endl;
    cout << "All turns are allowed." << endl;
    cout << "Green:0, Yellow:0, Red:0" << endl;
    Simulation sim5(0.3, 0.3, 0, 0, 0, 0.3, 
                    0.3, 4, 0.25, 0.25, 0.25,
                    20, 0);
    for(int i = 0; i < 10000; i++)
        sim5.update(i);
    cout << "STATS AT T=10000" << endl;
    sim5.printStats();


	return 0;
}





