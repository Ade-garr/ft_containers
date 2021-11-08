#include <iostream>

class A {
    public:
    A() {}
    ~A() {}
};

class B {
    public:
    B() {}
    B(A const x) {}
    ~B() {}

    bool operator!=(B const &x) { return true; }
};

int main() {

    A a;
    B b;

    // if (a != b)
    //     std::cout << "lol\n";
    if (b != a)
        std::cout << "lol\n";
}