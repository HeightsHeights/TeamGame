#include "./matrix3f.h"
#include <stdio.h>

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
            ret.matrix[i] += this->matrix[(i / Matrix3x3f_MAX_LINE) * Matrix3x3f_MAX_LINE + j] * obj.matrix[i % Matrix3x3f_MAX_LINE + Matrix3x3f_MAX_LINE * j];
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
            retPointer[i] += this->matrix[i * Matrix3x3f_MAX_LINE + j] * objPointer[j];
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
    return *this * -1;
}
float Matrix3x3f::getElement(unsigned int i, unsigned int j)
{
    i--;
    j--;

    int index = Matrix3x3f_MAX_LINE * i + j;

    return this->matrix[index];
}

void Matrix3x3f::callMe()
{
    for (int i = 0; i < Matrix3x3f_MAX_ROW; i++)
    {
        int lineIndex = Matrix3x3f_MAX_LINE * i;
        printf("%4f\t%4f\t%4f\n", this->matrix[lineIndex], this->matrix[lineIndex + 1], this->matrix[lineIndex + 2]);
    }
    printf("\n\n\n");
}