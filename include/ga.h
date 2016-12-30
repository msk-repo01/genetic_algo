/*
 * ga.h
 * A simple Genetic Algorithm to evolve solutions for a given problem.
 *
 *  Created on: Dec 24, 2016
 *      Author: S.Khan
 *
 */

#ifndef GA_H_
#define GA_H_

#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <float.h>

using namespace std;

namespace ga
{

/**
 * SIMPLE GENETIC ALGORITHM (simple_ga)
 * ====================================
 * It is a simple Genetic Algorithm (GA) written as a generic class with type parameter T.
 * Type parameter T is the type used to represent an individual that GA would evolve.
 * In most cases a vector of int would represent an individual and T would be "vector<int>".
 * Note :- Some methods in GA are specific to type parameter T and are left
 * as pure virtual methods to be implemented when T is defined. For example, generating
 * a random individual of type T cannot be implemented without knowing T.
 *
 * FUNCTION MAXIMIZATION
 * It works on fitness maximization of individual (that represents a solution for the problem).
 * Problems that would find a minima, should use a negative value of fitness and invert it.
 *
 * PARENT SELECTION
 * It uses a Roulette Wheel Selection for selecting parents for crossover.
 *
 * MUTATION OPERATION
 * Mutation is done stochastically at two levels :
 * 1. Individual mutation probability - probability with which an individual is selected for mutation
 * 2. Allele mutation probability - posterior probability with which an allele is selected in
 * selected individual for mutation
 *
 * ELITISM - is true by default.
 *
 * STOPPING CRITERION - when GA has run for set maximum number of generations.
 * This criterion can be overriden in a derived class. Examples of other criteria are :
 * Elapsed time or average fitness compared to best fitness.
 *
 */

/**
 * --- PURE VIRTUAL METHODS TO IMPLEMENT ---
 * =========================================
 * Following methods must be implemented in derived class after parameter instantiation:
 * 1. T getRandomIndiv() - generate a random individual
 * 2. void displayIndiv(const T indiv) - display an individual
 * 3. double getFitness(const T indiv) - get fitness of an individual
 * 4. T crossOver(const crossoverParents crossoverParents) - create an offspring from two parents
 * 5. void mutate(T & indiv) - mutate an individual
 *
 * *** Additionally, method that can optionally be overridden ***
 * 6. bool shouldStop() - stopping criteria for the GA
 *
 */
template <typename T>
class simple_ga
{
public :
	/**
	 * optional method for changing default parameter settings
	 */
	void setParameters(int population_size, int max_num_generations,
			double crossover_prob, double mutation_prob,
			double allele_mutation_prob, bool elitism);

	/**
	 * displays current parameter settings
	 */
	void displaySettings();

	/**
	 * run genetic algorithm
	 */
	void run();

	/**
	 * displays results after GA run
	 */
	void displayResults();

	/**
	 * returns current number of generations
	 */
	int getNumOfGenerations()
	{
		return num_of_generations;
	}

	/**
	 * returns the best individual known so far
	 */
	T getBestSolution()
	{
		return best_individual;
	}

	/**
	 * returns the best fitness known so far
	 */
	double getBestFitness()
	{
		return best_fitness;
	}

protected:
	size_t POPULATION_SIZE = 100;
	int MAX_NUM_OF_GENERATIONS = 1000;

	double CROSSOVER_PROBABILITY = 0.8;
	double MUTATION_PROBABILITY = 0.1;
	double ALLELE_MUTATION_PROBABILITY = 0.1;

	bool ELITISM = true;

	struct crossoverParents
	{
		const T * parent1 = NULL;
		const T * parent2 = NULL;
	};

	vector<T> population;
	map<const T *, double> fitness_map;
	map<const T *, double> cumulative_map;

	int num_of_generations = -1;

	// best known so far
	T best_individual;
	double best_fitness = - DBL_MAX;

	// current generation best fitness
	T gen_best_individual;
	double gen_best_fitness = - DBL_MAX;

	// current generation minimum fitness
	T * gen_min_fit_indivP = NULL;
	double gen_min_fitness = DBL_MAX;

	double avg_fitness = 0;
	double fitness_sum = 0;

	void initializeRandomPopulation();
	void copyNextGeneration(T * new_indivP);
	void updateCurrentGenMinMaxFitness(T * indivP, double t_fitness);
	bool resetCumulativeMap();

	crossoverParents selectCrossOverParents();
	T * selectAParent(const T * already_selectedP);
	T * rouletteWheelSelection(const T * already_selectedP);
	T * selectSimilarFit(const T * indivP);

	void tryMutation(T & indiv);

	/**
	 * defines the stopping criteria for genetic algorithm.
	 * This method can optionally be overridden.
	 */
	virtual bool shouldStop()
	{
		return num_of_generations >= MAX_NUM_OF_GENERATIONS;
	}

	/**
	 * --- METHODS TO OVERRIDE IN DERIVED CLASS ---
	 * --------------------------------------------
	 */
	// generate a random individual of type T
	virtual T getRandomIndiv() = 0;
	// display individual of type T
	virtual void displayIndiv(const T & indiv) = 0;
	// calculate fitness for individual (implement fitness function)
	virtual double getFitness(const T & indiv) = 0;
	// crossover operation to generate an individual of type T
	virtual T crossOver(const crossoverParents & crossoverParents) = 0;
	// mutation operation on individual of type T
	virtual void mutate(T & indiv) = 0;

	// optional destructor
	virtual ~simple_ga() {};

private:

	// Roulette wheel random engine
	mt19937 roulette_random_engine;
	// crossover random engine
	mt19937 crossover_random_engine;
	// individual mutation random engine
	mt19937 mutation_random_engine;
	// generate uniformly distributed double value between 0 and 1
	uniform_real_distribution<double> _uniform_distribution{0, 1};
};

/**
 * IMPLEMENTATION OF METHODS OF CLASS "simple_ga<T>"
 * =================================================
 */

/**
 * An optional method to change default parameter settings
 */
template<typename T>
void simple_ga<T>::setParameters(int population_size, int max_num_generations,
		double crossover_prob, double mutation_prob,
		double allele_mutation_prob, bool elitism)
{
	if(population_size >= 2)
	{
		if(population_size == 2)
			cerr<<"warning population size : "<<population_size<<
			" Roulette wheel selection would not work properly for size < 3"<<endl;

		POPULATION_SIZE = population_size;
	}
	else
	{
		cerr<<"error population size : "<<population_size<<" (size < 2 is not allowed)."
				<<" setting it to default size "<<POPULATION_SIZE<<endl;
	}

	MAX_NUM_OF_GENERATIONS = max_num_generations;
	CROSSOVER_PROBABILITY = crossover_prob;
	MUTATION_PROBABILITY = mutation_prob;
	ALLELE_MUTATION_PROBABILITY = allele_mutation_prob;
	ELITISM = elitism;
}

/**
 * It displays parameter settings
 */
template<typename T>
void simple_ga<T>::displaySettings()
{
	cout<<"**********G A Settings*************"<<endl;
	cout<<"POPULATION_SIZE - "<<POPULATION_SIZE<<endl;
	cout<<"MAX_NUM_OF_GENERATIONS - "<<MAX_NUM_OF_GENERATIONS<<endl;
	cout<<"CROSSOVER_PROBABILITY - "<<CROSSOVER_PROBABILITY<<endl;
	cout<<"ELITISM ON(1)/OFF(0) - "<<ELITISM<<endl;
	cout<<"MUTATION_PROBABILITY - "<<MUTATION_PROBABILITY<<endl;
	cout<<"ALLELE_MUTATION_PROBABILITY - "<<ALLELE_MUTATION_PROBABILITY<<endl;
	cout<<"***********************************"<<endl;
}

/**
 * It runs GA with set prameter values
 */
template<typename T>
void simple_ga<T>::run()
{
	initializeRandomPopulation();

	// atleast 2 indiv required
	if(population.size() < 2)
	{
		cerr<<"error cannot perform GA for population size < 2"<<endl;
		return;
	}

	num_of_generations = 0;
	T * new_indivP = NULL;
	vector<T> next_gen_population(POPULATION_SIZE);
	while(!shouldStop())
	{
		// create new individuals for next generation
		new_indivP = &next_gen_population[0];
		for(size_t i = 0; i < POPULATION_SIZE; i++)
		{
			*new_indivP = _uniform_distribution(crossover_random_engine) <= CROSSOVER_PROBABILITY
					? crossOver(selectCrossOverParents()) : population[i];

			tryMutation(*new_indivP);

			new_indivP++;
		}

		// copy new individuals as current population
		// and update fitness values
		copyNextGeneration(&next_gen_population[0]);

		num_of_generations++;

		// display best fitness for each generation
		cout<<"generation : "<<num_of_generations
				<<" best fitness : "<<best_fitness<<endl;
	}
}

template<typename T>
void simple_ga<T>::initializeRandomPopulation()
{
	T indiv;
	cout<<"generating random individuals.."<<endl;
	for(size_t i = 0 ; i < POPULATION_SIZE; i++)
	{
		indiv = getRandomIndiv();
		population.push_back(indiv);
		this->displayIndiv(indiv);
	}

	fitness_sum = 0;
	// initialize best and min fitness for this generation
	gen_best_fitness = - DBL_MAX;
	gen_min_fitness = DBL_MAX;
	double t_fitness;
	T * indivP = &population[0];
	for(size_t i = 0; i < POPULATION_SIZE; i++)
	{
		indiv = *indivP;
		t_fitness = getFitness(indiv);
		fitness_map.insert(pair<T*, double>(indivP, t_fitness));
		fitness_sum += t_fitness;
		updateCurrentGenMinMaxFitness(indivP, t_fitness);
		indivP++;
	}

	best_fitness = gen_best_fitness;
	best_individual = gen_best_individual;
	avg_fitness = (double) fitness_sum/POPULATION_SIZE;

	// set the cumulative fitness map
	resetCumulativeMap();
}

template<typename T>
void simple_ga<T>::copyNextGeneration(T * new_indivP)
{
	// store last generation best fitness
	double prev_best_fitness = gen_best_fitness;
	T prev_best_individual = gen_best_individual;

	fitness_sum = 0;
	// initialize best and min fitness for this generation
	gen_best_fitness = - DBL_MAX;
	gen_min_fitness = DBL_MAX;

	double t_fitness;
	T * indivP = &population[0];
	for(size_t i = 0; i < POPULATION_SIZE; i++)
	{
		*indivP = *new_indivP;
		t_fitness = getFitness(*indivP);
		fitness_map[indivP] = t_fitness;
		fitness_sum += t_fitness;
		updateCurrentGenMinMaxFitness(indivP, t_fitness);
		new_indivP++;
		indivP++;
	}

	if(ELITISM) // replace min fitness individual with previous best individual
	{
		// adjust fitness sum for replacement individual
		fitness_sum += prev_best_fitness - gen_min_fitness;

		// replace minimum fitness individual with
		// best known individual in previous generation
		*gen_min_fit_indivP = prev_best_individual;
		fitness_map[gen_min_fit_indivP] = prev_best_fitness;

		// update best fitness after replacement
		if(gen_best_fitness < prev_best_fitness)
		{
			gen_best_fitness = prev_best_fitness;
			gen_best_individual = prev_best_individual;
		}

		// update min fitness after replacement
		gen_min_fitness = DBL_MAX;
		indivP = &population[0];
		for(size_t i = 0; i < POPULATION_SIZE; i++)
		{
			if(fitness_map[indivP] < gen_min_fitness)
			{
				gen_min_fitness = fitness_map[indivP];
				gen_min_fit_indivP = indivP;
			}
			indivP++;
		}
	}

	// update best known result so far
	if(gen_best_fitness > best_fitness)
	{
		best_fitness = gen_best_fitness;
		best_individual = gen_best_individual;
	}

	avg_fitness = (double) fitness_sum/POPULATION_SIZE;

	// reset cumulative fitness map for this population
	resetCumulativeMap();
}

template<typename T>
void simple_ga<T>::updateCurrentGenMinMaxFitness(T * indivP, double t_fitness)
{
	if(t_fitness < gen_min_fitness)
	{
		gen_min_fitness = t_fitness;
		gen_min_fit_indivP = indivP;
	}
	if(t_fitness > gen_best_fitness)
	{
		gen_best_fitness = t_fitness;
		gen_best_individual = *indivP;
	}
}

template<typename T>
bool simple_ga<T>::resetCumulativeMap()
{
	if(gen_min_fitness == gen_best_fitness)
	{
		cerr<<"generation : "<<num_of_generations<<" both min & max fitness are equal"<<endl;
		if(gen_min_fitness == 0)
		{
			cerr<<"generation : "<<num_of_generations<<" both min & max fitness is 0"<<endl;
		}

		// set each to equal in the cum_fitness
		T * indivP = &population[0];
		double equal_fitness = (double) 1/POPULATION_SIZE;
		for(size_t i = 0; i < POPULATION_SIZE; i++)
		{
			cumulative_map[indivP] = equal_fitness*(i+1);
			indivP++;
		}
		return true;
	}
	else
	{
		// shift each fitness by min fitness, to make min fitness = 0
		// shift total_fitness by POPULATION_SIZE*min fitness
		double total_shifted_fitness = fitness_sum - (POPULATION_SIZE*gen_min_fitness);

		double shifted_fitness;
		double relative_fitness;
		double cum_relative_fitness = 0;

		T * indivP = &population[0];
		for(size_t i = 0; i < POPULATION_SIZE; i++)
		{
			// move fitness along x-axis, to shift min fitness to 0
			shifted_fitness = fitness_map[indivP] - gen_min_fitness;

			// divide each fitness by max shifted fitness, i.e. fitnessRange
			relative_fitness = (double) shifted_fitness/total_shifted_fitness;
			cum_relative_fitness += relative_fitness;
			cumulative_map[indivP] = cum_relative_fitness;
			indivP++;
		}
		return true;
	}
}

template<typename T>
typename simple_ga<T>::crossoverParents simple_ga<T>::selectCrossOverParents()
{
	crossoverParents crossoverParents;
	crossoverParents.parent1 = selectAParent(NULL);
	crossoverParents.parent2 = selectAParent(crossoverParents.parent1);

	// safeguard if selection is not done
	if(crossoverParents.parent1 == NULL || crossoverParents.parent2 == NULL)
	{
		cerr<<"error selecting parent(s) for crossover."
				" returning first two individuals as crossover parents."<<endl;
		// return first two individuals from the population
		crossoverParents.parent1 = &population[0];
		crossoverParents.parent2 = &population[1];
	}

	return crossoverParents;
}

template<typename T>
T * simple_ga<T>::selectAParent(const T * already_selectedP)
{
	return rouletteWheelSelection(already_selectedP);
}

template<typename T>
T * simple_ga<T>::rouletteWheelSelection(const T * already_selectedP)
{
	T * parent = NULL;
	T * indivP = &population[0];
	double random_value = _uniform_distribution(roulette_random_engine);
	for(size_t i = 0; i < POPULATION_SIZE; i++)
	{
		// first cumulative fitness that exceeds random value
		if(cumulative_map[indivP] > random_value)
		{
			// select this if not already selected else
			// find an individual with similar fitness
			parent = indivP == already_selectedP ?
					selectSimilarFit(indivP) : indivP;

			break;
		}

		indivP++;
	}

	// if random value >= last cumulative fitness
	// (case when random value is 1 or
	// case when last cumulative fitness value is less than 1
	// due to limited bit precision of mathematical operations)
	// then do selection for the individual with last cumulative fitness
	if(random_value >= cumulative_map[&population[POPULATION_SIZE-1]])
	{
		indivP = &population[POPULATION_SIZE-1];
		// select this if not already selected else
		// find an individual with similar fitness
		parent = indivP == already_selectedP ?
				selectSimilarFit(indivP) : indivP;
	}

	return parent;
}

/**
 * find another individual whose fitness is
 * very close to fitness of this individual
 */
template<typename T>
T * simple_ga<T>::selectSimilarFit(const T * indivP)
{
	double indiv_fitness = fitness_map[indivP];
	// absolute fitness difference for each individual
	double abs_fitness_diff;
	// least absolute difference to track the closest fit individual
	double least_abs_diff = DBL_MAX;
	// iterate over each individual
	T * another_indivP = &population[0];
	T * most_similar_indivP = NULL;
	for(size_t j = 0; j < POPULATION_SIZE; j++)
	{
		if(another_indivP != indivP)
		{
			abs_fitness_diff = abs(indiv_fitness - fitness_map[another_indivP]);
			if(abs_fitness_diff < least_abs_diff)    // this fitness difference is less
			{
				// this is the most similar individual known so far
				most_similar_indivP = another_indivP;
				least_abs_diff = abs_fitness_diff;
			}
		}

		another_indivP++;
	}

	return most_similar_indivP;
}

template<typename T>
void simple_ga<T>::tryMutation(T & indiv)
{
	if(_uniform_distribution(mutation_random_engine)
			<= MUTATION_PROBABILITY)
	{
		// try mutation on this individual
		this->mutate(indiv);
	}
}

/**
 * displays results after GA run
 */
template<typename T>
void simple_ga<T>::displayResults()
{
	if(num_of_generations < 0)
	{
		cerr<<"error values not initialized to display any result"<<endl;
		return;
	}

	cout<<endl<<"total number of generations - "<<num_of_generations<<endl;
	double best_fitness = getFitness(best_individual);
	if(best_fitness != this->best_fitness)
	{
		cerr<<"error best fitness has not been updated correctly - "
				<<"stored best fitness is "<<this->best_fitness
				<<" fitness of best individual is "<<best_fitness<<endl;
		cerr<<"best indiv"<<endl;
		displayIndiv(best_individual);
	}
	else
	{
		cout<<"best fitness found - "<<best_fitness<<endl;
		cout<<"best indiv - "<<endl;
		displayIndiv(best_individual);
	}
}

// end of definitions
}
#endif /* GA_H_ */
