#include <iostream>
#include <vector>
#include <random> // rand_dev
#include <algorithm> // std::max_element
#include "colony.h"

// https://qiita.com/ganariya/items/25824f1502478a673005	
const double Colony::init_phero = 1.0;// initilaize pheromone
const double Colony::evap_rate = 0.9;// evaporate when pheromone updates
const double Colony::alpha = 3.0;// prob_next_city
const double Colony::beta = 5.0;// prob_next_city
const double Colony::q = 1.0;// divided by tour length
double Colony::threshold = 0.5;// whether choose random or follow phero
const double Colony::decay_rate = 0.95;	
double INFIN = 100000;


void Colony::run_ACO()
{
	double min_distance = INFIN;
	for(int i = 0; i < ant_time_step; i++){
		std::cout << std::endl << "time step: " << i << std::endl;
		move_ants();
		double total_tour_distance = 0.0;
		update_phero_matrix(total_tour_distance);
		if (total_tour_distance < min_distance){
			min_distance = total_tour_distance;
			show_each_car_tour();
		}
		update_threshold();
		reset_at_each_step();
	}
}


void Colony::reset_at_each_step()
{
	for (int i = 0; i < num_car; i++){
		cars[i].tour.clear();
		cars[i].now_load = 0;
		cars[i].now_idx = 0;
		cars[i].now_time = 0;
	}
	for (int i = 0; i < num_node; i++){
		nodes[i].visited = false;
	}
}

void Colony::update_threshold()
{
	threshold *= decay_rate;
}

void Colony::update_phero_matrix(double &total_tour_distance)
{
	for (int i = 0; i < num_car; i++){
		double tour_distance = 0.0;
		calc_tour_distance(cars[i].tour, tour_distance);
		total_tour_distance += tour_distance;
		for (int j = 0; j < cars[i].tour.size(); j++){
			if(j+1 != cars[i].tour.size()){
				phero_matrix[cars[i].tour[j].idx][cars[i].tour[j+1].idx] = evap_rate * phero_matrix[cars[i].tour[j].idx][cars[i].tour[j+1].idx] + q / tour_distance;
			} 
		}
	}
}

void Colony::move_ants()
{
	int car_idx = 0;
	while(!is_all_visited()){
		if(cars[car_idx].tour.empty()){
			cars[car_idx].add_node(&nodes[0], distance_matrix);// nodes[0] denotes depot
		}
		std::vector< std::pair<int, int> > feasible_edges;
		feasible_edges.clear();
		while (feasible_edges.empty() && cars[car_idx].now_time <= 1200){
			for(int node_idx = 1; node_idx < num_node; node_idx++){
				if(!nodes[node_idx].visited){
					if(cars[car_idx].ok_capacity(nodes[node_idx])){
						if(cars[car_idx].ok_time(nodes[node_idx], distance_matrix)){
							feasible_edges.push_back(std::make_pair(cars[car_idx].now_idx, node_idx));
						}
					}
				}
			}
			if(feasible_edges.empty()){
				cars[car_idx].now_time += 30;// wait for the tw_open at the depot
			}
		}
		
		if(feasible_edges.empty()){// if still edges are not found, return depot
			if(car_idx + 1 < num_car){// check if the rest of vehicles exists
				if(cars[car_idx].now_idx != 0){// in case the vehicle did not return back to the depot
					cars[car_idx].add_node(&nodes[0], distance_matrix);
				}
				car_idx += 1;// assign next vehicle			
			}
			else{
				std::cout << "cannot visit all customers this step." << std::endl;
				break;
			}
		}
		else{
			int next_node_idx;
			if (get_rand() < threshold){// choose randomly next node, this prevents local optimization
				next_node_idx = feasible_edges[rand() % feasible_edges.size()].second;
			}
			else{// follow heuristc and pheromone formula, choose next node
				std::vector<double> ups, probs, cumulative_sum;
				double sum = 0.0;
				for (auto feasible_edge : feasible_edges){
					double up = calc_prob(feasible_edge.first, feasible_edge.second);
					sum += up;
					ups.push_back(up);
				}
				for (auto up : ups){
					probs.push_back(up / sum);
				}
				cumulative_sum.push_back(probs.front());
				for (int i = 0; i < probs.size() - 1; i ++){
					probs[i+1] += probs[i];
					cumulative_sum.push_back(probs[i+1]);
				}
				int candi_idx, best_idx;
				double candi_v;
				double best_v = INFIN;
				double r = get_rand();
				for (int x = 0; x < cumulative_sum.size(); x++){
					if (r <= cumulative_sum[x]){
						candi_idx = x;
						candi_v = cumulative_sum[x];
						if (candi_v < best_v){
							best_idx = candi_idx;
							best_v = candi_v;
						}
					}
				}
				if (best_v == INFIN){
						break;
				}
				next_node_idx = feasible_edges[best_idx].second;
				
				// search algorithm
				// double rand = get_rand();
				// // std::sort(cumulative_sum.begin(), cumulative_sum.end());
				// for (auto itr = cumulative_sum.begin(); itr != cumulative_sum.end(); itr++){
				// 	if (rand_num < *itr){
				// 		int next_node_idx = itr;
				// 		break;
				// 	}
				// }
				// auto iter = std::max_element(cumulative_sum.begin(), cumulative_sum.end());
				// next_node_idx = std::distance(cumulative_sum.begin(), iter);// https://teramonagi.hatenablog.com/entry/20130225/1361793892
			}
			cars[car_idx].add_node(&nodes[next_node_idx], distance_matrix);
		}
	}// while loop done
	if(cars[car_idx].now_idx != 0){// in case the vehicle did not return back to the depot
		cars[car_idx].add_node(&nodes[0], distance_matrix);
	}
}

double Colony::calc_prob(int now_node_idx, int next_node_idx) const
{
	double ETAij = pow (etha_matrix[now_node_idx][next_node_idx], beta);
	double TAUij = pow (phero_matrix[now_node_idx][next_node_idx], alpha);
	return ETAij * TAUij;
}


double Colony::get_rand() const
{
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<double> distr(0, 1);
    return distr(generator);
}

Colony::Colony(std::vector<std::vector<int> > param,
				int car_capacity, int num_car) : Graph(param, car_capacity, num_car)
{
	std::cout << "constructor!!" << std::endl;
	phero_matrix = new double* [num_node];
	etha_matrix = new double* [num_node]; 
	for(int i = 0; i < num_node; i++){
		phero_matrix[i] = new double [num_node];
		etha_matrix[i] = new double [num_node];
		for(int j = 0; j < num_node; j++){
			phero_matrix[i][j] = 0;// initialize all elements in a row
			etha_matrix[i][j] = 0;
		}
	}
	for(int i = 0; i < num_node; i++){
		for(int j = i + 1; j < num_node; j++){
			phero_matrix[i][j] = phero_matrix[j][i] = init_phero;
			etha_matrix[i][j] = etha_matrix[j][i] = q / distance_matrix[i][j];
		}
	}
}

Colony::~Colony()
{ 
	std::cout << "destructor!!" << std::endl;
	for(int i = 0; i < num_node; i++){
		delete[] phero_matrix[i];
		phero_matrix[i] = nullptr;
		delete[] etha_matrix[i];
		etha_matrix[i] = nullptr;
	}
	delete[] phero_matrix;
	phero_matrix = nullptr;
	delete[] etha_matrix;
	etha_matrix = nullptr;
}
