template <class T>
class UniquePtr {
private:
    T* pointer = nullptr;
   
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
    :pointer(nullptr)
    {std::cout<<"konstruktor"<<std::endl;}

template <class T>
UniquePtr<T>::UniquePtr(T* object)
    :pointer(object)
    {}

// copy constructor
template <class T>
UniquePtr<T>::UniquePtr(const UniquePtr<T>& object)
    :pointer(object.pointer)
    {}


// destructor
template <class T>
UniquePtr<T>::~UniquePtr() {
    this->release();
}

// operators
template <class T>
UniquePtr<T> &UniquePtr<T>::operator=(const UniquePtr<T>& object){
    if(this != &object){
        pointer = object.pointer;
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
