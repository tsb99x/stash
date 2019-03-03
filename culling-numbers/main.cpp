#include "main.h"

using namespace std::string_literals;

int main(const int argc, const char *argv[])
{
    try {
        auto args = convert_args(argc, argv);
        auto culled = cull(args);
        output(culled, std::cout);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what();
    }
}

std::vector<int> convert_args(const int argc, const char *argv[])
{
    if (argc < 2) {
        throw std::runtime_error("Failed to get arguments");
    }

    std::vector<int> vec;

    for (int i = 1; i < argc; i++) {
        int arg;

        try {
            arg = std::stoi(argv[i]);
        } catch (const std::invalid_argument &ia) {
            throw std::runtime_error("Failed to process invalid argument of '"s + argv[i] + "'");
        }

        vec.push_back(arg);
    }

    return vec;
}

std::vector<int> cull(const std::vector<int> &args)
{
    std::vector<int> res;
    std::unordered_set<int> unique;

    for (const int arg : args) {
        if (!contains(unique, arg)) {
            unique.insert(arg);
            res.push_back(arg);
        }
    }

    return res;
}

bool contains(const std::unordered_set<int> &container, const int element)
{
    return container.find(element) != container.end();
}

void output(const std::vector<int> &vec, std::ostream &stream)
{
    if (vec.empty()) {
        return;
    }

    stream << vec[0];
    for (int i = 1; i < vec.size(); i++) {
        stream << " " << vec[i];
    }
}
