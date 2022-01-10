#pragma once

class NodeGene
{
public:
	NodeGene(unsigned int _inn);
	NodeGene(unsigned int _inn, double _layer);
	NodeGene(unsigned int _inn, double _layer, unsigned int _in,unsigned int _out);

	unsigned int getInnNum() { return inn; }
	void setInnNum(unsigned int _inn) { inn = _inn; }

	//double getWeight() { return weight; }
	//void setWeight(double _weight) { weight = _weight; }

	double getLayer() { return layer; }
	void setLayer(double _layer) { layer = _layer; }

	unsigned int getIn() { return in; }
	void setIn(unsigned int _in) { in = _in; }

	unsigned int getOut() { return out; }
	void setOut(unsigned int _out) { out = _out; }


	bool isEqual(NodeGene other);

private:
	unsigned int inn;
	//double weight;
	double layer;
	unsigned int in;
	unsigned int out;

};

