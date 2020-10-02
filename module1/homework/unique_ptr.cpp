#include <iostream>

template <typename T>
class unique_ptr{
public:
    unique_ptr(T* ptr = nullptr) : ptr_(ptr){}

    unique_ptr(unique_ptr<T>&) = delete;
    unique_ptr<T>& operator=(unique_ptr<T>&) = delete;

    unique_ptr(unique_ptr<T>&& otherPtr) : ptr_(otherPtr.ptr_){
        otherPtr.ptr_ = nullptr;
    }

    unique_ptr<T>& operator=(unique_ptr<T>&& otherPtr){
        if(this != &otherPtr){
            delete ptr_;
            ptr_ = otherPtr.ptr_;
            otherPtr.ptr_ = nullptr;
            return *this;
        }
        return *this;
    }

    ~unique_ptr(){ delete ptr_; }
    T& operator*() const { return *ptr_; }
    T* get() const { return ptr_; }

    T* release(){
        T* tmpPtr = ptr_;
        ptr_ = nullptr;
        return tmpPtr;
    }

    void reset(T* otherPtr){
        delete ptr_;
        ptr_ = otherPtr;
    }

private:
    T* ptr_;
};

int main(){
    return 0;
}