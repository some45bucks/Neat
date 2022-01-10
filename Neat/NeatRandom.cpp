#include "NeatRandom.h"

NeatRandom::NeatRandom()
	:NeatRandom(0)
{
}

NeatRandom::NeatRandom(int seed)
	:gen(std::default_random_engine(seed))
{
}

double NeatRandom::getRandomDouble(double lower, double upper)
{
	std::uniform_real_distribution<double> range = std::uniform_real_distribution<>(lower, upper);
	return range(gen);
}

int NeatRandom::getRandomInt(int lower, int upper)
{
	if (lower == upper) 
	{
		return lower;
	}
	std::uniform_int_distribution<int> range = std::uniform_int_distribution<>(lower,upper);
	return range(gen);
}
