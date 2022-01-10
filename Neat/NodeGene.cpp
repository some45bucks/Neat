#include "NodeGene.h"
#include <ostream>

NodeGene::NodeGene(unsigned int _inn)
	:NodeGene(_inn,0)
{
}

NodeGene::NodeGene(unsigned int _inn, double _layer)
	:NodeGene(_inn,_layer,0,0)
{
}

NodeGene::NodeGene(unsigned int _inn, double _layer, unsigned int _in, unsigned int _out)
	:inn(_inn),
	layer(_layer),
	in(_in),
	out(_out)
{
}
