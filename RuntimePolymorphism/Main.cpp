#include <iostream>
#include <vector>

#include "VehicleConcept.h"

struct  Car
{
	void Accelerate()
	{
		std::cout << "anyNumber = " << anyNumber << std::endl;
	}

	int anyNumber = 0;
};

struct  Truck
{
	void Accelerate()
	{
		std::cout << "truck do brum brum" << std::endl;
	}
};

std::vector<VehicleConcept> vehicles;

int main() 
{
	vehicles.reserve(10);

	Car c { 1 };
	for (int i = 0; i < 5; ++i)
		vehicles.emplace_back(c);

	for (int i = 10; i < 15; ++i) 
		vehicles.emplace_back(Car{i});

	c.anyNumber = 67;

	for (auto& v : vehicles)
		v.Accelerate();

	std::reverse(vehicles.begin(), vehicles.end());

	for (auto& v : vehicles)
		v.Accelerate();
	
	
	std::cin.get();
	return 0;

}