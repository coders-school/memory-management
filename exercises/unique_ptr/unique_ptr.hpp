#ifndef HOME_RKUMANEK_REPOS_CODERS_SCHOOL_MEMORY_MANAGEMENT_EXERCISES_UNIQUE_PTR_UNIQUE_PTR_H
#define HOME_RKUMANEK_REPOS_CODERS_SCHOOL_MEMORY_MANAGEMENT_EXERCISES_UNIQUE_PTR_UNIQUE_PTR_H
#include <cstddef>

namespace my
{

template <typename T>
class unique_ptr{
public:
    unique_ptr(T*);
    ~unique_ptr();

    unique_ptr(unique_ptr&&);
    unique_ptr& operator=(unique_ptr&&);

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    T* get();
    T* release();
    T& operator*();
    void reset();
    void reset(T * new_other);

private:
    T* resource_;
};

template <typename T>
unique_ptr<T>::unique_ptr(T* resource) : resource_(resource)
{

}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr<T>&& other) : resource_(other.resource_)
{
    other.resource_ = nullptr;
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& other)
{
    if(resource_)
    {
        delete resource_;
        resource_ = nullptr;
    }

    resource_ = other.resource_;
    other.resource_ = nullptr;
    return *this;
}

template <typename T>
unique_ptr<T>::~unique_ptr()
{
    delete resource_;
}

template <typename T>
T& unique_ptr<T>::operator*()
{
    return *resource_;
}

template <typename T>
T* unique_ptr<T>::get()
{
    return resource_;
}

template <typename T>
T* unique_ptr<T>::release()
{
    T* ptr = resource_;
    resource_ = nullptr;
    return ptr;
}

template <typename T>
void unique_ptr<T>::reset()
{
    if(resource_)
    {
        delete resource_;
    }

    resource_ = nullptr;
}

template <typename T>
void unique_ptr<T>::reset(T * new_other)
{
    if(resource_)
    {
        delete resource_;
    }
    
    resource_ = new_other;
}
} // namespace my

#endif // HOME_RKUMANEK_REPOS_CODERS_SCHOOL_MEMORY_MANAGEMENT_EXERCISES_UNIQUE_PTR_UNIQUE_PTR_H