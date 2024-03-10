FileMonitorReactor
FileMonitorReactor is a C++ application showcasing the integration of the Reactor Design Pattern with inotify for efficient and event-driven monitoring of file changes.

Overview
This application provides a scalable and responsive solution for monitoring changes in multiple files concurrently. Leveraging the inotify API in Linux, along with the Reactor pattern, it allows developers to register handlers for specific files and react to file modifications dynamically.

Compile
$ g++ -o fileMonitorReactor fileMonitorReactor.cpp -std=c++17

Run
$ ./fileMonitorReactor file1.txt file2.txt
