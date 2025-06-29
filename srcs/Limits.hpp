#pragma once

class Limits
{
public:
    virtual constexpr bool Contains(const Vector& point) const = 0;
};
