/*
 * function_minimizer_ga.h
 * A simple Genetic Algorithm for minimizing any given mathematical function
 *
 *  Created on: Feb 21, 2017
 *      Author: S.Khan
 */

#ifndef FUNCTION_MINIMIZER_GA_H_
#define FUNCTION_MINIMIZER_GA_H_

#include "ga.h"

using namespace std;
using namespace ga;

/**
 * GENETIC ALGORITHM FOR MINIMIZING MATHEMATICAL FUNCTIONS (function_minimizer_ga)
 * ===============================================================================
 * It currently supports minimization of function with two variables.
 *
 */

/**
 * container for variables x and y
 */
struct function_variables
{
	double x;
	double y;
};

class function_minimizer_ga : public simple_ga<function_variables>
{
public :

	/**
	 * use this constructor when min and max values are same for both variables
	 */
	function_minimizer_ga(double(* a_function) (double x, double y),
			double min_values, double max_values)
	{
		func_to_minimize = a_function;
		init_min_max(min_values, min_values, max_values, max_values);
	}

	/**
	 * for explicitly setting the min and max values of both the variables
	 */
	function_minimizer_ga(double (*a_function)(double x, double y),
			double min_value_x, double min_value_y, double max_value_x, double max_value_y)
	{
		func_to_minimize = a_function;
		init_min_max(min_value_x, min_value_y, max_value_x, max_value_y);
	}

protected:

	/**
	 * a pointer to the function to be minimized
	 */
	double (* func_to_minimize)(double x, double y) = NULL;

	/**
	 * methods that would be overriden from 'simple_ga' class
	 */
	function_variables getRandomIndiv() override;
	double getFitness(const function_variables & indiv) override;
	void displayIndiv(const function_variables & indiv) override;
	function_variables crossOver(const crossoverParents & crossover_parents) override;
	void mutate(function_variables &indiv) override;


	void boundX(function_variables &indiv);
	void boundY(function_variables &indiv);

private:

	// minimum value for x and y
	function_variables VAR_MIN_VALUES;
	// maximum value for x and y
	function_variables VAR_MAX_VALUES;

	// random engine for generating values of x
	mt19937 random_engine_x;
	// random engine for generating values of y
	mt19937 random_engine_y;

	// random engine for generating values of weight for parent1
	mt19937 random_engine_weight_parent1;

	// random engine for making selection of variable for mutation
	mt19937 random_engine_var_selection;
	// random engine for increment in x
	mt19937 random_engine_increment_x;
	// random engine for increment in y
	mt19937 random_engine_increment_y;


	// generate uniformly distributed values for various cases

	// for general purpose between 0 and 1
	uniform_real_distribution<double>
	_uniform_distribution_0_and_1 {0, 1};

	// for x between its min and max value
	uniform_real_distribution<double>
	_uniform_distribution_x;

	// for y between its min and max value
	uniform_real_distribution<double>
	_uniform_distribution_y;

	// for increment in x while mutating
	uniform_real_distribution<double>
	_uniform_distribution_increment_x;

	// for increment in y while mutating
	uniform_real_distribution<double>
	_uniform_distribution_increment_y;


	// for initialization of variables and distributions
	// initialize values dependent on min and max values of variables
	void init_min_max(double min_value_x, double min_value_y,
			double max_value_x, double max_value_y);
};

#endif /* FUNCTION_MINIMIZER_GA_H_ */
