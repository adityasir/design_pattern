/*
 * Reactor.cpp
 *
 *  Created on: Jul 10, 2021
 *      Author: aditya
 */

#include "Reactor.h"

Reactor::Reactor() {
	// TODO Auto-generated constructor stub
	epoll.control();
}

Reactor::~Reactor() {
	// TODO Auto-generated destructor stub
}


void Reactor::addHandler(std::string event, std::function<void()> callback) {
        handlers.emplace(std::move(event), std::move(callback));
}

void Reactor::run() {
	while (true) {
		int numberOfEvents = wait();

		for (int i = 0; i < numberOfEvents; ++i) {
			std::string input;
			std::getline(std::cin, input);

			try {
				handlers.at(input)();
			} catch (const std::out_of_range& e) {
				std::cout << "no handler for " << input << '\n';
			}
		}
	}
}

int Reactor::wait() {
    int numberOfEvents = epoll.wait();
    return numberOfEvents;
}
