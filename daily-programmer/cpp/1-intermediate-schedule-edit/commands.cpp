#include "main.h"

#include "utils.hpp"

using namespace std;
using namespace utils;

string fn_help(vector<event> &events,
               const vector<string> &args)
{
    UNUSED(events);
    UNUSED(args);

    ostringstream ss;

    ss << "command list: " << newl
       << tab << "- help             -- output current message" << newl
       << tab << "- list             -- ordered list of all events" << newl
       << tab << "- create HOUR NAME -- add new event" << newl
       << tab << "- update INDEX     -- edit specific event" << newl
       << tab << "- delete INDEX     -- remove specific event" << newl
       << tab << "- exit             -- quit application";

    return ss.str();
}

bool comparator(const event &a,
                const event &b)
{
    return a.hour < b.hour;
}

string fn_list(vector<event> &events,
               const vector<string> &args)
{
    UNUSED(args);

    if (events.empty())
        return "no events added yet";

    ostringstream ss;
    for (size_t i = 0; i < events.size(); i++)
        ss << "[" << i << "]: hour = " << events[i].hour
           << ", name = " << events[i].name;

    return ss.str();
}

string fn_create(vector<event> &events,
                 const vector<string> &args)
{
    auto opt_hour = convert<int>(args[1]);
    if (!opt_hour.has_value())
        return "hour argument must be an int";
    int hour = opt_hour.value();

    if (hour < 0 || hour > 23)
        return "hour argument must be in [0, 23], but was "s + to_string(hour);

    events.push_back({hour, args[2]});
    sort(begin(events), end(events), comparator);
    return "event was successfully added";
}

string fn_update(vector<event> &events,
                 const vector<string> &args)
{
    auto opt_idx = convert<int>(args[1]);
    if (!opt_idx.has_value())
        return "idx argument must be an int";
    int idx = opt_idx.value();

    if (idx < 0)
        return "idx argument must be greater or equal to 0";

    if (static_cast<size_t>(idx) >= events.size())
        return "idx of "s + to_string(idx) + " does not exist";

    event evt = events[idx];

    string hour_str = prompt("input hour ("s + to_string(evt.hour) + ") > ");
    if (!hour_str.empty()) {
        auto opt_hour = convert<int>(args[1]);
        if (!opt_hour.has_value())
            return "hour argument must be an int";
        int hour = opt_hour.value();

        if (hour < 0 || hour > 23)
            return "hour argument must be in [0, 23], but was "s +
                   to_string(hour);

        evt.hour = hour;
    }

    string name = prompt("input name ("s + evt.name + ") > ");
    if (!name.empty())
        evt.name = name;

    events.erase(begin(events) + idx);
    events.push_back(evt);

    sort(begin(events), end(events), comparator);
    return "event was successfully updated";
}

string fn_delete(vector<event> &events,
                 const vector<string> &args)
{
    auto opt_idx = convert<int>(args[1]);
    if (!opt_idx.has_value())
        return "idx argument must be an int";
    int idx = opt_idx.value();

    if (idx < 0)
        return "idx argument must be greater or equal to 0";

    if (static_cast<size_t>(idx) >= events.size())
        return "idx of "s + to_string(idx) + " does not exist";

    events.erase(begin(events) + idx);
    return "event was successfully removed";
}

string fn_exit(vector<event> &events,
               const vector<string> &args)
{
    UNUSED(events);
    UNUSED(args);
    exit(EXIT_SUCCESS);
}
