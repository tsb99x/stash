#include "utils.h"

#include <sstream>

using namespace std;

vector<string> args(const int argc, const char *const *const argv)
{
    vector<string> res;

    for (int i = 0; i < argc; i++)
        res.emplace_back(argv[i]);

    return res;
}

string join(const vector<char> &vec, const string &sep)
{
    ostringstream os;

    if (vec.size() > 0)
        os << vec[0];
    for (size_t i = 1; i < vec.size(); i++)
        os << sep << vec[i];

    return os.str();
}
