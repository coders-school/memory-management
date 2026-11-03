
template <typename T>
class MySmartPointer
{
public:
	MySmartPointer() = default;
	MySmartPointer(T* ptr);
	MySmartPointer(MySmartPointer&& other);
	MySmartPointer(MySmartPointer& other);

	~MySmartPointer();

	T* Release();
	T* Get();
	void Reset(T* other);
	MySmartPointer<T>& operator=(MySmartPointer<T>& other);
	MySmartPointer<T>& operator=(MySmartPointer<T>&& other);
	T& operator*();
	T* operator->();


private:
	T* m_ptr = nullptr;
};

template<typename T>
MySmartPointer<T>::MySmartPointer(T* ptr)
{
	m_ptr = ptr;
}

template<typename T>
MySmartPointer<T>::MySmartPointer(MySmartPointer&& other)
{
	m_ptr = other.m_ptr;
	other.m_ptr = nullptr;
}

template<typename T>
inline MySmartPointer<T>::MySmartPointer(MySmartPointer& other)
{
	m_ptr = other.m_ptr;
	other.m_ptr = nullptr;
}

template<typename T>
MySmartPointer<T>::~MySmartPointer()
{
	if (m_ptr)
		delete m_ptr;
}

template<typename T>
T* MySmartPointer<T>::Release()
{
	T* output = nullptr;
	if (m_ptr)
	{
		output = m_ptr;
		m_ptr = nullptr;
	}

	return output;
}

template<typename T>
T* MySmartPointer<T>::Get()
{
	if (m_ptr)
		return m_ptr;
}

template<typename T>
void MySmartPointer<T>::Reset(T* other)
{
	if (m_ptr)
		delete m_ptr;
	m_ptr = other;
}

template<typename T>
MySmartPointer<T>& MySmartPointer<T>::operator=(MySmartPointer<T>& other)
{
	this->m_ptr = other.Release();

	return *this;
}

template<typename T>
inline MySmartPointer<T>& MySmartPointer<T>::operator=(MySmartPointer<T>&& other)
{
	this->m_ptr = other.Release();

	return *this;
}

template<typename T>
inline T& MySmartPointer<T>::operator*()
{
	return *m_ptr;
}

template<typename T>
inline T* MySmartPointer<T>::operator->()
{
	return m_ptr;
}

