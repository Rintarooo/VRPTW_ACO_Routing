#include <iostream>
#include <vector>
#include <string>
#include <cmath> // sqrt, pow
#include <iomanip> // std::setprecision
#include "graph.h"

void Car::add_node(Node *a)
{
	tour.push_back(*a);
	load += a->demand;
	location = a->idx;
	a->visited = true;
}

bool Car::ok_capacity(Node a)
{
	if(load + a.demand < car_capacity){
		return true;
	}
	else{
		return false;
	}
}

Route::Route(std::vector<std::vector<int>> param,
				int car_capacity, int num_car)
{
	this->car_capacity = car_capacity;
	this->num_car = num_car;
	this->num_node = param.size();//-1 means not counting the depot 

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
		// time windows, cars[i].spped = 1; 
		// bool ok_time , double arrival time = current time + travel time; 
		// {if(tw_open <= arrival time && arrival time + unload_time <= tw_close) return ture;}
		// nodes[i].tw_open = param[i][4];
		// nodes[i].tw_close = param[i][5];
		// nodes[i].unload_time = param[i][6];
	}

	for(int i = 0; i < num_car; i++){
		cars[i].car_capacity = car_capacity;
	}

	distance_matrix = new double* [num_node]; 
	for(int i = 0; i < num_node; i++){
		distance_matrix[i] = new double [num_node];
		for(int j = 0; j < num_node; j++){
			distance_matrix[i][j] = 0;// initialization all elements in a row
		}
	}
	for(int i = 0; i < num_node; i++){
		for(int j = i + 1; j < num_node; j++){
			double dx = nodes[i].x - nodes[j].x;
			double dy = nodes[i].y - nodes[j].y;
			double node_distance = sqrt(pow(dx, 2) + pow(dy, 2));
			distance_matrix[i][j] = distance_matrix[j][i] = node_distance;
		}
	}
}

Route::~Route()
{ 
	std::cout << "call destructor" << std::endl;
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

void Route::show_distance_matrix() const
{
	std::cout << num_node << "*" << num_node << " distance matrix." << std::endl;
	for(int i = 0; i < num_node; i++){
		for(int j = 0; j < num_node; j++){
			std::cout << std::fixed << std::setprecision(1) << distance_matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

bool Route::is_all_visited()
{
	for(int i = 0; i < num_node; i++){
		if(!nodes[i].visited){
			return false;
		}
	}
	return true;
}

void Route::GreedyAlgorithm()
{
	int car_idx = 0;
	while(!is_all_visited()){
		int best_node_idx;
		double min_distance = 100000;
		bool is_return_depot = true;
		
		if(cars[car_idx].tour.empty()){
			cars[car_idx].add_node(&nodes[0]);// nodes[0] is depot
		}

		for(int node_idx = 1; node_idx < num_node; node_idx++){
			if(!nodes[node_idx].visited){
				if(cars[car_idx].ok_capacity(nodes[node_idx])){
					double tmp_distance = distance_matrix[cars[car_idx].location][node_idx];
					if(tmp_distance < min_distance){
						min_distance = tmp_distance;
						is_return_depot = false;
						best_node_idx = node_idx;
					}

				}
			}
		}

		if(!is_return_depot){
			cars[car_idx].add_node(&nodes[best_node_idx]);
		}
		else{
			if(car_idx + 1 < num_car){// check if enough the number of vehicle exists
				if(cars[car_idx].location != 0){// if the vehicle does not return back to the depot
					cars[car_idx].add_node(&nodes[0]);
				}
				car_idx += 1;// assign next vehicle
			}
			else{
				std::cout << "cannot solve for this Greedy algorithm." << std::endl;
				break;// std::exit(0);
			}
			
		}
	}
	if(cars[car_idx].location != 0){// if the vehicle does not return back to the depot
					cars[car_idx].add_node(&nodes[0]);
	}
	std::cout << "algorithm done." << std::endl;
}

void Route::show_each_car_tour() const
{
	for(int i = 0; i < num_car; i++){
		if(!cars[i].tour.empty()){
			std::cout << "vehicle" << i << " tour: ";
			for(int j = 0; j < cars[i].tour.size(); j++){
				std::cout << cars[i].tour[j].idx << " ";
			}
			std::cout << std::endl;
		}
		else{
			std::cout << "vehicle" << i << ": not used" << std::endl;
		}
	}
}

void Route::show_node_info() const
{
	std::cout << "idx,x,y,demand" << std::endl;
	for(int i = 0; i < num_node; i++){
		std::cout << nodes[i].idx << " " << nodes[i].x << " " << nodes[i].y << " " << nodes[i].demand << std::endl;
	}
}