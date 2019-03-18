#include <fstream>
#include <vector>
#include <tuple>
#include <iostream>

using namespace std;

vector<string> read_words()
{
    ifstream file("enable1.txt");
    if (!file.is_open()) {
        throw runtime_error("Failed to open words file 'enable1.txt'");
    }

    vector<string> res;
    string line;

    while (getline(file, line)) {
        res.push_back(line);
    }

    file.close();
    return res;
}

vector<string> get_inputs()
{
    cout << "Input line count: ";
    int n;
    cin >> n;

    vector<string> res;
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
    for (const char &ch : word) {
        if (input.find(ch) == string::npos) {
            return false;
        }
    }
    return true;
}

const string *find_longest_match(const vector<string> &words,
                                 const string &input)
{
    const string *best = nullptr;
    for (const string &word : words) {
        if (!includes_every_char(word, input)) {
            continue;
        }

        if (best == nullptr || word.length() > best->length()) {
            best = &word;
        }
    }
    return best;
}

vector<tuple<const string &, const string *>>
pair_match(const vector<string> &words,
           const vector<string> &inputs)
{
    vector<tuple<const string &, const string *>> res;
    for (const string &input : inputs) {
        auto match = find_longest_match(words, input);
        res.emplace_back(input, match);
    }
    return res;
}

void output(const vector<tuple<const string &, const string *>> &pairs,
            ostream &stream)
{
    for (auto &elem : pairs) {
        stream << get<0>(elem) << " : ";
        if (get<1>(elem) == nullptr) {
            stream << "no match exists";
        } else {
            stream << *get<1>(elem);
        }
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
