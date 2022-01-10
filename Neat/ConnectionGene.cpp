#include "ConnectionGene.h"

ConnectionGene::ConnectionGene(unsigned int _inn)
	:ConnectionGene(_inn,0.5)
{
}

ConnectionGene::ConnectionGene(unsigned int _inn, double _weight)
	: ConnectionGene(_inn, 0.5,0,0)
{
}

ConnectionGene::ConnectionGene(unsigned int _inn, double _weight, unsigned int _from, unsigned int _to)
	: inn(_inn),
	weight(_weight),
	from(_from),
	to(_to),
	enabled(true)
{
}
