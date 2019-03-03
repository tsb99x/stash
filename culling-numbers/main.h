#ifndef CULLING_NUMBERS_MAIN_H
#define CULLING_NUMBERS_MAIN_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

std::vector<int> convert_args(int argc, const char *argv[]);

std::vector<int> cull(const std::vector<int> &args);

bool contains(const std::unordered_set<int> &container, int element);

void output(const std::vector<int> &vec, std::ostream &stream);

#endif //CULLING_NUMBERS_MAIN_H
