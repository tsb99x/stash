#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

std::vector<std::string> args(const unsigned argc,
                              const char *argv[])
{
    std::vector<std::string> res;
    res.reserve(argc);

    for (unsigned i = 0; i < argc; i++)
        res.emplace_back(argv[i]);

    return res;
}

template<typename T>
std::string join(const T &cont,
                 const std::string &sep)
{
    std::ostringstream os;

    auto it = std::cbegin(cont);
    auto end = std::cend(cont);

    if (it != end)
        os << *it++;

    while (it != end)
        os << sep << *it++;

    return os.str();
}

std::vector<std::string> read_file(const std::string &filename)
{
    std::vector<std::string> res;

    std::ifstream input(filename);
    if (!input.is_open())
        throw std::runtime_error(
                std::string("Failed to open '") + filename + "' file");

    std::string str;
    while (std::getline(input, str))
        res.push_back(str);

    return res;
}

template<typename T>
T prompt(const std::string &invite)
{
    T res;

    std::cout << invite;
    std::cin >> res;

    return res;
}

#endif
