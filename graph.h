#include <vector>

#ifndef GRAPH_H
#define GRAPH_H

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

class Route{
public:
	// std::vector<Car> cars;
	// std::vector<Node> nodes;
	// std::vector<std::vector<double>> distance_matrix;
	int num_car, num_node;
	Car* cars;
	Node* nodes;
	double** distance_matrix;
	double calculate_distance(Node, Node) const;
	Route(std::vector<std::vector<int>>, int, int);
	~Route();
	void show_distance_matrix() const;
	bool is_all_visited() const;
	void GreedyAlgorithm();
	void show_each_car_tour() const;
	void show_node_info() const;
};

#endif