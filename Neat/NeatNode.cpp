#include "NeatNode.h"

NeatNode::NeatNode(unsigned int _id)
	:weightNodeList(std::vector<std::pair<double, std::shared_ptr<NeatNode>>>()),
	currentTotalVal(0),
	numberOfFeedIn(0),
	numberOfActiveFeedIns(0),
	id(_id)
{
}

void NeatNode::connectNode(double weight, std::shared_ptr<NeatNode> newNode)
{
	std::pair<double, std::shared_ptr<NeatNode>> newPair(weight,newNode);
	weightNodeList.push_back(newPair);
	newNode->addFeedIn();
}

void NeatNode::pushAlongData()
{
	currentTotalVal = activationFunction(currentTotalVal);

	for(auto& pair: weightNodeList)
	{
		pair.second->reciveData(pair.first * currentTotalVal);
	}
}

double NeatNode::activationFunction(double x)
{
	return 1 / (1 + (exp(-x)));
}

void NeatNode::reciveData(double data)
{
	currentTotalVal += data;

	numberOfActiveFeedIns++;

	if (numberOfActiveFeedIns == numberOfFeedIn) 
	{
		pushAlongData();
	}
}
