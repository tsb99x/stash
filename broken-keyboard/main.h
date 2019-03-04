#ifndef BROKEN_KEYBOARD_MAIN_H
#define BROKEN_KEYBOARD_MAIN_H

#include <vector>
#include <string>
#include <tuple>
#include <iostream>

std::vector<std::string> read_words();

std::vector<std::string> get_inputs();

std::vector<std::tuple<const std::string &, const std::string *>> pair_match(const std::vector<std::string> &words, const std::vector<std::string> &inputs);

const std::string *find_longest_match(const std::vector<std::string> &words, const std::string &input);

bool includes_every_char(const std::string &word, const std::string &input);

void output(const std::vector<std::tuple<const std::string &, const std::string *>> &pairs, std::ostream &stream);

#endif //BROKEN_KEYBOARD_MAIN_H
