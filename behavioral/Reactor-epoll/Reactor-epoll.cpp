
#include <iostream>
#include "Reactor.h"

using namespace std;

int main(int argc, char **argv) {
	 Reactor reactor;

	    reactor.addHandler("one", [](){
	        std::cout << "one handler called!" << '\n';
	    });
	    reactor.addHandler("two", [](){
	        std::cout << "two handler called!" << '\n';
	    });

	    reactor.run();
	return 0;
}
