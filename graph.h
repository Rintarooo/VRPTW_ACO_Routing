#include <vector>

#ifndef GRAPH_H
#define GRAPH_H

class Node{
public:
	int x, y, idx, demand;
	int tw_open, tw_close, unload_time;//tw: time windows
	bool visited;
};

class Car{
public:
	int car_capacity, load, location;
	// double run_distance;// for future work
	// int load_time;//time windows
	std::vector<Node> tour; 
	void add_node(Node*);
	bool ok_capacity(Node);
};

class Route{
public:
	// std::vector<Car> cars;
	// std::vector<Node> nodes;
	// std::vector<std::vector<double>> distance_matrix;
	int car_capacity, num_car, num_node;
	Car* cars;
	Node* nodes;
	double** distance_matrix;
	Route(std::vector<std::vector<int>>, int, int);
	~Route();
	void show_distance_matrix();
	bool is_all_visited();
	void GreedyAlgorithm();
	void show_each_car_tour();
	void show_node_info();
};

#endif