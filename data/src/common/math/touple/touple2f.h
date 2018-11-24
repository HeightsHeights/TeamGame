#pragma once

#define Touple2f_MAX_SIZE 2
/******************************************************************************
 * class Touple2f
 * 
******************************************************************************/

class Touple2f
{
private:
public:
  float x;
  float y;

  Touple2f();
  Touple2f(float x, float y);

  Touple2f operator+(Touple2f obj);
  Touple2f operator-(Touple2f obj);
  Touple2f operator*(float scalar);
  Touple2f operator/(float scalar);
  Touple2f operator=(Touple2f obj);
  Touple2f operator+=(Touple2f obj);
  Touple2f operator-=(Touple2f obj);
  Touple2f operator*=(float scalar);
  Touple2f operator/=(float scalar);
  Touple2f operator+();
  Touple2f operator-();

  operator float *() { return (float *)&x; }
  operator const float *() const { return (const float *)&x; }

  void callMe();
};
