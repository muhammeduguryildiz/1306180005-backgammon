#include "row.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

row::row(void) {

	numOfBeyaz = 0;
	numOfSiyah = 0;
}

row::~row(void)
{

}

int row::getNumofSiyah() {
	return numOfSiyah;
}

int row::getNumOfBeyaz() {
	return numOfBeyaz;
}

void row::PrintRow() {
	for (int i = 0; i < 6; i++) {
		cout << list[i];
	}
}

string row::getRow(string row) {
	row.clear();
	for (int i = 0; i < 6; i++) {
		row += list[i];
	}
	return row;
}

void row::RowGuncelleSil(int l, int r) {
	int index = l - 1;
	if (r < 12) {
		list[index] = '-';
	}
	else {
		switch (index) {
		case 0:
			list[5] = '-';
			break;
		case 1:
			list[4] = '-';
			break;
		case 2:
			list[3] = '-';
			break;
		case 3:
			list[2] = '-';
			break;
		case 4:
			list[1] = '-';
			break;
		case 5:
			list[0] = '-';
			break;
		}
		
	}
}

void row::RowGuncelleBeyaz(int l, int r) {
	int index = l;
	if (r < 12) {
		list[index] = 'B';
	}
	else {
		switch (index) {
		case 0:
			list[5] = 'B';
			break;
		case 1:
			list[4] = 'B';
			break;
		case 2:
			list[3] = 'B';
			break;
		case 3:
			list[2] = 'B';
			break;
		case 4:
			list[1] = 'B';
			break;
		case 5:
			list[0] = 'B';
			break;
		}
	}
}

void row::RowGuncelleSiyah(int l, int r) {
	int index = l;
	if (r < 12)
	{
		list[index] = 'S';
	}
	else
	{
		switch (index)
		{
		case 0:
			list[5] = 'S';
			break;
		case 1:
			list[4] = 'S';
			break;
		case 2:
			list[3] = 'S';
			break;
		case 3:
			list[2] = 'S';
			break;
		case 4:
			list[1] = 'S';
			break;
		case 5:
			list[0] = 'S';
			break;
		}
	}
}

void row::BeyazArttir() {
	numOfBeyaz++;
}

void row::SiyahArttir() {
	numOfSiyah++;
}

void row::BeyazAzalt() {
	numOfBeyaz--;
}

void row::SiyahAzalt() {
	numOfSiyah--;
}

void row::setLoadRow(int x,vector<string>rowlar) {
	string rowload;
	char* char_arr;

		rowload = rowlar[x];
		char_arr = &rowload[0];
		strcpy_s(list, strlen(list)+1, char_arr);
		numOfBeyaz = stoi(rowlar[x + 1]);
		numOfSiyah = stoi(rowlar[x + 2]);

}


void row::setRow(int x)
{
	switch (x)
	{
	case -1:
		strcpy_s(list, strlen(list)+1, "||||||");
		break;
	case 0:
		strcpy_s(list, strlen(list), "SS----");
		numOfSiyah = 2;
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 6:
	case 8:
	case 9:
	case 10:
		strcpy_s(list, strlen(list), "------");
		break;
	case 5:
		strcpy_s(list, strlen(list), "BBBBB-");
		numOfBeyaz = 5;
		break;
	case 7:
		strcpy_s(list, strlen(list), "BBB---");
		numOfBeyaz = 3;
		break;
	case 11:
		strcpy_s(list, strlen(list), "SSSSS-");
		numOfSiyah = 5;
		break;
	case 12:
		strcpy_s(list, strlen(list), "-BBBBB");
		numOfBeyaz = 5;
		break;
	case 13:
	case 14:
	case 15:
	case 17:
	case 20:
	case 19:
	case 21:
	case 22:
		strcpy_s(list, strlen(list), "------");
		break;
	case 16:
		strcpy_s(list, strlen(list) , "---SSS");
		numOfSiyah = 3;
		break;
	case 18:
		strcpy_s(list, strlen(list), "-SSSSS");
		numOfSiyah = 5;
		break;
	case 23:
		strcpy_s(list, strlen(list), "----BB");
		numOfBeyaz = 2;
		break;
	case 24:
		strcpy_s(list, strlen(list)+1, "||||||");
		break;
		
	}
}