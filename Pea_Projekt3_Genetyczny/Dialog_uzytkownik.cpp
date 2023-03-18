#include "Dialog_uzytkownik.h"

void Dialog_uzytkownik::dialog()
{
	Matrix matrix;
	cout << "Autor Jakub Budzilo\nWitam w TSP\n\n";
	matrix.initialization();
	int x;
	int time = kryterium_stopu();
	int paths = sciezki_wybor();
	int type_mutation = mutacja_wybor();
	int factor_crossing = wspolczynnik_krzyzowanie();
	int factor_mutation = wspolczynnik_mutacje();
	for (;;)
	{
		cout << "0.Wybierz macierz" << endl;
		cout << "1.Zamien kryterium_stopu" << endl;
		cout << "2.Zmiana ilosci sciezek" << endl;
		cout << "3.Uruchom algorytm" << endl;
		cout << "4.Wybierz typ mutacji" << endl;
		cout << "5.Zmien wspolczynnik krzyzowania" << endl;
		cout << "6.Zmien wspolczynnik mutacji" << endl;
		cout << "7.Opusc program" << endl;

		x = duza_liczba(0, 7);

		switch (x)
		{
		case 0:
		{
			matrix.initialization();
		}
		break;
		case 1:
		{
			time = kryterium_stopu();
		}
		break;
		case 2:
		{
			paths =  sciezki_wybor();
		}
		break;
		case 3:
		{
			for (int i = 0; i < 6; i++) {
				GeneticAlgorithm* geneticlgorithm = new GeneticAlgorithm(matrix.get_matrix());
				geneticlgorithm->run(time, paths, factor_crossing, factor_mutation, type_mutation);
				delete geneticlgorithm;
			}
		}
		break;
		case 4:
		{
			type_mutation = mutacja_wybor();
		}
		break;
		case 5:
		{
			factor_crossing = wspolczynnik_krzyzowanie();
		}
		break;
		case 6:
		{
			factor_mutation = wspolczynnik_mutacje();
		}
		break;
		case 7:
		{
			exit(0);
		}
		break;
		}
	}
}

int Dialog_uzytkownik::duza_liczba(int min, int max)
{
	cout << "Podaj wartosc:";
	string text;
	cin >> text;
	while (!czy_liczba_nieujemna(text))
	{
	et1:
		cout << "Niepoprawny znak";
		cin.clear();
		cin.ignore(50, '\n');
		cout << endl << "Podaj wartosc:";
		cin >> text;

	}
	int x = stoi(text);
	if (x > max || x < min)
		goto et1;
	cout << "\n";
	return x;
}
int Dialog_uzytkownik::duza_liczba()
{
	cout << "Podaj wartosc:";
	string text;
	cin >> text;
	while (!czy_liczba(text))
	{

		cout << "Niepoprawny znak";
		cin.clear();
		cin.ignore(50, '\n');
		cout << endl << "Podaj wartosc:";
		cin >> text;

	}
	int x = stoi(text);
	cout << "\n";
	return x;
}
bool Dialog_uzytkownik::czy_liczba_nieujemna(string text)
{
	for (int i = 0; i < text.length(); i++) if (text[i] > '9' || text[i] < '0') return false;

	return true;
}

bool Dialog_uzytkownik::czy_liczba(string text)
{

	for (int i = 0; i < text.length(); i++) if (text[i] > '9' || text[i] < '0')
		if (!((text[0] == '-') && i == 0))
			return false;

	return true;
}

int Dialog_uzytkownik::kryterium_stopu() {
	int time;
	cout << "Podaj czas wykonywania algorytmu w sekundach:\n";
	do {
		time = duza_liczba(1, INT_MAX);
	} while (time <= 0);
	return time;
}
int Dialog_uzytkownik::sciezki_wybor() {
	int sciezki;
	cout << "Podaj ilosc sciezek\n";
	sciezki = duza_liczba(1, INT_MAX);
	return sciezki;
}

int Dialog_uzytkownik::mutacja_wybor() {
	int mutacja;
	cout << "Podaj mutacje:\n'1' = SWAP\n'2' = INVERSE\n";
	mutacja = duza_liczba(1, 2);
	return mutacja;
}
int Dialog_uzytkownik::wspolczynnik_krzyzowanie()
{
	int wspolczynnik;
	cout << "Podaj wspolczynnik krzyzowania w procentach\n";
	wspolczynnik = duza_liczba(1, 100);
	return wspolczynnik;

}

int Dialog_uzytkownik::wspolczynnik_mutacje()
{
	int wspolczynnik;
	cout << "Podaj wspolczynnik mutacji w procentach\n";
	wspolczynnik = duza_liczba(1, 100);
	return wspolczynnik;

}