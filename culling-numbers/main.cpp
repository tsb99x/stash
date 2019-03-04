#include "main.h"

#include <string>

using namespace std;

int main(const int argc, const char *argv[])
{
    try {
        auto args = convert_args(argc, argv);
        auto culled = cull(args);
        output(culled, cout);
    } catch (const runtime_error &e) {
        cerr << e.what();
    }
}

vector<int> convert_args(const int argc, const char *argv[])
{
    if (argc < 2) {
        throw runtime_error("Failed to get arguments");
    }

    vector<int> vec;

    for (int i = 1; i < argc; i++) {
        int arg;

        try {
            arg = stoi(argv[i]);
        } catch (const invalid_argument &ia) {
            throw runtime_error("Failed to process invalid argument of '"s + argv[i] + "'");
        }

        vec.push_back(arg);
    }

    return vec;
}

vector<int> cull(const vector<int> &args)
{
    vector<int> res;
    unordered_set<int> unique;

    for (const int arg : args) {
        if (unique.find(arg) == unique.end()) { // If doesn't contain
            unique.insert(arg);
            res.push_back(arg);
        }
    }

    return res;
}

void output(const vector<int> &vec, ostream &stream)
{
    if (vec.empty()) {
        return;
    }

    stream << vec[0];
    for (int i = 1; i < vec.size(); i++) {
        stream << " " << vec[i];
    }
}
