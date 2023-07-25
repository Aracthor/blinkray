#include "Maths.hpp"

constexpr Matrix Matrix::RotationMatrixAroundX(float angle)
{
    const float cosinus = Maths::cos(angle);
    const float sinus = Maths::sin(angle);

    Matrix matrix;
    matrix[1][1] = cosinus;
    matrix[1][2] = -sinus;
    matrix[2][1] = sinus;
    matrix[2][2] = cosinus;
    return matrix;
}

constexpr Matrix Matrix::RotationMatrixAroundY(float angle)
{
    const float cosinus = Maths::cos(angle);
    const float sinus = Maths::sin(angle);

    Matrix matrix;
    matrix[0][0] = cosinus;
    matrix[0][2] = sinus;
    matrix[2][0] = -sinus;
    matrix[2][2] = cosinus;
    return matrix;
}

constexpr Matrix Matrix::RotationMatrixAroundZ(float angle)
{
    const float cosinus = Maths::cos(angle);
    const float sinus = Maths::sin(angle);

    Matrix matrix;
    matrix[0][0] = cosinus;
    matrix[0][1] = -sinus;
    matrix[1][0] = sinus;
    matrix[1][1] = cosinus;
    return matrix;
}

constexpr Matrix::Matrix()
    : m_data{}
{
    m_data[0][0] = 1.f;
    m_data[1][1] = 1.f;
    m_data[2][2] = 1.f;
}

constexpr Matrix::Matrix(const Vector& row0, const Vector& row1, const Vector& row2)
    : m_data{}
{
    m_data[0][0] = row0.x;
    m_data[0][1] = row0.y;
    m_data[0][2] = row0.z;
    m_data[1][0] = row1.x;
    m_data[1][1] = row1.y;
    m_data[1][2] = row1.z;
    m_data[2][0] = row2.x;
    m_data[2][1] = row2.y;
    m_data[2][2] = row2.z;
}

constexpr float Matrix::Determinant() const
{
    const float square0 = m_data[1][1] * m_data[2][2] - m_data[2][1] * m_data[1][2];
    const float square1 = m_data[1][0] * m_data[2][2] - m_data[2][0] * m_data[1][2];
    const float square2 = m_data[1][0] * m_data[2][1] - m_data[2][0] * m_data[1][1];
    return m_data[0][0] * square0 - m_data[0][1] * square1 + m_data[0][2] * square2;
}

constexpr Matrix Matrix::Transpose() const
{
    Matrix result;
    result[0][0] = m_data[0][0];
    result[0][1] = m_data[1][0];
    result[0][2] = m_data[2][0];
    result[1][0] = m_data[0][1];
    result[1][1] = m_data[1][1];
    result[1][2] = m_data[2][1];
    result[2][0] = m_data[0][2];
    result[2][1] = m_data[1][2];
    result[2][2] = m_data[2][2];
    return result;
}

constexpr Matrix Matrix::Adjoint() const
{
    Matrix result;
    const auto& d = m_data;
    result[0][0] = (d[1][1] * d[2][2] - d[1][2] * d[2][1]);
    result[0][1] = (d[1][0] * d[2][2] - d[1][2] * d[2][0]) * -1;
    result[0][2] = (d[1][0] * d[2][1] - d[1][1] * d[2][0]);
    result[1][0] = (d[0][1] * d[2][2] - d[2][1] * d[0][2]) * -1;
    result[1][1] = (d[0][0] * d[2][2] - d[0][2] * d[2][0]);
    result[1][2] = (d[0][0] * d[2][1] - d[0][1] * d[2][0]) * -1;
    result[2][0] = (d[0][1] * d[1][2] - d[0][2] * d[1][1]);
    result[2][1] = (d[0][0] * d[1][2] - d[0][2] * d[1][0]) * -1;
    result[2][2] = (d[0][0] * d[1][1] - d[0][1] * d[1][0]);
    return result.Transpose();
}

constexpr Matrix Matrix::Invert() const
{
    const float determinant = Determinant();
    Matrix result = Adjoint();
    result[0][0] /= determinant;
    result[0][1] /= determinant;
    result[0][2] /= determinant;
    result[1][0] /= determinant;
    result[1][1] /= determinant;
    result[1][2] /= determinant;
    result[2][0] /= determinant;
    result[2][1] /= determinant;
    result[2][2] /= determinant;
    return result;
}

constexpr Vector Matrix::operator*(const Vector& vector) const
{
    Vector result = {0.f, 0.f, 0.f};
    result.x += m_data[0][0] * vector.x;
    result.x += m_data[0][1] * vector.y;
    result.x += m_data[0][2] * vector.z;
    result.y += m_data[1][0] * vector.x;
    result.y += m_data[1][1] * vector.y;
    result.y += m_data[1][2] * vector.z;
    result.z += m_data[2][0] * vector.x;
    result.z += m_data[2][1] * vector.y;
    result.z += m_data[2][2] * vector.z;
    return result;
}

constexpr bool Matrix::operator==(const Matrix& other) const
{
    return (m_data[0][0] == other[0][0] && m_data[0][1] == other[0][1] && m_data[0][2] == other[0][2] &&
            m_data[1][0] == other[1][0] && m_data[1][1] == other[1][1] && m_data[1][2] == other[1][2] &&
            m_data[2][0] == other[2][0] && m_data[2][1] == other[2][1] && m_data[2][2] == other[2][2]);
}
