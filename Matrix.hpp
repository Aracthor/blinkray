#pragma once

#include "Vector.hpp"

class Matrix
{
public:
    static constexpr Matrix RotationMatrixAroundX(float angle);
    static constexpr Matrix RotationMatrixAroundY(float angle);
    static constexpr Matrix RotationMatrixAroundZ(float angle);

    constexpr Matrix();
    constexpr Matrix(const Vector& row0, const Vector& row1, const Vector& row2);

    constexpr float Determinant() const;
    constexpr Matrix Transpose() const;
    constexpr Matrix Adjoint() const;
    constexpr Matrix Invert() const;

    constexpr float* operator[](int index) { return m_data[index]; }
    constexpr const float* operator[](int index) const { return m_data[index]; }

    constexpr Vector operator*(const Vector& vector) const;

    constexpr bool operator==(const Matrix& other) const;

private:
    float m_data[3][3];
};

#include "Matrix.ipp"

static_assert(Matrix({2, -3, 1}, {2, 0, -1}, {1, 4, 5}).Determinant() == 49);
static_assert(Matrix({1, 3, 2}, {-3, -1, -3}, {2, 3, 1}).Determinant() == -15);

static_assert(Matrix({2, -3, -1}, {2, 0, -1}, {1, 4, 5}).Transpose() ==
              Matrix({2, 2, 1}, {-3, 0, 4}, {-1, -1, 5}));

static_assert(Matrix({9, 2, 1}, {5, -1, 6}, {4, 0, -2}).Adjoint() ==
              Matrix({2, 4, 13}, {34, -22, -49}, {4, 8, -19}));

static_assert(Matrix({2, 4, 8}, {0, 1, 0}, {1, -4, 1}).Invert() ==
              Matrix({-1.f / 6.f, 6, 4.f / 3.f}, {0, 1, 0}, {1.f / 6.f, -2, -1.f / 3.f}));
