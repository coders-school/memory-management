#include <stdexcept>
#include <iostream>
using namespace std;

struct TalkingObject {
    TalkingObject()  { cout << "Constructor" << '\n'; }
    ~TalkingObject() { cout << "Destructor" << '\n'; }
};
struct ThrowingObject {
    ThrowingObject() { std::cout << "Throwing c-tor\n"; }
    ~ThrowingObject() {}
};

void foo() noexcept
{ throw 42; }

int main() {
    TalkingObject outside;
    try {
        // try {
            ThrowingObject inside;
            foo();
        // } catch(std::exception const&) {
            // std::cout << "std::exception" << '\n';
            // throw;
        // }
    } catch(int) {
        std::cout << "unknown" << '\n';
    }
}