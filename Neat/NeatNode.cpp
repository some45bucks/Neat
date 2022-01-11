#include "NeatNode.h"

NeatNode::NeatNode(unsigned int _id,std::function<double(double)> f)
	:weightNodeList(std::vector<std::pair<double, std::reference_wrapper<NeatNode>>>()),
	currentTotalVal(0),
	numberOfFeedIn(0),
	numberOfActiveFeedIns(0),
	activationFunction(f),
	id(_id)
{
}

void NeatNode::connectNode(double weight,NeatNode& newNode)
{
	std::pair<double, std::reference_wrapper<NeatNode>> newPair(weight,newNode);
	weightNodeList.push_back(newPair);
	newNode.addFeedIn();
}

void NeatNode::pushAlongData()
{
	currentTotalVal = activationFunction(currentTotalVal);

	for(auto& pair: weightNodeList)
	{
		pair.second.get().reciveData(pair.first * currentTotalVal);
	}
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
