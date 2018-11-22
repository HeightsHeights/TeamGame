#pragma once

#define Vector2f_MAX_SIZE 2
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
  operator float *() { return (float *)&x; }
  operator const float *() const { return (const float *)&x; }
  Touple2f operator=(Touple2f obj);

  void callMe();
};
