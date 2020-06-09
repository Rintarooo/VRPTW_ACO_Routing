#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>
#include <vector>
// #include <stdlib.h>// atoi; cast into int
#include "graph.h"
#include "vehicle.h"
#include "colony.h"

void file_loader (char *filename, 
				std::vector<std::vector<int> > &param, 
				int &car_capacity, int &num_car)
{
	//https://qiita.com/Reed_X1319RAY/items/098596cda78e9c1a6bad
	std::ifstream ifs(filename, std::ios::in);
	if(!ifs){
		std::cout << "File not found, check argv" << std::endl;
		std::exit(1); 
    }
    std::string line;
    for(int i = 0; i < 4; i++){
        std::getline(ifs, line);
    }
    std::getline(ifs, line);
    std::stringstream ss(line);
    ss >> num_car >> car_capacity;
    while (std::getline(ifs, line)){
        //std::cout << line.size() << std::endl;
	    if(line.size() == 72){
		    std::stringstream ss(line);
	        std::vector<int> tmp_vec;
	        int tmp;
	        while (ss >> tmp){
	            tmp_vec.push_back(tmp);
	        }
	        param.push_back(tmp_vec);
	    }
    }
    ifs.close();
}

int main(int argc, char *argv[]){
	if (argc < 2){
		std::cout << "argc should be >= 2" << std::endl;
		exit(0);
	}
	const clock_t start_time = clock();
	std::vector<std::vector<int> > param;
	int car_capacity, num_car;
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
	// colony->show_each_car_tour();
	// colony->show_distance_matrix();
	delete colony;
	colony = nullptr;

	const clock_t end_time = clock();
	std::cout << (end_time - start_time)/ double(CLOCKS_PER_SEC) << "sec" << std::endl;
	return 0;
}
