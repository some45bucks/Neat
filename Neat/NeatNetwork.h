#pragma once
#include "Genome.h"
#include "NeatNode.h"
#include <vector>
#include <map>

class NeatNetwork
{
public:
	NeatNetwork(Genome& genome);
	std::vector<double> NetworkIO(std::vector<double> inputs);
	void addFitness(double add) { fitness += add; }

private:
	std::vector<std::shared_ptr<NeatNode>> inputNodes;
	std::vector<std::shared_ptr<NeatNode>> outputNodes;
	double& fitness;
	std::function<double(double)> activationFunction;
	std::map<unsigned int, std::shared_ptr<NeatNode>> allNodes;


	void linkNode(std::shared_ptr<NeatNode> node, Genome& genome);
};

