#pragma once
class ConnectionGene
{
public:
	ConnectionGene(unsigned int _inn);
	ConnectionGene(unsigned int _inn, double _weight);
	ConnectionGene(unsigned int _inn, double _weight, unsigned int _from, unsigned int _to);

	unsigned int getInnNum() { return inn; }
	void setInnNum(unsigned int _inn) { inn = _inn; }

	double getWeight() { return weight; }
	void setWeight(double _weight) { weight = _weight; }

	unsigned int getFrom() { return from; }
	void setFrom(unsigned int _from) { from = _from; }

	unsigned int getTo() { return to; }
	void setTo(unsigned int _to) { to = _to; }

	bool getEnabled() { return enabled; }
	void toggleEnabled() { enabled = !enabled; }

	bool isEqual(ConnectionGene other);

private:
	unsigned int inn;
	double weight;
	unsigned int from;
	unsigned int to;
	bool enabled;
};

