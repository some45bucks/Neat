#pragma once
#include "Genome.h"
#include "NeatNode.h"
#include <vector>
#include <map>

class NeatNetwork
{
public:
	NeatNetwork(Genome& genome);
	NeatNetwork(Genome& genome, std::function<double(double)> f);
	std::vector<double> NetworkIO(std::vector<double> inputs);
	void addFitness(double add) { fitness += add; }

private:
	std::vector<std::reference_wrapper<NeatNode>> inputNodes;
	std::vector<std::reference_wrapper<NeatNode>> outputNodes;
	double& fitness;
	std::function<double(double)> activationFunction;
	std::map<unsigned int,NeatNode> allNodes;


	void linkNode(NeatNode& node, Genome& genome);
};

