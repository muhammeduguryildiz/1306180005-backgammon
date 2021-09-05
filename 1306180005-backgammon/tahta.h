#pragma once
#include "row.h"
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>

class tahta {
public:
	bool checkStuckBeyaz(int x, int y);//beyazýn hareket edecek yeri var mý kontrol eder

	bool checkStuckSiyah(int x, int y);//siyahýn hareket edecek yeri var mý kontrol eder

	bool checkPenaltyBeyaz();//kýrýk beyaz taþ var mý kontrol eder

	bool checkPenaltySiyah();//kýrýk siyah taþ var mý kontrol eder

	int moveTasSiyah(int x,int y);//siyah taþ oynatýr

	int moveTasBeyaz(int x, int y);//beyaz taþ oynatýr

	int moveTasPenaltyBeyaz(int row, int secim);//kýrýk beyaz taþ oynar

	int moveTasPenaltySiyah(int row, int secim);//kýrýk siyah taþ oynar

	int numOfBeyaz(int x);//sýradaki beyaz sayýsýný kontrol eder

	int numOfSiyah(int x);//sýradaki siyah sayýsýný kontrol eder

	bool checkSiyahWin();//siyahýn kazanýp kazanmadýðýný kontrol eder

	bool checkBeyazWin();//beyazýn kazanýp kazanmadýðýný kontrol eder

	void PrintTahta();//tahtayý çýktý verir

	void saveTahta(int turn,vector<string>save,int zar1,int zar2,string player);//tahtayý çýktý verir

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