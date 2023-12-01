#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <chrono>
#include <sstream>
#include <numeric>

std::map<std::string, uint64_t>
    numbers{{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

uint64_t with_letters()
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
        std::pair<size_t, size_t> firstl{90, 0}, lastl{0, 0}, firstn{90, 0}, lastn{0, 0};

        for (const auto &[k, v] : numbers)
        {
            if (const auto found = line.find(k); found != std::string::npos)
            {
                if (found <= firstl.first)
                {
                    firstl = {found, v};
                }
            }

            if (const auto found = line.rfind(k); found != std::string::npos)
            {
                if (found >= lastl.first)
                {
                    lastl = {found, v};
                }
            }
        }

        for (auto it = 0; it < firstl.first; ++it)
        {
            if (std::isdigit(line.at(it)))
            {
                firstn = {it, line[it] - '0'};
                break;
            }
        }

        for (auto it = line.size() - 1; it >= lastl.first; --it)
        {
            if (std::isdigit(line.at(it)))
            {
                lastn = {it, line[it] - '0'};
                break;
            }
        }

        sum += firstl.first < firstn.first ? firstl.second * 10 : firstn.second * 10;
        sum += lastl.first > lastn.first ? lastl.second : lastn.second;
    }
    input.close();

    return sum;
}

uint64_t sum_call()
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
        uint64_t n{0};
        for (auto it = line.begin(); it != line.end(); ++it)
        {
            if (std::isdigit(*it))
            {
                n = (*it - '0') * 10;
                break;
            }
        }

        for (auto it = line.rbegin(); it != line.rend(); ++it)
        {
            if (std::isdigit(*it))
            {
                n += *it - '0';
                break;
            }
        }

        sum += n;
    }
    input.close();

    return sum;
}

void part_1()
{
    const auto t_start = std::chrono::high_resolution_clock::now();
    auto sumcal = sum_call();
    const auto t_stop = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t_stop - t_start);

    std::cout << "Part 1: " << sumcal << '\n';
    std::cout << "It took " << duration.count() << "us \n";
    return;
}

void part_2()
{
    const auto t_start = std::chrono::high_resolution_clock::now();
    auto l = with_letters();
    const auto t_stop = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t_stop - t_start);

    std::cout << "Part 2: " << l << '\n';
    std::cout << "It took " << duration.count() << "us \n";
    return;
}

int main()
{
    part_1();
    part_2();
    return 0;
}