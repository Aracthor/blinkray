#pragma once

#include "Vector.hpp"

class Matrix
{
public:
    static constexpr Matrix RotationMatrixAroundX(double angle);
    static constexpr Matrix RotationMatrixAroundY(double angle);
    static constexpr Matrix RotationMatrixAroundZ(double angle);

    constexpr Matrix();
    constexpr Matrix(const Vector& row0, const Vector& row1, const Vector& row2);

    constexpr double Determinant() const;
    constexpr Matrix Transpose() const;
    constexpr Matrix Adjoint() const;
    constexpr Matrix Invert() const;

    constexpr double* operator[](int index) { return m_data[index]; }
    constexpr const double* operator[](int index) const { return m_data[index]; }

    constexpr Vector operator*(const Vector& vector) const;

    constexpr bool operator==(const Matrix& other) const;

private:
    double m_data[3][3];
};

#include "Matrix.ipp"

static_assert(Matrix({2, -3, 1}, {2, 0, -1}, {1, 4, 5}).Determinant() == 49);
static_assert(Matrix({1, 3, 2}, {-3, -1, -3}, {2, 3, 1}).Determinant() == -15);

static_assert(Matrix({2, -3, -1}, {2, 0, -1}, {1, 4, 5}).Transpose() == Matrix({2, 2, 1}, {-3, 0, 4}, {-1, -1, 5}));

static_assert(Matrix({9, 2, 1}, {5, -1, 6}, {4, 0, -2}).Adjoint() == Matrix({2, 4, 13}, {34, -22, -49}, {4, 8, -19}));

static_assert(Matrix({2, 4, 8}, {0, 1, 0}, {1, -4, 1}).Invert() ==
              Matrix({-1.0 / 6.0, 6, 4.0 / 3.0}, {0, 1, 0}, {1.0 / 6.0, -2, -1.0 / 3.0}));
