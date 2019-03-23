#include "utils.hpp"

using namespace std;
using namespace utils;

int main()
{
    cout << "You may pick a number in [0, 100]" << newl
         << "Input [l] for lower, [h] for higher, [i] for it" << endl;

    int range_min = 0;
    int range_max = 100;

    for (int iter = 1;; iter++) {
        if (range_min == range_max) {
            cerr << "Cheater! You re-picked number in the middle of game"
                 << endl;
            exit(EXIT_FAILURE);
        }

        int guess = (range_min + range_max) / 2;

        while (true) {
            cout << "Your number is " << guess << "? ";
            string in = prompt("> ");

            if (in == "l") {
                range_max = guess;
                break;
            }

            if (in == "h") {
                range_min = guess;
                break;
            }

            if (in == "i") {
                cout << "PC won in " << iter << " iterations" << endl;
                exit(EXIT_SUCCESS);
            }

            cout << "Invalid input, please select one of [l], [h] or [i]"
                 << endl;
        }
    }
}
