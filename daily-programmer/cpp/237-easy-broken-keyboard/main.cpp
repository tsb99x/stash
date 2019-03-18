#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

vector<string> read_words()
{
    vector<string> res;

    ifstream file("enable1.txt");
    if (!file.is_open())
        throw runtime_error("Failed to open words file 'enable1.txt'");

    string line;
    while (getline(file, line))
        res.push_back(line);

    return res;
}

vector<string> get_inputs()
{
    vector<string> res;

    cout << "Input line count: ";
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Line #" << i + 1 << ": ";
        string str;
        cin >> str;
        res.push_back(str);
    }

    return res;
}

bool includes_every_char(const string &word,
                         const string &input)
{
    for (const char &ch : word)
        if (input.find(ch) == string::npos)
            return false;

    return true;
}

const string *find_longest_match(const vector<string> &words,
                                 const string &input)
{
    const string *best = nullptr;

    for (const string &word : words) {
        if (!includes_every_char(word, input))
            continue;
        if (best == nullptr || word.length() > best->length())
            best = &word;
    }

    return best;
}

struct assoc {
    const string &src;
    const string *best;
};

vector<assoc> pair_match(const vector<string> &words,
                         const vector<string> &inputs)
{
    vector<assoc> res;

    for (const string &input : inputs) {
        auto match = find_longest_match(words, input);
        res.push_back({input, match});
    }

    return res;
}

void output(const vector<assoc> &pairs,
            ostream &stream)
{
    for (auto &elem : pairs) {
        stream << elem.src << " : ";
        if (elem.best == nullptr)
            stream << "no match exists";
        else
            stream << *elem.best;
        stream << endl;
    }
}

int main()
{
    try {

        auto words = read_words();
        auto inputs = get_inputs();
        auto pairs = pair_match(words, inputs);
        output(pairs, cout);

    } catch (const exception &e) {

        cerr << e.what();

    }
}
