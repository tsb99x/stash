#include "utils.hpp"

using namespace std;
using namespace utils;

int main()
{
    string name = prompt("Input name > ");
    string age = prompt("Input age > ");
    string username = prompt("Input username > ");

    cout << "your name is (" << name
         << "), you are (" << age
         << ") years old, and your username is (" << username << ")" << endl;

    ofstream os("log.txt", ios_base::app);
    if (!os.is_open()) {
        cerr << "Failed to open 'log.txt' file";
        exit(EXIT_FAILURE);
    }

    os << "name: " << name
       << ", age: " << age
       << ", username: " << username << endl;
}
