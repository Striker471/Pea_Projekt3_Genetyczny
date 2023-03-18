#pragma once
#include <iostream>
#include <string>
#include "Matrix.h"
#include "GeneticAlgorithm.h"

using std::cout; using std::endl; using std::string; using std::cin;

class Dialog_uzytkownik
{
public:
	void dialog();
	static int duza_liczba();
	static int duza_liczba(int min, int max);
	static bool czy_liczba_nieujemna(std::string text);
	static bool czy_liczba(std::string text);
	static int kryterium_stopu();
	static int sciezki_wybor();
	static int mutacja_wybor();
	static int wspolczynnik_krzyzowanie();
	static int wspolczynnik_mutacje();
};

