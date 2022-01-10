#pragma once
#include <Random>

class NeatRandom
{
public:
	NeatRandom();
	NeatRandom(int seed);

	double getRandomDouble(double lower, double upper);
	int getRandomInt(int lower, int upper);

private:
	std::default_random_engine gen;
};

