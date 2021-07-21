/*
 * Reactor.h
 *
 *  Created on: Jul 10, 2021
 *      Author: aditya
 */

#ifndef REACTOR_H_
#define REACTOR_H_
#include "Epoll.h"
#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>
#include <array>
#include <limits>
#include <functional>
#include <unordered_map>

class Reactor {
 public:
    Reactor();
    ~Reactor();
    void addHandler(std::string event, std::function<void()> callback);
    void run();

private:
    std::unordered_map<std::string, std::function<void()>> handlers{};
    Epoll epoll;
    int wait();
};

#endif /* REACTOR_H_ */
