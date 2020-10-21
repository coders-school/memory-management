#pragma once

namespace kontrybutor {

template <typename T>
class UniquePtr {
private:
    T* m_data;

public:
    explicit UniquePtr(T* data = nullptr)
        : m_data(data)
    {
    }
    ~UniquePtr()
    {
        if (m_data) {
            delete m_data;
        }
    }
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&& rhs) noexcept
        : m_data(rhs.m_data)
    {
        rhs.m_data = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& rhs)
    {
        if (&rhs == this) {
            return *this;
        }
        delete m_data;
        m_data = rhs.m_data;
        rhs.m_data = nullptr;
        return *this;
    }

    T& operator*() const { return m_data; };
    T* operator->() const { return *m_data; };

    T* get() const { return m_data; };
    T* release() noexcept
    {
        T* result = nullptr;
        std::swap(result, nullptr);
        return result;
    }
    void reset(T* data) noexcept
    {
        delete m_data;
        m_data = nullptr;
        m_data = data;
    }
};
} // namespace kontrybutor