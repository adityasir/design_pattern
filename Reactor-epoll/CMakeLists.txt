cmake_minimum_required (VERSION 2.6)

project (reactor-epoll)

add_executable(reactor-epoll Reactor-epoll.cpp Reactor.cpp Epoll.cpp)


target_link_libraries(reactor-epoll PUBLIC -lboost_system -lboost_thread -lpthread)


target_include_directories(reactor-epoll PUBLIC "${PROJECT_BINARY_DIR}")

                              