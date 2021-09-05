#include "zar.h"
#include <iostream>

using namespace std;

zar::zar(void) {

}

zar::~zar(void)
{

}

int zar::zarAt() {

	srand(rand() + time(0));
	dice = 1 + (rand() % 6);
	return dice;
}

int zar::getZar() {
	return dice;
}

void zar::PrintZar() {
	cout << dice;
}