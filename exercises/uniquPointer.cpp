#include <iostream>
#include <cassert>


template <class uniqPtrType>
class UniquePtr {
private:
    uniqPtrType* pointer = nullptr;
   
public:
    UniquePtr();
    UniquePtr(uniqPtrType* object);
    UniquePtr(const UniquePtr<uniqPtrType>& object) = delete;
    UniquePtr(UniquePtr<uniqPtrType> && object);
    ~UniquePtr();
    UniquePtr<uniqPtrType>& operator=(const UniquePtr<uniqPtrType>& object) = delete;
    UniquePtr<uniqPtrType>& operator=(UniquePtr<uniqPtrType>&& object);
    uniqPtrType& operator*();
    uniqPtrType* operator->();
    uniqPtrType* get()const;
    uniqPtrType* release();
    void reset(uniqPtrType* object);
};

// constructor
template <class uniqPtrType>
UniquePtr<uniqPtrType>::UniquePtr()
    :pointer(nullptr)
    {std::cout<<"konstruktor"<<std::endl;}


template <class uniqPtrType>
UniquePtr<uniqPtrType>::UniquePtr(uniqPtrType* object)
    :pointer(object)
    {}

// copy constructor
/* DO USUNIECIA
template <class uniqPtrType>
UniquePtr<uniqPtrType>::UniquePtr(const UniquePtr<uniqPtrType>& object)
    :pointer(object.pointer)
    {}
*/
template <class uniqPtrType>
UniquePtr<uniqPtrType>::UniquePtr(UniquePtr<uniqPtrType> && object) 
    :pointer(std::move(object.pointer))
    {}


// destructor
template <class uniqPtrType>
UniquePtr<uniqPtrType>::~UniquePtr() {
    delete this->pointer;
}

// operators
/* DO USUNIECIA
template <class uniqPtrType>
UniquePtr<uniqPtrType> &UniquePtr<uniqPtrType>::operator=(const UniquePtr<uniqPtrType>& object)
{
    if(this != &object){
        pointer = object.pointer;
    }
    return *this;
}
*/

template <class uniqPtrType>
UniquePtr<uniqPtrType> &UniquePtr<uniqPtrType>::operator=(UniquePtr<uniqPtrType>&& object)
{
    if(this != &object){
        pointer = object.pointer;
        object.pointer = nullptr;
    }
    return *this;
}

template <class uniqPtrType>
uniqPtrType& UniquePtr<uniqPtrType>::operator*() 
{
    return *(this->pointer);
}

template <class uniqPtrType>
uniqPtrType* UniquePtr<uniqPtrType>::operator->()
{
    return this->pointer;
}

template <class uniqPtrType>
uniqPtrType *UniquePtr<uniqPtrType>::get()const
{
    return this->pointer;
}

template <class uniqPtrType>
uniqPtrType *UniquePtr<uniqPtrType>::release()
{
    pointer = nullptr;
    return this->pointer;
}


template <class uniqPtrType>
void UniquePtr<uniqPtrType>::reset(uniqPtrType* object)
{
    pointer = object.pointer;
    delete object;
}

int main(){

   
   UniquePtr<int> myPointer( new int(1));


    return 0;
}
