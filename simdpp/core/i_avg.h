/*  libsimdpp
    Copyright (C) 2013  Povilas Kanapickas povilas@radix.lt
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef LIBSIMDPP_SIMDPP_CORE_I_AVG_H
#define LIBSIMDPP_SIMDPP_CORE_I_AVG_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/bit_xor.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/i_add.h>
#include <simdpp/core/i_shift_r.h>
#include <simdpp/null/foreach.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif


/// @{
/** Computes rounded average of the unsigned 8-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline uint8x16 avg(uint8x16 a, uint8x16 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<uint8x16>(a, b, [](uint8_t a, uint8_t b){
        return (uint16_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    return _mm_avg_epu8(a, b);
#elif SIMDPP_USE_NEON
    return vrhaddq_u8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector uint8_t)a, (__vector uint8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline uint8x32 avg(uint8x32 a, uint8x32 b)
{
    return _mm256_avg_epu8(a, b);
}
#endif

template<unsigned N>
uint8<N> avg(uint8<N> a, uint8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint8<N>, avg, a, b);
}
/// @}

/// @{
/** Computes rounded average of signed 8-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4-5}

    @par 256-bit version:
    @icost{SSE2-AVX, 8-9}
    @icost{AVX2, 4-5}
    @icost{NEON, ALTIVEC, 2}
*/
inline int8x16 avg(int8x16 a, int8x16 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<int8x16>(a, b, [](int8_t a, int8_t b){
        return (int16_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    uint8x16 a2, b2, bias, r;
    bias = uint8x16::make_const(0x80);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#elif SIMDPP_USE_NEON
    return vrhaddq_s8(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector int8_t)a, (__vector int8_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline int8x32 avg(int8x32 a, int8x32 b)
{
    uint8x32 a2, b2, bias, r;
    bias = uint8x32::make_const(0x80);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
}
#endif

template<unsigned N>
int8<N> avg(int8<N> a, int8<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int8<N>, avg, a, b);
}
/// @}

/// @{
/** Computes rounded average of unsigned 16-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
inline uint16x8 avg(uint16x8 a, uint16x8 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<uint16x8>(a, b, [](uint16_t a, uint16_t b){
        return (uint32_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    return _mm_avg_epu16(a, b);
#elif SIMDPP_USE_NEON
    return vrhaddq_u16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector uint16_t)a, (__vector uint16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline uint16x16 avg(uint16x16 a, uint16x16 b)
{
    return _mm256_avg_epu16(a, b);
}
#endif

template<unsigned N>
uint16<N> avg(uint16<N> a, uint16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint16<N>, avg, a, b);
}
/// @}

/// @{
/** Computes rounded average of signed 16-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 4-5}

    @par 256-bit version:
    @icost{SSE2-AVX, 8-9}
    @icost{AVX2, 4-5}
    @icost{NEON, ALTIVEC, 2}
*/
inline int16x8 avg(int16x8 a, int16x8 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<int16x8>(a, b, [](int16_t a, int16_t b){
        return (int32_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    uint16x8 a2, b2, bias, r;
    bias = uint16x8::make_const(0x8000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#elif SIMDPP_USE_NEON
    return vrhaddq_s16(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector int16_t)a, (__vector int16_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline int16x16 avg(int16x16 a, int16x16 b)
{
    uint16x16 a2, b2, bias, r;
    bias = uint16x16::make_const(0x8000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
}
#endif

template<unsigned N>
int16<N> avg(int16<N> a, int16<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int16<N>, avg, a, b);
}
/// @}

/// @{
/** Computes rounded average of unsigned 32-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 6-7}

    @par 256-bit version:
    @icost{SSE2-AVX, 12-13}
    @icost{AVX2, 6-7}
    @icost{NEON, ALTIVEC, 2}
*/
inline uint32x4 avg(uint32x4 a, uint32x4 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<uint32x4>(a, b, [](uint32_t a, uint32_t b){
        return (uint64_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    // (x & y) + ((x ^ y) >> 1) + (x ^ y) & 1
    uint32x4 x1, x2, round;
    x1 = bit_and(a, b);
    x2 = bit_xor(a, b);
    round = bit_and(x2, uint32x4::make_const(1));
    x1 = add(x1, shift_r<1>(x2));
    x1 = add(x1, round);
    return x1;
#elif SIMDPP_USE_NEON
    return vrhaddq_u32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector uint32_t)a, (__vector uint32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline uint32x8 avg(uint32x8 a, uint32x8 b)
{
    // (x & y) + ((x ^ y) >> 1) + (x ^ y) & 1
    uint32x8 x1, x2, round;
    x1 = bit_and(a, b);
    x2 = bit_xor(a, b);
    round = bit_and(x2, uint32x8::make_const(1));
    x1 = add(x1, shift_r<1>(x2));
    x1 = add(x1, round);
    return x1;
}
#endif

template<unsigned N>
uint32<N> avg(uint32<N> a, uint32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(uint32<N>, avg, a, b);
}
/// @}

/// @{
/** Computes rounded average of signed 32-bit values.

    @code
    r0 = (a0 + b0 + 1) / 2
    ...
    rN = (aN + bN + 1) / 2
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX2, 9-10}
    @icost{NEON, 1}

    @par 256-bit version:
    @icost{SSE2-AVX, 18-19}
    @icost{AVX2, 9-10}
    @icost{NEON, ALTIVEC, 2}
*/
inline int32x4 avg(int32x4 a, int32x4 b)
{
#if SIMDPP_USE_NULL
    return null::foreach<int32x4>(a, b, [](int32_t a, int32_t b){
        return (int64_t(a) + b + 1) >> 1;
    });
#elif SIMDPP_USE_SSE2
    uint32x4 a2, b2, bias, r;
    bias = uint32x4::make_const(0x80000000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
#elif SIMDPP_USE_NEON
    return vrhaddq_s32(a, b);
#elif SIMDPP_USE_ALTIVEC
    return vec_avg((__vector int32_t)a, (__vector int32_t)b);
#endif
}

#if SIMDPP_USE_AVX2
inline int32x8 avg(int32x8 a, int32x8 b)
{
    uint32x8 a2, b2, bias, r;
    bias = uint32x8::make_const(0x80000000);
    a2 = bit_xor(a, bias); // add
    b2 = bit_xor(b, bias); // add
    r = avg(a2, b2); // unsigned
    r = bit_xor(r, bias); // sub
    return r;
}
#endif

template<unsigned N>
int32<N> avg(int32<N> a, int32<N> b)
{
    SIMDPP_VEC_ARRAY_IMPL2(int32<N>, avg, a, b);
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
