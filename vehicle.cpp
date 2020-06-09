#include <iostream>
#include "vehicle.h"

void Car::add_node(Node *a, double** matrix)
{
	if(!tour.empty()){// though the tour first adds the depot, it doesnt count time 
		now_time += (int)matrix[now_idx][a->idx] / car_speed;
		now_time += a->unload_time;	
	}
	tour.push_back(*a);
	now_load += a->demand;
	now_idx = a->idx;
	a->visited = true;
}

bool Car::ok_capacity(Node a) const
{
	if(now_load + a.demand <= car_capacity){
		return true;
	}
	else{
		return false;
	}
}

bool Car::ok_time(Node a, double** matrix) const
{
	int travel_time = (int)matrix[now_idx][a.idx] / car_speed;
	int arrival_time = now_time + travel_time;
	if(a.tw_open >= arrival_time){// arrive before open
		return false;
	}
	else{
		if(arrival_time + a.unload_time >= a.tw_close){// leave after close
			return false;
		}
		else{
			return true;
		}
	}
}