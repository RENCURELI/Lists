#include <iostream>
#include "SList.h"

int main()
{
	std::cout << "Hello World!";
	
	// Ghost scope to cause a destruction
	{
		SList<int> intList = { 1, 10, 5, -5 };

		intList.PrintList();

		std::cout << "\n" << intList.GetSize() << "\n";
		std::cout << intList.IsEmpty() << "\n";
	}
	std::cout << "I hope this worked";
}