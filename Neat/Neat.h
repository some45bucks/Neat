#pragma once
#include "NodeGene.h"
#include "ConnectionGene.h"
#include "NeatList.h"

class Genome;
class Species;

class Neat
{
public:
	Neat(unsigned int _inputSize,unsigned int _outputSize, unsigned int _numberOfGenomes);
	Neat(unsigned int _inputSize, unsigned int _outputSize, unsigned int _numberOfGenomes, NeatRandom _neatRandom);
	Neat(unsigned int _inputSize, unsigned int _outputSize, unsigned int _numberOfGenomes, unsigned int seed);

	void fillGenomeList();
	void mutateGenomes();
	void speciate();
	bool sameSpecies(std::shared_ptr<Genome> A, std::shared_ptr<Genome> B);
	std::shared_ptr<Genome> crossOver(std::shared_ptr<Genome> A, std::shared_ptr<Genome> B);
	void cullGenomes();
	//NeatList<NeatNetwork> createNeatNetworks();
	ConnectionGene createOrGetNewConnectionGene(unsigned int from, unsigned int to);
	NodeGene createOrGetNewNodeGene(unsigned int in, unsigned int out,double layer);


	//NeatRandom getNeatRandom() { return neatRandom; }


private:
	unsigned int inputSize;
	unsigned int outputSize;
	unsigned int numberOfGenomes;

	double GENOME_DISTANCE = 7;
	
	double C1 = 1;
	double C2 = 1;
	double C3 = 1;

	double MUTATE_ADJUST_WEIGHT_CHANCE = .05;
	double MUTATE_RANDOM_WEIGHT_CHANCE = .05;
	double MUTATE_ENABLE_DISABLE_CHANCE = .05;
	double MUTATE_ADD_CONNECTION_CHANCE = .05;
	double MUTATE_ADD_NODE_CHANCE = .05;

	std::shared_ptr<NeatRandom> neatRandom;
	NeatList<NodeGene> nodeGeneList;
	NeatList<ConnectionGene> connectionGeneList;
	NeatList<std::shared_ptr<Genome>> genomeList;
	NeatList< std::shared_ptr<Species>> speciesList;

	void mutateAdjustWeight(std::shared_ptr<Genome> _genome);
	void mutateRandomWeight(std::shared_ptr<Genome> _genome);
	void mutateEnableDisable(std::shared_ptr<Genome> _genome);
	void mutateAddConnection(std::shared_ptr<Genome> _genome);
	void mutateAddNode(std::shared_ptr<Genome> _genome);

	
};