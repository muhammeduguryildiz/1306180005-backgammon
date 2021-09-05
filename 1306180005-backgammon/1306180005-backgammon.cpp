#include "zar.h"
#include "tahta.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

bool beyazTurn(tahta&, string, string);
//Beyazin sirasini oynatir
bool siyahTurn(tahta&, string, string);
//Siyahin sirasini oynatir

int turns = 1;


vector<string> save;

int main()
{

	string baslangic;
	int turn = 3;
	string p1, p2;
	tahta backgammon;
	bool whiteWin = false;
	bool blackWin = false;
	zar zar1, zar2;

	cout << "Son kayitli oyuna donmek icin kayit, yeni oyuna baslamak icin yeni yaziniz" << endl;
	getline(cin, baslangic);
	cout << endl;

	if (baslangic == "kayit") {
		string line;
		const char FileName[] = "save.txt";
		ifstream my_file(FileName);
		vector<string> bolum;
		vector<string> oyuncular;
		if (my_file.is_open())
		{

			while (getline(my_file, line))
			{
				bolum.push_back(line);

			}
		}
		my_file.close();

		stringstream ss(bolum[0]);
		while (ss.good()) {
			string substr;
			getline(ss, substr, ',');
			oyuncular.push_back(substr);
		}
		p1 = oyuncular[0];
		p2 = oyuncular[1];
		turn = stoi(oyuncular[2]);
		my_file.close();
		backgammon.loadSaveTahta();
	}
	else if (baslangic == "yeni") {

		cout << "Oyunun herhangi bir aninda kaydedip cikmak icin lutfen -1 yaziniz" << endl;

		cout << "Birinci oyuncunun ismi: ";
		getline(cin, p1);
		cout << endl;

		cout << "Ikinci oyuncunun ismi: ";
		getline(cin, p2);
		cout << endl;

		cout << "Ilk kimin baslayacagi icin zar atiliyor";
		cout << endl;
		system("pause");

		do
		{
			zar1.zarAt();
			zar2.zarAt();
			cout << p1 << "'nun zari ";
			zar1.PrintZar();
			cout << endl;
			cout << p2 << "'nun zari ";
			zar2.PrintZar();
			cout << endl;

			if (zar1.getZar() == zar2.getZar())
			{
				cout << "Zarlar esit, tekrar atiliyor" << endl;
			}
		} while (zar1.getZar() == zar2.getZar());


		if (zar1.getZar() > zar2.getZar())
		{
			cout << p1 << " oyuna basliyor.";
		}

		else if (zar1.getZar() < zar2.getZar())
		{
			cout << p2 << " oyuna basliyor.";
			turn++;
		}

		cout << endl << endl;

		system("pause");
	}
	else {
		cout << "dogru parametre girilmedigi icin oyun kapatiliyor" << endl;
		exit(1);
	}
	backgammon.PrintTahta();
	cout << endl << endl;

	while (!whiteWin && !blackWin)
	{

		if (turn % 2 == 0)
		{
			blackWin = siyahTurn(backgammon, p1, p2);
			turn++;
		}
		else
		{
			whiteWin = beyazTurn(backgammon, p1, p2);
			turn++;
		}
		whiteWin = backgammon.checkBeyazWin();
		blackWin = backgammon.checkSiyahWin();
	}

	backgammon.PrintTahta();

	if (whiteWin)
	{
		cout << endl << endl << p1 << ", oyunu kazandi" << endl;
		system("pause");
		return 0;
	}

	if (blackWin)
	{
		cout << endl << endl << p2 << ", oyunu kazandi" << endl;
		system("pause");
		return 0;
	}
}

bool beyazTurn(tahta& backgammon, string p1, string p2)
{
	int move1 = 0;
	int move2 = 0;
	int move3 = 0;
	int move4 = 0;

	bool check = false;
	bool stuck = false;
	bool penalty = false;
	int errorCheck;

	int rowChoice;
	int moved;
	zar dice1, dice2;
	int choice;

	cout << p1 << ", beyaz icin zar atiliyor." << endl << endl;
	cout << endl << "Birinci zar : ";
	move1 = dice1.zarAt();
	move2 = dice2.zarAt();

	cout << move1 << " ve ikinci zar : " << endl << move2 << endl << endl;

	if (move1 == move2)
	{

		cout << "Cift zar atildi, her zar icin iki kez oynama hakki" << endl << endl;
		move3 = move1;
		move4 = move2;
	}

	penalty = backgammon.checkPenaltyBeyaz();

	while (penalty)
	{
		rowChoice = 25;
		stuck = backgammon.checkStuckBeyaz(move1, move2);
		if (stuck)
		{
			cout << "Oynanacak tas olmadigi icin turunuz geciliyor." << endl;
			return false;
		}
		if (move1 != 0 && move2 == 0)
		{
			cout << "Kalan zar hareketiniz " << move1 << endl;
			choice = 1;
		}
		else if (move2 != 0 && move1 == 0)
		{
			cout << "Kalan zar hareketiniz " << move2 << endl;
			choice = 2;
		}
		else
		{
			do {
				try
				{


					cout << "Ilk kullanmak istediginiz zari giriniz" << endl << "1. zar icin 1 yaziniz, 1. zarin degeri: " << move1 << endl << "2. zar icin 2 yaziniz, 2. zarin degeri : " << move2 << endl;
					cin >> choice;
					if (choice == -1) {
						backgammon.getSaveTahta(p1,p2,turns+2);
					}
					if (!cin)
					{
						throw 3;

					}
					cout << endl << endl;
					check = true;
				}

				catch (int)
				{
					cout << endl << endl << "Girilen deger yanlis, lutfen zar secmek icin 1 veya 2 giriniz";
					cin.clear();
					cin.ignore(100, '\n');
					cout << endl;
				}
			} while (check == false);
		}
		switch (choice)
		{
		case 1:
			if (move3 != 0)
			{
				moved = rowChoice - move3;
				errorCheck = backgammon.moveTasPenaltyBeyaz(rowChoice, moved);
				if (errorCheck == 0)
				{
					move3 = 0;
					penalty = backgammon.checkPenaltyBeyaz();
					backgammon.PrintTahta();
					
				}
				break;
			}
			moved = rowChoice - move1;
			errorCheck = backgammon.moveTasPenaltyBeyaz(rowChoice, moved);
			if (errorCheck == 0)
			{
				move1 = 0;
				penalty = backgammon.checkPenaltyBeyaz();
				backgammon.PrintTahta();
				
			}
			break;
		case 2:
			if (move4 != 0)
			{
				moved = rowChoice - move4;
				errorCheck = backgammon.moveTasPenaltyBeyaz(rowChoice, moved);
				if (errorCheck == 0)
				{
					move4 = 0;
					penalty = backgammon.checkPenaltyBeyaz();
					backgammon.PrintTahta();
					
				}
				break;
			}

			moved = rowChoice - move2;
			errorCheck = backgammon.moveTasPenaltyBeyaz(rowChoice, moved);
			if (errorCheck == 0)
			{
				move2 = 0;
				penalty = backgammon.checkPenaltyBeyaz();
				backgammon.PrintTahta();
				
			}
			break;
		default:
			cout << "Girdiniz deger yanlis. Lutfen asagidan baslamak istediginiz zari seciniz." << endl << endl;
			break;
		}
	}

	do
	{
		if (move1 != 0 && move2 == 0)
		{
			cout << "Kalan zar hareketiniz " << move1 << endl;
			choice = 1;
		}
		else if (move2 != 0 && move1 == 0)
		{
			cout << "Kalan zar hareketiniz " << move2 << endl;
			choice = 2;
		}
		else
		{
			check = false;
			do {
				try
				{


					cout << "Ilk kullanmak istediginiz zari giriniz." << endl << "1. zar icin 1 yaziniz, 1. zarin degeri:  " << move1 << endl << "2. zar icin 2 yaziniz, 2. zarin degeri:  " << move2 << endl;
					cin >> choice;
					if (choice == -1) {
						backgammon.getSaveTahta(p1, p2, turns + 2);
					}
					if (!cin)
					{
						throw 3;

					}
					cout << endl << endl;
					check = true;
				}

				catch (int)
				{
					cout << endl << endl << "Girilen deger yanlis, lutfen zar secmek icin 1 veya 2 giriniz";
					cin.clear();
					cin.ignore(100, '\n');
					cout << endl;
				}
			} while (check == false);
		}

		check = false;
		do {
			try
			{

				cout << "Oynamak istediginiz tasin sirasini seciniz ";
				cin >> rowChoice;
				if (rowChoice == -1) {
					backgammon.getSaveTahta(p1, p2, turns + 2);
				}

				if (!cin)
				{
					throw 4;

				}
				cout << endl << endl;
				check = true;
			}

			catch (int)
			{
				cout << endl << endl << "Girilen sira yanlis lutfen 1 ve 24 arasinda bir deger giriniz";
				cin.clear();
				cin.ignore(100, '\n');
				cout << endl;
			}
		} while (check == false);


		switch (choice)
		{
		case 1:
			if (move3 != 0)
			{
				moved = rowChoice - move3;
				errorCheck = backgammon.moveTasBeyaz(rowChoice, moved);
				if (errorCheck == 0)
				{
					move3 = 0;

					if (backgammon.checkBeyazWin())
					{
						return true;
					}
				}
				break;
			}
			moved = rowChoice - move1;
			errorCheck = backgammon.moveTasBeyaz(rowChoice, moved);
			if (errorCheck == 0)
			{
				move1 = 0;

				if (backgammon.checkBeyazWin())
				{
					return true;
				}
			}
			break;
		case 2:
			if (move4 != 0)
			{
				moved = rowChoice - move4;
				errorCheck = backgammon.moveTasBeyaz(rowChoice, moved);
				if (errorCheck == 0)
				{
					move4 = 0;

					if (backgammon.checkBeyazWin())
					{
						return true;
					}

				}
				break;
			}

			moved = rowChoice - move2;
			errorCheck = backgammon.moveTasBeyaz(rowChoice, moved);
			if (errorCheck == 0)
			{
				move2 = 0;

				if (backgammon.checkBeyazWin())
				{
					return true;
				}
			}
			break;
		default:
			cout << "Girdiniz deger yanlis. Lutfen asagidan baslamak istediginiz zari seciniz." << endl << endl;
			break;
		}

		backgammon.PrintTahta();
		
		
	} while (move1 != 0 || move2 != 0);
	backgammon.saveTahta(turns, save,dice1.getZar(),dice2.getZar(),p1);
	turns++;
	return false;
}

bool siyahTurn(tahta& backgammon, string p1, string p2)
{
	int move1 = 0;
	int move2 = 0;
	int move3 = 0;
	int move4 = 0;

	bool check = false;
	bool stuck;
	bool penalty;

	int errorCheck;

	int rowChoice;
	int moved;
	zar dice1, dice2;
	int choice;

	cout << p2 << ", siyah icin zar atiliyor" << endl << endl;
	cout << "Birinci zar : ";
	move1 = dice1.zarAt();
	move2 = dice2.zarAt();

	cout << move1 << "ve ikinci zar : " << move2 << endl << endl;

	if (move1 == move2)
	{

		cout << "Cift zar atildi, her zar icin iki kez oynama hakki" << endl << endl;
		move3 = move1;
		move4 = move2;
	}

	penalty = backgammon.checkPenaltySiyah();

	while (penalty)
	{
		rowChoice = -1;
		stuck = backgammon.checkStuckSiyah(move1, move2);
		if (stuck)
		{
			cout << "Oynanacak tas olmadigi icin turunuz geciliyor." << endl;

			return false;
		}
		if (move1 != 0 && move2 == 0)
		{
			cout << "Kalan zar hareketiniz: " << move1 << endl;
			choice = 1;
		}
		else if (move2 != 0 && move1 == 0)
		{
			cout << "Kalan zar hareketiniz: " << move2 << endl;
			choice = 2;
		}
		else
		{

			check = false;
			do {
				try
				{


					cout << "Ilk kullanmak istediginiz zari giriniz." << endl << "1. zar icin 1 yaziniz, 1. zarin degeri:  " << move1 << endl << "2. zar icin 2 yaziniz, 2. zarin degeri: " << move2 << endl << ":";
					cin >> choice;
					if (choice == -1) {
						backgammon.getSaveTahta(p1, p2, turns + 2);
					}
					if (!cin)
					{
						throw 3;

					}
					cout << endl << endl;
					check = true;
				}

				catch (int)
				{
					cout << endl << endl << "Girilen deger yanlis, lutfen zar secmek icin 1 veya 2 giriniz";
					cin.clear();
					cin.ignore(100, '\n');
					cout << endl;
				}
			} while (check == false);
		}
		switch (choice)
		{
		case 1:
			if (move3 != 0)
			{
				moved = rowChoice + move3;
				errorCheck = backgammon.moveTasPenaltySiyah(rowChoice, moved);
				if (errorCheck == 0)
				{
					move3 = 0;
					penalty = backgammon.checkPenaltySiyah();
					backgammon.PrintTahta();
					
				}
				break;
			}
			moved = rowChoice + move1;
			errorCheck = backgammon.moveTasPenaltySiyah(rowChoice, moved);
			if (errorCheck == 0)
			{
				move1 = 0;
				penalty = backgammon.checkPenaltySiyah();
				backgammon.PrintTahta();
				
			}
			break;
		case 2:
			if (move4 != 0)
			{
				moved = rowChoice + move4;
				errorCheck = backgammon.moveTasPenaltySiyah(rowChoice, moved);
				if (errorCheck == 0)
				{
					move4 = 0;
					penalty = backgammon.checkPenaltySiyah();
					backgammon.PrintTahta();
					
				}

				break;
			}

			moved = rowChoice + move2;
			errorCheck = backgammon.moveTasPenaltySiyah(rowChoice, moved);
			if (errorCheck == 0)
			{
				move2 = 0;
				penalty = backgammon.checkPenaltySiyah();
				backgammon.PrintTahta();
				
			}
			break;
		default:
			cout << "Girdiniz deger yanlis. Lutfen asagidan baslamak istediginiz zari seciniz." << endl << endl;
			break;
		}
	}

	do
	{
		if (move1 != 0 && move2 == 0)
		{
			cout << "Kalan zar hareketiniz " << move1 << endl;
			choice = 1;
		}
		else if (move2 != 0 && move1 == 0)
		{
			cout << "Kalan zar hareketiniz " << move2 << endl;
			choice = 2;
		}
		else
		{
			check = false;
			do {
				try
				{


					cout << "Ilk kullanmak istediginiz zari giriniz." << endl << "1. zar icin 1 yaziniz, 1. zarin degeri:  " << move1 << endl << "2. zar icin 2 yaziniz, 2. zarin degeri:  " << move2 << endl;
					cin >> choice;
					if (choice == -1) {
						backgammon.getSaveTahta(p1, p2, turns + 2);
					}
					if (!cin)
					{
						throw 3;

					}
					cout << endl << endl;
					check = true;
				}

				catch (int)
				{
					cout << endl << endl << "Girilen deger yanlis, lutfen zar secmek icin 1 veya 2 giriniz";
					cin.clear();
					cin.ignore(100, '\n');
					cout << endl;
				}
			} while (check == false);
		}

		check = false;
		do {
			try
			{


				cout << "Oynamak istediginiz tasin sirasini seciniz ";
				cin >> rowChoice;
				if (rowChoice == -1) {
					backgammon.getSaveTahta(p1, p2, turns + 2);
				}
				if (!cin)
				{
					throw 4;

				}
				cout << endl << endl;
				check = true;
			}

			catch (int)
			{
				cout << endl << endl << "Girilen sira yanlis lutfen 1 ve 24 arasinda bir deger giriniz";
				cin.clear();
				cin.ignore(100, '\n');
				cout << endl;
			}
		} while (check == false);


		switch (choice)
		{
		case 1:
			if (move3 != 0)
			{
				moved = rowChoice + move3;
				errorCheck = backgammon.moveTasSiyah(rowChoice, moved);
				if (errorCheck == 0)
				{
					move3 = 0;


					if (backgammon.checkSiyahWin())
					{
						return true;
					}
				}
				break;
			}
			moved = rowChoice + move1;
			errorCheck = backgammon.moveTasSiyah(rowChoice, moved);
			if (errorCheck == 0)
			{
				move1 = 0;

				if (backgammon.checkSiyahWin())
				{
					return true;
				}
			}
			break;
		case 2:
			if (move4 != 0)
			{
				moved = rowChoice + move4;
				errorCheck = backgammon.moveTasSiyah(rowChoice, moved);
				if (errorCheck == 0)
				{
					move4 = 0;

					if (backgammon.checkSiyahWin())
					{
						return true;
					}
				}
				break;
			}

			moved = rowChoice + move2;
			errorCheck = backgammon.moveTasSiyah(rowChoice, moved);
			if (errorCheck == 0)
			{
				move2 = 0;

				if (backgammon.checkSiyahWin())
				{
					return true;
				}
			}
			break;
		default:
			cout << "Girdiniz deger yanlis. Lutfen asagidan baslamak istediginiz zari seciniz." << endl << endl;
			break;
		}

		backgammon.PrintTahta();
		
		
	} while (move1 != 0 || move2 != 0);
	backgammon.saveTahta(turns, save, dice1.getZar(), dice2.getZar(), p2);
	turns++;
	return false;
}
