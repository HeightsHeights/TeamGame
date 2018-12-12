#include "./matrix4f.h"
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
            ret.matrix[i] += this->matrix[(i / Matrix4x4f_MAX_LINE) * Matrix4x4f_MAX_LINE + j] * obj.matrix[i % Matrix4x4f_MAX_LINE + Matrix4x4f_MAX_LINE * j];
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
            retPointer[i] += this->matrix[i * Matrix4x4f_MAX_LINE + j] * objPointer[j];
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
    return *this * -1;
}
float Matrix4x4f::getElement(unsigned int i, unsigned int j)
{
    int index = Matrix4x4f_MAX_LINE * i + j;

    return this->matrix[index];
}
float Matrix4x4f::determinant()
{
    float ret = 1.0f;
    Matrix4x4f copy = *this;
    //三角行列を作成
    for (int i = 0; i < Matrix4x4f_MAX_LINE; i++)
    {
        for (int j = 0; j < Matrix4x4f_MAX_LINE; j++)
        {
            if (i < j)
            {
                float buf = copy.getElement(j, i) / copy.getElement(i, i);
                for (int k = 0; k < Matrix4x4f_MAX_LINE; k++)
                {
                    copy.matrix[j * Matrix4x4f_MAX_LINE + k] -= copy.getElement(i, k) * buf;
                }
            }
        }
    }

    //対角部分の積
    for (int i = 0; i < Matrix4x4f_MAX_LINE; i++)
    {
        ret *= copy.getElement(i, i);
    }
    return ret;
}
bool Matrix4x4f::isRegularMatrix()
{
    bool ret = false;
    if (determinant() != 0)
    {
        ret = true;
    }
    return ret;
}
Matrix4x4f *Matrix4x4f::getInverseMatrix()
{
    if (!isRegularMatrix())
    {
        return NULL;
    }
    Matrix4x4f copy = *this;

    Matrix4x4f *ret = new Matrix4x4f_IDENTITY;
    for (int i = 0; i < Matrix4x4f_MAX_LINE; i++)
    {
        float buf = 1 / copy.getElement(i, i);
        for (int j = 0; j < Matrix4x4f_MAX_LINE; j++)
        {
            copy.matrix[i * Matrix4x4f_MAX_LINE + j] *= buf;
            ret->matrix[i * Matrix4x4f_MAX_LINE + j] *= buf;
        }
        for (int j = 0; j < Matrix4x4f_MAX_LINE; j++)
        {
            if (i != j)
            {
                float buf = copy.matrix[j * Matrix4x4f_MAX_LINE + i];
                for (int k = 0; k < Matrix4x4f_MAX_LINE; k++)
                {
                    copy.matrix[j * Matrix4x4f_MAX_LINE + k] -= copy.matrix[i * Matrix4x4f_MAX_LINE + k] * buf;
                    ret->matrix[j * Matrix4x4f_MAX_LINE + k] -= ret->matrix[i * Matrix4x4f_MAX_LINE + k] * buf;
                }
            }
        }
    }
    return ret;
}
void Matrix4x4f::callMe()
{
    for (int i = 0; i < Matrix4x4f_MAX_ROW; i++)
    {
        int lineIndex = Matrix4x4f_MAX_LINE * i;
        printf("%4f\t%4f\t%4f\t%4f\n", this->matrix[lineIndex], this->matrix[lineIndex + 1], this->matrix[lineIndex + 2], this->matrix[lineIndex + 3]);
    }
    printf("\n\n\n");
}
