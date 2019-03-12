#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

std::vector<std::string> args(const int argc, const char *const *const argv);

template <typename T>
std::string join(const std::vector<T> &vec, const std::string &sep);

#endif
