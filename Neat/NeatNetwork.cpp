#include "NeatNetwork.h"

NeatNetwork::NeatNetwork(Genome& genome)
	:NeatNetwork(genome, [](double x) {return 1 / (1 + (exp(-x))); })
{

}

NeatNetwork::NeatNetwork(Genome& genome, std::function<double(double)> f)
	:inputNodes(std::vector<std::reference_wrapper<NeatNode>>()),
	outputNodes(std::vector<std::reference_wrapper<NeatNode>>()),
	fitness(genome.getFitness()),
	activationFunction(f),
	allNodes(std::map<unsigned int,NeatNode>())
{
	genome.sortByInnNum();
	for (NodeGene& nG:genome.getNodeGeneList()) 
	{
		allNodes[nG.getInnNum()] = (NeatNode(nG.getInnNum(), activationFunction));

		if (nG.getLayer() == 0) 
		{
			inputNodes.push_back(allNodes[nG.getInnNum()]);
		}

		if (nG.getLayer() == 1)
		{
			outputNodes.push_back(allNodes[nG.getInnNum()]);
		}
	}

	for (NeatNode& nN : inputNodes)
	{
		linkNode(nN,genome);
	}
}

void NeatNetwork::linkNode(NeatNode& node, Genome& genome)
{
	for (ConnectionGene& cG : genome.getConnectionGeneList())
	{
		if (cG.getEnabled() && cG.getFrom() == node.getId()) 
		{
			node.connectNode(cG.getWeight(), allNodes[cG.getTo()]);
			linkNode(allNodes[cG.getTo()],genome);
		}
	}
}

std::vector<double> NeatNetwork::NetworkIO(std::vector<double> inputs)
{
	for (decltype(inputs.size()) i=0;i<inputs.size();i++) 
	{
		inputNodes[i].get().setData(inputs[i]);
	}

	for (NeatNode& node : inputNodes)
	{
		node.pushAlongData();
	}

	std::vector<double> output = std::vector<double>();

	for(NeatNode& node: outputNodes)
	{
		output.push_back(node.getData());
	}

	return output;
}
