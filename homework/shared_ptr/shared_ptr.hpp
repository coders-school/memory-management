#pragma once
#include <cstddef>
#include <unordered_map>

// shared_ptr()
// shared_ptr(&)
// shared_ptr(&&)


// operator=(&)
// operator=(&&)

namespace my
{

template <typename T>
class shared_ptr
{
public:
    shared_ptr();
    shared_ptr(T* ptr);
    shared_ptr(T &&rref);
    ~shared_ptr();

    T *release();
    size_t use_count();

private:
    struct controlBlock
    {
        std::atomic<size_t> m_shared_refs_count = 0;
        std::atomic<size_t> m_weak_refs_count = 0;
    };

    T *m_ptr = nullptr;
    controlBlock *m_controlBlock = nullptr;
    inline static std::unordered_map<T*, controlBlock*> map;

    void allocateControlBlock(T *ptr);

};

template <typename T>
inline shared_ptr<T>::shared_ptr()
{
    m_controlBlock = new controlBlock;
}

template <typename T>
inline shared_ptr<T>::shared_ptr(T* ptr)
{
    allocateControlBlock(ptr);    
    m_controlBlock->m_shared_refs_count++;
}

template <typename T>
inline shared_ptr<T>::shared_ptr(T &&rref)
{

}

template <typename T>
inline shared_ptr<T>::~shared_ptr()
{
    m_controlBlock->m_shared_refs_count--;
    if (m_controlBlock == 0)
    {
        map.erase(map.find(m_ptr));

        delete m_ptr;
        delete m_controlBlock;
    }
}

template <typename T>
inline T *shared_ptr<T>::release()
{
    T *output = nullptr;
    if (m_ptr)
    {
        output = m_ptr;
        m_ptr = nullptr;
    }

    return output;
}

template <typename T>
inline size_t shared_ptr<T>::use_count()
{
    return m_controlBlock->m_shared_refs_count;
}

template <typename T>
inline void shared_ptr<T>::allocateControlBlock(T *ptr)
{
    auto it = map.find(ptr);
    if (it != map.end())
    {
        m_ptr = it->first;
        m_controlBlock = it->second;
    }
    else
    {
        m_controlBlock = new controlBlock;
        m_ptr = ptr;
        map.try_emplace(m_ptr, m_controlBlock);
    }
}

}