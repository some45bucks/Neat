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

	speciesList.setRandom(neatRandom);
	genomeList.setRandom(neatRandom);
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

std::vector<NeatNetwork> Neat::createNetworks()
{
	std::vector<NeatNetwork> networkList = std::vector<NeatNetwork>();

	for (std::shared_ptr<Genome> genome: genomeList) 
	{
		networkList.push_back(NeatNetwork(*genome));
	}

	return networkList;
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
		std::shared_ptr<Genome> newGenome = std::make_shared<Genome>(*this,gId++);

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
		_genome->getConnectionGeneList().getRandomObject().toggleEnabled();
	}
}

void Neat::cullGenomes()
{
	genomeList.clear();

	for (std::shared_ptr<Species> specie: speciesList) 
	{
		specie->cull();

		if (specie->size() > 1) 
		{
			for (std::shared_ptr<Genome> genome : specie->getGenomes())
			{
				genomeList.addObject(genome);
			}
		}

		
	}

	speciesList.sort([](std::shared_ptr<Species> a, std::shared_ptr<Species> b){
		return a->size() > b->size();
	});

	while (speciesList.size() > 0 && speciesList[speciesList.size()-1]->size() < 1) 
	{
		speciesList.popEnd();
	}
}

void Neat::rePop()
{
	std::vector<std::pair<double, std::shared_ptr<Species>>> holdMap = std::vector<std::pair<double, std::shared_ptr<Species>>>();

	speciesList.sort([](std::shared_ptr<Species> a, std::shared_ptr<Species> b) {
		return a->getAverageFitness() > b->getAverageFitness();
	});

	holdMap.push_back(std::pair<double,std::shared_ptr<Species>>(speciesList[0]->getAverageFitness(),speciesList[0]));

	for (auto i=1;i<speciesList.size();i++) 
	{
		double newDoub = speciesList[i]->getAverageFitness() + holdMap[i - 1].first;

		holdMap.push_back(std::pair<double, std::shared_ptr<Species>>(newDoub, speciesList[i]));
	}

	double max = holdMap[speciesList.size() - 1].first;

	while (genomeList.size() < numberOfGenomes)
	{
		double randDoub = neatRandom->getRandomDouble(0,max);

		std::shared_ptr<Species> spec = speciesList.getRandomObject();

		for (auto p: holdMap) 
		{
			if (randDoub <= p.first) 
			{
				spec = p.second;
				break;
			}
		}

		genomeList.addObject(crossOver(spec->getGenomes().getRandomObject(), spec->getGenomes().getRandomObject()));
	}
}

void Neat::clearfitness()
{
	for(auto geno: genomeList)
	{
		geno->setFitness(0);
	}
}

void Neat::evoStep()
{
	cullGenomes();
	rePop();
	mutateGenomes();
	speciate();
	clearfitness();
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

	_genome->addConnectionGene(newGene);
}

void Neat::mutateAddNode(std::shared_ptr<Genome> _genome)
{
	if (_genome->getConnectionGeneList().size() == 0)
	{
		return;
	}

	ConnectionGene& midGene = _genome->getConnectionGeneList().getRandomObject();

	double newLayer = (nodeGeneList[midGene.getFrom()].getLayer() + nodeGeneList[midGene.getTo()].getLayer()) / 2;

	NodeGene newGene = createOrGetNewNodeGene(midGene.getFrom(), midGene.getTo(), newLayer);

	if (_genome->addNodeGene(newGene));
	{
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
	for (std::shared_ptr<Species> species : speciesList)
	{
		species->getNewRep();
		//species->getGenomes().clear();
	}

	for (std::shared_ptr<Genome> genome: genomeList) 
	{
		if (genome->getHasSpecies()) 
		{
			continue;
		}

		bool foundSpecies = false;

		for (std::shared_ptr<Species>& species: speciesList) 
		{
			if (sameSpecies(species->getRep(),genome)) 
			{
				species->addGenome(genome);
				genome->setHasSpecies(true);
				foundSpecies = true;
				break;
			}
		}

		if (!foundSpecies) 
		{
			std::shared_ptr<Species> newSpecies = std::make_shared<Species>(*this, sId++, genome);
			newSpecies->setUpRandom(neatRandom);
			genome->setHasSpecies(true);
			newSpecies->addGenome(genome);
			speciesList.addObject(newSpecies);

		}
		
	}

	speciesList.sort([](auto a,auto b) {
		return a->getId() > b->getId();
	});
	std::cout << speciesList.size() << ": ";
	for (auto sp : speciesList) {
		std::cout << sp->getId()<< ": " << sp->size() << ", ";
	}
	std::cout << "\n";
	
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
	if (A->getFitness() < B->getFitness())
	{
		std::swap(A, B);
	}

	A->sortByInnNum();
	B->sortByInnNum();

	unsigned int ANum = 0;
	unsigned int BNum = 0;

	auto& Alist = A->getConnectionGeneList();
	auto& Blist = B->getConnectionGeneList();

	auto& Alist2 = A->getNodeGeneList();
	auto& Blist2 = B->getNodeGeneList();

	std::shared_ptr<Genome> newGenome = std::make_shared<Genome>(*this,gId++);

	for (auto ioG: nodeGeneList) 
	{
		if (ioG.getLayer() == 1 || ioG.getLayer() == 0) 
		{
			newGenome->addNodeGene(ioG);
		}
	}

	while (ANum < Alist.size())
	{
		if (BNum < Blist.size() && ANum < Alist.size() && Alist[ANum].getInnNum() == Blist[BNum].getInnNum())
		{
			if (neatRandom->getRandomInt(0,1) == 1) 
			{
				unsigned int from = Alist[ANum].getFrom();
				unsigned int to = Alist[ANum].getTo();
				newGenome->addNodeGene(nodeGeneList[from]);
				newGenome->addNodeGene(nodeGeneList[to]);

				newGenome->addConnectionGene(Alist[ANum]);
				
			}
			else
			{
				unsigned int from = Blist[BNum].getFrom();
				unsigned int to = Blist[BNum].getTo();
				newGenome->addNodeGene(nodeGeneList[from]);
				newGenome->addNodeGene(nodeGeneList[to]);

				newGenome->addConnectionGene(Blist[BNum]);
			}

			ANum++;
			BNum++;
		}
		else if ((BNum < Blist.size() && (Alist[ANum].getInnNum() > Blist[BNum].getInnNum())))
		{
			unsigned int from = Blist[BNum].getFrom();
			unsigned int to = Blist[BNum].getTo();
			newGenome->addNodeGene(nodeGeneList[from]);
			newGenome->addNodeGene(nodeGeneList[to]);

			newGenome->addConnectionGene(Blist[BNum]);

			BNum++;
		}
		else
		{
			unsigned int from = Alist[ANum].getFrom();
			unsigned int to = Alist[ANum].getTo();
			newGenome->addNodeGene(nodeGeneList[from]);
			newGenome->addNodeGene(nodeGeneList[to]);

			newGenome->addConnectionGene(Alist[ANum]);

			ANum++;
		}

	}

	newGenome->setUpRandom(neatRandom);
	return newGenome;
}


