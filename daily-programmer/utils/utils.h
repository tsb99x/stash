#ifndef UTILS_H
#define UTILS_H

#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> args(const int argc, const char *const *const argv);

template <typename T>
std::string join(const T &cont, const std::string &sep)
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

#endif
