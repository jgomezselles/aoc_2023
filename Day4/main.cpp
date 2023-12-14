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
#include <optional>

std::map<uint64_t, uint64_t> card_scores;

uint64_t sum_points()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        exit(1);
    }

    uint64_t score{0}, count_line{0};
    std::string line;
    while (getline(input, line))
    {
        ++count_line;
        std::stringstream ss(line);
        std::string numbers;
        getline(ss, numbers, ':');
        getline(ss, numbers, '|');

        std::set<uint64_t> my_numbers;
        std::stringstream ss2(numbers);
        std::string tmp;

        while (getline(ss2, tmp, ' '))
        {
            if (tmp.empty())
            {
                continue;
            }
            my_numbers.emplace(stoi(tmp));
        }

        getline(ss, numbers);

        std::set<uint64_t> winning_numbers;
        std::stringstream ss3(numbers);
        uint64_t tmp_score{0}, tmp_score_pt_2{0};

        while (getline(ss3, tmp, ' '))
        {
            if (!tmp.empty() && my_numbers.contains(stoi(tmp)))
            {
                tmp_score = tmp_score == 0 ? tmp_score + 1 : 2 * tmp_score;
                ++tmp_score_pt_2;
            }
            card_scores[count_line] = tmp_score_pt_2;
        }

        score += tmp_score;
    }

    input.close();

    return score;
}

void part_1()
{
    const auto t_start = std::chrono::high_resolution_clock::now();
    auto sumcal = sum_points();
    const auto t_stop = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t_stop - t_start);

    std::cout << "Part 1: " << sumcal << '\n';
    std::cout << "It took " << duration.count() << "us \n";
    return;
}

uint64_t sum_cards()
{
    std::map<uint64_t, uint64_t> cards;
    for (const auto &[k, v] : card_scores)
    {
        cards[k] += 1;
        for (uint64_t i = k + 1; i <= k + v && i <= uint64_t(card_scores.size()); ++i)
        {
            cards[i] += cards[k];
        }
    }

    uint64_t res{0};
    for (const auto &[_, v] : cards)
    {
        res += v;
    }

    return res;
}

void part_2()
{
    const auto t_start = std::chrono::high_resolution_clock::now();
    auto sumcal = sum_cards();
    const auto t_stop = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t_stop - t_start);

    std::cout << "Part 2: " << sumcal << '\n';
    std::cout << "It took " << duration.count() << "us \n";
    return;
}

int main()
{
    part_1();
    part_2();
    return 0;
}