#pragma once
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class row {
public:
	int getNumOfBeyaz(); //s�radaki beyaz say�s�n� bulur

	int getNumofSiyah(); //s�radaki siyah say�s�n� bulur

	void RowGuncelleSil(int l, int r);//silinen ta�� tabloda g�ncelle

	void RowGuncelleBeyaz(int l, int r);//eklenen beyaz� tabloda g�ncelle

	void RowGuncelleSiyah(int l, int r);//eklenen siyah� tabloda g�ncelle

	void BeyazArttir();//s�raya beyaz ekle

	void SiyahArttir();//s�raya siyah ekle

	string getRow(string row);

	void BeyazAzalt();//s�radan beyaz sil

	void SiyahAzalt();//s�radan siyah sil

	void setRow(int x);

	void setLoadRow(int x, vector<string>rowlar);

	void PrintRow();

	row(void);
	~row(void);

private:
	int numOfSiyah;
	int numOfBeyaz;
	char list[6];
};