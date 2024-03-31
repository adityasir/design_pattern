Overview:
The Curiously Recurring Template Pattern (CRTP) is an advanced C++ programming technique that allows for static polymorphism, also known as compile-time polymorphism, without the use of virtual functions.
This pattern is characterized by a base class template that takes a derived class as its template parameter.
The derived class then inherits from the base class, thereby "recurring" the base class template with itself as the template argument.

At a high level, CRTP leverages the compiler's template instantiation mechanism to achieve polymorphic behavior.
By inheriting from the base class template and providing specialized implementations of its methods, derived classes effectively extend the functionality of the base class.
When methods of the base class are called, they are resolved at compile time to the corresponding methods in the derived class, eliminating the runtime overhead associated with virtual function dispatch. Overall, the Curiously Recurring Template Pattern is a versatile and powerful technique in C++ programming, providing a mechanism for achieving static polymorphism and facilitating efficient and flexible code design.

Advantage:
CRTP is particularly useful in scenarios where runtime polymorphism through virtual functions is not desired or incurs performance overhead.
It allows for efficient code generation, as method calls are resolved statically at compile time rather than dynamically at runtime.
Additionally, CRTP can facilitate code reuse and enable static type checking, making it a powerful tool in the C++ programmer's toolkit.

Limitation:
Using the template approach, the compiler instantiates the derived class at compile time, making it impossible to use a base class object to point to its derived class. For example, we can't declare a vector of the base class.
