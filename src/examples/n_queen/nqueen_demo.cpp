/*
 * nqueen_demo.cpp
 * A Genetic Algorithm demo for solving N-QUEEN problem
 *
 *  Created on: Dec 24, 2016
 *      Author: S.Khan
 *
 */

#include "nqueen_ga.h"

using namespace std;

/**
 * N-QUEEN DEMO
 * ============
 * A demo run for solving N-QUEEN problem with N = 100
 *
 * Tune your parameter settings if you are changing N.
 *
 *
 */

int main()
{
	nqueen_genetic_algo _nqueen_genetic_algo(100);
	_nqueen_genetic_algo.setParameters(100, -1, 0.9, 0.1, 0.03, true);
	_nqueen_genetic_algo.run();
	_nqueen_genetic_algo.displaySettings();
	_nqueen_genetic_algo.displayResults();

	return 0;
}

