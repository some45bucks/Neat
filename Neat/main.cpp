#include <iostream>

#include "Neat.h"
#include "NeatNetwork.h"

void NeatRandomTest() 
{
	NeatRandom rand = NeatRandom(100);
	
	for (int i=0;i<10;i++) 
	{
		std::cout << rand.getRandomDouble(0, 1) << "\n";
	}

	std::cout << "\n";

	for (int i = 0; i < 10; i++)
	{
		std::cout << rand.getRandomInt(0, 10) << "\n";
	}

	std::cout << "\n";
}

void NeatListTest() 
{
	NeatList<std::string> stringList = NeatList <std::string>();

	stringList.addObject("one");
	stringList.addObject("two");
	stringList.addObject("three");
	stringList.addObject("four");

	stringList.print();

	stringList.sort([](std::string a, std::string b) {
		return a.size() > b.size();
	});

	stringList.print();

	stringList.addObject("five");

	stringList.print();

	stringList.sort([](std::string a, std::string b) {
		return a.size() > b.size();
	});

	stringList.print();

	stringList.popEnd();

	stringList.print();
}

void NeatTest() 
{
	auto gen = std::default_random_engine(90);
	std::uniform_int_distribution<int> range = std::uniform_int_distribution<>(0, 149);
	auto x = range(gen);

	Neat neat = Neat(20,20,300,90);
	Neat::NetworkList list = neat.createNetworks();

	for(int i=0;i<100;i++)
	{
		std::cout << i << "\n";
		neat.evoStep();
		list = neat.createNetworks();
	}
	
}

void tests() 
{
	NeatRandomTest();
	NeatListTest();
	NeatTest();
}

int main() 
{
	tests();

	return 0;
}