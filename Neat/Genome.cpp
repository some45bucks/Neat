#include "Genome.h"

Genome::Genome(Neat& _neat,unsigned int _id)
	:neat(_neat),
	id(_id),
	connectionGeneList(NeatList<ConnectionGene>()),
	nodeGeneList(NeatList<NodeGene>()),
	fitness(0),
	species(nullptr)
{
}

Genome::Genome(Neat& _neat, unsigned int _id, Species _species)
	:neat(_neat),
	id(_id),
	connectionGeneList(NeatList<ConnectionGene>()),
	nodeGeneList(NeatList<NodeGene>()),
	fitness(0),
	species(std::make_shared<Species>(_species) )
{
}

Genome::Genome(const Genome& other)
	:neat(other.neat),
	id(other.id),
	fitness(other.fitness)
{
	if (this != &other) 
	{
		connectionGeneList = other.connectionGeneList;
		nodeGeneList = other.nodeGeneList;
		species = other.species;
	}
}

Genome& Genome::operator=(const Genome& other)
{
	if (this != &other)
	{
		neat = other.neat;
		id = other.id;
		connectionGeneList = other.connectionGeneList;
		nodeGeneList = other.nodeGeneList;
		fitness = other.fitness;
		species = other.species;
	}

	return *this;
}

void Genome::setUpRandom(std::shared_ptr<NeatRandom> neatRandom)
{
	nodeGeneList.setRandom(neatRandom);
	connectionGeneList.setRandom(neatRandom);
}

const double Genome::getAdjustedFitness()
{
	return fitness/species->size();
}

void Genome::sortByInnNum()
{
	connectionGeneList.sort([](ConnectionGene a, ConnectionGene b) {
		return a.getInnNum() < b.getInnNum();
	});

	nodeGeneList.sort([](NodeGene a, NodeGene b) {
		return a.getInnNum() < b.getInnNum();
	});
}

void Genome::printLists()
{
	std::cout << *this << "\n";
	nodeGeneList.print();
	std::cout << "\n";
	connectionGeneList.print();
	std::cout << "\n";
}