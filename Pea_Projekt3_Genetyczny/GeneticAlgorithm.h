#pragma once
#include <vector>
#include "Time.h"
#include<iostream>

using namespace std;

class GeneticAlgorithm
{
	long long int frequency, start;
	long long int endTime = 0; //Warunek stopu
	Time timee;
	std::vector<std::vector<int>> matrix; //macierz odleglosci miast
	int size_of_matrix;
	vector<vector<int>> crossing;

public: 
	GeneticAlgorithm(std::vector<std::vector<int>> Matrix) : matrix(Matrix), size_of_matrix(Matrix.size()) {
		srand(time(NULL));

		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	}

	vector<vector<int>> generateInitPath(int number_of_paths, int number_of_crossing);
	void generate_crossing(int number_of_paths);
	void crossover(vector<vector<int>> &paths, int number_of_paths);
	void mutation_swap(vector<vector<int>>& paths, int probability, int number_of_paths, int method);
	int getPathCost(vector <int> path);
	void run(int timetostop, int number_of_paths, int wspolczynnik_krzyzowania, int wspolczynnik_mutacji, int method);
	void sort_paths(vector<vector<int>> &paths);
	void displayPath(std::vector<int> path);
	void test();
};

