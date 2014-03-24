#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <parallel/algorithm>

typedef std::map<std::string, std::pair<float, float>> Dict;

std::vector<std::string> recipe;
std::vector<std::string> combination;

Dict d;

float total_bookings;
float total_visits;

void apply_func(std::string s)
{
    total_visits += d[s].first;
    total_bookings += d[s].second;
}

void print_CR(const std::vector<std::string>& v) {
    total_bookings = 0;
    total_visits = 0;

    __gnu_parallel::for_each(v.begin(), v.end(), apply_func);

    float CR = total_bookings / total_visits;
    std::cout << CR << std::endl;
}

void comb(int offset, int k) {
    if (k == 0) {
        print_CR(combination);
        return;
    }

    for (unsigned long i = offset; i <= recipe.size() - k; ++i) {
        combination.push_back(recipe[i]);
        comb(i+1, k-1);
        combination.pop_back();
    }
}

int main(int argc, char* argv[]) 
{
    std::string line;

    std::string delimiter = "|";
    std::string recipe_name;
    float visits;
    float bookings;

    while (std::getline(std::cin, line))
    {
        recipe_name = line.substr(0, line.find(delimiter));
        
        line.erase(0, line.find(delimiter) + delimiter.length());

        std::istringstream(line.substr(0, line.find(delimiter))) >> visits;    
        line.erase(0, line.find(delimiter) + delimiter.length());

        std::istringstream(line.substr(0, line.find(delimiter))) >> bookings;
       
        d[recipe_name] = std::make_pair(visits, bookings); 

    }

    for (auto it = d.begin(); it != d.end(); ++it)
    {
        recipe.push_back(it->first);
    }

    std::istringstream iss( argv[1] );
    int choose;

    if (argc > 1)
    {
        iss >> choose;
    }

    else
    {
        choose = 2;
    }
        
    // generate permutations
    std::cout << "x\n";
    comb(0, choose);

    return 0;
            
}
