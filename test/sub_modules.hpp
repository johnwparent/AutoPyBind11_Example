#include <string>

class A {
public:
    A(int v) : v(v) {  }
    ~A() {  }
    A(const A&) {  }
    A& operator=(const A &copy) { v = copy.v; return *this; }
    std::string toString() { return "A[" + std::to_string(v) + "]"; }
private:
    int v;
};

class B {
public:
    B() { }
    ~B() {  }
    B(const B&) {  }
    B& operator=(const B &copy) { a1 = copy.a1; a2 = copy.a2; return *this; }
    A &get_a1() { return a1; }
    A &get_a2() { return a2; }

    A a1{1};
    A a2{2};
};