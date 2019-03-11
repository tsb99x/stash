#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

enum mode { complement, identify };

vector<string> args(const int argc, const char *const *const argv)
{
    vector<string> res;

    for (int i = 0; i < argc; i++)
        res.emplace_back(argv[i]);

    return res;
}

mode parse_mode(const vector<string> &args)
{
    if (args.size() != 2)
        throw runtime_error("Failed to obtain mode arg, use:\n"
                            "\t'-c' to complement\n"
                            "\t'-i' to identify");

    if (args[1] == "-c")
        return complement;
    if (args[1] == "-i")
        return identify;

    throw runtime_error("Failed to parse mode of '"s + args[1] + "'");
}

string read_input()
{
    string res;

    cout << "SRC > ";
    getline(cin, res);

    return res;
}

string validate(const string &src)
{
    size_t not_valid_idx = src.find_first_not_of("ACGT ");

    if (not_valid_idx != string::npos)
        throw runtime_error(
            "Input must consist of 'A', 'C', 'G', 'T' and spaces, but found '"s +
            src[not_valid_idx] + "'");

    return src;
}

vector<char> convert_input(const string &src)
{
    vector<char> res;

    for (auto &ch : src)
        if (ch != ' ')
            res.push_back(ch);

    return res;
}

char lookup_base_complement(const char base)
{
    switch (base) {
    case 'A':
        return 'T';
    case 'T':
        return 'A';
    case 'G':
        return 'C';
    case 'C':
        return 'G';
    default:
        throw runtime_error("Failed to complement base of '"s + base + "'");
    }
}

vector<char> do_complement(const vector<char> &bases)
{
    vector<char> res;
    for (auto &base : bases) {
        res.push_back(lookup_base_complement(base));
    }
    return res;
}

void output(ostream &os, const vector<char> &res)
{
    os << "RES > ";
    if (res.size() > 0)
        os << res[0];
    for (size_t i = 1; i < res.size(); i++)
        os << " " << res[i];
}

int main(int argc, char *argv[])
{
    try {

        mode m = parse_mode(args(argc, argv));
        string src = validate(read_input());
        vector<char> bases = convert_input(src);

        vector<char> res;
        if (m == complement)
            res = do_complement(bases);
        else
            throw runtime_error("Identification is not implemented yet...");

        output(cout, res);

    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}
