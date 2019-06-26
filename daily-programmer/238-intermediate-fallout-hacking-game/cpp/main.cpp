#include "utils.hpp"

#include <algorithm>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;
using namespace utils;

int get_difficulty()
{
    int res;

    cout << "Difficulty (0-4)? ";
    cin >> res;

    if (res < 0 || res > 4)
        throw runtime_error("Input difficulty must be in 0-4 range");

    return res;
}

struct range {
    int from;
    int to;
};

range diff_map[] = {
        {4,  5},
        {6,  8},
        {9,  10},
        {11, 12},
        {13, 15}
};

int get_rand_from_range(const range &range,
                        default_random_engine &dre)
{
    uniform_int_distribution range_dist(range.from, range.to);
    return range_dist(dre);
}

vector<string> filter_words(const vector<string> &dict,
                            const size_t length,
                            default_random_engine &dre)
{
    vector<string> res;

    for (const auto &word: dict)
        if (word.length() == length)
            res.push_back(word);

    shuffle(res.begin(), res.end(), dre);

    return res;
}

vector<string> select_words(const vector<string> &words,
                            const int count)
{
    vector<string> res;

    for (int i = 0; i < count && !words.empty(); i++)
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
    for (size_t i = 0; i < word.length() && i < str.length(); i++)
        if (str[i] == word[i])
            counter++;

    cout << counter << "/" << word.length() << " correct" << endl;
    return guesses_left - 1;
}

void try_guess(const string &word,
               int guesses_left)
{
    while (guesses_left > 0)
        guesses_left = guess(guesses_left, word);

    if (guesses_left == -1)
        cout << "You win!" << endl;
    else
        cout << "You lose!" << endl;
}

int main()
{
    try {

        time_point tp = system_clock::now();
        default_random_engine gen(tp.time_since_epoch().count());

        vector<string> dict = read_file("enable1.txt");
        int diff_val = get_difficulty();

        int word_length = get_rand_from_range(diff_map[diff_val], gen);
        vector<string> filtered = filter_words(dict, word_length, gen);

        int word_count = get_rand_from_range(diff_map[diff_val], gen);
        vector<string> words = select_words(filtered, word_count);
        output_words(words);

        string word = words[get_rand_from_range({0, word_count}, gen)];
        try_guess(word, 4);

    } catch (const exception &e) {

        cerr << e.what();

    }
}
