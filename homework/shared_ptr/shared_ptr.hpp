#pragma once
#include <atomic>
#include <cstddef>
#include <unordered_map>

namespace my
{

template <typename T>
class shared_ptr
{
public:
    shared_ptr();
    explicit shared_ptr(T *ptr);
    explicit shared_ptr(shared_ptr &other);
    explicit shared_ptr(shared_ptr &&rref);
    ~shared_ptr();

    T *get() const noexcept;
    void reset(T *other = nullptr) noexcept;
    size_t use_count() const noexcept;

    operator bool() const noexcept;
    T &operator*() const noexcept;
    T *operator->() const noexcept;

    shared_ptr<T> &operator=(const shared_ptr<T> &other) noexcept;
    shared_ptr<T> &operator=(shared_ptr<T> &&other) noexcept;

private:
    struct controlBlock
    {
        std::atomic<size_t> m_shared_refs_count = 0;
        std::atomic<size_t> m_weak_refs_count = 0;
    };

    T *m_ptr = nullptr;
    controlBlock *m_controlBlock = nullptr;
    inline static std::unordered_map<T *, controlBlock *> map;

    void allocateControlBlock(T *ptr);
};

template <typename T>
inline shared_ptr<T>::shared_ptr()
{
    m_controlBlock = new controlBlock;
}

template <typename T>
inline shared_ptr<T>::shared_ptr(T *ptr)
{
    allocateControlBlock(ptr);
}

template <typename T>
inline shared_ptr<T>::shared_ptr(shared_ptr &other)
{
    allocateControlBlock(other.get());
}

template <typename T>
inline shared_ptr<T>::shared_ptr(shared_ptr &&rref)
{
    m_ptr = rref.m_ptr;
    m_controlBlock = rref.m_controlBlock;

    rref.m_ptr = nullptr;
    rref.m_controlBlock = new controlBlock;
}

template <typename T>
inline shared_ptr<T>::~shared_ptr()
{
    this->reset();
}

template <typename T>
inline T *shared_ptr<T>::get() const noexcept
{
    return m_ptr;
}

template <typename T>
inline void shared_ptr<T>::reset(T *other) noexcept
{
    if (m_controlBlock->m_shared_refs_count > 0)
        m_controlBlock->m_shared_refs_count--;

    if (m_controlBlock->m_shared_refs_count == 0)
    {
        if (m_ptr)
        {
            map.erase(map.find(m_ptr));
            delete m_ptr;
            m_ptr = nullptr;
        }
        if (m_controlBlock->m_weak_refs_count == 0)
            delete m_controlBlock;
    }

    if (other)
        allocateControlBlock(other);
}

template <typename T>
inline size_t shared_ptr<T>::use_count() const noexcept
{
    return m_controlBlock->m_shared_refs_count;
}

template <typename T>
inline shared_ptr<T>::operator bool() const noexcept
{
    return m_ptr != nullptr;
}

template <typename T>
inline T &shared_ptr<T>::operator*() const noexcept
{
    return *m_ptr;
}

template <typename T>
inline T *shared_ptr<T>::operator->() const noexcept
{
    return m_ptr;
}

template <typename T>
inline shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr<T> &other) noexcept
{
    this->allocateControlBlock(other.get());
    return *this;
}

template <typename T>
inline shared_ptr<T> &shared_ptr<T>::operator=(shared_ptr<T> &&other) noexcept
{
    this->allocateControlBlock(other.get());

    other.m_ptr = nullptr;
    other.m_controlBlock->m_shared_refs_count--;
    return *this;
}

template <typename T>
inline void shared_ptr<T>::allocateControlBlock(T *ptr)
{
    auto it = map.find(ptr);
    if (it != map.end())
    {
        m_ptr = it->first;
        if (m_controlBlock)
            delete m_controlBlock;
        m_controlBlock = it->second;
    }
    else
    {
        m_controlBlock = new controlBlock;
        m_ptr = ptr;
        map.try_emplace(m_ptr, m_controlBlock);
    }

    m_controlBlock->m_shared_refs_count++;
}

} // namespace my