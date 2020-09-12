// Author: Arda Basaran, Nicholas Biffis, Oliver Cho
// Date: 16 December 2017
// File description: This is the driver file of the simulation. It reads input, initializes the simulation and runs it.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include "Simulation.h"

using namespace std;


std::mt19937 Random::rng(123456);
std::uniform_int_distribution<int> Random::randint01(0,100);
std::uniform_real_distribution<double> Random::randdouble(0.0,1.0);


int main(int argc, char* argv[])
{
	ifstream inputFile;

	if(argc < 2)
	{
		cerr << "Usage: " << argv[0] << " [input file]" << endl;
		exit(0);
	}

	// open file and check that it was successfully opened
    inputFile.open( argv[1] );
    if ( !inputFile.is_open() )
    {
        cerr << "Error: Unable to open file " << argv[1] << endl;
        exit(1);
    }

    double probLeft;
    double probRight;
    int greenTicks;
	int yellowTicks;
	int redTicks;
	double carProb;
	double suvProb;
	int spawnNum;
	double probLaneEast;
	double probLaneWest;
	double probLaneNorth;
	int maxTime;
	int laneLength;
	int printSimulation;

    while ( inputFile.good() )
    {

        inputFile >> probLeft;
		inputFile >> probRight;
		inputFile >> greenTicks;
		inputFile >> yellowTicks;
		inputFile >> redTicks;
		inputFile >> carProb;
		inputFile >> suvProb;
		inputFile >> spawnNum;
		inputFile >> probLaneEast;
		inputFile >> probLaneWest;
		inputFile >> probLaneNorth;
		inputFile >> maxTime;
		inputFile >> laneLength;
		inputFile >> printSimulation;


        if ( inputFile.fail() )
        {
            // If the fail flag is set by >>, something unexpected happened:
            //    e.g., wrong data type in file for reading;
            //    e.g., only thing left to read is end-of-file character 
            // If the former, one could (should) print an error message;
            // if the latter, the .eof() method can be used to identify and
            // break out.
            if (inputFile.eof())
            {
                // no problem here -- just exit loop and handle results
                break;
            }
            else
            {
                // failed for some other reason (e.g., string or float input);
                // print a message and exit
                cerr << "Error reading the input" << endl;
                cerr << "Input file should have 12 lines as follows:" << endl;
                cerr << "[Double: Probability left]" << endl;
                cerr << "[Double: Probability right]" << endl;
                cerr << "[Integer: Number of green ticks]" << endl;
                cerr << "[Integer: Number of yellow ticks]" << endl;
                cerr << "[Integer: Number of red ticks]" << endl;
                cerr << "[Double: Probability car]" << endl;
                cerr << "[Double: Probability SUV]" << endl;
                cerr << "[Integer: Number of spawns per tick]" << endl;
                cerr << "[Double: Probability lane east]" << endl;
                cerr << "[Double: Probability lane west]" << endl;
                cerr << "[Double: Probability lane north]" << endl;
                cerr << "[Integer: Max time]" << endl;
                cerr << "[Integer: Lane length (>10)]" << endl;
                cerr << "[Integer: Print simulation (0 or 1)]" << endl;
                exit(1);
            }
        }


    }

    inputFile.close();  // always good practice to close the input file


    if(probLeft + probRight > 1 || (probLeft < 0 || probRight < 0) )
	{
		cerr << "Probability of left and right turns should be larger than or equal to 0 and their sum cannot be greater than 1." << endl;
		exit(0);
	}
	if (redTicks != greenTicks + yellowTicks)
	{
		cerr << "Number of green ticks and yellow ticks should add upp to red ticks." << endl;
		exit(0);
	}
	if(redTicks < 0 || yellowTicks < 0 || greenTicks < 0)
	{
		cerr << "Red ticks, yellow ticks and green ticks all need to be larger than or equal to 0." << endl;
		exit(0);
	}
	if(carProb + suvProb > 1 || (carProb < 0 || suvProb < 0) )
	{
		cerr << "Probability of car and suv should be larger than or equal to 0 and their sum cannot be greater than 1." << endl;
		exit(0);
	}
	if(probLaneEast < 0 || probLaneWest < 0 || probLaneNorth < 0)
	{
		cerr << "Probability of east/west/north lane should be at least 0." << endl;
		exit(0);
	}
	if(probLaneEast + probLaneNorth + probLaneWest > 1)
	{
		cerr << "Sum of east&west&north lane probabilities cannot be greater than 1." << endl;
		exit(0);
	}
	if(laneLength < 10)
	{
		cerr << "The lane length must be at least 10." << endl;
		exit(0);
	}
	if(printSimulation != 1 && printSimulation != 0)
	{
		cerr << "Print simulation must be either 0 or 1." << endl;
		exit(0);
	}

	Simulation sim(probLeft, probRight, greenTicks, yellowTicks, redTicks, carProb, 
					suvProb, spawnNum, probLaneEast, probLaneWest, probLaneNorth,
					laneLength, printSimulation);

	//timer
	int t = 0;

	while(t < maxTime)
	{
		sim.update(t);
		t++;
	}

	sim.printStats();

	return 0;

}
