#include <iostream>
#include <vector>
#include <string>
#include <cmath> // sqrt, pow
#include <iomanip> // std::setprecision
#include "graph.h"

// double INIT_PHERO = 1;
// double EVAP_RATE = 0.5;
// double ALPHA = 50;
// double BETA = 1;

const double Colony::init_phero = 1;
const double Colony::evap_rate = 0.5;//evaporation
const double Colony::alpha = 50;//prob_next_city
const double Colony::beta = 1;//prob_next_city
const double Colony::q = 1;//update egde pheromone using tour_length

Colony::Colony(std::vector<std::vector<int>> param,
				int car_capacity, int num_car) : Graph(param, car_capacity, num_car)
{
	std::cout << "constructor!!" << std::endl;
	phero_matrix = new double* [num_node]; 
	for(int i = 0; i < num_node; i++){
		phero_matrix[i] = new double [num_node];
		for(int j = 0; j < num_node; j++){
			phero_matrix[i][j] = init_phero;// initialize all elements in a row
		}
	}
}

Colony::~Colony()
{ 
	std::cout << "destructor!!" << std::endl;
	for(int i = 0; i < num_node; i++){
		delete[] phero_matrix[i];
		phero_matrix[i] = nullptr;
	}
	delete[] phero_matrix;
	phero_matrix = nullptr;
}

void Car::add_node(Node *a, double** matrix)
{
	if(!tour.empty()){// though the tour first adds the depot, it doesnt count time 
		now_time += (int)matrix[tour.back().idx][a->idx] / car_speed;
		now_time += a->unload_time;	
	}
	tour.push_back(*a);
	now_load += a->demand;
	now_idx = a->idx;
	a->visited = true;
	
}

bool Car::ok_capacity(Node a) const
{
	if(now_load + a.demand < car_capacity){
		return true;
	}
	else{
		return false;
	}
}

bool Car::ok_time(Node a, double** matrix) const
{
	int travel_time = (int)matrix[tour.back().idx][a.idx] / car_speed;
	int arrival_time = now_time + travel_time;
	if(a.tw_open <= arrival_time && arrival_time + a.unload_time <= a.tw_close){
		return true;
	}
	else{
		return false;
	}
}

void Graph::calculate_node_distance()
{
	for(int i = 0; i < num_node; i++){
		for(int j = i + 1; j < num_node; j++){
			distance_matrix[i][j] = distance_matrix[j][i] = sqrt(pow(nodes[i].x - nodes[j].x, 2) + pow(nodes[i].y - nodes[j].y, 2));
		}
	}
}

Graph::Graph(std::vector<std::vector<int>> param,
				int car_capacity, int num_car)
{
	this->num_car = num_car;
	this->num_node = param.size();//-1 denotes not counting the depot 

	std::cout << "constructor!" << std::endl;
	std::cout << "num_car:" << num_car << " car_capacity:" \
		<< car_capacity << " num_node(depot + customer):" << num_node << std::endl;

	nodes = new Node[num_node];
	cars = new Car[num_car];

	for(int i = 0; i < num_node; i++){
		nodes[i].idx = param[i][0];
		nodes[i].x = param[i][1];
		nodes[i].y = param[i][2];
		nodes[i].demand = param[i][3];
		nodes[i].visited = false;
		//time windows
		nodes[i].tw_open = param[i][4];
		nodes[i].tw_close = param[i][5];
		nodes[i].unload_time = param[i][6];
	}

	for(int i = 0; i < num_car; i++){
		cars[i].car_capacity = car_capacity;
		cars[i].now_load = 0;
		cars[i].now_idx = 0;
		//time windows
		cars[i].car_speed = 1;
		cars[i].now_time = 0;
	}

	distance_matrix = new double* [num_node]; 
	for(int i = 0; i < num_node; i++){
		distance_matrix[i] = new double [num_node];
		for(int j = 0; j < num_node; j++){
			distance_matrix[i][j] = 0;// initialization all elements in a row
		}
	}
	calculate_node_distance();
}

Graph::~Graph()
{ 
	std::cout << "destructor!" << std::endl;
	delete[] nodes;
	nodes = nullptr;
	delete[] cars;
	cars = nullptr;
	for(int i = 0; i < num_node; i++){
		delete[] distance_matrix[i];
		distance_matrix[i] = nullptr;
	}
	delete[] distance_matrix;
	distance_matrix = nullptr;
}

void Graph::show_distance_matrix() const
{
	std::cout << num_node << "*" << num_node << " distance matrix." << std::endl;
	for(int i = 0; i < num_node; i++){
		for(int j = 0; j < num_node; j++){
			std::cout << std::fixed << std::setprecision(1) << distance_matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

bool Graph::is_all_visited() const
{
	for(int i = 0; i < num_node; i++){
		if(!nodes[i].visited){
			return false;
		}
	}
	return true;
}

void Graph::GreedyAlgorithm()
{
	int car_idx = 0;
	while(!is_all_visited()){
		int best_node_idx;
		double min_distance = 100000;
		bool is_return_depot = true;
		
		if(cars[car_idx].tour.empty()){
			cars[car_idx].add_node(&nodes[0], distance_matrix);// nodes[0] is depot
		}

		for(int node_idx = 1; node_idx < num_node; node_idx++){
			if(!nodes[node_idx].visited){
				if(cars[car_idx].ok_capacity(nodes[node_idx])){
					if(cars[car_idx].ok_time(nodes[node_idx], distance_matrix)){
						double tmp_distance = distance_matrix[cars[car_idx].now_idx][node_idx];
						if(tmp_distance < min_distance){
							min_distance = tmp_distance;
							is_return_depot = false;
							best_node_idx = node_idx;
						}
					}
				}
			}
		}

		if(!is_return_depot){
			cars[car_idx].add_node(&nodes[best_node_idx], distance_matrix);
		}
		else{
			if(car_idx + 1 < num_car){// check if enough the number of vehicle exists
				if(cars[car_idx].now_idx != 0){// if the vehicle does not return back to the depot
					cars[car_idx].add_node(&nodes[0], distance_matrix);
				}
				car_idx += 1;// assign next vehicle
			}
			else{
				std::cout << "Cannot solve this by Greedy algorithm." << std::endl;
				break;// std::exit(0);
			}
			
		}
	}//while loop done
	if(cars[car_idx].now_idx != 0){// if the vehicle does not return back to the depot
					cars[car_idx].add_node(&nodes[0], distance_matrix);
	}
	std::cout << "algorithm done." << std::endl;
}

void Graph::calculate_tour_distance(std::vector<Node>tour, double &tour_distance) const
{
	for(int j = 0; j < tour.size(); j++){
		std::cout << tour[j].idx << " ";
		if(j+1 != tour.size()){
			tour_distance += distance_matrix[tour[j].idx][tour[j+1].idx];
		}
	}
	std::cout << " " << std::fixed << std::setprecision(1) << tour_distance << "km";
}

void Graph::show_each_car_tour() const
{
	double total_tour_distance = 0;
	for(int i = 0; i < num_car; i++){
		if(cars[i].tour.size() > 1){
			std::cout << "vehicle" << i << " tour: ";
			double tour_distance = 0;
			calculate_tour_distance(cars[i].tour, tour_distance);
			total_tour_distance += tour_distance;
			std::cout << ", visited customer:" << cars[i].tour.size()-2 << std::endl;
		}
		else{
			std::cout << "vehicle" << i << ": not used" << std::endl;
		}
	}
	std::cout << "total distance:" << std::fixed << std::setprecision(1) << total_tour_distance << "km" << std::endl;
}

void Graph::show_node_info() const
{
	std::cout << std::endl << "idx,x,y,demand,tw_open,tw_close,unload_time" << std::endl;
	for(int i = 0; i < num_node; i++){
		std::cout << nodes[i].idx << " " << nodes[i].x << " " << nodes[i].y << " " << nodes[i].demand << \
			" " << nodes[i].tw_open << " " << nodes[i].tw_close << " " << nodes[i].unload_time << std::endl;
	}
}