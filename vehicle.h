#include <vector>
#ifndef VEHICLE_H
#define VEHICLE_H

class Node{
public:
	int x, y, idx, demand;
	bool visited;
	int tw_open, tw_close, unload_time;//time windows
};

class Car{
public:
	int car_capacity, now_load, now_idx;
	int car_speed, now_time;//time windows
	std::vector <Node> tour; 
	void add_node(Node*, double**);
	bool ok_capacity(Node) const;
	bool ok_time(Node, double**) const;//time windows
};

#endif