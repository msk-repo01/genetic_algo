/*
 * nqueen_ga.cpp
 * Implementation of nqueen_genetic_algo class in "nqueen_ga.h"
 *
 *  Created on: Dec 24, 2016
 *      Author: S.Khan
 */

#include "nqueen_ga.h"

using namespace std;
using namespace ga;

/**
 * IMPLEMENTATION OF N-QUEEN GENETIC ALGORITHM (nqueen_genetic_algo)
 * =================================================================
 *
 * FITNESS FUNCTION - Negative of total number of unique conflicts
 *                   (-1 for each unique horizontal/cross conflict)
 *
 * CROSSOVER OPERATOR - 1-Point Order Crossover (see method documentation for more details)
 *
 * MUTATION OPERATOR - Swap Mutation (randomly selected allele is swapped with
 * an allele at one of the conflicting position of the individual)
 *
 * STOPPING CRITERION - a solution is found with no conflict
 *
 */

/**
 * generate random integers between 0 to (N_QUEEN_NUM - 1)
 * for N positions and make sure each integer occurs only once.
 */
vector<int> nqueen_genetic_algo::getRandomIndiv()
{
	vector<int> indiv;
	int position;
	map<int, bool> taken_map;
	for(int i = 0; i < N_QUEEN_NUM; i++)
	{
		do
		{
			position = (int) (rand()%N_QUEEN_NUM);
		}
		while(taken_map[position]);
		indiv.push_back(position);
		taken_map[position] = true;
	}
	return indiv;
}

/**
 * add negative values for horizontal and cross conflicts
 * for each of the allele uniquely
 */
double nqueen_genetic_algo::getFitness(const vector<int> & indiv)
{
	double fitness = 0;
	const int MAX_VALUE = N_QUEEN_NUM - 1;
	for(int i = 0; i < N_QUEEN_NUM; i++)
	{
		for(int j = i - 1; j >= 0; j--)
		{
			int distance_x = i - j;
			// check for horizontal conflict
			if((indiv[j] == indiv[i]) ||
					// check for cross conflict from top
					// and make sure it does not lie outside the board
					(indiv[j] == indiv[i] - distance_x && indiv[j] >= 0) ||
					// check for cross conflict from below
					// and make sure it does not lie outside the board
					(indiv[j] == indiv[i] + distance_x && indiv[j] <= MAX_VALUE))
			{
				fitness -= 1;
			}
		}
	}
	return fitness;
}

/**
 * do one point order crossover
 */
vector<int> nqueen_genetic_algo::crossOver(const crossoverParents & crossover_parents)
{
	return onePointOrderCrossover(crossover_parents);
}

/**
 * 1-POINT ORDER CROSSOVER
 * =======================
 *
 * parent1  : a b c d e f g h i j
 * parent2  : d g b a i c j e f h
 *
 * create offspring by following the steps described below:
 * --------------------------------------------------------
 *
 * STEP 1 - select a random point P1
 *
 * parent1  : a b c | d e f g h i j
 * parent2  : d g b | a i c j e f h
 *                  P1
 *
 *
 * STEP 2 - copy values of parent1 till point P1
 *
 * parent1  : a b c | d e f g h i j
 * parent2  : d g b | a i c j e f h
 * --------------------------------
 * offspring: a b c | x x x x x x x
 *
 *
 * STEP 3 - copy remaining values of parent2 and
 * leave the position unassigned if the value was already added
 *
 * parent1  : a b c | d e f g h i j
 * parent2  : d g b | a i c j e f h
 * --------------------------------
 * offspring: a b c | - i - j e f h
 *
 *
 * STEP 4 - fill unassigned positions with remaining values of parent2
 * in the order they appear in parent2
 *
 * parent1  : a b c | d e f g h i j
 * parent2  : d g b | a i c j e f h
 * --------------------------------
 * offspring: a b c | d i g j e f h
 *                    ^   ^
 *
 * The offspring created from two parents
 *
 * parent1  : a b c d e f g h i j
 * parent2  : d g b a i c j e f h
 *
 * offspring: a b c d i g j e f h
 *
 */
vector<int> nqueen_genetic_algo::onePointOrderCrossover(const crossoverParents & crossoverParents)
{
	// first shuffle parent1 and parent2 to remove any bias
	// (specially for individuals with large number of allele)
	vector<int> parent1, parent2;
	if(_uniform_float_distribution(random_engine_shuffle) < 0.5f)
	{
		parent1 = (vector<int>) *crossoverParents.parent1;
		parent2 = (vector<int>) *crossoverParents.parent2;
	}
	else
	{
		parent1 = (vector<int>) *crossoverParents.parent2;
		parent2 = (vector<int>) *crossoverParents.parent1;
	}

	int crossover_point1 = _uniform_distribution_crossover_pt(random_engine_crossover_pt1);

	vector<int> indiv(N_QUEEN_NUM);
	map<int, bool> assigned_map;
	int ith_value;
	for(int i = 0; i < crossover_point1; i++)
	{
		ith_value = parent1[i];
		indiv[i] = ith_value;
		assigned_map[ith_value] = true;
	}

	// copy from parent2 with no repetition
	vector<int> unassigned_positions;
	for(int i = crossover_point1; i < N_QUEEN_NUM; i++)
	{
		ith_value = parent2[i];
		if(assigned_map[ith_value])
		{
			// value at this position is already assigned
			// so leave this position and
			// store it as an unassigned position
			unassigned_positions.push_back(i);
		}
		else
		{
			indiv[i] = ith_value;
			assigned_map[ith_value] = true;
		}
	}

	// find out the unassigned values of parent2
	vector<int> unassigned_values;
	for(int value_parent2 : parent2)
	{
		if(!assigned_map[value_parent2])
		{
			unassigned_values.push_back(value_parent2);
		}
	}

	if(unassigned_positions.size() != unassigned_values.size())
	{
		cerr<<"error in crossover, returning one of the parent - "
				<<"something went wrong, unassigned values do not fit "
				" exactly in remaining unassigned positions - "
				<<unassigned_values.size()<<" => "<<unassigned_positions.size();

		// no crossover can be done further, so return parent1
		return parent1;
	}

	// fill remaining values to unassigned positions
	for(int unassigned_position : unassigned_positions)
	{
		// take unassigned values from beginning in parent2
		indiv[unassigned_position] = unassigned_values.front();
		unassigned_values.erase(unassigned_values.begin());
	}

	return indiv;
}

/**
 * display integers in the vector
 */
void nqueen_genetic_algo::displayIndiv(const vector<int> & indiv)
{
	for(int position : indiv)
	{
		cout<<position<<" ";
	}
	cout<<endl;
}

/**
 * stop when a solution is found with no conflict
 */
bool nqueen_genetic_algo::shouldStop()
{
	return best_fitness >= 0;
}

/**
 * swap a random allele with a conflicting position
 */
void nqueen_genetic_algo::mutate(vector<int> &indiv)
{
	vector<int> conflicting_positions = getConflictingPositions(indiv);
	int total_conflicts;
	for(int i = 0; i < N_QUEEN_NUM; i++)
	{
		if(_uniform_double_distribution(random_engine_allele_mutation)
				< ALLELE_MUTATION_PROBABILITY)
		{
			total_conflicts = conflicting_positions.size();
			if(total_conflicts > 0)
			{
				int jth_random = rand()%total_conflicts;
				int conflict_position = conflicting_positions[jth_random];

				// swap conflict position value with this value
				int temp_value = indiv[i];
				indiv[i] = indiv[conflict_position];
				indiv[conflict_position] = temp_value;

				// remove this conflicting position
				conflicting_positions.erase(conflicting_positions.begin() + jth_random);
			}
		}
	}
}

vector<int> nqueen_genetic_algo::getConflictingPositions(const vector<int> & indiv)
{
	vector<int> conflicting_positions;
	int distance_x;
	const int MAX_VALUE = N_QUEEN_NUM - 1;
	for(int i = 0; i < N_QUEEN_NUM; i++)
	{
		for(int j = i - 1; j >= 0; j--)
		{
			distance_x = i - j;
			// check for horizontal conflict
			if((indiv[j] == indiv[i]) ||
					// check for cross conflict from top
					// and make sure it does not lie outside the board
					(indiv[j] == indiv[i] - distance_x && indiv[j] >= 0) ||
					// check for cross conflict from below
					// and make sure it does not lie outside the board
					(indiv[j] == indiv[i] + distance_x && indiv[j] <= MAX_VALUE))
			{
				conflicting_positions.push_back(i);
			}
		}
	}
	return conflicting_positions;
}
