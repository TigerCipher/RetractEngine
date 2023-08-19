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
#pragma once

#include "Retract/Types.h"
#include <cmath>
#include <limits>

namespace retract::math
{
constexpr f32 pi                 = 3.1415926535f;
constexpr f32 two_pi             = pi * 2.0f;
constexpr f32 half_pi            = pi / 2.0f;
constexpr f32 infinity           = std::numeric_limits<f32>::infinity();
constexpr f32 neg_infinity       = -infinity;
constexpr f32 epsilon            = 0.001f;
constexpr f32 deg2rad_multiplier = pi / 180.0f;
constexpr f32 rad2deg_multiplier = 180.0f / pi;
constexpr f32 nan                = std::numeric_limits<f32>::quiet_NaN();


template<primitive_type T>
constexpr T Min(T a, T b)
{
    return a < b ? a : b;
}

template<primitive_type T>
constexpr T Max(T a, T b)
{
    return a < b ? b : a;
}

template<primitive_type T>
constexpr T Clamp(T value, T lower, T upper)
{
    return Min(upper, Max(lower, value));
}

// standard abs is not constexpr until C++23 -- this engine is C++20
template<primitive_type T>
constexpr T Abs(T x)
{
    return x < 0 ? -x : x;
}

constexpr bool NearEqual(f32 x, f32 y, f32 tolerance = epsilon)
{
    return Abs(x - y) <= tolerance;
}

constexpr bool NearZero(f32 val, f32 tolerance = epsilon)
{
    return Abs(val) <= tolerance;
}

constexpr f32 SqrtNewton(f32 x, f32 current, f32 previous)
{
    return NearEqual(current, previous) ? current : SqrtNewton(x, 0.5f * (current + x / current), current);
}

constexpr f32 Sqrt(f32 x)
{
    return x >= 0 && x < infinity ? SqrtNewton(x, x, 0.f) : nan;
}

constexpr f32 ToRadians(f32 degrees)
{
    return degrees * deg2rad_multiplier;
}

constexpr f32 ToDegrees(f32 radians)
{
    return radians * rad2deg_multiplier;
}

constexpr bool IsPowerOfTwo(u64 value)
{
    return value != 0 && (value & (value - 1)) == 0;
}

constexpr f32 Lerp(f32 a, f32 b, f32 f)
{
    return a + f * (b - a);
}


inline f32 Sin(f32 x)
{
    return sinf(x);
}

inline f32 Cos(f32 x)
{
    return cosf(x);
}

inline f32 Tan(f32 x)
{
    return tanf(x);
}

inline f32 Cot(f32 x)
{
    return 1.f / Tan(x);
}

inline f32 Acos(f32 x)
{
    return acosf(x);
}

inline f32 Atan2(f32 y, f32 x)
{
    return atan2f(y, x);
}

inline f32 Fmod(f32 numer, f32 denom)
{
    return fmodf(numer, denom);
}

class Vector2
{
public:
    // clang-format off
    union { f32 x, r, u; };
    union { f32 y, g, v; };
    // clang-format on

    Vector2() = default;
    constexpr Vector2(f32 _x, f32 _y) : x(_x), y(_y) {}

    const f32* data() const { return &x; }

    friend Vector2 operator+(const Vector2& a, const Vector2& b) { return { a.x + b.x, a.y + b.y }; }

    friend Vector2 operator-(const Vector2& a, const Vector2& b) { return { a.x - b.x, a.y - b.y }; }

    friend Vector2 operator*(const Vector2& a, const Vector2& b) { return { a.x * b.x, a.y * b.y }; }

    friend Vector2 operator*(const Vector2& v, f32 scalar) { return { v.x * scalar, v.y * scalar }; }

    friend Vector2 operator*(f32 scalar, const Vector2& v) { return { v.x * scalar, v.y * scalar }; }

    friend Vector2 operator/(const Vector2& a, const Vector2& b) { return { a.x / b.x, a.y / b.y }; }

    friend Vector2 operator/(const Vector2& v, f32 scalar) { return { v.x / scalar, v.y / scalar }; }

    Vector2& operator+=(const Vector2& right)
    {
        x += right.x;
        y += right.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& right)
    {
        x -= right.x;
        y -= right.y;
        return *this;
    }

    Vector2& operator*=(const Vector2& right)
    {
        x *= right.x;
        y *= right.y;
        return *this;
    }

    Vector2& operator/=(const Vector2& right)
    {
        x /= right.x;
        y /= right.y;
        return *this;
    }

    Vector2& operator+=(f32 scalar)
    {
        x += scalar;
        y += scalar;
        return *this;
    }

    Vector2& operator-=(f32 scalar)
    {
        x -= scalar;
        y -= scalar;
        return *this;
    }

    Vector2& operator*=(f32 scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2& operator/=(f32 scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    constexpr f32 Length() const { return math::Sqrt(LengthSq()); }

    constexpr f32 LengthSq() const { return x * x + y * y; }

    Vector2& Normalize()
    {
        const f32 len = Length();
        x /= len;
        y /= len;
        return *this;
    }
};

class Vector3
{
public:
    // clang-format off
    union { f32 x, r; };
    union { f32 y, g; };
    union { f32 z, b; };
    // clang-format on

    Vector3() = default;
    constexpr Vector3(f32 _x, f32 _y, f32 _z) : x(_x), y(_y), z(_z) {} // NOLINT(cppcoreguidelines-pro-type-member-init)

    const f32* data() const { return &x; }

    friend Vector3 operator+(const Vector3& a, const Vector3& b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }

    friend Vector3 operator-(const Vector3& a, const Vector3& b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }

    friend Vector3 operator*(const Vector3& a, const Vector3& b) { return { a.x * b.x, a.y * b.y, a.z * b.z }; }

    friend Vector3 operator/(const Vector3& a, const Vector3& b) { return { a.x / b.x, a.y / b.y, a.x / b.x }; }

    friend Vector3 operator*(const Vector3& v, f32 scalar) { return { v.x * scalar, v.y * scalar, v.z * scalar }; }

    friend Vector3 operator*(f32 scalar, const Vector3& v) { return { v.x * scalar, v.y * scalar, v.z * scalar }; }

    friend Vector3 operator/(const Vector3& v, f32 scalar) { return { v.x / scalar, v.y / scalar, v.z / scalar }; }

    Vector3& operator+=(const Vector3& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
        return *this;
    }

    Vector3& operator-=(const Vector3& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
        return *this;
    }

    Vector3& operator*=(const Vector3& right)
    {
        x *= right.x;
        y *= right.y;
        z *= right.z;
        return *this;
    }

    Vector3& operator/=(const Vector3& right)
    {
        x /= right.x;
        y /= right.y;
        z /= right.z;
        return *this;
    }

    Vector3& operator+=(f32 scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;
        return *this;
    }

    Vector3& operator-=(f32 scalar)
    {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        return *this;
    }

    Vector3& operator*=(f32 scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3& operator/=(f32 scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    constexpr f32 Length() const { return math::Sqrt(LengthSq()); }

    constexpr f32 LengthSq() const { return x * x + y * y + z * z; }

    Vector3& Normalize()
    {
        const f32 len = Length();
        x /= len;
        y /= len;
        z /= len;
        return *this;
    }
};

class Vector4
{
public:
    // clang-format off
    union { f32 x, r; };
    union { f32 y, g; };
    union { f32 z, b; };
    union { f32 w, a; };

    Vector4() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {} // NOLINT(cppcoreguidelines-pro-type-member-init)

    constexpr Vector4(f32 _x, f32 _y, f32 _z, f32 _w) : x(_x), y(_y), z(_z), w(_w) {} // NOLINT(cppcoreguidelines-pro-type-member-init)
    // clang-format on

    Vector4(const Vector3& axis, const f32 angle) // NOLINT(cppcoreguidelines-pro-type-member-init)
    {
        const f32 scalar = Sin(angle * 0.5f);
        x                = axis.x * scalar;
        y                = axis.y * scalar;
        z                = axis.z * scalar;
        w                = Cos(angle * 0.5f);
    }

    [[nodiscard]] const f32* data() const { return &x; }

    friend Vector4 operator+(const Vector4& a, const Vector4& b) { return { a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w }; }

    friend Vector4 operator-(const Vector4& a, const Vector4& b) { return { a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w }; }

    friend Vector4 operator*(const Vector4& a, const Vector4& b) { return { a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w }; }

    friend Vector4 operator/(const Vector4& a, const Vector4& b) { return { a.x / b.x, a.y / b.y, a.x / b.x, a.w / b.w }; }

    friend Vector4 operator*(const Vector4& v, f32 scalar) { return { v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar }; }

    friend Vector4 operator*(f32 scalar, const Vector4& v) { return { v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar }; }

    friend Vector4 operator/(const Vector4& v, f32 scalar) { return { v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar }; }

    Vector4& operator+=(const Vector4& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
        w += right.w;
        return *this;
    }

    Vector4& operator-=(const Vector4& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
        w -= right.w;
        return *this;
    }

    Vector4& operator*=(const Vector4& right)
    {
        x *= right.x;
        y *= right.y;
        z *= right.z;
        w *= right.w;
        return *this;
    }

    Vector4& operator/=(const Vector4& right)
    {
        x /= right.x;
        y /= right.y;
        z /= right.z;
        w /= right.w;
        return *this;
    }

    Vector4& operator+=(f32 scalar)
    {
        x += scalar;
        y += scalar;
        z += scalar;
        w += scalar;
        return *this;
    }

    Vector4& operator-=(f32 scalar)
    {
        x -= scalar;
        y -= scalar;
        z -= scalar;
        w -= scalar;
        return *this;
    }

    Vector4& operator*=(f32 scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        w *= scalar;
        return *this;
    }

    Vector4& operator/=(f32 scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
        return *this;
    }

    constexpr f32 Length() const { return math::Sqrt(LengthSq()); }

    constexpr f32 LengthSq() const { return x * x + y * y + z * z + w * w; }

    Vector4& Normalize()
    {
        const f32 len = Length();
        x /= len;
        y /= len;
        z /= len;
        z /= len;
        return *this;
    }


    Vector4& Conjugate()
    {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }
};

Vector2 Transform(const Vector2& vec, const class Matrix3& mat, f32 w = 1.f);
Vector3 Transform(const Vector3& vec, const class Matrix4& mat, f32 w = 1.f);
Vector3 Transform(const Vector3& vec, const Vector4& quaternion);
Vector3 TransformWithPerspDiv(const Vector3& vec, const Matrix4& mat, f32 w = 1.f);


inline Vector2 Normalize(const Vector2& v)
{
    Vector2 temp = v;
    return temp.Normalize();
}

inline f32 Dot(const Vector2& a, const Vector2& b)
{
    return a.x * b.x + a.y * b.y;
}

// Lerp from vector A to B by f
inline Vector2 Lerp(const Vector2& a, const Vector2& b, f32 f)
{
    return a + f * (b - a);
}

// reflect vector v about n (a normalized vector)
inline Vector2 Reflect(const Vector2& v, const Vector2& n)
{
    return v - 2.0f * Dot(v, n) * n;
}

inline Vector3 Normalize(const Vector3& v)
{
    Vector3 temp = v;
    return temp.Normalize();
}

inline f32 Dot(const Vector3& a, const Vector3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vector3 Cross(const Vector3& a, const Vector3& b)
{
    Vector3 temp{};
    temp.x = a.y * b.z - a.z * b.y;
    temp.y = a.z * b.x - a.x * b.z;
    temp.z = a.x * b.y - a.y * b.x;
    return temp;
}

inline Vector3 Lerp(const Vector3& a, const Vector3& b, f32 f)
{
    return a + f * (b - a);
}

inline Vector3 Reflect(const Vector3& v, const Vector3& n)
{
    return v - 2.0f * Dot(v, n) * n;
}

inline Vector4 Normalize(const Vector4& v)
{
    Vector4 temp = v;
    return temp.Normalize();
}

inline f32 Dot(const Vector4& a, const Vector4& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline Vector4 Lerp(const Vector4& a, const Vector4& b, f32 f)
{
    Vector4 temp{};
    temp.x = Lerp(a.x, b.x, f);
    temp.y = Lerp(a.y, b.y, f);
    temp.z = Lerp(a.z, b.z, f);
    temp.w = Lerp(a.w, b.w, f);
    return temp.Normalize();
}

Vector4 Slerp(const Vector4& a, const Vector4& b, f32 f);
Vector4 Concatinate(const Vector4& q, const Vector4& p);

class Matrix3
{
public:
    f32 mat[3][3]{
        {1.f, 0.f, 0.f},
        {0.f, 1.f, 0.f},
        {0.f, 0.f, 1.f}
    };

    constexpr Matrix3() = default;

    Matrix3(f32 _mat[3][3]) { memcpy(mat, _mat, 9 * sizeof(f32)); }

    [[nodiscard]] const f32* data() const { return &mat[0][0]; }

    friend Matrix3 operator*(const Matrix3& left, const Matrix3& right)
    {
        Matrix3 ret;
        // row 0
        ret.mat[0][0] = left.mat[0][0] * right.mat[0][0] + left.mat[0][1] * right.mat[1][0] + left.mat[0][2] * right.mat[2][0];

        ret.mat[0][1] = left.mat[0][0] * right.mat[0][1] + left.mat[0][1] * right.mat[1][1] + left.mat[0][2] * right.mat[2][1];

        ret.mat[0][2] = left.mat[0][0] * right.mat[0][2] + left.mat[0][1] * right.mat[1][2] + left.mat[0][2] * right.mat[2][2];

        // row 1
        ret.mat[1][0] = left.mat[1][0] * right.mat[0][0] + left.mat[1][1] * right.mat[1][0] + left.mat[1][2] * right.mat[2][0];

        ret.mat[1][1] = left.mat[1][0] * right.mat[0][1] + left.mat[1][1] * right.mat[1][1] + left.mat[1][2] * right.mat[2][1];

        ret.mat[1][2] = left.mat[1][0] * right.mat[0][2] + left.mat[1][1] * right.mat[1][2] + left.mat[1][2] * right.mat[2][2];

        // row 2
        ret.mat[2][0] = left.mat[2][0] * right.mat[0][0] + left.mat[2][1] * right.mat[1][0] + left.mat[2][2] * right.mat[2][0];

        ret.mat[2][1] = left.mat[2][0] * right.mat[0][1] + left.mat[2][1] * right.mat[1][1] + left.mat[2][2] * right.mat[2][1];

        ret.mat[2][2] = left.mat[2][0] * right.mat[0][2] + left.mat[2][1] * right.mat[1][2] + left.mat[2][2] * right.mat[2][2];

        return ret;
    }

    Matrix3& operator*=(const Matrix3& right)
    {
        *this = *this * right;
        return *this;
    }
};

class Matrix4
{
public:
    f32 mat[4][4]{
        {1.f, 0.f, 0.f, 0.f},
        {0.f, 1.f, 0.f, 0.f},
        {0.f, 0.f, 1.f, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    };

    constexpr Matrix4() = default;

    Matrix4(f32 _mat[4][4]) { memcpy(mat, _mat, 16 * sizeof(f32)); }

    [[nodiscard]] const f32* data() const { return &mat[0][0]; }

    friend Matrix4 operator*(const Matrix4& left, const Matrix4& right)
    {
        Matrix4 ret;
        // row 0
        ret.mat[0][0] = left.mat[0][0] * right.mat[0][0] + left.mat[0][1] * right.mat[1][0] + left.mat[0][2] * right.mat[2][0] +
                        left.mat[0][3] * right.mat[3][0];

        ret.mat[0][1] = left.mat[0][0] * right.mat[0][1] + left.mat[0][1] * right.mat[1][1] + left.mat[0][2] * right.mat[2][1] +
                        left.mat[0][3] * right.mat[3][1];

        ret.mat[0][2] = left.mat[0][0] * right.mat[0][2] + left.mat[0][1] * right.mat[1][2] + left.mat[0][2] * right.mat[2][2] +
                        left.mat[0][3] * right.mat[3][2];

        ret.mat[0][3] = left.mat[0][0] * right.mat[0][3] + left.mat[0][1] * right.mat[1][3] + left.mat[0][2] * right.mat[2][3] +
                        left.mat[0][3] * right.mat[3][3];

        // row 1
        ret.mat[1][0] = left.mat[1][0] * right.mat[0][0] + left.mat[1][1] * right.mat[1][0] + left.mat[1][2] * right.mat[2][0] +
                        left.mat[1][3] * right.mat[3][0];

        ret.mat[1][1] = left.mat[1][0] * right.mat[0][1] + left.mat[1][1] * right.mat[1][1] + left.mat[1][2] * right.mat[2][1] +
                        left.mat[1][3] * right.mat[3][1];

        ret.mat[1][2] = left.mat[1][0] * right.mat[0][2] + left.mat[1][1] * right.mat[1][2] + left.mat[1][2] * right.mat[2][2] +
                        left.mat[1][3] * right.mat[3][2];

        ret.mat[1][3] = left.mat[1][0] * right.mat[0][3] + left.mat[1][1] * right.mat[1][3] + left.mat[1][2] * right.mat[2][3] +
                        left.mat[1][3] * right.mat[3][3];

        // row 2
        ret.mat[2][0] = left.mat[2][0] * right.mat[0][0] + left.mat[2][1] * right.mat[1][0] + left.mat[2][2] * right.mat[2][0] +
                        left.mat[2][3] * right.mat[3][0];

        ret.mat[2][1] = left.mat[2][0] * right.mat[0][1] + left.mat[2][1] * right.mat[1][1] + left.mat[2][2] * right.mat[2][1] +
                        left.mat[2][3] * right.mat[3][1];

        ret.mat[2][2] = left.mat[2][0] * right.mat[0][2] + left.mat[2][1] * right.mat[1][2] + left.mat[2][2] * right.mat[2][2] +
                        left.mat[2][3] * right.mat[3][2];

        ret.mat[2][3] = left.mat[2][0] * right.mat[0][3] + left.mat[2][1] * right.mat[1][3] + left.mat[2][2] * right.mat[2][3] +
                        left.mat[2][3] * right.mat[3][3];

        // row 3
        ret.mat[3][0] = left.mat[3][0] * right.mat[0][0] + left.mat[3][1] * right.mat[1][0] + left.mat[3][2] * right.mat[2][0] +
                        left.mat[3][3] * right.mat[3][0];

        ret.mat[3][1] = left.mat[3][0] * right.mat[0][1] + left.mat[3][1] * right.mat[1][1] + left.mat[3][2] * right.mat[2][1] +
                        left.mat[3][3] * right.mat[3][1];

        ret.mat[3][2] = left.mat[3][0] * right.mat[0][2] + left.mat[3][1] * right.mat[1][2] + left.mat[3][2] * right.mat[2][2] +
                        left.mat[3][3] * right.mat[3][2];

        ret.mat[3][3] = left.mat[3][0] * right.mat[0][3] + left.mat[3][1] * right.mat[1][3] + left.mat[3][2] * right.mat[2][3] +
                        left.mat[3][3] * right.mat[3][3];

        return ret;
    }

    Matrix4& operator*=(const Matrix4& right)
    {
        *this = *this * right;
        return *this;
    }

    // Not in SIMD, slow af
    void Invert();

    [[nodiscard]] Vector3 Translation() const { return { mat[3][0], mat[3][1], mat[3][2] }; }
    [[nodiscard]] Vector3 XAxis() const { return Normalize({ mat[0][0], mat[0][1], mat[0][2] }); } // X / Forward axis
    [[nodiscard]] Vector3 YAxis() const { return Normalize({ mat[1][0], mat[1][1], mat[1][2] }); } // Y / Left axis
    [[nodiscard]] Vector3 ZAxis() const { return Normalize({ mat[2][0], mat[2][1], mat[2][2] }); } // Z / Up axis

    [[nodiscard]] Vector3 Scale() const
    {
        Vector3 ret;
        ret.x = Vector3{ mat[0][0], mat[0][1], mat[0][2] }.Length();
        ret.y = Vector3{ mat[1][0], mat[1][1], mat[1][2] }.Length();
        ret.z = Vector3{ mat[2][0], mat[2][1], mat[2][2] }.Length();
        return ret;
    }
};

inline Matrix3 Scale(f32 x, f32 y)
{
    f32 mat[3][3] = {
        {  x, 0.f, 0.f},
        {0.f,   y, 0.f},
        {0.f, 0.f, 1.f},
    };

    return { mat };
}

inline Matrix3 Scale(const Vector2& scale)
{
    return Scale(scale.x, scale.y);
}

// rotation about z-axis. Theta is in radians
inline Matrix3 Rotation(f32 theta)
{
    f32 mat[3][3] = {
        { Cos(theta), Sin(theta), 0.f},
        {-Sin(theta), Cos(theta), 0.f},
        {        0.f,        0.f, 1.f},
    };

    return { mat };
}

inline Matrix3 Translation(f32 x, f32 y)
{
    f32 mat[3][3] = {
        {1.f, 0.f, 0.f},
        {0.f, 1.f, 0.f},
        {  x,   y, 1.f},
    };

    return { mat };
}

inline Matrix3 Translation(const Vector2& trans)
{
    return Translation(trans.x, trans.y);
}

inline Matrix4 Scale(f32 x, f32 y, f32 z)
{
    f32 mat[4][4] = {
        {  x, 0.f, 0.f, 0.f},
        {0.f,   y, 0.f, 0.f},
        {0.f, 0.f,   z, 0.f},
        {0.f, 0.f, 0.f, 1.f}
    };
    return { mat };
}

inline Matrix4 Scale(const Vector3& scale)
{
    return Scale(scale.x, scale.y, scale.z);
}

inline Matrix4 Scale(f32 x)
{
    return Scale(x, x, x);
}

inline Matrix4 RotationX(f32 theta)
{
    f32 mat[4][4] = {
        {1.f,         0.f,        0.f, 0.f},
        {0.f,  Cos(theta), Sin(theta), 0.f},
        {0.f, -Sin(theta), Cos(theta), 0.f},
        {0.f,         0.f,        0.f, 1.f},
    };

    return { mat };
}

inline Matrix4 RotationY(f32 theta)
{
    f32 mat[4][4] = {
        {Cos(theta), 0.f, -Sin(theta), 0.f},
        {       0.f, 1.f,         0.f, 0.f},
        {Sin(theta), 0.f,  Cos(theta), 0.f},
        {       0.f, 0.f,         0.f, 1.f},
    };

    return { mat };
}

inline Matrix4 RotationZ(f32 theta)
{
    f32 mat[4][4] = {
        { Cos(theta), Sin(theta), 0.f, 0.f},
        {-Sin(theta), Cos(theta), 0.f, 0.f},
        {        0.f,        0.f, 1.f, 0.f},
        {        0.f,        0.f, 0.f, 1.f},
    };

    return { mat };
}

inline Matrix4 Translation(const Vector3& trans)
{
    f32 mat[4][4] = {
        {    1.f,     0.f,     0.f, 0.f},
        {    0.f,     1.f,     0.f, 0.f},
        {    0.f,     0.f,     1.f, 0.f},
        {trans.x, trans.y, trans.z, 1.f},
    };

    return { mat };
}

using Quaternion = Vector4;

Matrix4 FromQuaternion(const Quaternion& quat);

inline Matrix4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
    const Vector3 zaxis = Normalize(target - eye);
    const Vector3 xaxis = Normalize(Cross(up, zaxis));
    const Vector3 yaxis = Normalize(Cross(zaxis, xaxis));

    Vector3 trans;
    trans.x = -Dot(xaxis, eye);
    trans.y = -Dot(yaxis, eye);
    trans.z = -Dot(zaxis, eye);

    float mat[4][4] = {
        {xaxis.x, yaxis.x, zaxis.x, 0.f},
        {xaxis.y, yaxis.y, zaxis.y, 0.f},
        {xaxis.z, yaxis.z, zaxis.z, 0.f},
        {trans.x, trans.y, trans.z, 1.f},
    };

    return { mat };
}

inline Matrix4 Orthographic(f32 width, f32 height, f32 near, f32 far)
{
    f32 mat[4][4] = {
        {2.f / width,          0.f,                 0.f, 0.f},
        {        0.f, 2.f / height,                 0.f, 0.f},
        {        0.f,          0.f,  1.f / (far - near), 0.f},
        {        0.f,          0.f, near / (near - far), 1.f},
    };

    return { mat };
}

inline Matrix4 Perspective(f32 fovY, f32 width, f32 height, f32 near, f32 far)
{
    const f32 yScale = Cot(fovY * 0.5f);
    const f32 xScale = yScale * height / width;

    f32 mat[4][4] = {
        {xScale,    0.f,                        0.f, 0.f},
        {   0.f, yScale,                        0.f, 0.f},
        {   0.f,    0.f,         far / (far - near), 1.f},
        {   0.f,    0.f, -near * far / (far - near), 0.f},
    };

    return { mat };
}

inline Matrix4 SimpleViewProjection(f32 width, f32 height)
{
    f32 mat[4][4] = {
        {2.f / width,          0.f, 0.f, 0.f},
        {        0.f, 2.f / height, 0.f, 0.f},
        {        0.f,          0.f, 1.f, 0.f},
        {        0.f,          0.f, 1.f, 1.f},
    };

    return { mat };
}


constexpr Vector2 zero_vec2{ 0, 0 };
constexpr Vector2 unitx_vec2{ 1, 0 };
constexpr Vector2 unity_vec2{ 0, 1 };
constexpr Vector2 neg_unitx_vec2{ -1, 0 };
constexpr Vector2 neg_unity_vec2{ 0, -1 };

constexpr Vector3 zero_vec3{ 0, 0, 0 };
constexpr Vector3 unitx_vec3{ 1, 0, 0 };
constexpr Vector3 unity_vec3{ 0, 1, 0 };
constexpr Vector3 unitz_vec3{ 0, 0, 1 };
constexpr Vector3 neg_unitx_vec3{ -1, 0, 0 };
constexpr Vector3 neg_unity_vec3{ 0, -1, 0 };
constexpr Vector3 neg_unitz_vec3{ 0, 0, -1 };

constexpr Vector4 identity_vec4{ 0, 0, 0, 1 };

constexpr Matrix3 identity_mat3{};
constexpr Matrix4 identity_mat4{};

} // namespace retract::math

using vec2       = retract::math::Vector2;
using vec3       = retract::math::Vector3;
using vec4       = retract::math::Vector4;
using mat3       = retract::math::Matrix3;
using mat4       = retract::math::Matrix4;
using quaternion = vec4;
using color4     = vec4;
using color3     = vec3;

namespace retract::color
{
constexpr color3 black        = { 0.f, 0.f, 0.f };
constexpr color3 white        = { 1.f, 1.f, 1.f };
constexpr color3 red          = { 1.f, 0.f, 0.f };
constexpr color3 green        = { 0.f, 1.f, 0.f };
constexpr color3 blue         = { 0.f, 0.f, 1.f };
constexpr color3 yellow       = { 1.f, 1.f, 0.f };
constexpr color3 magenta      = { 1.f, 0.f, 1.f };
constexpr color3 cyan         = { 0.f, 1.f, 1.f };
constexpr color3 light_yellow = { 1.f, 1.f, 0.88f };
constexpr color3 light_blue   = { 0.68f, 0.85f, 0.9f };
constexpr color3 light_pink   = { 1.f, 0.71f, 0.76f };
constexpr color3 light_green  = { 0.56f, 0.93f, 0.56f };
} // namespace retract::color