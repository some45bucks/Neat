#include "Neat.h"
#include "Genome.h"
#include "Species.h"
#include "NeatNetwork.h"

#include <iostream>

Neat::Neat(unsigned int _inputSize, unsigned int _outputSize, unsigned int _numberOfGenomes)
	:Neat(_inputSize,_outputSize,_numberOfGenomes,0)
{
}

Neat::Neat(unsigned int _inputSize, unsigned int _outputSize, unsigned int _numberOfGenomes, unsigned int seed)
	: Neat(_inputSize, _outputSize, _numberOfGenomes, NeatRandom(seed))
{
}

Neat::Neat(unsigned int _inputSize, unsigned int _outputSize, unsigned int _numberOfGenomes, NeatRandom _neatRandom)
	: inputSize(_inputSize),
	outputSize(_outputSize),
	numberOfGenomes(_numberOfGenomes),
	neatRandom(std::make_shared<NeatRandom>(_neatRandom)),
	nodeGeneList(NeatList<NodeGene>()),
	connectionGeneList(NeatList<ConnectionGene>()),
	genomeList(NeatList<std::shared_ptr<Genome>>()),
	speciesList(NeatList<std::shared_ptr<Species>>())
{
	fillGenomeList();
	mutateGenomes();
	speciate();

	/*for (const NodeGene& G : nodeGeneList)
	{
		std::cout << G << "\n";
	}

	for (const ConnectionGene& C : connectionGeneList)
	{
		std::cout << C << "\n";
	}*/
}

ConnectionGene Neat::createOrGetNewConnectionGene(unsigned int from, unsigned int to)
{
	for (ConnectionGene& connectionGene: connectionGeneList) 
	{
		if (connectionGene.getFrom() == from && connectionGene.getTo() == to) 
		{
			return connectionGene;
		}
	}

	ConnectionGene newGene = ConnectionGene(connectionGeneList.size(), neatRandom->getRandomDouble(-2, 2), from, to);

	connectionGeneList.addObject(newGene);

	return newGene;
}

NodeGene Neat::createOrGetNewNodeGene(unsigned int in, unsigned int out, double layer)
{
	for (NodeGene& nodeGene : nodeGeneList)
	{
		if (nodeGene.getIn() == in && nodeGene.getOut() == out)
		{
			return nodeGene;
		}
	}

	NodeGene newGene = NodeGene(nodeGeneList.size(), layer, in, out);

	nodeGeneList.addObject(newGene);

	return newGene;
}

void Neat::fillGenomeList()
{
	for (unsigned int i = 0; i < inputSize; i++)
	{
		NodeGene newNodeGene = NodeGene(nodeGeneList.size(),0);

		nodeGeneList.addObject(newNodeGene);
	}

	for (unsigned int i = 0; i < outputSize; i++)
	{
		NodeGene newNodeGene = NodeGene(nodeGeneList.size(), 1);

		nodeGeneList.addObject(newNodeGene);
	}

	for (unsigned int i=0;i<numberOfGenomes;i++) 
	{
		std::shared_ptr<Genome> newGenome = std::make_shared<Genome>(*this,genomeList.size());

		for (NodeGene& nodeGene: nodeGeneList)
		{
			newGenome->addNodeGene(nodeGene);
		}

		newGenome->setUpRandom(neatRandom);

		genomeList.addObject(newGenome);
	}
}

void Neat::mutateGenomes()
{
	for (std::shared_ptr<Genome> G: genomeList) 
	{
		if (neatRandom->getRandomDouble(0, 1) <= MUTATE_ADD_CONNECTION_CHANCE)
		{
			mutateAddConnection(G);
		}

		if (neatRandom->getRandomDouble(0, 1) <= MUTATE_ADD_NODE_CHANCE)
		{
			mutateAddNode(G);
		}

		if (neatRandom->getRandomDouble(0, 1) <= MUTATE_ADJUST_WEIGHT_CHANCE)
		{
			mutateAdjustWeight(G);
		}

		if (neatRandom->getRandomDouble(0, 1) <= MUTATE_ENABLE_DISABLE_CHANCE)
		{
			mutateEnableDisable(G);
		}

		if (neatRandom->getRandomDouble(0, 1) <= MUTATE_RANDOM_WEIGHT_CHANCE)
		{
			mutateRandomWeight(G);
		}
	}
}

void Neat::mutateAdjustWeight(std::shared_ptr<Genome> _genome)
{
	if (_genome->getConnectionGeneList().size() > 0) 
	{
		ConnectionGene& connectionGene = _genome->getConnectionGeneList().getRandomObject();
		connectionGene.setWeight(neatRandom->getRandomDouble(-.1,.1)+ connectionGene.getWeight());
	}
}

void Neat::mutateRandomWeight(std::shared_ptr<Genome> _genome)
{
	if (_genome->getConnectionGeneList().size() > 0)
	{
		ConnectionGene& connectionGene = _genome->getConnectionGeneList().getRandomObject();
		connectionGene.setWeight(neatRandom->getRandomDouble(-2, 2));
	}
}

void Neat::mutateEnableDisable(std::shared_ptr<Genome> _genome)
{
	if (_genome->getConnectionGeneList().size() > 0)
	{
		ConnectionGene& connectionGene = _genome->getConnectionGeneList().getRandomObject();
		connectionGene.toggleEnabled();
	}
}

void Neat::mutateAddConnection(std::shared_ptr<Genome> _genome)
{
	unsigned int from = 0;
	unsigned int to = 0;
	double l1 = 0;
	double l2 = 0;

	while (to == from || l1 >= l2)
	{
		NodeGene randGene1 = _genome->getNodeGeneList().getRandomObject();
		NodeGene randGene2 = _genome->getNodeGeneList().getRandomObject();

		from = randGene1.getInnNum();
		to = randGene2.getInnNum();

		l1 = randGene1.getLayer();
		l2 = randGene2.getLayer();
	}

	ConnectionGene newGene = createOrGetNewConnectionGene(from,to);

	bool contains = false;

	for (ConnectionGene& connectionGene :_genome->getConnectionGeneList()) 
	{
		if (connectionGene.getInnNum() == newGene.getInnNum()) 
		{
			contains = true;
			break;
		}
	}

	if (!contains) 
	{
		_genome->addConnectionGene(newGene);
	}
}

void Neat::mutateAddNode(std::shared_ptr<Genome> _genome)
{
	if (_genome->getConnectionGeneList().size() == 0)
	{
		return;
	}

	ConnectionGene& midGene = _genome->getConnectionGeneList().getRandomObject();

	double newLayer = (nodeGeneList[midGene.getFrom()].getLayer() + nodeGeneList[midGene.getTo()].getLayer()) / 2;

	NodeGene newGene = createOrGetNewNodeGene(midGene.getFrom(),midGene.getTo(),newLayer);

	bool contains = false;

	for (NodeGene& nodeGene : _genome->getNodeGeneList())
	{
		if (nodeGene.getInnNum() == newGene.getInnNum())
		{
			contains = true;
			break;
		}
	}

	if (!contains)
	{
		_genome->addNodeGene(newGene);

		if (midGene.getEnabled())
		{
			midGene.toggleEnabled();
		}

		ConnectionGene first = createOrGetNewConnectionGene(midGene.getFrom(), newGene.getInnNum());
		first.setWeight(1);
		ConnectionGene second = createOrGetNewConnectionGene(newGene.getInnNum(), midGene.getTo());
		second.setWeight(midGene.getWeight());

		_genome->addConnectionGene(first);
		_genome->addConnectionGene(second);
	}
}

void Neat::speciate()
{
	for (std::shared_ptr<Species>& species : speciesList)
	{
		species->getNewRep();
	}

	for (std::shared_ptr<Genome>& genome: genomeList) 
	{
		bool foundSpecies = false;

		for (std::shared_ptr<Species>& species: speciesList) 
		{
			if (sameSpecies(species->getRep(),genome)) 
			{
				species->addGenome(genome);
				genome->setSpecies(species);
				foundSpecies = true;
				break;
			}
		}

		if (!foundSpecies) 
		{
			std::shared_ptr<Species> newSpecies = std::make_shared<Species>(*this, speciesList.size(), genome);
			genome->setSpecies(newSpecies);
			speciesList.addObject(newSpecies);
		}
		
	}

	std::cout << speciesList.size() << "\n";
}

bool Neat::sameSpecies(std::shared_ptr<Genome> A, std::shared_ptr<Genome> B)
{
	if (A->getFitness() < B->getFitness()) 
	{
		std::swap(A,B);
	}

	unsigned int N = 0;
	unsigned int S = 0;
	double W = 0;
	unsigned int D = 0;
	unsigned int E = 0;

	A->sortByInnNum();
	B->sortByInnNum();

	unsigned int ANum = 0;
	unsigned int BNum = 0;

	auto& Alist = A->getConnectionGeneList();
	auto& Blist = B->getConnectionGeneList();

	while (ANum < Alist.size() && BNum < Blist.size())
	{
		if (BNum < Blist.size() && ANum < Alist.size() && Alist[ANum].getInnNum() == Blist[BNum].getInnNum())
		{
			S++;
			W += std::abs(Alist[ANum].getWeight() - Blist[BNum].getWeight());

			ANum++;
			BNum++;
		}
		else if (ANum >= Alist.size() || (BNum < Blist.size() && (Alist[ANum].getInnNum() > Blist[BNum].getInnNum())))
		{
			if (ANum >= Alist.size()) 
			{
				E++;
			}
			else
			{
				D++;
			}
			BNum++;
		}
		else 
		{
			if (BNum >= Blist.size())
			{
				E++;
			}
			else
			{
				D++;
			}
			ANum++;
		}
	}

	N = std::max(Alist.size(),Blist.size());

	if (N <= 20) 
	{
		N = 1;
	}

	if (S == 0) 
	{
		S = 1;
	}

	double num = (C1 * D / N) + (C2 * E / N) + (C3 * W / S);

	return num <= GENOME_DISTANCE;
}

std::shared_ptr<Genome> Neat::crossOver(std::shared_ptr<Genome> A, std::shared_ptr<Genome> B)
{
	return A;
}

void Neat::cullGenomes()
{

}
