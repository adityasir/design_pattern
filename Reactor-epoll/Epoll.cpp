/*
 * Epoll.cpp
 *
 *  Created on: Jul 10, 2021
 *      Author: aditya
 */

#include "Epoll.h"

Epoll::Epoll() {
      fileDescriptor = epoll_create1(NO_FLAGS);

      event.data.fd = STDIN_FILENO;
      event.events = EPOLLIN | EPOLLPRI;
}

Epoll::~Epoll()  {
	 // TODO Auto-generated destructor stub
      close(fileDescriptor);
}

int Epoll::control() {
      return epoll_ctl(fileDescriptor, EPOLL_CTL_ADD, STDIN_FILENO, &event);
}

int Epoll::wait() {
      return epoll_wait(
              fileDescriptor,
              events.begin(),
              MAX_EVENTS,
              BLOCK_INDEFINITELY);
}


