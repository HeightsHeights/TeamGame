#pragma once

#define Vector4f_MAX_SIZE 4
/******************************************************************************
 * class Touple4f
 * 四元数や色情報を作るための親クラス
******************************************************************************/

class Touple4f
{
private:
public:
  float x;
  float y;
  float z;
  float w;
  Touple4f();
  Touple4f(float x, float y, float z, float w);
  operator float *() { return (float *)&x; }
  operator const float *() const { return (const float *)&x; }
  Touple4f operator=(Touple4f obj);

  void callMe();
};
