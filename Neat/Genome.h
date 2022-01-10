#pragma once
#include "Neat.h"
#include "Species.h"
#include "ConnectionGene.h"
#include "NodeGene.h"
#include "NeatList.h"

#include <iostream>

class Genome
{
public:
	Genome(Neat& _neat,unsigned int _id);
	Genome(Neat& _neat, unsigned int _id, Species _species);
	Genome(const Genome& other);

	Genome& operator=(const Genome& other);

	void addConnectionGene(ConnectionGene _connectionGene) { connectionGeneList.addObject(_connectionGene); }
	void addNodeGene(NodeGene _nodeGene) { nodeGeneList.addObject(_nodeGene); }

	NeatList<ConnectionGene>& getConnectionGeneList() { return connectionGeneList; }
	NeatList<NodeGene>& getNodeGeneList() {return nodeGeneList;}

	void setSpecies(std::shared_ptr<Species> _species) { species = _species; }
	std::shared_ptr<Species> getSpecies() { return species; }

	void setFitness(double _fitness) { fitness = _fitness; }
	double getFitness() { return fitness; }
	double getAdjustedFitness();

	unsigned int getId() { return id; }

	void setUpRandom(std::shared_ptr<NeatRandom> neatRandom);

	void sortByInnNum();

private:
	Neat& neat;
	unsigned int id;
	NeatList<ConnectionGene> connectionGeneList;
	NeatList<NodeGene> nodeGeneList;
	double fitness;
	std::shared_ptr<Species> species;
};

