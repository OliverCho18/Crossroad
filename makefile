OBJS = Driver.o Simulation.o Statistics.o Vehicle.o StopLight.o CrossRoad.o Section.o 	# all the object files
OBJS2 = Tester.o Simulation.o Statistics.o Vehicle.o StopLight.o CrossRoad.o Section.o 	# all the object files
EXECS = simExec testerExec		# executable files to create

CC = g++ 	# the compiler to use
LD = $(CC)	# command used to link objects (usually same as compiler)


CCFLAGS = -Wall -Wno-deprecated $(INCDIR) -g -c -std=c++11    # compiler options
LDFLAGS = -Wall -Wno-deprecated -g -std=c++11 	# linker options

all: $(EXECS)
simExec: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o simExec
testerExec: $(OBJS2)
	$(LD) $(LDFLAGS) $(OBJS2) -o testerExec
Tester.o: Tester.cpp Simulation.h Vehicle.h CrossRoad.h Statistics.h StopLight.h Random.h
	$(CC) $(CCFLAGS) Tester.cpp
Driver.o: Driver.cpp Simulation.h
	$(CC) $(CCFLAGS) Driver.cpp
Simulation.o: Simulation.cpp Vehicle.h CrossRoad.h Statistics.h StopLight.h Random.h
	$(CC) $(CCFLAGS) Simulation.cpp
Statistics.o: Statistics.cpp Vehicle.h
	$(CC) $(CCFLAGS) Statistics.cpp
Vehicle.o: Vehicle.cpp Section.h
	$(CC) $(CCFLAGS) Vehicle.cpp
StopLight.o: StopLight.cpp
	$(CC) $(CCFLAGS) StopLight.cpp
CrossRoad.o: CrossRoad.cpp Section.h
	$(CC) $(CCFLAGS) CrossRoad.cpp
Section.o: Section.cpp
	$(CC) $(CCFLAGS) Section.cpp
clean:
	/bin/rm -f $(OBJS) Tester.o $(EXECS)
