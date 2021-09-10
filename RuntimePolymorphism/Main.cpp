#include <iostream>
#include <vector>

#include "Drawable.h"
#include <vector>

struct  X
{
	void Draw()
	{
		std::cout << "X::Draw()"  << std::endl;
	}

	void Draw2()
	{
		std::cout << "X::Draw2()" << std::endl;
	}
};

struct  Y
{
	void Draw()
	{
		std::cout << "Y::Draw()" << std::endl;
	}


};

struct Any 
{
	int i = 45;
	float f = 5.6f;
	
	void Draw() 
	{
		std::cout << "i = " << i << " ,f = " << f << std::endl;
 	}

	void foo() {}
};

std::vector<Drawable> document;

int main() 
{
	document.reserve(10);

	X x;
	document.push_back(x);

	Y y;
	document.push_back(y);

	Any any{3, 3.14f};
	document.push_back(any);


	std::reverse(document.begin(), document.end());

	for (auto& d : document)
		d.Draw();

	endl(std::cout);

	for (auto& d : document)
		d.Draw2();


	
	
	std::cin.get();
	return 0;

}