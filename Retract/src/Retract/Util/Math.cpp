// ------------------------------------------------------------------------------
//
// RetractEngine
//    Copyright 2023 Matthew Rogers
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
// File Name: Math
// Date File Created: 08/18/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#include "Math.h"

namespace retract::math
{
Vector4 Slerp(const Vector4& a, const Vector4& b, f32 f)
{
    const f32 raw_cosm = Dot(a, b);
    f32       cosom;
    if (raw_cosm >= 0.0f)
        cosom = raw_cosm;
    else
        cosom = -raw_cosm;

    f32 scale0, scale1;
    if (cosom < 0.9999f)
    {
        const f32 omega   = acosf(cosom);
        const f32 inv_sin = 1.0f / sinf(omega);
        scale0            = sinf((1.0f - f) * omega) * inv_sin;
        scale1            = sinf(f * omega) * inv_sin;
    } else
    {
        scale0 = 1.0f - f;
        scale1 = f;
    }

    if (raw_cosm < 0.0f)
        scale1 = -scale1;

    vec4 ret{};
    ret.x = scale0 * a.x + scale1 * b.x;
    ret.y = scale0 * a.y + scale1 * b.y;
    ret.z = scale0 * a.z + scale1 * b.z;
    ret.w = scale0 * a.w + scale1 * b.w;
    return ret.Normalize();
}

Vector4 Concatinate(const Vector4& q, const Vector4& p)
{
    vec4       ret{};
    const vec3 qv{ q.x, q.y, q.z };
    const vec3 pv{ p.x, p.y, p.z };
    const vec3 new_vec = p.w * qv + q.w * pv + Cross(pv, qv);
    ret.x              = new_vec.x;
    ret.y              = new_vec.y;
    ret.z              = new_vec.z;

    ret.w = p.w * q.w - Dot(pv, qv);

    return ret;
}

Vector2 Transform(const Vector2& vec, const Matrix3& mat, f32 w)
{
    Vector2 ret;
    ret.x = vec.x * mat.mat[0][0] + vec.y * mat.mat[1][0] + w * mat.mat[2][0];
    ret.y = vec.x * mat.mat[0][1] + vec.y * mat.mat[1][1] + w * mat.mat[2][1];
    return ret;
}

Vector3 Transform(const Vector3& vec, const Matrix4& mat, f32 w)
{
    Vector3 ret;
    ret.x = vec.x * mat.mat[0][0] + vec.y * mat.mat[1][0] + vec.z * mat.mat[2][0] + w * mat.mat[3][0];
    ret.y = vec.x * mat.mat[0][1] + vec.y * mat.mat[1][1] + vec.z * mat.mat[2][1] + w * mat.mat[3][1];
    ret.z = vec.x * mat.mat[0][2] + vec.y * mat.mat[1][2] + vec.z * mat.mat[2][2] + w * mat.mat[3][2];
    return ret;
}

Vector3 Transform(const Vector3& vec, const Vector4& quaternion)
{
    const Vector3 qv{ quaternion.x, quaternion.y, quaternion.z };
    Vector3       ret = vec;
    ret += 2.f * Cross(qv, Cross(qv, vec) + quaternion.w * vec);
    return ret;
}

Vector3 TransformWithPerspDiv(const Vector3& vec, const Matrix4& mat, f32 w)
{
    Vector3 ret;
    ret.x            = vec.x * mat.mat[0][0] + vec.y * mat.mat[1][0] + vec.z * mat.mat[2][0] + w * mat.mat[3][0];
    ret.y            = vec.x * mat.mat[0][1] + vec.y * mat.mat[1][1] + vec.z * mat.mat[2][1] + w * mat.mat[3][1];
    ret.z            = vec.x * mat.mat[0][2] + vec.y * mat.mat[1][2] + vec.z * mat.mat[2][2] + w * mat.mat[3][2];
    f32 transformedW = vec.x * mat.mat[0][3] + vec.y * mat.mat[1][3] + vec.z * mat.mat[2][3] + w * mat.mat[3][3];
    if (!NearZero(Abs(transformedW)))
    {
        transformedW = 1.f / transformedW;
        ret *= transformedW;
    }
    return ret;
}

void Matrix4::Invert()
{
    f32 tmp[12];
    f32 src[16];
    f32 dst[16];

    // Transpose matrix
    // row 1 to col 1
    src[0]  = mat[0][0];
    src[4]  = mat[0][1];
    src[8]  = mat[0][2];
    src[12] = mat[0][3];

    // row 2 to col 2
    src[1]  = mat[1][0];
    src[5]  = mat[1][1];
    src[9]  = mat[1][2];
    src[13] = mat[1][3];

    // row 3 to col 3
    src[2]  = mat[2][0];
    src[6]  = mat[2][1];
    src[10] = mat[2][2];
    src[14] = mat[2][3];

    // row 4 to col 4
    src[3]  = mat[3][0];
    src[7]  = mat[3][1];
    src[11] = mat[3][2];
    src[15] = mat[3][3];

    // Calculate cofactors
    tmp[0]  = src[10] * src[15];
    tmp[1]  = src[11] * src[14];
    tmp[2]  = src[9] * src[15];
    tmp[3]  = src[11] * src[13];
    tmp[4]  = src[9] * src[14];
    tmp[5]  = src[10] * src[13];
    tmp[6]  = src[8] * src[15];
    tmp[7]  = src[11] * src[12];
    tmp[8]  = src[8] * src[14];
    tmp[9]  = src[10] * src[12];
    tmp[10] = src[8] * src[13];
    tmp[11] = src[9] * src[12];

    dst[0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
    dst[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
    dst[1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
    dst[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
    dst[2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
    dst[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
    dst[3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
    dst[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
    dst[4] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
    dst[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
    dst[5] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
    dst[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
    dst[6] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
    dst[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
    dst[7] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
    dst[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

    tmp[0]  = src[2] * src[7];
    tmp[1]  = src[3] * src[6];
    tmp[2]  = src[1] * src[7];
    tmp[3]  = src[3] * src[5];
    tmp[4]  = src[1] * src[6];
    tmp[5]  = src[2] * src[5];
    tmp[6]  = src[0] * src[7];
    tmp[7]  = src[3] * src[4];
    tmp[8]  = src[0] * src[6];
    tmp[9]  = src[2] * src[4];
    tmp[10] = src[0] * src[5];
    tmp[11] = src[1] * src[4];

    dst[8] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
    dst[8] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
    dst[9] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
    dst[9] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
    dst[10] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
    dst[10] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
    dst[11] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
    dst[11] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
    dst[12] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
    dst[12] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
    dst[13] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
    dst[13] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
    dst[14] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
    dst[14] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
    dst[15] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
    dst[15] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];

    // Calculate determinant
    f32 det = src[0] * dst[0] + src[1] * dst[1] + src[2] * dst[2] + src[3] * dst[3];

    // Inverse of matrix is divided by determinant
    det = 1 / det;
    for (f32& j : dst)
    {
        j *= det;
    }

    // Set it back
    for (i32 i = 0; i < 4; i++)
    {
        for (i32 j = 0; j < 4; j++)
        {
            mat[i][j] = dst[i * 4 + j];
        }
    }
}

Matrix4 FromQuaternion(const Quaternion& quat)
{
    f32 mat[4][4];

    mat[0][0] = 1.f - 2.f * quat.y * quat.y - 2.f * quat.z * quat.z;
    mat[0][1] = 2.f * quat.x * quat.y + 2.f * quat.w * quat.z;
    mat[0][2] = 2.f * quat.x * quat.z - 2.f * quat.w * quat.y;
    mat[0][3] = 0.f;

    mat[1][0] = 2.f * quat.x * quat.y - 2.f * quat.w * quat.z;
    mat[1][1] = 1.f - 2.f * quat.x * quat.x - 2.f * quat.z * quat.z;
    mat[1][2] = 2.f * quat.y * quat.z + 2.f * quat.w * quat.x;
    mat[1][3] = 0.f;

    mat[2][0] = 2.f * quat.x * quat.z + 2.f * quat.w * quat.y;
    mat[2][1] = 2.f * quat.y * quat.z - 2.f * quat.w * quat.x;
    mat[2][2] = 1.f - 2.f * quat.x * quat.x - 2.f * quat.y * quat.y;
    mat[2][3] = 0.f;

    mat[3][0] = 0.f;
    mat[3][1] = 0.f;
    mat[3][2] = 0.f;
    mat[3][3] = 1.f;

    return { mat };
}


} // namespace retract::math