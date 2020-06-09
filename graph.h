#include <vector>
#include <unordered_map>
#include "vehicle.h"
#ifndef GRAPH_H
#define GRAPH_H

class Graph{
public:
	// std::vector<Car> cars;
	// std::vector<Node> nodes;
	// std::vector<std::vector<double>> distance_matrix;
	int num_car, num_node;
	Car* cars;
	Node* nodes;
	double** distance_matrix;
	void calc_node_distance();
	void calc_tour_distance(std::vector<Node>, double&) const;
	Graph(std::vector<std::vector<int> >, int, int);
	virtual ~Graph();
	void show_distance_matrix() const;
	bool is_all_visited() const;
	void run_GreedyAlgorithm();
	void show_each_car_tour() const;
	void show_node_info() const;
};

#endif