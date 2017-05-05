#include "stdafx.h"
#include "Factory.h"

void main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randint0_5(0,5);
	
	Container < Shape > figures;

	try {
		int type;
		for (int i = 0; i < 25; i++) {
			type = randint0_5(gen);
			figures.InsTail(figure(type));
		}
		
		std::cout << "Quantity of figures: " << Shape::GetCount() << std::endl;

		figures.Clear();
		
		std::cout << "Quantity of figures: " << Shape::GetCount() << std::endl;
	}
	catch (char const * error) {
		std::cout << error << std::endl;
	}
	


}
