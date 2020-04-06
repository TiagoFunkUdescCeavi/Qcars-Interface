#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <string>

#include "../model/Solution.h"
#include "../algorithm/PopulationGenerator.h"

using namespace std;

class Algorithm {
private:
	int sizePopulation;
	double sizePlasmideo;
	double cross;
	double elite;
	int limitIterations;
	string strategy;
	string selectionStrategy;
	string intermediaryStrategy;

	vector< Solution > population;
	vector< Solution > elitePopulation;
	vector< Solution > selection;
	vector< Solution > offspring;

public:
	Algorithm(
		string strategy,
		int sizePopulation,
		double elite,
		int limitIterations,
		double sizePlasmideo,
		double cross,
		string selectionStrategy,
		string intermediaryStrategy
	);

	Solution lets_go();
};

#endif /* ALGORITHM_H_ */
