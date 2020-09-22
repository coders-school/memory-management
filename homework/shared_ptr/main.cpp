#include <iostream>

#include "make_shared.hpp"
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

void customDeleter(int* ptr) {
    std::cout << "Custom deleter\n";
    delete ptr;
}

struct Node {
    cs::shared_ptr<Node> child;
    cs::weak_ptr<Node> parent;
};

int main() {
    cs::shared_ptr<int> ptr(new int{5});
    auto ptr2(ptr);
    cs::shared_ptr<int> ptr3(new int{5});
    ptr3 = ptr;
    auto ptr4(std::move(ptr));
    cs::shared_ptr<int> ptr5(new int{5});
    ptr5 = std::move(ptr3);

    cs::shared_ptr<int> ptrDel(new int{5}, customDeleter);

    cs::weak_ptr<int> wptr{};
    std::cout << wptr.use_count() << '\n';
    cs::weak_ptr<int> wptr2{std::move(wptr)};
    std::cout << wptr.use_count() << '\n';

    cs::weak_ptr<int> wptr3{wptr};
    std::cout << wptr.use_count() << '\n';
    wptr3 = wptr2;
    std::cout << wptr.use_count() << '\n';

    cs::shared_ptr<int> sptr1{new int{5}};
    cs::weak_ptr<int> wptr4{sptr1};
    std::cout << wptr4.use_count() << '\n';

    cs::shared_ptr<Node> root(new Node{});
    cs::shared_ptr<Node> child(new Node{});

    root->child = child;
    child->parent = root;

    return 0;
}
