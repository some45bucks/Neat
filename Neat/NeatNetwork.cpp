#include "NeatNetwork.h"
NeatNetwork::NeatNetwork(Genome& genome)
	:inputNodes(std::vector<std::shared_ptr<NeatNode>>()),
	outputNodes(std::vector<std::shared_ptr<NeatNode>>()),
	fitness(genome.getFitnessRef()),
	allNodes(std::map<unsigned int, std::shared_ptr<NeatNode>>())
{
	genome.sortByInnNum();
	for (NodeGene& nG: genome.getNodeGeneList()) 
	{
		allNodes[nG.getInnNum()] = std::make_shared<NeatNode>(nG.getInnNum());

		if (nG.getLayer() == 0) 
		{
			inputNodes.push_back(allNodes[nG.getInnNum()]);
		}

		if (nG.getLayer() == 1)
		{
			outputNodes.push_back(allNodes[nG.getInnNum()]);
		}
	}

	for (std::shared_ptr<NeatNode> nN : inputNodes)
	{
		linkNode(nN,genome);
	}
}

void NeatNetwork::linkNode(std::shared_ptr<NeatNode> node, Genome& genome)
{
	for (ConnectionGene& cG : genome.getConnectionGeneList())
	{
		if (cG.getEnabled() && cG.getFrom() == node->getId()) 
		{
			node->connectNode(cG.getWeight(), allNodes[cG.getTo()]);
			linkNode(allNodes[cG.getTo()],genome);
		}
	}
}

std::vector<double> NeatNetwork::NetworkIO(std::vector<double> inputs)
{
	for (decltype(inputs.size()) i=0;i<inputs.size();i++) 
	{
		inputNodes[i]->setData(inputs[i]);
	}

	for (std::shared_ptr<NeatNode> node : inputNodes)
	{
		node->pushAlongData();
	}

	std::vector<double> output = std::vector<double>();

	for(std::shared_ptr<NeatNode> node: outputNodes)
	{
		output.push_back(node->getData());
	}

	return output;
}