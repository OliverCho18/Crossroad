Final Project Design

The main class which will read the input and initialize/run the simulation will be the Driver class. Driver class will have an instance of Simulation class which is responsible for handling the simulation, handling the updates and spawns. Simulation class will have an array of Vehicles (a Vehicle can be a Car, an SUV or a Truck), 4 instances of Lane for each bound and also two StopLight instances. We have four lanes called north, west, east, south, numbered 1, 2, 3, 4, respectively. Each direction, up, left, right, down, numbered 1, 2, 3, 4, Based on the lane the vehicle is in and the turn it’s going to make (left, right, straight), its direction is determined. For example, a vehicle spawned in the west lane (lane 2) and it is turning right, its direction will be up, which is 1. The Simulation class will also have an instance of the Statistics class which will keep the record of some statistics as the simulation runs. Each bound (west/east/north/south) is an array of “Section”s. The sections for the intersections are shared among the lanes. Section keeps a boolean value to indicate whether it is occupied or not, a boolean value to indicate whether it’s an intersection or not and also three links to next Sections for each direction (left, right, straight). Note that these sections will be linked so that for a section, “left” can be the section to the forward, as a vehicle that will turn left still need to go forward except the intersection (so the links to left and straight may point to the same section). Vehicle instances will keep an array of Sections to indicate their location.

The update method of the Simulation will call the updates in Vehicle and StopLight classes as well as spawn new vehicles. Every random operation will be handles using an instance of Random class. The overall structure of all the classes that will be used can be find below.

Testing and Implementation

After completing the implementation of each of our classes, we tested the classes individually to ensure they worked correctly. When we completed all of the individual tests and were confident with our simulation, we proceeded to write a test class to completely test our simulation.
First we tested our constructors as well as the accessor and mutator methods. Then we tested our crossroad, intersection and stoplight classes to ensure that they were linked correctly. In the test class we concluded by testing the following preset configurations for our simulation as you can see on the next page. These tests included conditions where no turns were allowed, only right turns and straight were allowed, and tests with nothing restricted. In addition we tested with different amounts of vehicles and different values for our stoplights.

After reviewing our results from our tests we concluded that our traffic simulation worked correctly within the specific bounds.
We tested our code in the local Valgrind in the computer lab and found that there were a few errors and a few memory leaks. After a few edits the code was all fine.

SIMULATION SETUP North-South only.
No left&right turn.
Lights are always green STATS AT T=10000
Car spawned: 929
Truck spawned: 1326
SUV spawned: 924 Vehicle not spawned: 6821 Car gone: 928
Truck gone: 1325
SUV gone: 922
Car life span: 8.72737
Truck life span: 10.3079
SUV life span: 9.43818
Car intersection wait: 1.39763 Truck intersection wait: 3.01283 SUV intersection wait: 2.10954 Car cross road wait: 0.329741 Truck cross road wait: 0.295094 SUV cross road wait: 0.328633

SIMULATION SETUP North-South only.
No left&right turn. Green:5, Yellow:2, Red:7 STATS AT T=10000
Car spawned: 474
Truck spawned: 681
SUV spawned: 540 Vehicle not spawned: 8305 Car gone: 474
Truck gone: 679
SUV gone: 540
Car life span: 14.308
Truck life span: 17.9985
SUV life span: 15.9407
Car intersection wait: 5.83122 Truck intersection wait: 9.69809 SUV intersection wait: 7.38889
Car cross road wait: 1.47679 Truck cross road wait: 1.30044 SUV cross road wait: 1.55185

SIMULATION SETUP
All bounds are in use.
No left turn.
Green:5, Yellow:2, Red:7 STATS AT T=10000
Car spawned: 1013
Truck spawned: 1353
SUV spawned: 1012 Vehicle not spawned: 6622 Car gone: 1013
Truck gone: 1351
SUV gone: 1009
Car life span: 12.3544
Truck life span: 15.2783
SUV life span: 13.6323
Car intersection wait: 4.75617 Truck intersection wait: 7.67802 SUV intersection wait: 5.96432 Car cross road wait: 0.912142 Truck cross road wait: 0.906736 SUV cross road wait: 0.961348

SIMULATION SETUP
All bounds are in use.
All turns are allowed. Green:7, Yellow:3, Red:10 STATS AT T=10000
Car spawned: 672
Truck spawned: 909
SUV spawned: 651
Vehicle not spawned: 37768 Car gone: 668
Truck gone: 904
SUV gone: 644
Car life span: 35.0464
Truck life span: 39.1692
SUV life span: 37.073
Car intersection wait: 3.62425 Truck intersection wait: 7.78872 SUV intersection wait: 5.61025
Car cross road wait: 12.4177 Truck cross road wait: 12.3805

SIMULATION SETUP
All bounds are in use.
All turns are allowed. Green:0, Yellow:0, Red:0 STATS AT T=10000
Car spawned: 0
Truck spawned: 4
SUV spawned: 8
Vehicle not spawned: 39988 Car gone: 0
Truck gone: 0
SUV gone: 0
Car life span: 0
Truck life span: 0
SUV life span: 0
Car intersection wait: 0 Truck intersection wait: 0 SUV intersection wait: 0 Car cross road wait: 0 Truck cross road wait: 0 SUV cross road wait: 0

Compilation and Execution Instructions:
SUV cross road wait: 12.4565
1.	In a terminal, navigate to the directory containing the simulation.
2.	Type and execute “make” in the command line. This will create two executables:
“simExec” and “testerExec”
3.	To run the simulation type ./simExec [inputfile]. For example, you can run ./simExec
input.txt. The input file should be of the format:
"[Double: Probability "[Double: Probability "[Integer: Number of "[Integer: Number of "[Integer: Number of "[Double: Probability "[Double: Probability "[Integer: Number of "[Double: Probability "[Double: Probability "[Double: Probability "[Integer: Max time]" 
left]"
right]"
green ticks]" yellow ticks]"
red ticks]"
car]"
SUV]"
spawns per tick]" lane east]"
lane west]"
lane north]"
