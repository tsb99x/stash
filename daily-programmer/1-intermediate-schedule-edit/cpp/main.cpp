#include "main.h"

#include "utils.hpp"

using namespace std;
using namespace utils;

vector<string> split(const string &orig,
                     const char sep)
{
    vector<string> res;

    stringstream ss(orig);
    string tok;
    while (getline(ss, tok, sep))
        res.push_back(tok);

    return res;
}

int main()
{
    vector<event> events;

    unordered_map<string, command> commands{
            {"help",   {0, fn_help}},
            {"list",   {0, fn_list}},
            {"create", {2, fn_create}},
            {"update", {1, fn_update}},
            {"delete", {1, fn_delete}},
            {"exit",   {0, fn_exit}}
    };

    while (true) {
        string raw = prompt("> ");
        vector<string> tokens = split(raw, ' ');

        if (tokens.empty())
            continue;

        auto res = commands.find(tokens[0]);
        if (res == commands.end()) {
            cout << "failed to find command '" << tokens[0] << "'" << endl;
            continue;
        }

        if (static_cast<size_t>(res->second.argc + 1) != tokens.size()) {
            cout << "command '" << tokens[0]
                 << "' require " << res->second.argc << " arg(s)" << endl;
            continue;
        }

        cout << res->second.fn(events, tokens) << endl;
    }
}
