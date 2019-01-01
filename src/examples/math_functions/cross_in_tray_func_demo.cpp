/*
 * cross_in_tray_func_demo.cpp
 * A demo for minimizing Cross-In-Tray function
 *
 *  Created on: Feb 21, 2017
 *      Author: S.Khan
 *
 */

#define _USE_MATH_DEFINES

#include "function_minimizer_ga.h"

using namespace std;

/**
 * Cross-In-Tray Function DEMO
 * ===========================
 * A demo run for minimizing Cross-in-Tray function
 * (x, y is in [-10, 10])
 *
 */


/**
 * Cross-In-Tray Function
 *      f(x, y) = -0.0001(|sin(x)sin(y)exp(|100 - (sqrt(x^2 + y^2)/PI)|)| + 1)^0.1
 */
double cross_in_tray_func(double x, double y)
{
	double function_x_y = -0.0001*(
			pow(((abs(sin(x) * sin(y) * exp(abs(100 -
					((sqrt(pow(x, 2) + pow(y, 2))) / M_PI))))) + 1), 0.1));

	return function_x_y;
}


int main()
{
	// set precision for display to 15 decimal places
	cout.precision(15);

	function_minimizer_ga _function_minimizer_ga(&cross_in_tray_func, -10.0, 10.0);
	_function_minimizer_ga.setParameters(100, 1000, 0.65, 0.005, -1, true);
	_function_minimizer_ga.run();
	_function_minimizer_ga.displaySettings();
	_function_minimizer_ga.displayResults();

	// display the actual function value after running GA
	cout<<"===================================="<<endl;
	function_variables best_value = _function_minimizer_ga.getBestSolution();
	cout<<"Cross-In-Tray function minimum value was found at"<<endl
			<<"x = "<<best_value.x<<", y = "<<best_value.y<<endl
			<<"value = "<<cross_in_tray_func(best_value.x, best_value.y)<<endl;

	return 0;
}

