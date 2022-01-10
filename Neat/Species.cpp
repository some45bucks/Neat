#include "Species.h"
#include "Genome.h"
#include <iostream>
#include <optional>

Species::Species(Neat& _neat,unsigned int _id)
	:rep(nullptr),
	neat(_neat),
	id(_id),
	genomes(NeatList<std::shared_ptr<Genome>>())
{
}

Species::Species(Neat& _neat, unsigned int _id, std::shared_ptr<Genome> _rep)
	:rep(_rep),
	neat(_neat),
	id(_id),
	genomes(NeatList<std::shared_ptr<Genome>>())
{
}

std::shared_ptr<Genome> Species::getRep()
{
	return rep;
}

double Species::getAverageFitness()
{
	double total = 0;

	for (std::shared_ptr<Genome> G: genomes)
	{
		total += G->getAdjustedFitness();
	}

	return total;
}

void Species::getNewRep()
{
	sortByFitness();
	rep = genomes[0];
}

void Species::sortByFitness()
{
	genomes.sort([](std::shared_ptr<Genome> a, std::shared_ptr<Genome> b) {
		return a->getFitness() > b->getFitness();
	});
}

std::shared_ptr<Genome> Species::getHighestFitnessGenome()
{
	sortByFitness();
	return genomes[0];
}

void Species::addGenome(std::shared_ptr<Genome> genome)
{
	if (rep == nullptr) 
	{
		rep = genome;
	}

	genomes.addObject(genome);
}

NeatList<unsigned int> Species::cull()
{
	//TODO

	return NeatList<unsigned int>();
}

unsigned int Species::size()
{
	return genomes.size();
}