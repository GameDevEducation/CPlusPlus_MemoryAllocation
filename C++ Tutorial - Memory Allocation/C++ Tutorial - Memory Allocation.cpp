// C++ Tutorial - Memory Allocation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// https://learn.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2022

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>

class SimpleClassA
{
public:
	int* intPtr = nullptr;

public:
	SimpleClassA()
	{
		intPtr = new int;
		*intPtr = 100;
		std::cout << "SimpleClassA()" << std::endl;
	}

	// must have a destructor to free up memory that we allocated
	// must be virtual if we want to support inheritance safely
	virtual ~SimpleClassA()
	{
		delete intPtr;
		std::cout << "~SimpleClassA()" << std::endl;
	}
};

class SimpleClassB : public SimpleClassA
{
public:
	int* intPtr2 = nullptr;

public:
	SimpleClassB() : SimpleClassA()
	{
		intPtr2 = new int;
		*intPtr2 = 100;
		std::cout << "SimpleClassB()" << std::endl;
	}

	virtual ~SimpleClassB()
	{
		delete intPtr2;
		std::cout << "~SimpleClassB()" << std::endl;
	}
};

int main()
{
	{ // allocating individual item
		int* intPtr = new int;

		*intPtr = 53;

		std::cout << intPtr << "," << *intPtr << std::endl;

		delete intPtr; // must delete so that we free up the memory
		intPtr = nullptr; // good practice to set to nullptr after delete
	}

	{ // allocating an array must use array delete (ie. delete[])
		int* intArray = new int[50];

		intArray[0] = 42;

		std::cout << intArray[0] << std::endl;

		delete[] intArray;
		intArray = nullptr;
	}

	{
		SimpleClassA variable1;

		SimpleClassA* variablePtr1 = new SimpleClassA;
		delete variablePtr1;
		variablePtr1 = nullptr;
	}

	{
		SimpleClassB variable1;

		SimpleClassA* variablePtr1 = new SimpleClassB;
		delete variablePtr1;
		variablePtr1 = nullptr;
	}

	_CrtDumpMemoryLeaks();
}
