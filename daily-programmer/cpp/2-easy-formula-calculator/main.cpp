#include "utils.hpp"

using namespace std;
using namespace utils;

#define acquire_input_or_return(TYPE, VAR_NAME) \
    string str_##VAR_NAME = prompt("input " #VAR_NAME " > "); \
    auto opt_##VAR_NAME = convert<float>(str_##VAR_NAME); \
    if (!opt_##VAR_NAME) \
        return "failed to parse float value for " #VAR_NAME; \
    TYPE VAR_NAME = opt_##VAR_NAME.value()

string calc_f()
{
    cout << "calculating f = m * a" << endl;

    acquire_input_or_return(float, m);
    acquire_input_or_return(float, a);

    return "f = " + to_string(m * a);
}

string calc_m()
{
    cout << "calculating m = f / a" << endl;

    acquire_input_or_return(float, f);
    acquire_input_or_return(float, a);

    return "m = " + to_string(f / a);
}

string calc_a()
{
    cout << "calculating a = f / m" << endl;

    acquire_input_or_return(float, f);
    acquire_input_or_return(float, m);

    return "a = " + to_string(f / m);
}

int main()
{
    while (true) {
        string choice = prompt(
                "select mode to calculate [f] = [m] * [a], [x] to exit > ");

        if (choice == "f") {
            cout << calc_f() << endl;
        } else if (choice == "m") {
            cout << calc_m() << endl;
        } else if (choice == "a") {
            cout << calc_a() << endl;
        } else if (choice == "x") {
            cout << "closing..." << endl;
            return 0;
        } else {
            cout << "unknown mode, please try again" << endl;
        };
    }
}
