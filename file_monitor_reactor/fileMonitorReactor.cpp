#include <iostream>
#include <sys/inotify.h>
#include <unistd.h>
#include <vector>
#include <functional>
#include <fstream>
#include <unordered_map>


class Reactor {
public:
    void addHandler(int watchDescriptor, std::function<void()> handler) {
        handlers_[watchDescriptor] = std::move(handler);
    }

    void handleEvents(int inotifyFd) {
        char buffer[4096];
        ssize_t bytesRead = read(inotifyFd, buffer, sizeof(buffer));

        if (bytesRead == -1) {
            perror("read");
            return;
        }

        struct inotify_event* event = reinterpret_cast<struct inotify_event*>(buffer);
        int watchDescriptor = event->wd;

        auto handlerIter = handlers_.find(watchDescriptor);
        if (handlerIter != handlers_.end()) {
            handlerIter->second();
        }
    }

private:
    std::unordered_map<int, std::function<void()>> handlers_;
};

bool isFileValid(const std::string& fileName) {
    std::ifstream file(fileName.c_str());
    return file.good();
}

void printFileContent(const std::string& fileName) {
    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string line;
        std::cout << "File Content:\n";
        while (getline(file, line)) {
            std::cout << line << '\n';
        }
        std::cout << std::endl;
        file.close();
    } else {
        std::cerr << "Error: Unable to open file - " << fileName << std::endl;
        // Handle file open error
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file1> [<file2> ...]" << std::endl;
        return 1;
    }

    int inotifyFd = inotify_init();
    if (inotifyFd == -1) {
        perror("inotify_init");
        return 1;
    }

    Reactor reactor;
    std::vector<std::string> files;

    for (int i = 1; i < argc; ++i) {
        std::string fileName = argv[i];
        if (isFileValid(fileName)) {
            files.push_back(fileName);

            int watchDescriptor = inotify_add_watch(inotifyFd, fileName.c_str(), IN_MODIFY);
            if (watchDescriptor == -1) {
                perror("inotify_add_watch");
                close(inotifyFd);
                return 1;
            }

            reactor.addHandler(watchDescriptor, [fileName = std::move(fileName)] {
                std::cout << fileName << " modified!\n";
                printFileContent(fileName);
            });
        } else {
            std::cerr << "Error: Invalid file provided - " << fileName << std::endl;
            // Handle invalid file error
        }
    }

    while (true) {
        reactor.handleEvents(inotifyFd);
        // Perform other non-blocking tasks if needed
    }

    close(inotifyFd);
    return 0;
}

