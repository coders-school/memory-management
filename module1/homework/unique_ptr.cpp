#include <iostream>

template <class T>
class unique_ptr{
public:
//    unique_ptr(T& ptr) : ptr_(&ptr) {};
    unique_ptr(T* v) : ptr_(v) {};
    unique_ptr(unique_ptr<T>&& other) noexcept
    : ptr_(std::move(other.ptr_)) {
        std::cout << "Moved!\n";
        other.ptr_ = nullptr;
    }
    ~unique_ptr(){
        std::cout << "Delete ptr_!\n";
        delete ptr_;
    }

    unique_ptr<T>& operator=(unique_ptr<T>&& other) = delete;
    unique_ptr(T&) = delete;

    T* operator->() const   { return ptr_; }
    T& operator*()  const   { return *ptr_; }

    T* get()        const   { return ptr_; }

    T* release(){
        T* tmp = nullptr;
        std::swap(tmp, ptr_);
        return tmp;
    }

    void reset(T* ptr){
        if(ptr_){
            delete ptr_;
        }
        ptr_ = ptr;
    }

private:
    T* ptr_;
};

int main(){
	return 0;
}

