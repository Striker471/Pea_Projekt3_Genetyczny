#include "GeneticAlgorithm.h"
#include <algorithm>

vector<vector<int>> GeneticAlgorithm::generateInitPath(int number_of_paths, int number_of_crossing) {

       vector<int> basic;
    basic.resize(size_of_matrix - 1);
    for (int i = 1; i < size_of_matrix; i++)
        basic[i - 1] = i;

    vector<vector<int>> all_paths;
    all_paths.resize(number_of_paths + number_of_crossing);
    for (int i = 0; i < number_of_paths + number_of_crossing; i++)
       all_paths[i].resize(size_of_matrix - 1);

    for (int i = 0; i < number_of_paths; i++) {
        all_paths[i] = basic;
        random_shuffle(all_paths[i].begin(), all_paths[i].end());
    }


    //zwracamy przetasowane sciezki
    return all_paths;
}

void GeneticAlgorithm::generate_crossing(int number_of_paths) {

    for (auto& path : crossing)
    {
        path[0] = rand() % number_of_paths ;
        do 
        {
            path[1] = rand() % number_of_paths;
        } while (path[0] == path[1]);
    }
}
    
void GeneticAlgorithm::crossover(vector<vector<int>> &paths, int number_of_paths) {
    int x, y; // miejsca w ktore wstawimy z p1 do p2
    int z = 0; // zmienna do crossing
    for (int current_path = number_of_paths; current_path < paths.size(); current_path++)
    {   
        x = rand() % (size_of_matrix - 1);    
        do
        {
            y = rand() % (size_of_matrix - 1);
        } while (x == y);
        if (x > y)
            swap(x, y);
        vector<int> copy_path;
        copy_path.resize(y - x + 1);
        int iter = 0;
        for (int j = x; j < y + 1; j++)
        {
            //crossing[i][0] crossing [i][1]
            paths[current_path][j] = paths[crossing[z][0]][j];
            copy_path[iter] = paths[crossing[z][0]][j];
            iter++;
        }

                
                   
        int next_place_p2 = y + 1;
        int next_place_new = y + 1;
        int faster_break = y - x + 1;
        for (int i = 0; i < size_of_matrix - 1; i++)
        {
            if (next_place_p2 == size_of_matrix - 1)
                next_place_p2 = 0;
            if (next_place_new == size_of_matrix - 1)
                next_place_new = 0;

            if (find(copy_path.begin(), copy_path.end(), paths[crossing[z][1]][next_place_p2]) == copy_path.end())
            {
                paths[current_path][next_place_new] = paths[crossing[z][1]][next_place_p2];
                faster_break++;
                next_place_new++;
            }

            if(faster_break == size_of_matrix - 1)
                break;
            next_place_p2++;
        }
        z++;
    }
}

void GeneticAlgorithm::sort_paths(vector<vector<int>> &paths){

    sort(paths.begin(), paths.end(), [this](auto&& l, auto&& r) { return getPathCost(l) < getPathCost(r); });
}

void GeneticAlgorithm::mutation_swap(vector<vector<int>> & paths, int probability, int number_of_paths, int method) {
    for (int i = 0; i < paths.size(); i++)
    {
        int z = rand() % (100/probability);
        if (z == 0)
        {
            int x, y;
            x = rand() % (size_of_matrix - 1);
            do
            {
                y = rand() % (size_of_matrix - 1);
            } while (x == y);
            if (method == 1)
                swap(paths[i][x], paths[i][y]);
            else if (method == 2)
            {
                if (x < y)
                    reverse(paths[i].begin() + x, paths[i].begin() + y);
                else
                    reverse(paths[i].begin() + y, paths[i].begin() + x);
        }
        }
    }
}



    int GeneticAlgorithm::getPathCost(vector <int> path) { //Liczenie kosztu dla danej œcie¿ki
    int cost = 0;

    cost += matrix[0][path[0]];
    for (int i = 0; i < path.size() - 1; i++)
        cost += matrix[path[i]][path[i + 1]];
    cost += matrix[path[path.size() - 1]][0];

    return cost;
}



void GeneticAlgorithm::run(int timetostop,int number_of_paths, int flat_of_crossing, int wspolczynnik_mutacji, int method) {

    start = Time::read_QPC();
    int number_of_crossing = number_of_paths * flat_of_crossing/ 100;
    crossing.resize(number_of_crossing);
    for (auto& path : crossing)
        path.resize(2);
    vector<vector<int>> paths = generateInitPath(number_of_paths, number_of_crossing);
    vector<int> best_path;
    int best_cost = INT_MAX;

    while (endTime < timetostop)
    {
        generate_crossing(number_of_paths);
     
        crossover(paths, number_of_paths);
 
        mutation_swap(paths, wspolczynnik_mutacji, number_of_paths, method);

        sort_paths(paths);

        endTime = ((Time::read_QPC() - start) / frequency);

        int cost = getPathCost(paths[0]);
        if (cost < best_cost)
        {
            best_cost = cost;
            best_path = paths[0];
            //cout << " Najlepszy koszt : " << best_cost << endl;;
        }
       
    }
   
        //displayPath(best_path);
    
    cout << " Najlepszy koszt : " << best_cost << endl;;
}



void GeneticAlgorithm::displayPath(std::vector<int> path) { //Wyœwietlanie koñcowego wyniku
    cout << "\n\nOdnaleziona droga: " << endl;
    cout << 0 << " -> ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " -> ";
    }
    cout << 0 << endl;
}

void GeneticAlgorithm::test() {
    auto z = generateInitPath(10,1);
    //crossover(z, 10);
    //mutation_swap(z, 1);
    for (int i = 0; i < 11; i++)
    {
       int x = getPathCost(z[i]);
       cout << x << endl;
    }
    sort_paths(z);
    for (int i = 0; i < 11; i++)
    {
        int x = getPathCost(z[i]);
        cout << x << endl;
    }


}