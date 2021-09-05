#pragma once
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

class row {
public:
	int getNumOfBeyaz(); //sýradaki beyaz sayýsýný bulur

	int getNumofSiyah(); //sýradaki siyah sayýsýný bulur

	void RowGuncelleSil(int l, int r);//silinen taþý tabloda güncelle

	void RowGuncelleBeyaz(int l, int r);//eklenen beyazý tabloda güncelle

	void RowGuncelleSiyah(int l, int r);//eklenen siyahý tabloda güncelle

	void BeyazArttir();//sýraya beyaz ekle

	void SiyahArttir();//sýraya siyah ekle

	string getRow(string row);

	void BeyazAzalt();//sýradan beyaz sil

	void SiyahAzalt();//sýradan siyah sil

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