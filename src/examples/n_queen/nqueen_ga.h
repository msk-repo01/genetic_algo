/*
 * nqueen_ga.h
 * A simple Genetic Algorithm for N-QUEEN problem
 *
 *  Created on: Dec 24, 2016
 *      Author: S.Khan
 */

#ifndef NQUEEN_GA_H_
#define NQUEEN_GA_H_

# include "ga.h"

using namespace std;
using namespace ga;

/**
 * A SIMPLE GENETIC ALGORITHM FOR N-QUEEN PROBLEM (nqueen_genetic_algo)
 * ====================================================================
 * REPRESENTATION - A vector of integers from 0 to N_QUEEN_NUM - 1 (each integer
 * occurring only once). An integer represents the row number(0-based) and the
 * position of this integer in the vector represents the column number(0-based)
 * of a queen.
 * Note - rows and column numbers are 0-based
 * Example for N = 4 :  a vector {2, 0, 3, 1} would mean :
 * First queen is in 2nd row , 0th column
 * Second queen is in 0th row, 1st column
 * Third queen is in 3rd row , 3rd column
 * Fourth queen is in 1st row, 4th column
 *
 * vector {2, 0, 3, 1} is shown below :
 *
 * 		|	| x	|	|	|
 * 		|	|	|	| x	|
 * 		| x	|	|	|	|
 * 		|	|	| x	|	|
 *
 *
 * CONSTRUCTOR - set the value of N in N-Queen problem.
 *               The default value is set to 100.
 *
 */

class nqueen_genetic_algo : public simple_ga<vector<int>>
{
public :
	explicit nqueen_genetic_algo(int n_queen_number)
	{
		if(n_queen_number < 4) // show error message and set to default
		{
			cerr<<"error invalid value of N : "<<n_queen_number<<
					" (solutions may not exist for N < 4 in N-queen problem)"<<endl<<
					"keeping default value of N : "<<N_QUEEN_NUM<<endl;
		}
		else
		{
			N_QUEEN_NUM = n_queen_number;
			// reset crossover point distribution
			_uniform_distribution_crossover_pt =
				uniform_int_distribution<int>(1, N_QUEEN_NUM - 1);
		}
	}

protected:
	vector<int> getRandomIndiv() override;
	double getFitness(const vector<int> & indiv) override;
	void displayIndiv(const vector<int> & indiv) override;
	vector<int> crossOver(const crossoverParents & crossover_parents) override;
	void mutate(vector<int> &indiv) override;
	bool shouldStop() override;

private:

	/**
	 * value of N for N-Queen problem
	 */
	int N_QUEEN_NUM = 100;

	// shuffle random engine
	mt19937 random_engine_shuffle;
	// allele mutation random engine
	mt19937 random_engine_allele_mutation;
	// crossover point 1 random engine
	mt19937 random_engine_crossover_pt1 {1};

	// generate uniformly distribution values
	// for float value between 0 and 1
	uniform_real_distribution<float> _uniform_float_distribution {0.0, 1.0};
	// for double value between 0 and 1
	uniform_real_distribution<double> _uniform_double_distribution {0.0, 1.0};
	// for integer value between 1 and NQUEEN_NUM - 1
	uniform_int_distribution<int> _uniform_distribution_crossover_pt {1, N_QUEEN_NUM - 1};

	vector<int> getConflictingPositions(const vector<int> & indiv);
	vector<int> onePointOrderCrossover(const crossoverParents & crossoverParents);
};

#endif /* NQUEEN_GA_H_ */
