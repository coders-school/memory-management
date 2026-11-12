namespace my {

template <typename T>
class unique_ptr {
public:
    unique_ptr() = default;
    unique_ptr(T* ptr);
    unique_ptr(unique_ptr&& other);
    unique_ptr(const unique_ptr& other) = delete;

    ~unique_ptr();

    T* release();
    T* get();
    void reset(T* other = nullptr);
    unique_ptr<T>& operator=(const unique_ptr<T>& other) = delete;
    unique_ptr<T>& operator=(unique_ptr<T>&& other);
    T& operator*();
    T* operator->();

private:
    T* m_ptr = nullptr;
};

template <typename T>
unique_ptr<T>::unique_ptr(T* ptr) {
    m_ptr = ptr;
}

template <typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& other) {
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
}

//template <typename T>
//inline unique_ptr<T>::unique_ptr(unique_ptr& other) {
//    m_ptr = other.m_ptr;
//    other.m_ptr = nullptr;
//}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    if (m_ptr)
        delete m_ptr;
}

template <typename T>
T* unique_ptr<T>::release() {
    T* output = nullptr;
    if (m_ptr) {
        output = m_ptr;
        m_ptr = nullptr;
    }

    return output;
}

template <typename T>
T* unique_ptr<T>::get() {
    return m_ptr;
}

template <typename T>
void unique_ptr<T>::reset(T* other) {
    if (m_ptr)
        delete m_ptr;
    m_ptr = other;
}

//template <typename T>
//unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>& other) {
//    this->m_ptr = other.release();
//
//    return *this;
//}

template <typename T>
inline unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& other) {
    this->m_ptr = other.release();

    return *this;
}

template <typename T>
inline T& unique_ptr<T>::operator*() {
    return *m_ptr;
}

template <typename T>
inline T* unique_ptr<T>::operator->() {
    return m_ptr;
}

}  // namespace my
