#pragma once

template <typename T>
class span
{
public:
    constexpr span(const T* ptr, std::size_t size)
        : m_ptr(ptr)
        , m_size(size)
    {
    }

    constexpr const T* begin() const { return m_ptr; }
    constexpr const T* end() const { return m_ptr + m_size; }

private:
    const T* const m_ptr;
    const std::size_t m_size;
};
