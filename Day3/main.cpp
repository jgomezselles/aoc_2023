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

struct coord
{
    int n;
    int l, s, f;
};

void print_v(const std::vector<coord> &v)
{
    for (const auto &n : v)
    {
        std::cout << "Found " << n.n << " at {" << n.s << "," << n.f << "} in line " << n.l << std::endl;
    }
}

void print_s(const std::map<int, std::map<int, char>> &s)
{
    for (const auto &[k, v] : s)
    {
        for (const auto &[x, y] : v)
        {
            std::cout << "Symbol " << y << " found at {" << k << "," << x << "}" << std::endl;
        }
    }
}

std::map<int, std::map<int, char>> symbols;
std::vector<std::pair<int, int>> symbols2;
std::map<int, std::map<int, int64_t>> n_part_pos;

uint64_t sum_games()
{
    std::ifstream input("input.txt");
    if (!input)
    {
        std::cerr << "Cannot open the input.txt" << std::endl;
        exit(1);
    }

    std::string line;
    std::vector<coord> n_pos;
    int l{0};

    while (getline(input, line))
    {
        bool started{false};
        std::string n_str;
        int n{0};

        for (int c = 0; c < line.size(); ++c)
        {
            auto ch = line.at(c);
            if (isdigit(ch))
            {
                n_str.push_back(ch);
                if (!started)
                {
                    started = true;
                    n = c;
                }

                if (c == line.size() - 1)
                {
                    started = false;
                    n_pos.push_back({stoi(n_str), l, n, n});
                    n_str.clear();
                }
            }
            else if (started)
            {
                started = false;
                n_pos.push_back({stoi(n_str), l, n, c - 1});
                n_str.clear();
            }

            if (!isdigit(ch) && ch != '.')
            {
                symbols[l][c] = ch;
                symbols2.push_back({l, c});
            }
        }
        ++l;
    }
    // print_v(n_pos);
    // print_s(symbols);

    input.close();

    size_t part_sum{0};

    for (const auto &n : n_pos)
    {
        bool part{false};
        for (int i : {n.l - 1, n.l, n.l + 1})
        {
            if (const auto &s = symbols.find(i); s != symbols.end())
            {
                for (int j = n.s - 1; j <= n.f + 1; ++j)
                {
                    if (const auto s2 = s->second.find(j); s2 != s->second.end())
                    {
                        part = true;
                        part_sum += n.n;
                        for (int k = n.s; k <= n.f; ++k)
                        {
                            n_part_pos[n.l][k] = n.n;
                        }
                        break;
                    }
                }
            }

            if (part)
            {
                break;
            }
        }
    }

    return part_sum;
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

int64_t gears()
{
    size_t ratios{0};

    for (const auto &s : symbols2) {
        std::optional<int64_t> found1, found2;
        bool b_too_much{false};

        for (int i : {s.first - 1, s.first, s.first + 1})
        {
            for (int j : {s.second - 1, s.second, s.second + 1})
            {
                if (const auto &p_l = n_part_pos.find(i); p_l != n_part_pos.end())
                {
                    if (const auto &p_c = p_l->second.find(j); p_c != p_l->second.end())
                    {
                        if (!found1.has_value())
                        {
                            found1.emplace(p_c->second);
                        }
                        else if (*found1 == p_c->second)
                        {
                            continue;
                        }
                        else if (!found2.has_value())
                        {
                            found2.emplace(p_c->second);
                        }
                        else if (*found2 == p_c->second)
                        {
                            continue;
                        }
                        else
                        {
                            b_too_much = true;
                            break;
                        }
                    }
                }
            }
            if (b_too_much)
            {
                break;
            }
        }

        if (!b_too_much && found1.has_value() && found2.has_value())
        {
            ratios += (found1.value() * found2.value());
        }
    }

    return ratios;
}

void part_2()
{
    const auto t_start = std::chrono::high_resolution_clock::now();
    auto sumcal = gears();
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