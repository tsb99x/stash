#include "utils.hpp"

#include <iostream>
#include <unordered_set>

using namespace std;
using namespace utils;

vector<int> process_args(const vector<string> &args)
{
    vector<int> res;

    if (args.size() < 2)
        throw runtime_error("Failed to get arguments");

    for (int i = 1; i < args.size(); i++) {
        int arg;

        try {
            arg = stoi(args[i]);
        } catch (const invalid_argument &ia) {
            throw runtime_error("Failed to process invalid argument of '"s +
                                args[i] + "'");
        }

        res.push_back(arg);
    }

    return res;
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

int main(const int argc,
         const char *argv[])
{
    try {

        auto nums = process_args(args(argc, argv));
        auto culled = cull(nums);
        cout << join(culled, " ");

    } catch (const exception &e) {
        cerr << e.what();
    }
}
