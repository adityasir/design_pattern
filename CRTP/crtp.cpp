
#include <iostream>

// Base class using CRTP
template<class Derived>
class Cook {
public:
    void cook() {
        static_cast<Derived*>(this)->cook(); // Call cook method on the derived class
    }
};

// Derived classes implementing cook method
class Biryani : public Cook<Biryani> {
public:
    void cook() {
        std::cout << "Cooking Biryani: Today is Thursday, so no non-veg." << std::endl;
    }
};

class Pulao : public Cook<Pulao> {
public:
    void cook() {
        std::cout << "Cooking Pulao: No special occasion, so making veg Pulao." << std::endl;
    }
};

int main() {
    // Creating objects and invoking the cook method
    Biryani biryani;
    biryani.cook();

    Pulao pulao;
    pulao.cook();

    return 0;
}


