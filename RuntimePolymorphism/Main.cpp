#include <iostream>
#include <vector>


#include "Concept.h"


struct  Car
{
	void Accelerate()
	{
		std::cout << "Car do ziuuummmm"  << std::endl;
	}

};

struct  Truck
{
	void Accelerate()
	{
		std::cout << "truck do brum brum" << std::endl;
	}
};

std::vector<idea::VehicleConcept> vehicles;

int main() 
{
	
	Car c;
	vehicles.emplace_back(c);

	Truck t;
	vehicles.emplace_back(t);

	for (auto& v : vehicles)
		v.Accelerate();
	
	

	std::cin.get();
	return 0;

}