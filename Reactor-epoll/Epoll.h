/*
 * Epoll.h
 *
 *  Created on: Jul 10, 2021
 *      Author: aditya
 */

#ifndef EPOLL_H_
#define EPOLL_H_

#include <sys/epoll.h>
#include <unistd.h>
#include <iostream>
#include <array>
#include <limits>
#include <functional>
#include <unordered_map>
#include <string>
#include <utility>


class Epoll {
 public:
    static const int NO_FLAGS = 0;
    static const int BLOCK_INDEFINITELY = -1;
    static const int MAX_EVENTS = 1;
    Epoll();
    ~Epoll();
    int control();
    int wait();

 private:
    int fileDescriptor;
    struct epoll_event event;
    std::array<epoll_event, MAX_EVENTS> events{};
};

#endif /* EPOLL_H_ */
