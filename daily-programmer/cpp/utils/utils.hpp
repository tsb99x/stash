#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

namespace utils {

/**
 * Convert standard C args to more object-oriented C++ ones.
 */

std::vector<std::string> args(const unsigned argc,
                              const char *argv[])
{
    std::vector<std::string> res;
    res.reserve(argc);

    for (unsigned i = 0; i < argc; i++)
        res.emplace_back(argv[i]);

    return res;
}

/**
 * Join any iteratable container elements to string.
 */

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

/**
 * Read file line-by-line to vector of lines (strings).
 */

std::vector<std::string> read_file(const std::string &filepath)
{
    std::vector<std::string> res;

    std::ifstream input(filepath);
    if (!input.is_open())
        throw std::runtime_error(
                std::string("Failed to open '") + filepath + "' file");

    std::string str;
    while (std::getline(input, str))
        res.push_back(str);

    return res;
}

/**
 * Standard input procedure.
 * Invites user to input data.
 * Returns a full line of input.
 */

std::string prompt(const std::string &invite)
{
    std::string res;

    std::cout << invite;
    std::getline(std::cin, res);

    return res;
}

/**
 * Insert newline into output.
 * Use like std::cout << newl;
 * Prefer this instead of std::endl to prevent flush part.
 */

std::ostream &newl(std::ostream &os)
{
    return os << "\n";
}

/**
 * Insert tab into output.
 * Use like std::cout << tab;
 */

std::ostream &tab(std::ostream &os)
{
    return os << "\t";
}

}

#endif
