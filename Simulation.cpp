// Author: Arda Basaran, Nicholas Biffis, Oliver Cho
// Date: 16 December 2017
// File description: This is the class file for the Simulation class

#include <iostream>
#include <vector>
#include "Simulation.h"


using namespace std;

/*
* Default constructor of the class
*/
Simulation::Simulation() :
nsLight(), weLight(), crossRoad(), vehicles(), stats()
{
	probLeft = 0;
    probRight = 0;
	carProb = 0;
	suvProb = 0;
	probLaneEast = 0;
	probLaneWest = 0;
	probLaneNorth = 0;
	greenTicks = 0;
	yellowTicks = 0;
	redTicks = 0;
	spawnNum = 0;
	laneLength = 0;
	printSim = 0;
}


/*
* Custom constructor that initializes a simulation with given parameters.
*
* @param
*	probLeft Probability of each vehicle making a left turn
*	probRight Probability of each vehicle making a right turn
*	greenTicks Number of ticks for stoplights to be green
*	yellowTicks Number of ticks for stoplights to be yellow
*	redTicks Number of ticks for stoplights to be red
*	carProb Probability of each vehicle spawned being a car
*	suvProb Probability of each vehicle spawned being a SUV
*	spawnNum Number of vehicles that the simulation will try to spawn at each tick
*	probLaneEast Probability of each spawned vehicle being on the east bound.
*	probLaneWest Probability of each spawned vehicle being on the west bound.
*	probLaneNorth Probability of each spawned vehicle being on the west bound.
*	laneLength Length of each lane.
*	printSim Integer value indicating whether to print the simulation.
*/
Simulation::Simulation(double probLeftSim, double probRightSim, int greenTicksSim, 
					int yellowTicksSim, int redTicksSim,
					double carProbSim, double suvProbSim, int spawnNumSim, 
					double probLaneEastSim, double probLaneWestSim,
					double probLaneNorthSim, int laneLengthSim, int print)
: 
probLeft(probLeftSim), probRight(probRightSim), greenTicks(greenTicksSim),
yellowTicks(yellowTicksSim), redTicks(redTicksSim), carProb(carProbSim),
suvProb(suvProbSim), spawnNum(spawnNumSim),
probLaneEast(probLaneEastSim), probLaneWest(probLaneWestSim), probLaneNorth(probLaneNorthSim),
laneLength(laneLengthSim), printSim(print), nsLight(redTicks, yellowTicks, greenTicks, 1), 
weLight(redTicks, yellowTicks, greenTicks, 3), crossRoad(laneLength), vehicles(), stats()
{
}


/*
* Destructor of the class.
*/
Simulation::~Simulation() {}


/*
* This method updates the simulation using the given time. It updates
* stoplights, vehicles and lanes according to the current state the simulation
* is in.
*
* @param
*	t Integer value indicating the current time. 
*/
void Simulation::update(int t)
{
	// Update Stop Lights
	nsLight.update(t);
	weLight.update(t);

	// Loop over every vehicle
	for(int i = 0; i < (int) vehicles.size(); i++)
	{
		// get location of the vehicle
		Section* loc = vehicles[i].getLocation();
		// get direction of the vehicle
		int dir = vehicles[i].getDirection();
		// get the spawnLane of the vehicle
		int spawnLane = vehicles[i].getSpawnLane();


		StopLight light;
		vector<Section*> lane;
		vector<Section*> oppositeLane;

		// get the length of the vehicle
		int length = vehicles[i].getLength();


		// get the corresponding light, lane and the opposite lane that the vehicle 
		// needs to check with respect to its spawn lane
		if(spawnLane == 1)
		{
			lane = crossRoad.getNorth();
			oppositeLane = crossRoad.getSouth();
			light = nsLight;
		}
		else if(spawnLane == 2)
		{
			lane = crossRoad.getWest();
			oppositeLane = crossRoad.getEast();
			light = weLight;
		}
		else if(spawnLane == 3)
		{
			lane = crossRoad.getEast();
			oppositeLane = crossRoad.getWest();
			light = weLight;
		}
		else
		{
			lane = crossRoad.getSouth();
			oppositeLane = crossRoad.getNorth();
			light = nsLight;
		}



		// DETERMINE WHETHER THE VEHICLE CAN MOVE OR NOT
		// There are 3 cases:
		// 1. The vehicle is in the intersection
		// 2. The vehicle is not in the intersection nor it is about to enter the intersection
		// 3. The vehicle is about to enter the intersection.
		// 	  For the third case we need to:
		//    3.1. Check the light (i.e whether it's red or not)
		//    3.2. Check the remaining time (whether it's enough to clear the intersection)
		//    3.3. Check the opposite lane (can make the turn before another vehicle enters)
		bool canMove = true;
		
		// 1. The vehicle is in the intersection
		if(loc->isIntersection() == true)
		{
			if(loc->getNext(dir)->isOccupied() == true)
			{

				//cout << "Vehicle " << i << " is in the intersection but it's occupied" << endl;
				canMove = false;
				vehicles[i].addWaitIntersection();
			}
		}
		
		else
		{
			// 2. The vehicle is not in the intersection nor it is about to enter the intersection
			if(loc->getNext(dir)->isIntersection() == false)
			{
				if(loc->getNext(dir)->isOccupied() == true)
				{
					//cout << "Vehicle " << i << " is in the lane and the next tile is occupied" << endl;
					canMove = false;
					vehicles[i].addWaitCrossRoad();
				}


			}

			// 3. The vehicle is about to enter the intersection.
			else
			{
				// 3.1. Check the light (i.e whether it's red or not)
				if(light.getColor() == 1)
				{
					//cout << "Vehicle " << i << " is about to enter the intersection but the light is red" << endl;
					canMove = false;
					vehicles[i].addWaitIntersection();
				}
				else
				{
					//3.2. Check the remaining time (whether it's enough to clear the intersection)

					int remaining = light.ticksLeft(t);

					// if the light is green, add yellow time as well
					if(light.getColor() == 3)
					{
						remaining += yellowTicks;
					}

					// get the time needed to clear the intersection
					int timeForTurn;
					if(vehicles[i].getTurn() == "left")
					{
						timeForTurn = length + 3;
					}
					else if(vehicles[i].getTurn() == "right")
					{
						timeForTurn = length + 1;
					}
					else
					{
						timeForTurn = length + 2;
					}

					//check if remaining time is enough to clear the intersection
					if(remaining < timeForTurn)
					{
						//cout << "Vehicle " << i << " is about to enter the intersection but the time is not enough to make the turn" << endl;
						canMove  = false;
						vehicles[i].addWaitIntersection();
					}


					//3.3. Check the opposite lane (can make the left turn before another vehicle enters)
					else if(vehicles[i].getTurn() == "left")
					{
						int subLaneLength = (laneLength-2)/2-1; 
						Vehicle oppositeVehicle;
						for(int j = 0; j < (int)vehicles.size(); j++)
						{
							if(i == j)
							{
								continue;
							}
							if(vehicles[j].getLocation() == oppositeLane[subLaneLength])
							{
								oppositeVehicle = vehicles[j];
							}
						}

						if(oppositeVehicle.getLength() != 0 && oppositeVehicle.getTurn() == "left" && (vehicles[i].getSpawnLane() == 1 || vehicles[i].getSpawnLane() == 2))
						{
							canMove = true;
						}
						else
						{
						
							for(int i = 0; i < timeForTurn; i++)
							{
								if(subLaneLength-i < 0)
								{
									break;
								}

								if(oppositeLane[subLaneLength-i]->isOccupied() == true)
								{
									//cout << "Vehicle " << i << " tries to make left turn, no luck" << endl;
									canMove = false;
									vehicles[i].addWaitIntersection();
									break;
								}
							}
						}
					}

				}

			}
		}

		// If the vehicle can move, then update it
		if(canMove)
		{
			vehicles[i].update();

			// after the update, check if we need to erase it
			if(vehicles[i].isGone() == true)
			{
				stats.recordStats(vehicles[i],t);
				vehicles.erase(vehicles.begin()+i);
				//cout << "ERASED VEHICLE" << endl;
				i--;
			}
			
		}

	}


	// Try to spawn a vehicle for spawnNum times
	for(int i = 0; i < spawnNum; i++)
	{
		spawnVehicle(t);
	}


	if(printSim)
	{
		// Print simulation to standard output
		printSimulation(t);
	}

}


/*
* This method tries to spawn a new vehicle to the simulation.
* 
* @param
*	t Integer value indicating curren time
*/
void Simulation::spawnVehicle(int t)
{
	// Pick the lane
	int laneNum;
	double probabilityLane = Random::randdouble01();
	if(probabilityLane <= probLaneNorth)
	{
		laneNum = 1;
	}
	else if(probabilityLane > probLaneNorth && probabilityLane <= probLaneNorth+probLaneWest)
	{
		laneNum = 2;
	}
	else if(probabilityLane > probLaneNorth+probLaneWest && probabilityLane <= probLaneNorth+probLaneWest+probLaneEast)
	{
		laneNum = 3;
	}
	else
	{
		laneNum = 4;
	}

	// Pick the direction
	double probabilityDir = Random::randdouble01();
	int dir;
	string turn;
	if(probabilityDir <= probLeft)
	{
		turn = "left";
		switch(laneNum)
		{
			case 1:
				dir = 2;
				break;
			case 2:
				dir = 4;
				break;
			case 3:
				dir = 1;
				break;
			case 4:
				dir = 3;
				break;
			default:
				break;

		}
	}
	else if(probabilityDir > probLeft && probabilityDir <= probLeft + probRight)
	{
		turn = "right";
		switch(laneNum)
		{
			case 1:
				dir = 3;
				break;
			case 2:
				dir = 1;
				break;
			case 3:
				dir = 4;
				break;
			case 4:
				dir = 2;
				break;
			default:
				break;
		}
	}
	else
	{
		turn = "straight";
		switch(laneNum)
		{
			case 1:
				dir = 1;
				break;
			case 2:
				dir = 2;
				break;
			case 3:
				dir = 3;
				break;
			case 4:
				dir = 4;
				break;
			default:
				break;

		}
	}

	// Set the spawn lane according to the laneNum
	vector<Section*> lane;
	switch(laneNum)
	{
		case 1:
			lane = crossRoad.getNorth();
			break;
		case 2:
			lane = crossRoad.getWest();
			break;
		case 3:
			lane = crossRoad.getEast();
			break;
		case 4:
			lane = crossRoad.getSouth();
			break;
	}

	// Pick the vehicle type
	double probabilityVehicle;
	Vehicle temp;

	probabilityVehicle=Random::randdouble01();

	// If the chosen lane is free to spawn a vehicle, spawn a vehicle
	if(lane[0]->isOccupied() == false)
	{

		if(probabilityVehicle <= carProb)
		{
			temp = Vehicle("car", dir, lane[0], laneNum, turn, t);
			stats.addCarSpawned();
		}
		else if(probabilityVehicle > carProb && probabilityVehicle <= carProb + suvProb)
		{
			temp = Vehicle("suv", dir, lane[0], laneNum, turn, t);
			stats.addSUVSpawned();
		}
		else
		{
			temp = Vehicle("truck", dir, lane[0], laneNum, turn, t);
			stats.addTruckSpawned();
		}
		vehicles.push_back(temp);
	}
	else
	{
		stats.addVehicleNotSpawned();
		//cout << "Cannot spawn." << endl;
	}

}


/*
* This method prints statistics collected by the simulation to the standard
* output.
*/
void Simulation::printStats()
{
	double* arr = new double[16];
	arr = stats.getStats(arr);

	cout << "Car spawned: " << arr[0] << endl;
	cout << "Truck spawned: " << arr[1] << endl;
	cout << "SUV spawned: " << arr[2] << endl;

	cout << "Vehicle not spawned: " << arr[15] << endl;

	cout << "Car gone: " << arr[3] << endl;
	cout << "Truck gone: " << arr[4] << endl;
	cout << "SUV gone: " << arr[5] << endl;

	cout << "Car life span: " << arr[6] << endl;
	cout << "Truck life span: " << arr[8] << endl;
	cout << "SUV life span: " << arr[7] << endl;

	cout << "Car intersection wait: " << arr[9] << endl;
	cout << "Truck intersection wait: " << arr[11] << endl;
	cout << "SUV intersection wait: " << arr[10] << endl;


	cout << "Car cross road wait: " << arr[12] << endl;
	cout << "Truck cross road wait: " << arr[14] << endl;
	cout << "SUV cross road wait: " << arr[13] << endl;

	delete[] arr;
}


/*
* This method prints the simulation to standard output.
*
* @param
* 	t Integer value indicating the current time
*/
void Simulation::printSimulation(int t)
{
	cout << "#######################################" << endl;
	cout << "Simulation time: " << t << endl;
	cout << "Num of vehicles: " << vehicles.size() << endl;
	switch(nsLight.getColor())
	{
		case 1:
			cout << "NS Light: Red" << endl;
			break;
		case 2:
			cout << "NS Light: Yellow" << endl;
			break;
		case 3:
			cout << "NS Light: Green" << endl;
			break;
	}
	switch(weLight.getColor())
	{
		case 1:
			cout << "WE Light: Red" << endl;
			break;
		case 2:
			cout << "WE Light: Yellow" << endl;
			break;
		case 3:
			cout << "WE Light: Green" << endl;
			break;
	}

	crossRoad.printCrossRoad();

	cout << endl;
}
