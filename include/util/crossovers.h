/*
 * crossovers.h
 * Commonly used crossover operators
 *
 *  Created on: Dec 30, 2016
 *      Author: S.Khan
 */

#ifndef CROSSOVERS_H_
#define CROSSOVERS_H_

#include <vector>
#include "ga.h"

using namespace std;

namespace ga
{
/**
 * 1-POINT CROSSOVER
 * ===================
 * create a new offspring by :
 * copying allele of one parent to a randomly selected point,
 * and copying rest of the alleles from another parent
 *
 */
template<typename T>
vector<T> onePointCrossover(const vector<T> & parent1, const vector<T> & parent2);


/**
 * 2-POINT CROSSOVER
 * ===================
 * create a new offspring by :
 * selecting two random points,
 * and copying allele of one parent from first to second randomly selected point,
 * and copying rest of the alleles from another parent
 *
 */
template<typename T>
vector<T> twoPointCrossover(const vector<T> & parent1, const vector<T> & parent2);


/**
 * IMPLEMENTATION OF CROSSOVERS
 * ============================
 */

template<typename T>
vector<T> onePointCrossover(const vector<T> & parent1, const vector<T> & parent2)
{
	if(parent1.size() > 1 && parent1.size() == parent2.size())
	{
		const int TOTAL_LENGTH = parent1.size();

		// shuffle between first and second parent
		// to remove any bias (specially for individuals with large number of allele)
		static mt19937 random_engine_shuffle;
		static uniform_real_distribution<float> distrib_shuffle(0.0, 1.0);
		vector<int> temp_parent;
		if(distrib_shuffle(random_engine_shuffle) < 0.5f)
		{
			temp_parent = parent1;
			parent1 = parent2;
			parent2 = temp_parent;
		}

		// crossover point 1 engine generator
		static mt19937 random_engine_point1(1);
		static uniform_int_distribution<int> distrib1(1, TOTAL_LENGTH - 1);
		int crossover_point1 = distrib1(random_engine_point1);

		vector<T> indiv(TOTAL_LENGTH);
		for(int i = 0; i < crossover_point1; i++)
		{
			indiv[i] = parent1[i];
		}

		for(int i = crossover_point1; i < TOTAL_LENGTH; i++)
		{
			indiv[i] = parent2[i];
		}

		return indiv;
	}
	else
	{
		cerr<<"cannot perform one point crossover with sizes - "
				<<parent1.size()<<", "<<parent2.size()<<endl;
		return parent1;
	}
}

template<typename T>
vector<T> twoPointCrossover(const vector<T> & parent1, const vector<T> & parent2)
{
	if(parent1.size() > 2 && parent1.size() == parent2.size())
	{
		const int TOTAL_LENGTH = parent1.size();

		// shuffle between first and second parent
		// to remove any bias for individuals specially with large number of allele
		static mt19937 random_engine_shuffle;
		static uniform_real_distribution<float> distrib_shuffle(0.0, 1.0);
		vector<int> temp_parent;
		if(distrib_shuffle(random_engine_shuffle) < 0.5f)
		{
			temp_parent = parent1;
			parent1 = parent2;
			parent2 = temp_parent;
		}

		// crossover point 1 engine generator
		static mt19937 random_engine_point1(1);
		static uniform_int_distribution<int> distrib1(1, TOTAL_LENGTH - 2);
		int crossover_point1 = distrib1(random_engine_point1);

		// crossover point 2 engine generator
		static mt19937 random_engine_point2(2);
		static uniform_int_distribution<int> distrib2(2, TOTAL_LENGTH - 1);
		int crossover_point2 = distrib2(random_engine_point2);
		/*
			if(crossover_point1 == crossover_point2)
			{
				// ignore this case
			}
			else
		 */
		if(crossover_point1 > crossover_point2)
		{
			int temp_value = crossover_point1;
			crossover_point1 = crossover_point2;
			crossover_point2 = temp_value;
		}

		vector<T> indiv(TOTAL_LENGTH);
		for(int i = 0; i < crossover_point1; i++)
		{
			indiv[i] = parent1[i];
		}

		for(int i = crossover_point1; i < crossover_point2; i++)
		{
			indiv[i] = parent2[i];
		}

		for(int i = crossover_point2; i < TOTAL_LENGTH; i++)
		{
			indiv[i] = parent1[i];
		}

		return indiv;
	}
	else
	{
		cerr<<"cannot perform two point crossover with sizes - "
				<<parent1.size()<<", "<<parent2.size()<<endl;
		return parent1;
	}
}
}

#endif /* CROSSOVERS_H_ */
