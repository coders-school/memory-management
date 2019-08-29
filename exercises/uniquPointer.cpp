class ReferenceCounter
{
private:
    int counter;

public:
    void increase() { counter++; }

    // Decrement and release reference count
    int release() { return --counter; }
};


template <class T>
class UniquePtr {
private:
    T* pointer = nullptr;
    ReferenceCounter* reference = nullptr;

public:
    UniquePtr();
    UniquePtr(T* object);
    UniquePtr(const UniquePtr<T>& object);
    ~UniquePtr();
    UniquePtr<T>& operator=(const UniquePtr<T>& object);
    T& operator*();
    T* operator->();
    void get()const;
    void release();
    void reset(T* object);
};

// constructor
template <class T>
UniquePtr<T>::UniquePtr()
    :pointer(nullptr), reference(nullptr){
        reference = new ReferenceCounter();
        reference->increase();
    }

template <class T>
UniquePtr<T>::UniquePtr(T* object)
    :pointer(object), reference(nullptr){
        reference = new ReferenceCounter();
        reference->increase();
    }


// copy constructor
template <class T>
UniquePtr<T>::UniquePtr(const UniquePtr<T>& object)
    :pointer(object.pointer), reference(object.reference){
        reference->increase();
    }


// destructor
template <class T>
UniquePtr<T>::~UniquePtr() {
    if(reference->release() == 0){
        this->release();
    }

}

// operators
template <class T>
UniquePtr<T> &UniquePtr<T>::operator=(const UniquePtr<T>& object){
    if(this != &object){
        if(reference->release() == 0){
             this->release();
        }
        pointer = object.pointer;
        reference = object.reference;
        reference->increase();
    }
    return *this;
}

template <class T>
T& UniquePtr<T>::operator*() {
    return *(this->pointer);
}

template <class T>
T* UniquePtr<T>::operator->(){
    return this->pointer;
}

template <class T>
void UniquePtr<T>::get()const{
    return this->pointer;
}

template <class T>
void UniquePtr<T>::release(){
    delete this->pointer;
    delete this->reference;
}


template <class T>
void UniquePtr<T>::reset(T* object){
    if((this->pointer) != object){
        this->pointer.release();
        this->pointer = object;
    }
}
int main(){


    UniquePtr<int> myPointer( new int() );
    UniquePtr<int> newPointer = myPointer;

    return 0;
}
