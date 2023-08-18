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
} // namespace retract::math