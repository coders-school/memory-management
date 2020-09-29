
#pragma once

template <typename T>
class my_unique_ptr
{

public:
    T* get() { return ptr_; }

    my_unique_ptr(T* ptr) : ptr_(ptr){};
    my_unique_ptr()
    {
        T someObject = T();
        ptr_ = &someObject;
        //        *ptr_ = T();
    };

    //    my_unique_ptr(my_unique_ptr<T> ) = delete;  //copy not allowed so we should delete auto generated copy ctor
    //    error: invalid constructor; you probably meant ‘my_unique_ptr<T> (const my_unique_ptr<T>&)’

    my_unique_ptr(const my_unique_ptr<T>&) = delete; // copy not allowed so we should delete auto generated copy ctor

    ~my_unique_ptr() { delete ptr_; }

    T operator*() { return *ptr_; }; // we can return object
/* very interesting error
fatal error: template instantiation depth exceeds maximum of 900 (use -ftemplate-depth= to increase the maximum)
    EXPECT_EQ(ptr->str, "");

    my_unique_ptr<T*> operator->()
    {
        return this;
    };
*/
    // here we can not return *ptr_ it is raw ptr so no gain we can do this in get() function when user knows what is
       // he doing

    T* operator->()
    {
        return this->ptr_;
    };

private:
    T* ptr_ = nullptr;
};
