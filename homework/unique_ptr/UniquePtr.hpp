template <typename T>
class UniquePtr {
public:
    UniquePtr(T* ptr);

    UniquePtr(const UniquePtr<T>&) = delete;
    UniquePtr<T>& operator=(const UniquePtr<t>) = delete;

    UniquePtr(UniquePtr<T>&& ptr);
    UniquePtr<T>& operator=(UniquePtr<T>&& ptr);

    T operator*() const;
    T* operator->() const;
    T* get();
    T* release();
    void reset(T* ptr);
    ~UniquePtr();

private:
    T* resource_;
};

template<typename T>
UniquePtr<T>::UniquePtr(T* ptr)
    : resource_(ptr) {
}

template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& ptr){

}

template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& ptr){

}

template<typename T>
T UniquePtr<T>::operator*() const{

}

template<typename T>
T* UniquePtr<T>::operator->() const{

}

template<typename T>
T* UniquePtr<T>::get(){

}

template<typename T>
T* UniquePtr<T>::release(){

}

template<typename T>
void UniquePtr<T>::reset(T* ptr){

}

template<typename T>
UniquePtr<T>::~UniquePtr(){
    delete resource_;
}
