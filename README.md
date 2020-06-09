# C++ implementation VRPTW with ACO and Greedy Algorithm
C++>11 required

## Problem description
Capacitated Vehicle Routing Problem (CVRP) and Vehicle Routing Problem with Time Windows(VRPTW) are briefly explained here(https://developers.google.com/optimization/routing/cvrp), (http://cognitive-robotics17.csail.mit.edu/docs/tutorials/Tutorial10_Multi_vehicle_Routing_with_Time_Windows.pdf).

I implemented 2 types of alogorithm, Ant Colony Optimization and Greedy Algorithm.

## Usage
Run the following command

```make clean && make```

```./main.exe ./Probs/solomon_***/***.txt```

the second argument is text file path

## Acknowledgement
Public benchmark for VRPTW, [Solomon's problem sets](http://w.cba.neu.edu/~msolomon/problems.htm) is obtained from "data" directory in this [repo](https://github.com/DouYishun/vrp-espprc).


![Screen Shot 2020-06-09 at 11 13 32 PM](https://user-images.githubusercontent.com/51239551/84159446-0a2a6680-aaa8-11ea-8249-51f29a33ae3c.png)
