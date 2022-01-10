#pragma once
#include "Neat.h"
#include "Species.h"
#include "ConnectionGene.h"
#include "NodeGene.h"
#include "NeatList.h"

#include <iostream>
#include <ostream>

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
	const std::shared_ptr<Species> getSpecies() { return species; }

	void setFitness(double _fitness) { fitness = _fitness; }
	const double getFitness() { return fitness; }
	const double getAdjustedFitness();

	const unsigned int getId() { return id; }

	void setUpRandom(std::shared_ptr<NeatRandom> neatRandom);

	void sortByInnNum();

	void printLists();

	friend std::ostream& operator<<(std::ostream& strm, const Genome& a) {
		return strm << "Genome " << a.id << "\n"
			<< "  Fitness: " << a.fitness << "\n";
	}

private:
	Neat& neat;
	unsigned int id;
	NeatList<ConnectionGene> connectionGeneList;
	NeatList<NodeGene> nodeGeneList;
	double fitness;
	std::shared_ptr<Species> species;
};

