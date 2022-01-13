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
	Genome(const Genome& other);

	Genome& operator=(const Genome& other);

	bool addConnectionGene(ConnectionGene _connectionGene);
	bool addNodeGene(NodeGene _nodeGene);

	NeatList<ConnectionGene>& getConnectionGeneList() { return connectionGeneList; }
	NeatList<NodeGene>& getNodeGeneList() {return nodeGeneList;}

	void setHasSpecies(bool _species) { hasSpecies = _species; }
	const bool getHasSpecies() { return hasSpecies; }

	void setFitness(double _fitness) { fitness = _fitness; }
	double& getFitnessRef() { return fitness; }
	double getFitness() { return fitness / sqrt(static_cast<double>(nodeGeneList.size())); }

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
	bool hasSpecies = false;
};

