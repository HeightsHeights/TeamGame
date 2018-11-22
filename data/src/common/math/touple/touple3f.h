#pragma once

#define Vector3f_MAX_SIZE 3
/******************************************************************************
 * class Touple3f
 * 
******************************************************************************/

class Touple3f
{
private:
public:
  float x;
  float y;
  float z;
  Touple3f();
  Touple3f(float x, float y, float z);
  operator float *() { return (float *)&x; }
  operator const float *() const { return (const float *)&x; }
  Touple3f operator=(Touple3f obj);

  void callMe();
};
