#include "../header/matrixf.h"
#include <stdio.h>

/******************************************************************************
 * Matrix4x4f
******************************************************************************/
Matrix4x4f::Matrix4x4f()
{
    for (int i = 0; i < Matrix4x4f_MAX_SIZE; i++)
    {
        this->matrix[i] = 0;
    }
}
Matrix4x4f::Matrix4x4f(const float matrix[Matrix4x4f_MAX_SIZE])
{
    for (int i = 0; i < Matrix4x4f_MAX_SIZE; i++)
    {
        this->matrix[i] = matrix[i];
    }
}

Matrix4x4f Matrix4x4f::operator+(Matrix4x4f obj)
{
    Matrix4x4f ret;
    for (int i = 0; i < Matrix4x4f_MAX_SIZE; i++)
    {
        ret.matrix[i] = this->matrix[i] + obj.matrix[i];
    }
    return ret;
}
Matrix4x4f Matrix4x4f::operator-(Matrix4x4f obj)
{
    Matrix4x4f ret = *this + (-obj);
    return ret;
}
Matrix4x4f Matrix4x4f::operator*(Matrix4x4f obj)
{
    Matrix4x4f ret;
    for (unsigned int i = 0; i < Matrix4x4f_MAX_SIZE; i++)
    {
        for (unsigned int j = 0; j < Matrix4x4f_MAX_LINE; j++)
        {
            ret.matrix[i] += this->matrix[(i / 4) * 4 + j] * obj.matrix[i % 4 + 4 * j];
        }
    }
    return ret;
}
Vector4f Matrix4x4f::operator*(Vector4f obj)
{
    Vector4f ret;
    float *retPointer = &(ret.x);
    float *objPointer = &(obj.x);

    for (unsigned int i = 0; i < Vector4f_MAX_SIZE; i++)
    {
        for (unsigned int j = 0; j < Vector4f_MAX_SIZE; j++)
        {
            retPointer[i] += this->matrix[i * 4 + j] * objPointer[j];
        }
    }
    return ret;
}
Matrix4x4f Matrix4x4f::operator*(float scalar)
{
    Matrix4x4f ret;
    for (int i = 0; i < Matrix4x4f_MAX_SIZE; i++)
    {
        ret.matrix[i] = this->matrix[i] * scalar;
    }
    return ret;
}
Matrix4x4f Matrix4x4f::operator/(float scalar)
{
    scalar = 1 / scalar;
    Matrix4x4f ret = *this * scalar;
    return ret;
}
Matrix4x4f Matrix4x4f::operator=(Matrix4x4f obj)
{
    for (int i = 0; i < Matrix4x4f_MAX_SIZE; i++)
    {
        this->matrix[i] = obj.matrix[i];
    }
    return *this;
}
Matrix4x4f Matrix4x4f::operator+=(Matrix4x4f obj)
{
    *this = *this + obj;
    return *this;
}
Matrix4x4f Matrix4x4f::operator-=(Matrix4x4f obj)
{
    *this = *this - obj;
    return *this;
}
Matrix4x4f Matrix4x4f::operator*=(Matrix4x4f obj)
{
    *this = *this * obj;
    return *this;
}
Matrix4x4f Matrix4x4f::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}
Matrix4x4f Matrix4x4f::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}
Matrix4x4f Matrix4x4f::operator+()
{
    return *this;
}
Matrix4x4f Matrix4x4f::operator-()
{
    Matrix4x4f ret;
    for (int i = 0; i < Matrix4x4f_MAX_SIZE; i++)
    {
        ret.matrix[i] = -this->matrix[i];
    }
    return ret;
}
float Matrix4x4f::getElement(unsigned int i, unsigned int j)
{
    i--;
    j--;

    int index = 4 * i + j;

    return this->matrix[index];
}

void Matrix4x4f::callMe()
{
    for (int i = 0; i < Matrix4x4f_MAX_ROW; i++)
    {
        printf("%4f\t%4f\t%4f\t%4f\n", this->matrix[4 * i], this->matrix[4 * i + 1], this->matrix[4 * i + 2], this->matrix[4 * i + 3]);
    }
    printf("\n\n\n");
}

/******************************************************************************
 * Matrix3x3f
******************************************************************************/
Matrix3x3f::Matrix3x3f()
{
    for (int i = 0; i < Matrix3x3f_MAX_SIZE; i++)
    {
        this->matrix[i] = 0;
    }
}
Matrix3x3f::Matrix3x3f(const float matrix[Matrix3x3f_MAX_SIZE])
{
    for (int i = 0; i < Matrix3x3f_MAX_SIZE; i++)
    {
        this->matrix[i] = matrix[i];
    }
}

Matrix3x3f Matrix3x3f::operator+(Matrix3x3f obj)
{
    Matrix3x3f ret;
    for (int i = 0; i < Matrix3x3f_MAX_SIZE; i++)
    {
        ret.matrix[i] = this->matrix[i] + obj.matrix[i];
    }
    return ret;
}
Matrix3x3f Matrix3x3f::operator-(Matrix3x3f obj)
{
    Matrix3x3f ret = *this + (-obj);
    return ret;
}
Matrix3x3f Matrix3x3f::operator*(Matrix3x3f obj)
{
    Matrix3x3f ret;
    for (unsigned int i = 0; i < Matrix3x3f_MAX_SIZE; i++)
    {
        for (unsigned int j = 0; j < Matrix3x3f_MAX_LINE; j++)
        {
            ret.matrix[i] += this->matrix[(i / 3) * 3 + j] * obj.matrix[i % 3 + 3 * j];
        }
    }
    return ret;
}
Vector3f Matrix3x3f::operator*(Vector3f obj)
{
    Vector3f ret;
    float *retPointer = &(ret.x);
    float *objPointer = &(obj.x);

    for (unsigned int i = 0; i < Vector3f_MAX_SIZE; i++)
    {
        for (unsigned int j = 0; j < Vector3f_MAX_SIZE; j++)
        {
            retPointer[i] += this->matrix[i * 3 + j] * objPointer[j];
        }
    }
    return ret;
}
Matrix3x3f Matrix3x3f::operator*(float scalar)
{
    Matrix3x3f ret;
    for (int i = 0; i < Matrix3x3f_MAX_SIZE; i++)
    {
        ret.matrix[i] = this->matrix[i] * scalar;
    }
    return ret;
}
Matrix3x3f Matrix3x3f::operator/(float scalar)
{
    scalar = 1 / scalar;
    Matrix3x3f ret = *this * scalar;
    return ret;
}
Matrix3x3f Matrix3x3f::operator=(Matrix3x3f obj)
{
    for (int i = 0; i < Matrix3x3f_MAX_SIZE; i++)
    {
        this->matrix[i] = obj.matrix[i];
    }
    return *this;
}
Matrix3x3f Matrix3x3f::operator+=(Matrix3x3f obj)
{
    *this = *this + obj;
    return *this;
}
Matrix3x3f Matrix3x3f::operator-=(Matrix3x3f obj)
{
    *this = *this - obj;
    return *this;
}
Matrix3x3f Matrix3x3f::operator*=(Matrix3x3f obj)
{
    *this = *this * obj;
    return *this;
}
Matrix3x3f Matrix3x3f::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}
Matrix3x3f Matrix3x3f::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}
Matrix3x3f Matrix3x3f::operator+()
{
    return *this;
}
Matrix3x3f Matrix3x3f::operator-()
{
    Matrix3x3f ret;
    for (int i = 0; i < Matrix3x3f_MAX_SIZE; i++)
    {
        ret.matrix[i] = -this->matrix[i];
    }
    return ret;
}
float Matrix3x3f::getElement(unsigned int i, unsigned int j)
{
    i--;
    j--;

    int index = 3 * i + j;

    return this->matrix[index];
}

void Matrix3x3f::callMe()
{
    for (int i = 0; i < Matrix3x3f_MAX_ROW; i++)
    {
        printf("%4f\t%4f\t%4f\n", this->matrix[3 * i], this->matrix[3 * i + 1], this->matrix[3 * i + 2]);
    }
    printf("\n\n\n");
}