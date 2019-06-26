#ifndef MAIN_H
#define MAIN_H

#include <string>
#include <vector>
#include <functional>

#define UNUSED(x) (void)(x)

struct event {
    int hour;
    std::string name;
};

struct command {
    int argc;
    std::function<std::string(std::vector<event> &events,
                              const std::vector<std::string> &args)> fn;
};

std::string fn_help(std::vector<event> &events,
                    const std::vector<std::string> &args);

std::string fn_list(std::vector<event> &events,
                    const std::vector<std::string> &args);

std::string fn_create(std::vector<event> &events,
                      const std::vector<std::string> &args);

std::string fn_update(std::vector<event> &events,
                      const std::vector<std::string> &args);

std::string fn_delete(std::vector<event> &events,
                      const std::vector<std::string> &args);

std::string fn_exit(std::vector<event> &events,
                    const std::vector<std::string> &args);

#endif
