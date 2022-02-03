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
	unsigned int numi = 300;
	Neat neat = Neat(5,4,numi);
	Neat::NetworkList list = neat.createNetworks();
	neat.save("save/");
	for(int i=0;i<100;i++)
	{
		std::cout << i << "\n";
		neat.evoStep();
		list = neat.createNetworks();
		
		double tot = 0;

		for (auto net : list)
		{
			std::vector<double> num = net.NetworkIO({ 0,0,0,0,0 });
			tot += (num[0]-num[1] * num[2]);
			net.addFitness((num[0] - num[1] * num[2]));
		}

		std::cout << tot / numi << "\n";
	}
	neat.save("save/");
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