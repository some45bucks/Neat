#include "Genome.h"

Genome::Genome(Neat& _neat,unsigned int _id)
	:neat(_neat),
	id(_id),
	connectionGeneList(NeatList<ConnectionGene>()),
	nodeGeneList(NeatList<NodeGene>()),
	fitness(0)
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
		hasSpecies = other.hasSpecies;
	}
}

bool Genome::addNodeGene(NodeGene _nodeGene)
{
	bool good = true;

	for (auto nG: nodeGeneList) 
	{
		if (nG.getInnNum() == _nodeGene.getInnNum()) 
		{
			good = false;
			break;
		}
	}

	if (good) 
	{
		nodeGeneList.addObject(_nodeGene);
	}

	return good;
}

bool Genome::addConnectionGene(ConnectionGene _connectionGene)
{
	bool good = true;

	for (auto nG : connectionGeneList)
	{
		if (nG.getInnNum() == _connectionGene.getInnNum())
		{
			good = false;
			break;
		}
	}

	if (good)
	{
		connectionGeneList.addObject(_connectionGene);
	}

	return good;
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
		hasSpecies = other.hasSpecies;
	}

	return *this;
}

void Genome::setUpRandom(std::shared_ptr<NeatRandom> neatRandom)
{
	nodeGeneList.setRandom(neatRandom);
	connectionGeneList.setRandom(neatRandom);
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