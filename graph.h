#include <vector>
#include <unordered_map>
#include <map>

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

class Graph{
public:
	// std::vector<Car> cars;
	// std::vector<Node> nodes;
	// std::vector<std::vector<double>> distance_matrix;
	int num_car, num_node;
	Car* cars;
	Node* nodes;
	double** distance_matrix;
	void calculate_node_distance();
	void calculate_tour_distance(std::vector<Node>, double&) const;
	Graph(std::vector<std::vector<int>>, int, int);
	virtual ~Graph();
	void show_distance_matrix() const;
	bool is_all_visited() const;
	void GreedyAlgorithm();
	void show_each_car_tour() const;
	void show_node_info() const;
};

class Colony : public Graph{
public:
	static const double init_phero;
	static const double evap_rate;//evaporation
	static const double alpha;//prob_next_city
	static const double beta;//prob_next_city
	static const double q;//update edge pheromone using tour_length
	double** phero_matrix;
	// std::vector<std::vector<double> > pheromones;
	Colony(std::vector<std::vector<int>>, int, int);
	~Colony();
	double evaporate;
	Node move_ant(Car*);
	void update_pheromone_using_evaporate();
	void update_pheromone_using_tour_length();
	void run();
};

// Node Colony::move_ant(Car* car)
// {


// }

// void Colony::run(){
// 	for (auto car : cars){
// 		auto next_node = move_ant(&car);
// 		if(car.ok_capacity(next_node) && car.ok_time(next_node, distance_matrix)){
// 			add_node(next_node, distance_matrix);
// 		}
// 		else{
// 			pass;
// 		}
// 		if(next_node is None){

// 		}
// 	}
// }

#endif