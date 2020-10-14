#include <iostream>
#include <utility>

template <class T>
class ControlBlockBase {
public:
    virtual T& getData() = 0;
};

template <class T>
class ControlBlock : public virtual ControlBlockBase<T> {
public:
    T& getData() {
        return refs_;
    }

private:
    T refs_{};
};

template <class T>
class ControlBlockData : public virtual ControlBlockBase<T> {
public:
    ControlBlockData(T data) : data_(data) {}
    T& getData() {
        return data_;
    }

private:
    T data_{};
};

template <class T>
class Shared {
public:
    Shared(T* pointer) : pointer_(pointer) {
        controller_ = new ControlBlock<T>();
        std::cout << "Public works\n";
        std::cout << *pointer_ << "\n";
    }

    T& operator*() {
        return *pointer_;
    }

    template <class M>
    friend Shared<M> MakeShared(M pointer);

private:
    Shared(ControlBlockData<T>* controller) {
        controller_ = controller;
        pointer_ = &controller_->getData();
        std::cout << "Private works\n";
        std::cout << controller_->getData() << "\n";
        std::cout << pointer_ << "\n";
    }
    T* pointer_{};
    ControlBlockBase<T>* controller_;
};

template <class T>
Shared<T> MakeShared(T value) {
    return Shared<T>(new ControlBlockData<T>(value));
}

int main() {
    std::cout << "NormalShared"
              << "\n";
    Shared<int> ptr(new int{100});
    std::cout << typeid(ptr).name() << "\n";
    std::cout << *ptr << "\n";
    std::cout << "MakeShared"
              << "\n";
    Shared<int> ptr2 = MakeShared<int>(777);
    std::cout << typeid(ptr2).name() << "\n";
    std::cout << *ptr2 << "\n";
    return 0;
}
