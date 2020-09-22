#include <vector>
#include "graph.h"
#ifndef COLONY_H
#define COLONY_H

class Colony : public Graph{
public:
	static const double init_phero;
	static const double evap_rate;
	static const double alpha;
	static const double beta;
	static const double q;
	static const int ant_time_step = 50;// ant time step iterator
	static double threshold;
	static const double decay_rate;
	double** phero_matrix;
	double** etha_matrix;//heuristic value
	Colony(std::vector<std::vector<int> >, int, int);
	~Colony();
	void move_ants();
	double get_rand() const;
	double calc_prob(int, int) const;
	void update_phero_matrix(double&);
	void update_threshold();
	void reset_at_each_step();
	void run_ACO();
};

// std::vector<std::vector<double> > phero_matrix;
// std::vector< std::vector<Node> > best_tour;// std::vector<Node> Car::tour;
// std::vector<std::vector<std::vector<Node>>> all_tours;

#endif