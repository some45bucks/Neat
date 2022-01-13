#pragma once
#include <vector>
#include <functional>
#include <memory>

class NeatNode
{
public:
	NeatNode() = default;
	NeatNode(unsigned int);
	void setData(double val) { currentTotalVal = val; }
	double getData() { return currentTotalVal; }
	void addFeedIn() { numberOfFeedIn++; }
	void connectNode(double weight, std::shared_ptr<NeatNode> newNode);
	void pushAlongData();
	void reciveData(double data);
	unsigned int getId() { return id; }
private:
	std::vector<std::pair<double, std::shared_ptr<NeatNode>>> weightNodeList;
	double currentTotalVal;
	unsigned int numberOfFeedIn;
	unsigned int numberOfActiveFeedIns;
	unsigned int id;

	double activationFunction(double x);
};

