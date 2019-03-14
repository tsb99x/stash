#include "utils.h"

using namespace std;

vector<string> args(const int argc, const char *const *const argv)
{
    vector<string> res;

    for (int i = 0; i < argc; i++)
        res.emplace_back(argv[i]);

    return res;
}
