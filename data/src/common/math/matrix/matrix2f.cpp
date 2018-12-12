#include "./matrix2f.h"
#include <stdio.h>

/******************************************************************************
 * Matrix2x2f
******************************************************************************/
Matrix2x2f::Matrix2x2f()
{
    for (int i = 0; i < Matrix2x2f_MAX_SIZE; i++)
    {
        this->matrix[i] = 0;
    }
}
Matrix2x2f::Matrix2x2f(const float matrix[Matrix2x2f_MAX_SIZE])
{
    for (int i = 0; i < Matrix2x2f_MAX_SIZE; i++)
    {
        this->matrix[i] = matrix[i];
    }
}

Matrix2x2f Matrix2x2f::operator+(Matrix2x2f obj)
{
    Matrix2x2f ret;
    for (int i = 0; i < Matrix2x2f_MAX_SIZE; i++)
    {
        ret.matrix[i] = this->matrix[i] + obj.matrix[i];
    }
    return ret;
}
Matrix2x2f Matrix2x2f::operator-(Matrix2x2f obj)
{
    Matrix2x2f ret = *this + (-obj);
    return ret;
}
Matrix2x2f Matrix2x2f::operator*(Matrix2x2f obj)
{
    Matrix2x2f ret;
    for (unsigned int i = 0; i < Matrix2x2f_MAX_SIZE; i++)
    {
        for (unsigned int j = 0; j < Matrix2x2f_MAX_LINE; j++)
        {
            ret.matrix[i] += this->matrix[(i / Matrix2x2f_MAX_LINE) * Matrix2x2f_MAX_LINE + j] * obj.matrix[i % Matrix2x2f_MAX_LINE + Matrix2x2f_MAX_LINE * j];
        }
    }
    return ret;
}
Vector2f Matrix2x2f::operator*(Vector2f obj)
{
    Vector2f ret;
    float *retPointer = &(ret.x);
    float *objPointer = &(obj.x);

    for (unsigned int i = 0; i < Vector2f_MAX_SIZE; i++)
    {
        for (unsigned int j = 0; j < Vector2f_MAX_SIZE; j++)
        {
            retPointer[i] += this->matrix[i * Matrix2x2f_MAX_LINE + j] * objPointer[j];
        }
    }
    return ret;
}
Matrix2x2f Matrix2x2f::operator*(float scalar)
{
    Matrix2x2f ret;
    for (int i = 0; i < Matrix2x2f_MAX_SIZE; i++)
    {
        ret.matrix[i] = this->matrix[i] * scalar;
    }
    return ret;
}
Matrix2x2f Matrix2x2f::operator/(float scalar)
{
    scalar = 1 / scalar;
    Matrix2x2f ret = *this * scalar;
    return ret;
}
Matrix2x2f Matrix2x2f::operator=(Matrix2x2f obj)
{
    for (int i = 0; i < Matrix2x2f_MAX_SIZE; i++)
    {
        this->matrix[i] = obj.matrix[i];
    }
    return *this;
}
Matrix2x2f Matrix2x2f::operator+=(Matrix2x2f obj)
{
    *this = *this + obj;
    return *this;
}
Matrix2x2f Matrix2x2f::operator-=(Matrix2x2f obj)
{
    *this = *this - obj;
    return *this;
}
Matrix2x2f Matrix2x2f::operator*=(Matrix2x2f obj)
{
    *this = *this * obj;
    return *this;
}
Matrix2x2f Matrix2x2f::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}
Matrix2x2f Matrix2x2f::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}
Matrix2x2f Matrix2x2f::operator+()
{
    return *this;
}
Matrix2x2f Matrix2x2f::operator-()
{
    return *this * -1;
}
float Matrix2x2f::getElement(unsigned int i, unsigned int j)
{
    int index = Matrix2x2f_MAX_LINE * i + j;

    return this->matrix[index];
}
float Matrix2x2f::determinant()
{
    return this->matrix[0] * this->matrix[3] - this->matrix[1] * this->matrix[2];
}
bool Matrix2x2f::isRegularMatrix()
{
    bool ret = false;
    if (determinant() != 0)
    {
        ret = true;
    }
    return ret;
}
Matrix2x2f *Matrix2x2f::getInverseMatrix()
{
    if (!isRegularMatrix())
    {
        return NULL;
    }
    Matrix2x2f copy = *this;
    
    Matrix2x2f *ret = new Matrix2x2f_IDENTITY;
    for (int i = 0; i < Matrix2x2f_MAX_LINE; i++)
    {
        float buf = 1 / copy.getElement(i, i);
        for (int j = 0; j < Matrix2x2f_MAX_LINE; j++)
        {
            copy.matrix[i * Matrix2x2f_MAX_LINE + j] *= buf;
            ret->matrix[i * Matrix2x2f_MAX_LINE + j] *= buf;
        }
        for (int j = 0; j < Matrix2x2f_MAX_LINE; j++)
        {
            if (i != j)
            {
                float buf = copy.matrix[j * Matrix2x2f_MAX_LINE + i];
                for (int k = 0; k < Matrix2x2f_MAX_LINE; k++)
                {
                    copy.matrix[j * Matrix2x2f_MAX_LINE + k] -= copy.matrix[i * Matrix2x2f_MAX_LINE + k] * buf;
                    ret->matrix[j * Matrix2x2f_MAX_LINE + k] -= ret->matrix[i * Matrix2x2f_MAX_LINE + k] * buf;
                }
            }
        }
    }
    return ret;
}
void Matrix2x2f::callMe()
{
    for (int i = 0; i < Matrix2x2f_MAX_ROW; i++)
    {
        int lineIndex = Matrix2x2f_MAX_LINE * i;
        printf("%4f\t%4f\n", this->matrix[lineIndex], this->matrix[lineIndex + 1]);
    }
    printf("\n\n\n");
}
