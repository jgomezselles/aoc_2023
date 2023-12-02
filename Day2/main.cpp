#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <chrono>
#include <sstream>
#include <numeric>
#include <algorithm>

const std::map<std::string, size_t> max{{"red", 12}, {"green", 13}, {"blue", 14}};

bool possible_game(const std::string &col)
{
    std::stringstream ss(col);
    std::string tmp;
    while (getline(ss, tmp, ','))
    {
        tmp.erase(std::remove_if(tmp.begin(), tmp.end(), isspace), tmp.end());
        std::string color, n;

        for (const auto &c : tmp)
        {
            if (isdigit(c))
            {
                n.push_back(c);
            }
            else
            {
                color.push_back(c);
            }
        }

        if (max.at(color) < stoi(n))
        {
            return false;
        }
    }

    return true;
}

size_t sum_ids(std::stringstream ss)
{
    std::string tmp;
    getline(ss, tmp, ':');
    size_t id = stoi(tmp.substr(tmp.find(' ')));
    while (getline(ss, tmp, ';'))
    {
        if (!possible_game(tmp))
        {
            return 0;
        }
    }
    return id;
}

uint64_t sum_games()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        exit(1);
    }

    std::string line;
    uint64_t sum{0};
    while (getline(input, line))
    {
        sum += sum_ids(std::stringstream(line));
    }
    input.close();

    return sum;
}

void part_1()
{
    const auto t_start = std::chrono::high_resolution_clock::now();
    auto sumcal = sum_games();
    const auto t_stop = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t_stop - t_start);

    std::cout << "Part 1: " << sumcal << '\n';
    std::cout << "It took " << duration.count() << "us \n";
    return;
}

void fill_mins(const std::string &col, std::map<std::string, int> &mins)
{
    std::stringstream ss(col);
    std::string tmp;
    while (getline(ss, tmp, ','))
    {
        tmp.erase(std::remove_if(tmp.begin(), tmp.end(), isspace), tmp.end());
        std::string color, n;

        for (const auto &c : tmp)
        {
            if (isdigit(c))
            {
                n.push_back(c);
            }
            else
                (color.push_back(c));
        }
        mins.at(color) = std::max(stoi(n), mins.at(color));
    }
    return;
}

size_t sum_powas(std::stringstream ss)
{
    std::string tmp;
    getline(ss, tmp, ':');

    std::map<std::string, int> mins{{"red", 0}, {"green", 0}, {"blue", 0}};

    while (getline(ss, tmp, ';'))
    {
        fill_mins(tmp, mins);
    }

    size_t res{1};
    for (const auto &[_, v] : mins)
    {
        res *= v;
    }

    return res;
}

uint64_t powa()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        exit(1);
    }

    std::string line;
    uint64_t sum{0};
    while (getline(input, line))
    {
        sum += sum_powas(std::stringstream(line));
    }
    input.close();

    return sum;
}

void part_2()
{
    const auto t_start = std::chrono::high_resolution_clock::now();
    auto res = powa();
    const auto t_stop = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t_stop - t_start);

    std::cout << "Part 2: " << res << '\n';
    std::cout << "It took " << duration.count() << "us \n";
    return;
}

int main()
{
    part_1();
    part_2();
    return 0;
}