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
    int index = Matrix3x3f_MAX_LINE * i + j;

    return this->matrix[index];
}
float Matrix3x3f::determinant()
{
    float ret;
    ret = getElement(0, 0) * getElement(1, 1) * getElement(2, 2);
    ret += getElement(1, 0) * getElement(2, 1) * getElement(0, 2);
    ret += getElement(2, 0) * getElement(0, 1) * getElement(1, 2);
    ret -= getElement(2, 0) * getElement(1, 1) * getElement(0, 2);
    ret -= getElement(1, 0) * getElement(0, 1) * getElement(2, 2);
    ret -= getElement(0, 0) * getElement(2, 1) * getElement(1, 2);
}
bool Matrix3x3f::isRegularMatrix()
{
    bool ret = false;
    if (determinant() != 0)
    {
        ret = true;
    }
    return ret;
}
Matrix3x3f *Matrix3x3f::getInverseMatrix()
{
    if (!isRegularMatrix())
    {
        return NULL;
    }
    Matrix3x3f copy = *this;

    Matrix3x3f *ret = new Matrix3x3f_IDENTITY;
    for (int i = 0; i < Matrix3x3f_MAX_LINE; i++)
    {
        float buf = 1 / copy.getElement(i, i);
        for (int j = 0; j < Matrix3x3f_MAX_LINE; j++)
        {
            copy.matrix[i * Matrix3x3f_MAX_LINE + j] *= buf;
            ret->matrix[i * Matrix3x3f_MAX_LINE + j] *= buf;
        }
        for (int j = 0; j < Matrix3x3f_MAX_LINE; j++)
        {
            if (i != j)
            {
                float buf = copy.matrix[j * Matrix3x3f_MAX_LINE + i];
                for (int k = 0; k < Matrix3x3f_MAX_LINE; k++)
                {
                    copy.matrix[j * Matrix3x3f_MAX_LINE + k] -= copy.matrix[i * Matrix3x3f_MAX_LINE + k] * buf;
                    ret->matrix[j * Matrix3x3f_MAX_LINE + k] -= ret->matrix[i * Matrix3x3f_MAX_LINE + k] * buf;
                }
            }
        }
    }
    return ret;
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
