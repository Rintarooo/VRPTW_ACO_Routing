# C++ VRPTW with ACO and Greedy Algorithm
C++11 or later required

## Problem description
Capacitated Vehicle Routing Problem (CVRP) and Vehicle Routing Problem with Time Windows(VRPTW) are briefly explained here  

https://developers.google.com/optimization/routing/cvrp  

http://cognitive-robotics17.csail.mit.edu/docs/tutorials/Tutorial10_Multi_vehicle_Routing_with_Time_Windows.pdf  

I implemented 2 types of alogorithm, Ant Colony Optimization (ACO) and Greedy Algorithm.
  
At each time step, if a calculated total distance is smaller than the minimum distance, the minimum distance would be updated and printed.
  
## Usage
Make sure you've installed CMake and its version above 3.1
  
```cmake --version```
  
Run the following command

```./run.sh```

```build/main.exe probs/solomon_***/***.txt```

Specify text file in the second argument
  
## Acknowledgement
Public benchmark for VRPTW, [Solomon's problem sets](http://w.cba.neu.edu/~msolomon/problems.htm) is obtained from "data" directory in this [repo](https://github.com/DouYishun/vrp-espprc).
  


## Example of Solution
e.g. seek minimum tour length by ACO

![Screen Shot 2020-06-09 at 11 13 32 PM](https://user-images.githubusercontent.com/51239551/84159446-0a2a6680-aaa8-11ea-8249-51f29a33ae3c.png)
