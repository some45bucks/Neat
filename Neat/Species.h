#pragma once
#include "Neat.h"
#include "NeatList.h"

class Genome;

class Species
{
public:
	Species(Neat& _neat,unsigned int _id);
	Species(Neat& _neat, unsigned int _id, std::shared_ptr<Genome> _rep);

	double getAverageFitness();
	std::shared_ptr<Genome> getHighestFitnessGenome();

	void getNewRep();

	std::shared_ptr<Genome> getRep();

	void addGenome(std::shared_ptr<Genome> genome);

	NeatList<unsigned int> cull();

	unsigned int size();

private:
	std::shared_ptr<Genome> rep;
	Neat& neat;
	unsigned int id;
	NeatList<std::shared_ptr<Genome>> genomes;

	void sortByFitness();
};

