#pragma once
#include "row.h"
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>

class tahta {
public:
	bool checkStuckBeyaz(int x, int y);//beyaz�n hareket edecek yeri var m� kontrol eder

	bool checkStuckSiyah(int x, int y);//siyah�n hareket edecek yeri var m� kontrol eder

	bool checkPenaltyBeyaz();//k�r�k beyaz ta� var m� kontrol eder

	bool checkPenaltySiyah();//k�r�k siyah ta� var m� kontrol eder

	int moveTasSiyah(int x,int y);//siyah ta� oynat�r

	int moveTasBeyaz(int x, int y);//beyaz ta� oynat�r

	int moveTasPenaltyBeyaz(int row, int secim);//k�r�k beyaz ta� oynar

	int moveTasPenaltySiyah(int row, int secim);//k�r�k siyah ta� oynar

	int numOfBeyaz(int x);//s�radaki beyaz say�s�n� kontrol eder

	int numOfSiyah(int x);//s�radaki siyah say�s�n� kontrol eder

	bool checkSiyahWin();//siyah�n kazan�p kazanmad���n� kontrol eder

	bool checkBeyazWin();//beyaz�n kazan�p kazanmad���n� kontrol eder

	void PrintTahta();//tahtay� ��kt� verir

	void saveTahta(int turn,vector<string>save,int zar1,int zar2,string player);//tahtay� ��kt� verir

	void getSaveTahta(string p1,string p2,int turn);

	void loadSaveTahta();


	tahta(void);
	~tahta(void);

private:
	row rows[24];
	row SiyahPenalty;
	row BeyazPenalty;
	int ToplamSiyah;
	int ToplamBeyaz;
};