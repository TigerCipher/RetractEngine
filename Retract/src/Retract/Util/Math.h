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
constexpr T abs(T x)
{
    return x < 0 ? -x : x;
}

constexpr bool NearEqual(f32 x, f32 y, f32 tolerance = epsilon)
{
    return abs(x - y) <= tolerance;
}

constexpr bool NearZero(f32 val, f32 tolerance = epsilon)
{
    return abs(val) <= tolerance;
}

constexpr f32 SqrtNewton(f32 x, f32 current, f32 previous)
{
    return NearEqual(current, previous) ? current : SqrtNewton(x, 0.5f * (current + x / current), current);
}

constexpr f32 sqrt(f32 x)
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

    constexpr f32 Length() const { return math::sqrt(LengthSq()); }

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

    constexpr f32 Length() const { return math::sqrt(LengthSq()); }

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
        const f32 scalar = sinf(angle * 0.5f);
        x                = axis.x * scalar;
        y                = axis.y * scalar;
        z                = axis.z * scalar;
        w                = cosf(angle * 0.5f);
    }

    const f32* data() const { return &x; }

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

    constexpr f32 Length() const { return math::sqrt(LengthSq()); }

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

} // namespace retract::math

using vec2       = retract::math::Vector2;
using vec3       = retract::math::Vector3;
using vec4       = retract::math::Vector4;
using quaternion = vec4;
using color4     = vec4;