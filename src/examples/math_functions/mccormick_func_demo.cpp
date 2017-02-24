/*
 * mccormick_func_demo.cpp
 * A demo for minimizing McCormick function
 *
 *  Created on: Feb 22, 2017
 *      Author: S.Khan
 *
 */

#define _USE_MATH_DEFINES

#include "function_minimizer_ga.h"

using namespace std;

/**
 * McCormick Function DEMO
 * =======================
 * A demo run for minimizing McCormick function
 * when x is in [-1.5, 4] and y is in [-3, 4]
 *
 */


/**
 * McCormick Function
 *      f(x, y) = sin(x + y) + (x - y)^2 - 1.5*x + 2.5*y + 1;
 */
double mccormick_func(double x, double y)
{
	return sin(x + y) + pow((x - y), 2) - 1.5*x + 2.5*y + 1;
}


int main()
{
	// set precision for display to 15 decimal places
	cout.precision(15);

	function_minimizer_ga _function_minimizer_ga(&mccormick_func, -1.54, -3, 4, 4);
	_function_minimizer_ga.setParameters(100, 1000, 0.8, 0.03, -1, true);
	_function_minimizer_ga.run();
	_function_minimizer_ga.displaySettings();
	_function_minimizer_ga.displayResults();

	// display the actual function value after running GA
	cout<<"===================================="<<endl;
	function_variables best_value = _function_minimizer_ga.getBestSolution();
	cout<<"McCormick function minimum value was found at"<<endl<<
			"x = "<<best_value.x<<", y = "<<best_value.y<<endl<<
			"value = "<<mccormick_func(best_value.x, best_value.y)<<endl;

	return 0;
}

