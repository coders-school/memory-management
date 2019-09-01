#include <iostream>
#include <cassert>


template <class uniqPtrType>
class UniquePtr 
{
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

template <class uniqPtrType>
UniquePtr<uniqPtrType>::UniquePtr()
    :pointer(nullptr)
    {std::cout<<"konstruktor"<<std::endl;}

template <class uniqPtrType>
UniquePtr<uniqPtrType>::UniquePtr(uniqPtrType* object)
    :pointer(object)
    {}

template <class uniqPtrType>
UniquePtr<uniqPtrType>::UniquePtr(UniquePtr<uniqPtrType> && object) 
    :pointer(std::move(object.pointer))
    {
        object.pointer = nullptr;
    }

template <class uniqPtrType>
UniquePtr<uniqPtrType>::~UniquePtr() 
{
    delete this->pointer;
}

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
    this-> pointer = nullptr;
    return this->pointer;
}

template <class uniqPtrType>
void UniquePtr<uniqPtrType>::reset(uniqPtrType* object)
{
    std::swap(pointer, object);
    delete object;
}

// tests

void testMovePointer()
{
    int* testPointer = new int(123);
    UniquePtr<int> myPointer(testPointer);
    UniquePtr<int> newPointer(std::move(myPointer));
    assert(newPointer.get() == testPointer);
    std::cout<<" - TestMovePointer \t- passed."<<std::endl;
}

 class testClass
{
public:
    bool printingFunction()
    { 
        return true;
    }
};

void testStarOperator()
{
    UniquePtr<testClass> myPointer(new testClass());
    assert((*myPointer).printingFunction());
    std::cout<<" - TestStarOperator \t- passed."<<std::endl;   
}

void testArrowOperator()
{
    UniquePtr<testClass> myPointer(new testClass());
    assert(myPointer->printingFunction());
    std::cout<<" - TestArrowOperator \t- passed."<<std::endl;   
}

void testGetFunction()
{
    int* testPointer = new int(123);
    UniquePtr<int> myPointer(testPointer);
    assert(myPointer.get() == testPointer);
    std::cout<<" - TestGetFunction \t- passed."<<std::endl;
}

void testReleaseFunction()
{
    int* testPointer = new int(123);
    UniquePtr<int> myPointer(testPointer);
    myPointer.release();
    delete testPointer;
    assert(myPointer.get() == nullptr);
    std::cout<<" - TestReleaseFunction \t- passed."<<std::endl;
}

void testResetFunction()
{
    UniquePtr<int> myPointer(new int(123));
    int* testPointer = new int(456);
    myPointer.reset(testPointer);
    assert(myPointer.get() == testPointer);
    std::cout<<" - TestResetFunction \t- passed."<<std::endl;
}


int main(){
   
   std::cout<<"Unique pointer implemetation:"<<std::endl;
   testMovePointer();
   testStarOperator();
   testArrowOperator();
   testGetFunction();
   testReleaseFunction();
   testResetFunction();

   return 0;
}
