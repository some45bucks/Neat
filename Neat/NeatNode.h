#pragma once
#include <vector>
#include <functional>

class NeatNode
{
public:
	NeatNode() = default;
	NeatNode(unsigned int _id,std::function<double(double)> f);
	void setData(double val) { currentTotalVal = val; }
	double getData() { return currentTotalVal; }
	void addFeedIn() { numberOfFeedIn++; }
	void connectNode(double weight,NeatNode& newNode);
	void pushAlongData();
	void reciveData(double data);
	unsigned int getId() { return id; }
private:
	std::vector<std::pair<double, std::reference_wrapper<NeatNode>>> weightNodeList;
	double currentTotalVal;
	unsigned int numberOfFeedIn;
	unsigned int numberOfActiveFeedIns;
	std::function<double(double)> activationFunction;
	unsigned int id;
};

