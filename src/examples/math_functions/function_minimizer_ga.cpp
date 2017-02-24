/*
 * function_minimizer_ga.cpp
 * Implementation of function_minimizer_ga class from "function_minimizer_ga.h"
 *
 *  Created on: Feb 21, 2017
 *      Author: S.Khan
 */
#include "function_minimizer_ga.h"

using namespace std;
using namespace ga;

/**
 * IMPLEMENTATION OF FUNCTION MINIMIZER GA (function_minimizer_ga)
 * ==============================================================
 *
 * FITNESS FUNCTION - Negative of the given function
 *
 * CROSSOVER OPERATOR - randomly weighted average of two parents
 *                     (a random point, between the two points, on the line joining them)
 *
 * MUTATION OPERATOR - increment/decrement a random value
 *                     (random value lies in [-10% of range of variable, +10% of range of variable])
 *
 */

/**
 * generate a random value for each variable between its min and max value
 */
function_variables function_minimizer_ga::getRandomIndiv()
{
	function_variables indiv;
	indiv.x = _uniform_distribution_x(random_engine_x);
	indiv.y = _uniform_distribution_y(random_engine_y);
	return indiv;
}

/**
 * negative of the given function
 *
 */
double function_minimizer_ga::getFitness(const function_variables & indiv)
{
	return -1*(*func_to_minimize)(indiv.x, indiv.y);
}

/**
 * weighted average of values of first and second parent
 * (weight is a random value uniformly distributed between 0 and 1)
 */
function_variables function_minimizer_ga::crossOver(const crossoverParents & crossover_parents)
{
	function_variables crossover_indiv;
	// generate random value for weight of parent1
	double weight_parent1 = _uniform_distribution_0_and_1(random_engine_weight_parent1);

	// weighted average of variable x
	crossover_indiv.x = (weight_parent1)*((function_variables) *crossover_parents.parent1).x
			+ (1 - weight_parent1)*((function_variables) *crossover_parents.parent2).x;
	// weighted average of variable y
	crossover_indiv.y = (weight_parent1)*((function_variables) *crossover_parents.parent1).y
			+ (1 - weight_parent1)*((function_variables) *crossover_parents.parent2).y;

	return crossover_indiv;
}

/**
 * display values of variables
 */
void function_minimizer_ga::displayIndiv(const function_variables & indiv)
{
	cout<<"x = " << indiv.x<<", ";
	cout<<"y = " << indiv.y<<endl;
}

/**
 * with equal probability select x and y
 */
void function_minimizer_ga::mutate(function_variables &indiv)
{
	float select_mutation_var = _uniform_distribution_0_and_1(random_engine_var_selection);

	// with 1/2 probability select x
	if(select_mutation_var <= 0.5)
	{
		indiv.x += _uniform_distribution_increment_x(random_engine_increment_x);
		boundX(indiv);
	}
	// with remaining 1/2 probability select y
	else
	{
		indiv.y += _uniform_distribution_increment_y(random_engine_increment_y);
		boundY(indiv);
	}
}

/**
 * reset x to be in [x min value, x max value]
 *
 */
void function_minimizer_ga::boundX(function_variables & indiv)
{
	// if it is less than x min value, then set it to x min value
	if(indiv.x < VAR_MIN_VALUES.x)
	{
		indiv.x = VAR_MIN_VALUES.x;
	}
	// if it is more than x max value, then set it to x max value
	else if(indiv.x > VAR_MAX_VALUES.x)
	{
		indiv.x = VAR_MAX_VALUES.x;
	}
}

/**
 * reset y to be in [y min value, y max value]
 *
 */
void function_minimizer_ga::boundY(function_variables & indiv)
{
	// if it is less than y min value, then set it to y min value
	if(indiv.y < VAR_MIN_VALUES.y)
	{
		indiv.y = VAR_MIN_VALUES.y;
	}
	// if it is more than y max value, then set it to y max value
	else if(indiv.y > VAR_MAX_VALUES.y)
	{
		indiv.y = VAR_MAX_VALUES.y;
	}
}

/**
 * initialize min and mix value for variables and
 * for uniform distribution generators
 */
void function_minimizer_ga::init_min_max(double min_value_x, double min_value_y,
		double max_value_x, double max_value_y)
{
	// set minimum value for x and y
	VAR_MIN_VALUES.x = min_value_x;
	VAR_MIN_VALUES.y = min_value_y;
	// set maximum value for x and y
	VAR_MAX_VALUES.x = max_value_x;
	VAR_MAX_VALUES.y = max_value_y;

	// uniform distribution of x between its min and max value
	_uniform_distribution_x =
			uniform_real_distribution<double> {min_value_x, max_value_x};
	// uniform distribution of y between its min and max value
	_uniform_distribution_y =
			uniform_real_distribution<double> {min_value_y, max_value_y};

	// multiplication factor 0.1 can be parameterized later
	// step size for x is +- 10% of the total range of x
	double x_increment_size = 0.1*abs(max_value_x - min_value_x);
	_uniform_distribution_increment_x =
			uniform_real_distribution<double> {-x_increment_size, x_increment_size};
	// step size for y is +- 10% of the total range of y
	double y_increment_size = 0.1*abs(max_value_y - min_value_y);
	_uniform_distribution_increment_y =
			uniform_real_distribution<double> {-y_increment_size, y_increment_size};
}
