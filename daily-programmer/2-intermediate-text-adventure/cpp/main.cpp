#include "utils.hpp"

#include <functional>
#include <memory>

using namespace std;
using namespace utils;

struct path_point;

struct choice {
    string invite;
    weak_ptr<path_point> next;
};

struct path_point {
    string msg;
    unordered_map<char, choice> choices;
};

ostream &operator<<(ostream &os,
                    const path_point &point)
{
    os << point.msg << newl;
    for (const auto &kv: point.choices)
        os << tab << "[" << kv.first << "]" << " - "
           << kv.second.invite << newl;
    return os;
}

int main()
{
    auto end = make_shared<path_point>();
    end->msg = "Slime is no more";

    auto slime = make_shared<path_point>();
    slime->msg = "Slime appeared before you";
    slime->choices.insert({'a', {"attack benevolent slime", end}});

    auto sword = make_shared<path_point>();
    sword->msg = "A sword is laying down in a grass";
    sword->choices.insert({'p', {"pickup sword", slime}});

    auto start = make_shared<path_point>();
    start->msg = "You are in the middle of nowhere and see a tree in a distance";
    start->choices.insert({'a', {"approach tree", sword}});
    start->choices.insert({'s', {"stay here a little bit more", start}});

    shared_ptr<path_point> current_point = start;
    while (!current_point->choices.empty()) {
        cout << *current_point;

        while (true) {
            string input = prompt("> ");
            if (input.empty() || input.size() > 1) {
                cerr << "Input must consist of singular char" << endl;
                continue;
            }

            auto sel = current_point->choices.find(input[0]);
            if (sel == current_point->choices.end()) {
                cerr << "No choice exists for char '"
                     << input[0] << "'" << endl;
                continue;
            }

            if (!(current_point = sel->second.next.lock())) {
                cerr << "Failed to lock weak_ptr" << endl;
                exit(EXIT_FAILURE);
            }
            break;
        }
    }

    cout << current_point->msg << newl
         << "Adventure is Over" << endl;
}
