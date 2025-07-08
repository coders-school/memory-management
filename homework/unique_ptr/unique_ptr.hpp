

namespace my
{

template<typename T>
class unique_ptr
{
public:
    unique_ptr(T* ptr) : ptr_(ptr);
    unique_ptr(const unique_ptr&);
    ~unique_ptr();
    unique_ptr(unique_ptr&& other);
    unique_ptr& operator=(const unique_ptr& other) = delete;
    unique_ptr& operator=(unique_ptr&& other);
    T& operator*();
    T* operator->();
    T* get() const;
    T* release();
    void reset(T* ptr);
private:
    T* ptr_;
};


};