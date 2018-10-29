/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Vector3f
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ベクトル演算などを定義
#include "../header/vector.h"
#include <cmath>
#include <stdio.h>

//コンストラクタ
Vector3f::Vector3f()
{
    x = 0;
    y = 0;
    z = 0;
}
Vector3f::Vector3f(float a, float b, float c)
{
    x = a;
    y = b;
    z = c;
}

//演算子のオーバーロード

Vector3f Vector3f::operator+(Vector3f obj)
{
    return *new Vector3f(this->x + obj.x, this->y + obj.y, this->z + obj.z);
}
Vector3f Vector3f::operator-(Vector3f obj)
{
    return *new Vector3f(this->x - obj.x, this->y - obj.y, this->z - obj.z);
}
Vector3f Vector3f::operator*(float scalar)
{
    return *new Vector3f(this->x * scalar, this->y * scalar, this->z * scalar);
}
Vector3f Vector3f::operator/(float scalar)
{

    return *this * (1 / scalar);
}
Vector3f Vector3f::operator=(Vector3f obj)
{
    this->x = obj.x;
    this->y = obj.y;
    this->z = obj.z;
    return *this;
}
Vector3f Vector3f::operator+()
{
    return *this;
}
Vector3f Vector3f::operator-()
{
    return *this * -1;
}

//メソッド
//絶対値

float Vector3f::magnitude_second_power()
{
    return (float)(std::pow(x, 2.0) + std::pow(y, 2.0) + std::pow(z, 2.0));
}
float Vector3f::magnitude()
{
    return (float)sqrt(magnitude_second_power());
}
//単位ベクトル
Vector3f Vector3f::normalize()
{
    float m = magnitude();
    return *this / m;
}

float Vector3f::dot(Vector3f a, Vector3f b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
Vector3f Vector3f::cross(Vector3f a, Vector3f b)
{
    return *new Vector3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

Vector3f Vector3f::Matrix_multiplication(float matrix[3][3])
{
    Vector3f ret;
    ret.x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z;
    ret.y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z;
    ret.z = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z;
    return ret;
}

Vector3f Vector3f::Scaling(Vector3f scale_vector)
{
    return *new Vector3f(x * scale_vector.x, y * scale_vector.y, z * scale_vector.z);
}

//ベクトル回転
Vector3f Vector3f::Rotate(Vector3f v, float angle)
{
    v = v.normalize();
    float rotation_matrix[3][3];
    float Radian_angle = angle * M_PI / 180.0f;

    float COSINE = (float)std::cos(Radian_angle);
    float SINE   = (float)std::sin(Radian_angle);

    rotation_matrix[0][0] = COSINE + (float)std::pow(v.x, 2.0) * (1.0f - COSINE);
    rotation_matrix[0][1] = v.x * v.y * (1.0f - COSINE) - v.z * SINE;
    rotation_matrix[0][2] = v.x * v.z * (1.0f - COSINE) + v.y * SINE;

    rotation_matrix[1][0] = v.y * v.x * (1.0f - COSINE) + v.z * SINE;
    rotation_matrix[1][1] = COSINE + (float)std::pow(v.y, 2.0) * (1.0f - COSINE);
    rotation_matrix[1][2] = v.y * v.z * (1.0f - COSINE) - v.x * SINE;

    rotation_matrix[2][0] = v.z * v.x * (1.0f - COSINE) - v.y * SINE;
    rotation_matrix[2][1] = v.z * v.y * (1.0f - COSINE) + v.x * SINE;
    rotation_matrix[2][2] = COSINE + (float)std::pow(v.z, 2.0) * (1.0f - COSINE);

    Vector3f ret = Matrix_multiplication(rotation_matrix);
    return ret;
}

//角度計算
float Vector3f::BetweenAngleRdian(Vector3f v)
{
    Vector3f THIS = *new Vector3f(x, y, z);
    return acosf(dot(THIS, v) / (THIS.magnitude() * v.magnitude()));
}

float Vector3f::BetweenAngleDegree(Vector3f v)
{
    return BetweenAngleRdian(v) * 180.0f / M_PI;
}

//使い方
/*
int main()
{
  Vector3f v1(1.0f, 1.0f, 0.0f);
  Vector3f v2(3.0f, 0.0f, 1.0f);

  Vector3f v3 = -v2 * 2 + v1;
  printf("x:%f,y:%f,z:%f\n", v3.x, v3.y, v3.z);
  printf("m:%f\n", v3.magnitude());
  return 0;
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Vector2f
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//コンストラクタ
Vector2f::Vector2f()
{
    x = 0;
    y = 0;
}
Vector2f::Vector2f(float a, float b)
{
    x = a;
    y = b;
}

//演算子のオーバーロード

Vector2f Vector2f::operator+(Vector2f obj)
{
    return *new Vector2f(this->x + obj.x, this->y + obj.y);
}
Vector2f Vector2f::operator-(Vector2f obj)
{
    return *new Vector2f(this->x - obj.x, this->y - obj.y);
}
Vector2f Vector2f::operator*(float scalar)
{
    this->x *= scalar;
    this->y *= scalar;

    return *this;
}
Vector2f Vector2f::operator/(float scalar)
{
    return *this * (1 / scalar);
}
Vector2f Vector2f::operator=(Vector2f obj)
{
    this->x = obj.x;
    this->y = obj.y;
    return *this;
}
Vector2f Vector2f::operator+()
{
    return *this;
}
Vector2f Vector2f::operator-()
{
    return *this * -1;
}

float Vector2f::magnitude_second_power()
{
    return (float)(std::pow(x, 2.0) + std::pow(y, 2.0));
}
float Vector2f::magnitude()
{
    return (float)sqrt(magnitude_second_power());
}
//単位ベクトル
Vector2f Vector2f::normalize()
{
    float m = magnitude();
    return *this / m;
}

float Vector2f::dot(Vector2f a, Vector2f b)
{
    return a.x * b.x + a.y * b.y;
}
Vector3f Vector2f::cross(Vector2f a, Vector2f b)
{
    return *new Vector3f(0, 0, a.x * b.y - a.y * b.x);
}