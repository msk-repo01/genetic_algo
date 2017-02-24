/*
 * schaffer_n4_func_demo.cpp
 * A demo for minimizing Schaffer N.4 function
 *
 *  Created on: Feb 22, 2017
 *      Author: S.Khan
 *
 */

#define _USE_MATH_DEFINES

#include "function_minimizer_ga.h"

using namespace std;

/**
 * Schaffer N.4 Function DEMO
 * ==========================
 * A demo run for minimizing Schaffer N.4 function
 * when x, y both are in [-100, 100]
 *
 */


/**
 * Schaffer N.4 function
 *      f(x, y) = 0.5 + ((((cos(sin(|x^2 - y^2|))^2) - 0.5)) / ((1 + (0.001*(x^2 + y^2)))^2))
 */
double schaffer_n4_func(double x, double y)
{
	double function_x_y = 0.5 + ((pow(cos(sin(abs(pow(x, 2) - pow(y, 2)))), 2) - 0.5) /
			(pow((1 + (0.001*(pow(x, 2) + pow(y, 2)))), 2)));

	return function_x_y;
}


int main()
{
	// set precision for display to 15 decimal places
	cout.precision(15);

	function_minimizer_ga _function_minimizer_ga(&schaffer_n4_func, -100, 100);
	_function_minimizer_ga.setParameters(100, 2000, 0.75, 0.02, -1, true);
	_function_minimizer_ga.run();
	_function_minimizer_ga.displaySettings();
	_function_minimizer_ga.displayResults();

	// display the actual function value after running GA
	cout<<"===================================="<<endl;
	function_variables best_value =
			_function_minimizer_ga.getBestSolution();
	cout<<"Schaffer N.4 function minimum value was found at"<<endl<<
			"x = "<<best_value.x<<", y = "<<best_value.y<<endl<<
			"value = "<<schaffer_n4_func(best_value.x, best_value.y)<<endl;

	return 0;
}

