#include "utils.hpp"

#include <iostream>
#include <unordered_map>

using namespace std;
using namespace utils;

enum mode {
    complement,
    identify
};

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

    for (const char ch : src)
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
    res.reserve(bases.size());

    for (const char base : bases)
        res.push_back(lookup_base_complement(base));

    return res;
}

unordered_map<string, string> codon_lookup = {

        {"TTT", "Phe"},
        {"TTC", "Phe"},

        {"TTA", "Leu"},
        {"TTG", "Leu"},
        {"CTT", "Leu"},
        {"CTC", "Leu"},
        {"CTA", "Leu"},
        {"CTG", "Leu"},

        {"ATT", "Ile"},
        {"ATC", "Ile"},
        {"ATA", "Ile"},

        {"ATG", "Met"},

        {"GTT", "Val"},
        {"GTC", "Val"},
        {"GTA", "Val"},
        {"GTG", "Val"},

        {"TCT", "Ser"},
        {"TCC", "Ser"},
        {"TCA", "Ser"},
        {"TCG", "Ser"},

        {"CCT", "Pro"},
        {"CCC", "Pro"},
        {"CCA", "Pro"},
        {"CCG", "Pro"},

        {"ACT", "Thr"},
        {"ACC", "Thr"},
        {"ACA", "Thr"},
        {"ACG", "Thr"},

        {"GCT", "Ala"},
        {"GCC", "Ala"},
        {"GCA", "Ala"},
        {"GCG", "Ala"},

        {"TAT", "Tyr"},
        {"TAC", "Tyr"},

        {"TAA", "STOP"},
        {"TAG", "STOP"},

        {"CAT", "His"},
        {"CAC", "His"},

        {"CAA", "Gln"},
        {"CAG", "Gln"},

        {"AAT", "Asn"},
        {"AAC", "Asn"},

        {"AAA", "Lys"},
        {"AAG", "Lys"},

        {"GAT", "Asp"},
        {"GAC", "Asp"},

        {"GAA", "Glu"},
        {"GAG", "Glu"},

        {"TGT", "Cys"},
        {"TGC", "Cys"},

        {"TGA", "STOP"},

        {"TGG", "Trp"},

        {"CGT", "Arg"},
        {"CGC", "Arg"},
        {"CGA", "Arg"},
        {"CGG", "Arg"},

        {"AGT", "Ser"},
        {"AGC", "Ser"},

        {"AGA", "Arg"},
        {"AGG", "Arg"},

        {"GGT", "Gly"},
        {"GGC", "Gly"},
        {"GGA", "Gly"},
        {"GGG", "Gly"},

};

vector<string> do_convert(const vector<char> &bases)
{
    vector<string> res;

    string codon_bases;
    for (const char ch : bases) {
        codon_bases += ch;
        if (codon_bases.length() == 3) {
            res.push_back(codon_lookup[codon_bases]);
            codon_bases.clear();
        }
    }

    if (!codon_bases.empty())
        res.emplace_back("...");

    return res;
}

int main(int argc,
         const char *argv[])
{
    try {

        mode m = parse_mode(args(argc, argv));
        string src = validate(read_input());
        vector<char> bases = convert_input(src);

        string res;
        if (m == complement)
            res = join(do_complement(bases), " ");
        else
            res = join(do_convert(bases), " ");

        cout << "RES > " << res;

    } catch (const exception &e) {
        cerr << e.what() << endl;
    }
}
