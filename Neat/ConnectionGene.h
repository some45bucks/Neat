#pragma once
#include <ostream>

class ConnectionGene
{
public:
	ConnectionGene(unsigned int _inn);
	ConnectionGene(unsigned int _inn, double _weight);
	ConnectionGene(unsigned int _inn, double _weight, unsigned int _from, unsigned int _to);

	unsigned int const getInnNum() { return inn; }
	void setInnNum(unsigned int _inn) { inn = _inn; }

	const double getWeight() { return weight; }
	void setWeight(double _weight) { weight = _weight; }

	const unsigned int getFrom() { return from; }
	void setFrom(unsigned int _from) { from = _from; }

	const unsigned int getTo() { return to; }
	void setTo(unsigned int _to) { to = _to; }

	const bool getEnabled() { return enabled; }
	void toggleEnabled() { enabled = !enabled; }

	friend std::ostream& operator<<(std::ostream& strm, const ConnectionGene& a) {
		return strm << "Connection Gene " << a.inn << "\n"
			<< "  Weight: " << a.weight << "\n"
			<< "  From: " << a.from << "\n"
			<< "  To: " << a.to << "\n";
	}

private:
	
	unsigned int inn;
	double weight;
	unsigned int from;
	unsigned int to;
	bool enabled;
};

