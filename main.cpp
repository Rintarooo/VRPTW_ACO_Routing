#include <iostream>
#include <ctime>
// #include <string>
#include <vector>
// #include <stdlib.h>// atoi; cast into int
#include "graph.h"
#include "vehicle.h"
#include "colony.h"
#include "fileloader.h"


int main(int argc, char *argv[]){
	if (argc < 2){
		std::cout << "argc should be >= 2" << std::endl;
		exit(0);
	}
	const clock_t start_time = clock();
	std::vector<std::vector<int> > param;
	int car_capacity, num_car;
	car_capacity=0;
	num_car=0;
	file_loader(argv[1], param, car_capacity, num_car);
	
	// Graph* graph = new Graph(param, car_capacity, num_car);
	// graph->run_GreedyAlgorithm();
	// graph->show_each_car_tour();
	// graph->show_node_info();
	// graph->show_distance_matrix();
	// delete graph;
	// graph = nullptr;
	
	Colony* colony = new Colony(param, car_capacity, num_car);
	colony->run_ACO();
	// colony->show_distance_matrix();
	delete colony;
	colony = nullptr;

	const clock_t end_time = clock();
	std::cout << (end_time - start_time)/ double(CLOCKS_PER_SEC) << "sec" << std::endl;
	return 0;
}
