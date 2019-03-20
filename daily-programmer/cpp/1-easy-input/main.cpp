#include <iostream>
#include <fstream>

using namespace std;

template<typename T>
T prompt(const string &invite)
{
    T res;

    cout << invite;
    cin >> res;

    return res;
}

int main()
{
    auto name = prompt<string>("Input name > ");
    auto age = prompt<string>("Input age > ");
    auto username = prompt<string>("Input username > ");

    cout << "your name is (" << name
         << "), you are (" << age
         << ") years old, and your username is (" << username << ")";

    ofstream os("log.txt", ios_base::app);
    if (!os.is_open()) {
        cerr << "Failed to open 'log.txt' file";
        exit(EXIT_FAILURE);
    }

    os << "name: " << name
       << ", age: " << age
       << ", username: " << username << endl;
}
