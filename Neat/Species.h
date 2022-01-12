#pragma once
#include "Neat.h"
#include "NeatList.h"

class Genome;

class Species
{
public:
	Species(Neat& _neat,unsigned int _id);
	Species(Neat& _neat, unsigned int _id, std::shared_ptr<Genome> _rep);

	NeatList<std::shared_ptr<Genome>>& getGenomes() { return genomes; }
	unsigned int getId() { return id; }

	double getAverageFitness();
	std::shared_ptr<Genome> getHighestFitnessGenome();

	void getNewRep();

	std::shared_ptr<Genome> getRep();

	void addGenome(std::shared_ptr<Genome> genome);

	void setUpRandom(std::shared_ptr<NeatRandom> rand) { genomes.setRandom(rand); }

	void cull();

	unsigned int size();

private:
	std::shared_ptr<Genome> rep;
	Neat& neat;
	unsigned int id;
	NeatList<std::shared_ptr<Genome>> genomes;

	void sortByFitness();
};

