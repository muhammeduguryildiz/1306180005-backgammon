#include "tahta.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

tahta::tahta(void)
{
	ToplamSiyah = 0;
	ToplamBeyaz = 0;

	for (int i = 0; i < 24; i++)
	{
		rows[i].setRow(i);
	}
	SiyahPenalty.setRow(-1);
	BeyazPenalty.setRow(24);
}

bool tahta::checkStuckBeyaz(int x, int y)
{
	if (rows[24 - x].getNumofSiyah() > 1 && rows[24 - y].getNumofSiyah() > 1)
	{
		return true;
	}
	else
		return false;
}

bool tahta::checkStuckSiyah(int x, int y)
{
	if (rows[-1 + x].getNumOfBeyaz() > 1 && rows[-1 + y].getNumOfBeyaz() > 1)
	{
		return true;
	}
	else
		return false;
}

bool tahta::checkPenaltyBeyaz()
{
	if (BeyazPenalty.getNumOfBeyaz() > 0)
	{
		cout << "Eger oynayabiliyorsaniz lutfen kirik tasinizi oynayiniz." << endl;
		return true;
	}
	else
		return false;
}

bool tahta::checkPenaltySiyah()
{
	if (SiyahPenalty.getNumofSiyah() > 0)
	{
		cout << "Eger oynayabiliyorsaniz lutfen kirik tasinizi oynayiniz." << endl;
		return true;
	}
	else
		return false;
}

int tahta::moveTasPenaltyBeyaz(int row, int choice)
{
	int moved = choice - 1;
	int length;
	if (rows[moved].getNumofSiyah() > 1)
	{
		cout << "Ýki veya daha fazla rakip tasi olan siraya tas oynanamaz!" << endl;
		return 1;
	}
	else if (rows[moved].getNumofSiyah() == 1)
	{
		length = BeyazPenalty.getNumOfBeyaz();
		BeyazPenalty.setRow(24);
		BeyazPenalty.BeyazAzalt();

		rows[moved].SiyahAzalt();
		length = rows[moved].getNumOfBeyaz();

		rows[moved].RowGuncelleBeyaz(length, moved); //7 and 4
		rows[moved].BeyazArttir();
		SiyahPenalty.SiyahArttir();
		SiyahPenalty.RowGuncelleSiyah(SiyahPenalty.getNumofSiyah() - 1, 0); //might switch 15 to lower
		return 0;
	}

	else if (rows[moved].getNumOfBeyaz() == 6) // untrue rule
	{
		cout << "Engellenmis hareket. Siradaki maksimum tas sayisina ulasildi." << endl;
		return 1;
	}

	else
	{
		length = BeyazPenalty.getNumOfBeyaz();

		BeyazPenalty.setRow(24);

		BeyazPenalty.BeyazAzalt();

		length = rows[moved].getNumOfBeyaz();
		rows[moved].RowGuncelleBeyaz(length, moved);
		rows[moved].BeyazArttir();
		return 0;
	}
}

int tahta::moveTasPenaltySiyah(int row, int choice)
{
	int moved = choice - 1;
	int length;
	if (rows[moved].getNumOfBeyaz() > 1)
	{
		cout << "Ýki veya daha fazla rakip tasi olan siraya tas oynanamaz!" << endl;
		return 1;
	}
	else if (rows[moved].getNumOfBeyaz() == 1)
	{
		length = SiyahPenalty.getNumofSiyah();
		SiyahPenalty.setRow(-1);
		SiyahPenalty.SiyahAzalt();

		rows[moved].BeyazAzalt();
		length = rows[moved].getNumofSiyah();

		rows[moved].RowGuncelleSiyah(length, moved); //7 and 4
		rows[moved].SiyahArttir();
		BeyazPenalty.BeyazArttir();
		BeyazPenalty.RowGuncelleBeyaz(BeyazPenalty.getNumOfBeyaz() - 1, 15); //might switch 15 to lower
		return 0;
	}

	else if (rows[moved].getNumofSiyah() == 6) // untrue rule
	{
		cout << "Engellenmis hareket. Siradaki maksimum tas sayisina ulasildi." << endl;
		return 1;
	}

	else
	{
		length = SiyahPenalty.getNumofSiyah();

		SiyahPenalty.setRow(-1);

		SiyahPenalty.SiyahAzalt();

		length = rows[moved].getNumofSiyah();
		rows[moved].RowGuncelleSiyah(length, moved);
		rows[moved].SiyahArttir();
		return 0;
	}
}

int tahta::moveTasBeyaz(int x, int y)
{
	int index = x - 1;
	int moved = y - 1;
	int length;

	if (rows[index].getNumOfBeyaz() == 0)
	{
		cout << "Bu sirada hic tasiniz yok,lutfen tekrar deneyiniz." << endl;
		return 1;
	}
	if (moved <= -1)
	{
		int homeSum = 0;
		int i;
		for (i = 0; i < 6; i++)
		{
			homeSum = homeSum + rows[i].getNumOfBeyaz();
		}
		homeSum = homeSum + ToplamBeyaz;
		if (homeSum == 15)
		{
			ToplamBeyaz++;
			length = rows[index].getNumOfBeyaz();
			rows[index].RowGuncelleSil(length, index);
			rows[index].BeyazAzalt();
			return 0;
		}
		else
		{
			cout << "Tasimaya baslamak icin tum parcalarinizin ev tahtasinda olmasi gerekir. Tekrar deneyin." << endl;
			return 1;
		}
	}
	else if (rows[moved].getNumofSiyah() > 1)
	{
		cout << "Ýki veya daha fazla rakip tasi olan siraya tas oynanamaz!" << endl;
		return 1;
	}
	else if (rows[moved].getNumofSiyah() == 1)
	{
		length = rows[index].getNumOfBeyaz();
		rows[index].RowGuncelleSil(length, index);
		rows[index].BeyazAzalt();

		rows[moved].SiyahAzalt();
		length = rows[moved].getNumOfBeyaz();

		rows[moved].RowGuncelleBeyaz(length, moved);
		rows[moved].BeyazArttir();
		SiyahPenalty.SiyahArttir();
		SiyahPenalty.RowGuncelleSiyah(SiyahPenalty.getNumofSiyah() - 1, 0); //might switch 15 to lower
		return 0;
	}
	else if (rows[moved].getNumOfBeyaz() == 6) // untrue rule
	{
		cout << "Engellenmis hareket. Siradaki maksimum tas sayisina ulasildi." << endl;
		return 1;
	}
	else
	{
		length = rows[index].getNumOfBeyaz();

		rows[index].RowGuncelleSil(length, index);

		rows[index].BeyazAzalt();

		length = rows[moved].getNumOfBeyaz();
		rows[moved].RowGuncelleBeyaz(length, moved);
		rows[moved].BeyazArttir();
		return 0;
	}
}

int tahta::moveTasSiyah(int x, int y)
{
	int index = x - 1;
	int moved = y - 1;
	int length;
	//check legality
	if (rows[index].getNumofSiyah() == 0)
	{
		cout << "Bu sirada hic tasiniz yok,lutfen tekrar deneyiniz." << endl;
		return 1;
	}

	if (moved >= 24)
	{
		int homeSum = 0;
		int i;
		for (i = 0; i < 6; i++)
		{
			homeSum = homeSum + rows[i].getNumofSiyah();
		}

		homeSum = homeSum + ToplamSiyah;
		if (homeSum == 15)
		{
			ToplamSiyah++;
			length = rows[index].getNumofSiyah();
			rows[index].RowGuncelleSil(length, index);
			rows[index].SiyahAzalt();
			return 0;
		}
		else
		{
			cout << "Tasimaya baslamak icin tum parcalarinizin ev tahtasinda olmasi gerekir. Tekrar deneyin." << endl;
			return 1;
		}
	}
	else if (rows[moved].getNumOfBeyaz() > 1)
	{
		cout << "Ýki veya daha fazla rakip tasi olan siraya tas oynanamaz!" << endl;
		return 1;
	}
	else if (rows[moved].getNumOfBeyaz() == 1)
	{
		length = rows[index].getNumofSiyah();
		rows[index].RowGuncelleSil(length, index);
		rows[index].SiyahAzalt();

		rows[moved].BeyazAzalt();

		length = rows[moved].getNumofSiyah();
		rows[moved].RowGuncelleSiyah(length, moved);
		rows[moved].SiyahArttir();
		BeyazPenalty.BeyazArttir();
		BeyazPenalty.RowGuncelleBeyaz(BeyazPenalty.getNumOfBeyaz() - 1, 15); //might switch zero to higher
		return 0;
	}
	else if (rows[moved].getNumofSiyah() == 6)
	{
		cout << "Engellenmis hareket. Siradaki maksimum tas sayisina ulasildi." << endl;
		return 1;
	}
	else
	{
		length = rows[index].getNumofSiyah();

		rows[index].RowGuncelleSil(length, index);

		rows[index].SiyahAzalt();

		length = rows[moved].getNumofSiyah();
		rows[moved].RowGuncelleSiyah(length, moved);
		rows[moved].SiyahArttir();
		return 0;
	}
}

int tahta::numOfSiyah(int x)
{
	return rows[x].getNumofSiyah();
}

int tahta::numOfBeyaz(int x)
{
	return rows[x].getNumOfBeyaz();
}

bool tahta::checkBeyazWin()
{
	if (ToplamBeyaz == 15)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool tahta::checkSiyahWin()
{
	if (ToplamSiyah == 15)
	{
		return true;
	}
	else
	{
		return false;
	}
}


tahta::~tahta(void)
{
}

void tahta::PrintTahta()
{
	cout << "######################" << endl;
	cout << "12" << " ";
	rows[11].PrintRow();
	cout << "   ";
	rows[12].PrintRow();
	cout << "  " << "13" << endl;
	cout << "11" << " ";
	rows[10].PrintRow();
	cout << "   ";
	rows[13].PrintRow();
	cout << "  " << "14" << endl;
	cout << "10" << " ";
	rows[9].PrintRow();
	cout << "   ";
	rows[14].PrintRow();
	cout << "  " << "15" << endl;
	cout << '9' << "  ";
	rows[8].PrintRow();
	cout << "   ";
	rows[15].PrintRow();
	cout << "  " << "16" << endl;
	cout << '8' << "  ";
	rows[7].PrintRow();
	cout << "   ";
	rows[16].PrintRow();
	cout << "  " << "17" << endl;
	cout << '7' << "  ";
	rows[6].PrintRow();
	cout << "   ";
	rows[17].PrintRow();
	cout << "  " << "18" << endl;

	cout << "SP ";
	SiyahPenalty.PrintRow();
	cout << "|||||||||  ##" << endl;

	cout << "## ";
	cout << "|||||||||";
	BeyazPenalty.PrintRow();
	cout << "  BP" << endl;

	cout << '6' << "  ";
	rows[5].PrintRow();
	cout << "   ";
	rows[18].PrintRow();
	cout << "  " << "19" << endl;
	cout << '5' << "  ";
	rows[4].PrintRow();
	cout << "   ";
	rows[19].PrintRow();
	cout << "  " << "20" << endl;
	cout << '4' << "  ";
	rows[3].PrintRow();
	cout << "   ";
	rows[20].PrintRow();
	cout << "  " << "21" << endl;
	cout << "3" << "  ";
	rows[2].PrintRow();
	cout << "   ";
	rows[21].PrintRow();
	cout << "  " << "22" << endl;
	cout << "2" << "  ";
	rows[1].PrintRow();
	cout << "   ";
	rows[22].PrintRow();
	cout << "  " << "23" << endl;
	cout << "1" << "  ";
	rows[0].PrintRow();
	cout << "   ";
	rows[23].PrintRow();
	cout << "  " << "24" << endl;
	cout << "######################" << endl;
}

void tahta::saveTahta(int turn,vector<string>save,int zar1,int zar2,string player)
{
	vector<string>zarlar;
	string saved;
	string row;
	string cikti;
	saved = to_string(turn) + ". tur\n";
	saved += player + " oyuncusunun zarlarý: \n" + "zar 1 :" + to_string(zar1) + "\nzar 2 :" + to_string(zar2) + "\n";
	zarlar.push_back(saved);
	saved = "######################\n";
	save.push_back(saved);
	saved = "12 ";
	row = rows[11].getRow(row);
	saved += row;
	saved += "   ";
	row = rows[12].getRow(row);
	saved += row;
	saved += "  13\n";
	save.push_back(saved);
	saved = "11 ";
	row = rows[10].getRow(row);
	saved += row;
	saved+= "   ";
	row=rows[13].getRow(row);
	saved += row;
	saved += "  14\n";
	save.push_back(saved);
	saved = "10 ";
	row=rows[9].getRow(row);
	saved += row;
	saved += "   ";
	row=rows[14].getRow(row);
	saved += row;
	saved += "  15\n";
	save.push_back(saved);
	saved = "9  ";
	row=rows[8].getRow(row);
	saved += row;
	saved += "   ";
	row=rows[15].getRow(row);
	saved += row;
	saved += "  16\n";
	save.push_back(saved);
	saved = "8  ";
	row=rows[7].getRow(row);
	saved += row;
	saved+= "   ";
	row=rows[16].getRow(row);
	saved += row;
	saved += "  17\n";
	save.push_back(saved);
	saved = "7  ";
	row=rows[6].getRow(row);
	saved += row;
	saved+= "   ";
	row=rows[17].getRow(row);
	saved += row;
	saved+="  18\n";
	save.push_back(saved);

	saved = "SP ";
	row=SiyahPenalty.getRow(row);
	saved += row;
	saved += "|||||||||  ##\n";
	save.push_back(saved);

	saved = "## |||||||||";
	row=BeyazPenalty.getRow(row);
	saved += row;
	saved += "  BP\n";
	save.push_back(saved);

	saved = "6  ";
	row=rows[5].getRow(row);
	saved += row;
	saved += "   ";
	row=rows[18].getRow(row);
	saved+=row;
	saved += "  19\n";
	save.push_back(saved);
	saved = "5  ";
	row=rows[4].getRow(row);
	saved += row;
	saved += "   ";
	row=rows[19].getRow(row);
	saved += row;
	saved += "  20\n";
	save.push_back(saved);
	saved = "4  ";
	row=rows[3].getRow(row);
	saved += row;
	saved += "   ";
	row=rows[20].getRow(row);
	saved += row;
	saved += "  21\n";
	save.push_back(saved);
	saved = "3  ";
	row=rows[2].getRow(row);
	saved += row;
	saved+= "   ";
	row=rows[21].getRow(row);
	saved += row;
	saved += "  22\n";
	save.push_back(saved);
	saved = "2  ";
	row=rows[1].getRow(row);
	saved += row;
	saved+= "   ";
	row=rows[22].getRow(row);
	saved += row;
	saved += "  23\n";
	save.push_back(saved);
	saved = "1  ";
	row=rows[0].getRow(row);
	saved += row;
	saved += "   ";
	row=rows[23].getRow(row);
	saved += row;
	saved += "  24\n";
	save.push_back(saved);
	saved = "######################\n";
	saved += "\n";
	saved += "\n";
	saved += "\n";
	save.push_back(saved);

	if (turn == 1) {
		ofstream cikti_file("table.dat", std::ofstream::out | std::ofstream::trunc);
		ofstream zar_file("dice.txt", std::ofstream::out | std::ofstream::trunc);

	}

	ofstream cikti_file("table.dat", std::ios_base::app);
	if (cikti_file.is_open())
	{
		for (int i = 0; i < save.size(); i++) {
			cikti = save[i];
			cikti_file << cikti;
		}
		cikti_file.close();
	}
	save.clear();

	ofstream zar_file("dice.txt", std::ios_base::app);
	if (zar_file.is_open())
	{
		for (int i = 0; i < zarlar.size(); i++) {
			cikti = zarlar[i];
			zar_file << cikti;
		}
		zar_file.close();
	}
	save.clear();
}

void tahta::getSaveTahta(string p1,string p2,int turn) {
	string oyuncular;
	string cikti;
	vector<string> saveRow;
	vector<int>tasBeyaz;
	vector<int>tasSiyah;
	string row;
	int beyaz=0;
	int siyah=0;
	oyuncular = p1 + ",";
	oyuncular += p2 + ",";
	oyuncular += to_string(turn) + "\n";
	for (int i = 0; i <= 23; i++) {
		row = rows[i].getRow(row);
		saveRow.push_back(row);
	}

	for (int i = 0; i <= 23; i++) {
		beyaz = rows[i].getNumOfBeyaz();
		tasBeyaz.push_back(beyaz);
	}

	for (int i = 0; i <= 23; i++) {
		siyah = rows[i].getNumofSiyah();
		tasSiyah.push_back(siyah);
	}

	ofstream cikti_file("save.txt");
	if (cikti_file.is_open())
	{

		cikti = oyuncular;
		cikti_file << cikti;
		cikti.clear();
		for (int i = 0; i < saveRow.size(); i++) {
			cikti = saveRow[i]+",";
			cikti += to_string(tasBeyaz[i])+",";
			cikti += to_string(tasSiyah[i])+"\n";
			cikti_file << cikti;
		}
		cikti_file.close();
	}
	exit(1);
}

void tahta::loadSaveTahta() {
	const char FileName[] = "save.txt";
	ifstream my_file(FileName);
	string line;
	vector<string> bolum;
	vector<string> oyuncular;
	vector<string> rowlar;
	string rowload;
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


	for (int i = 1; i <= 24; i++) {
		stringstream ss(bolum[i]);
		while (ss.good()) {
			string substr;
			getline(ss, substr, ',');
			rowlar.push_back(substr);
		}
	}

	int x = 0;

	for (int i = 0; i < 24; i++)
	{
		rows[i].setLoadRow(x,rowlar);
		x = x + 3;
	}
	my_file.close();
	SiyahPenalty.setRow(-1);
	BeyazPenalty.setRow(24);
}


