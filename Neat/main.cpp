#include <iostream>

#include "Neat.h"

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
	Neat neat = Neat(3,4,1000);
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