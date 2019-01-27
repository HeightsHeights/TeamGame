// #pragma once

// #include "./collider.h"
// #include "../../../../common/math/vector/vectorSet.h"

// class Obb : public Collider
// {
// private:
// public:
//   Vector3f center;
//   Vector3f normalDirect[3];
//   Vector3f length[3];

//   virtual bool isCollision(Obb obb);
//   virtual bool isCollision(Sphere sphere);
//   // FLOAT LenSegOnSeparateAxis(D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0)
//   // {
//   //   // 3つの内積の絶対値の和で投影線分長を計算
//   //   // 分離軸Sepは標準化されていること
//   //   FLOAT r1 = fabs(D3DXVec3Dot(Sep, e1));
//   //   FLOAT r2 = fabs(D3DXVec3Dot(Sep, e2));
//   //   FLOAT r3 = e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0;
//   //   return r1 + r2 + r3;
//   // }
// };