#include "fileloader.h"

void file_loader (const char *filename, 
				std::vector<std::vector<int> > &param, 
				int &car_capacity, int &num_car)
{
	//https://qiita.com/Reed_X1319RAY/items/098596cda78e9c1a6bad
	std::ifstream ifs(filename, std::ios::in);
	if(!ifs.is_open()){
		std::cerr << "Error, cannot open file, check argv: " << filename << std::endl;
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
   	std::cout << line.size() << std::endl;
	   if(66 <= line.size() && line.size() <= 75){
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
