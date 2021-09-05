#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class zar {
public:
	zar(void);
	~zar(void);
	int zarAt();

	int getZar();

	void PrintZar();

private:
	int dice;

};