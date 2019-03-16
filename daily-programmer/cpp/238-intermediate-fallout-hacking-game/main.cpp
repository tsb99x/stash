#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

vector<string> read_words()
{
    vector<string> res;

    ifstream input;
    input.open("enable1.txt");

    if (!input.is_open())
        throw runtime_error("Failed to open 'enable1.txt' file");

    string str;
    while (getline(input, str))
        res.push_back(str);
    input.close();

    return res;
}

int get_difficulty()
{
    int res;
    cout << "Difficulty (1-5)? ";
    cin >> res;
    return res;
}

struct diff_range {
    int from;
    int to;
};

diff_range diff_map[] = {
        {4,  5},
        {6,  8},
        {9,  10},
        {11, 12},
        {13, 15}
};

int get_rand_from_range(const diff_range &range)
{
    return rand() % (range.to - range.from + 1) + range.from;
}

vector<string> filter_words(const vector<string> &dict,
                            const int length)
{
    vector<string> res;

    for (const auto &word: dict)
        if (word.length() == length)
            res.push_back(word);

    int64_t seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(res.begin(), res.end(), default_random_engine(seed));

    return res;
}

vector<string> select_words(const vector<string> &words,
                            const int count)
{
    vector<string> res;

    for (int i = 0; i < count && words.size() > 0; i++)
        res.push_back(words[i]);

    return res;
}

void output_words(const vector<string> &words)
{
    for (const auto &word: words)
        cout << word << endl;
}

int guess(const int guesses_left,
          const string &word)
{
    cout << "Guess (" << guesses_left << " left)? ";

    string str;
    cin >> str;

    if (str == word) {
        cout << word.length() << "/" << word.length() << " correct" << endl;
        return -1;
    }

    int counter = 0;
    for (int i = 0; i < word.length() && i < str.length(); i++)
        if (str[i] == word[i])
            counter++;

    cout << counter << "/" << word.length() << " correct" << endl;
    return guesses_left - 1;
}

int main()
{
    try {

        srand(time(NULL));

        vector<string> dict = read_words();
        int diff_val = get_difficulty();
        int magic_num = get_rand_from_range(diff_map[diff_val]);
        vector<string> filtered = filter_words(dict, magic_num);
        vector<string> words = select_words(filtered, magic_num);

        output_words(words);
        string word = words[get_rand_from_range({0, magic_num})];

        int guesses_left = 4;
        while (guesses_left > 0)
            guesses_left = guess(guesses_left, word);

        if (guesses_left == -1)
            cout << "You win!" << endl;
        else
            cout << "You lose!" << endl;

    } catch (const exception &e) {

        cerr << e.what();

    }
}
