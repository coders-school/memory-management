namespace my {

template <typename T>
class unique_ptr {
public:
    unique_ptr() = default;
    unique_ptr(T* ptr);
    unique_ptr(unique_ptr&& other);
    unique_ptr(unique_ptr& other);

    ~unique_ptr();

    T* Release();
    T* Get();
    void Reset(T* other);
    unique_ptr<T>& operator=(unique_ptr<T>& other);
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

template <typename T>
inline unique_ptr<T>::unique_ptr(unique_ptr& other) {
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
}

template <typename T>
unique_ptr<T>::~unique_ptr() {
    if (m_ptr)
        delete m_ptr;
}

template <typename T>
T* unique_ptr<T>::Release() {
    T* output = nullptr;
    if (m_ptr) {
        output = m_ptr;
        m_ptr = nullptr;
    }

    return output;
}

template <typename T>
T* unique_ptr<T>::Get() {
    if (m_ptr)
        return m_ptr;
}

template <typename T>
void unique_ptr<T>::Reset(T* other) {
    if (m_ptr)
        delete m_ptr;
    m_ptr = other;
}

template <typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>& other) {
    this->m_ptr = other.Release();

    return *this;
}

template <typename T>
inline unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<T>&& other) {
    this->m_ptr = other.Release();

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
