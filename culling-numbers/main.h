#ifndef CULLING_NUMBERS_MAIN_H
#define CULLING_NUMBERS_MAIN_H

#include <vector>
#include <unordered_set>
#include <iostream>

std::vector<int> convert_args(int argc, const char *argv[]);

std::vector<int> cull(const std::vector<int> &args);

void output(const std::vector<int> &vec, std::ostream &stream);

#endif //CULLING_NUMBERS_MAIN_H
