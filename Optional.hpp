#pragma once

#include <experimental/optional>

// Big drawback compared to std::optional : T must have a default initializer,
// and is default-initialized for nothing in the default constructor.
// But at least, unlike std::optional, it is fully constexpr even in C++17.
template <typename T>
class Optional
{
public:
    constexpr Optional()
        : m_hasValue(false)
        , m_data()
    {
    }
    constexpr Optional(const T& value)
        : m_hasValue(true)
        , m_data(value)
    {
    }
    constexpr Optional(const Optional<T>& other)
        : m_hasValue(other.m_hasValue)
        , m_data(other.m_data)
    {
    }

    constexpr const T& operator*() const
    {
        if (!m_hasValue)
            throw std::experimental::bad_optional_access();
        return m_data;
    }
    constexpr const T* operator->() const
    {
        if (!m_hasValue)
            throw std::experimental::bad_optional_access();
        return &m_data;
    }
    constexpr operator bool() const { return m_hasValue; }

    constexpr Optional<T>& operator=(const T& other)
    {
        m_hasValue = true;
        m_data = other;
        return *this;
    }

private:
    bool m_hasValue;
    T m_data;
};