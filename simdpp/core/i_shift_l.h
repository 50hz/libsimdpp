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

#ifndef LIBSIMDPP_SIMDPP_CORE_I_SHIFT_L_H
#define LIBSIMDPP_SIMDPP_CORE_I_SHIFT_L_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/detail/not_implemented.h>
#include <simdpp/core/bit_and.h>
#include <simdpp/core/bit_andnot.h>
#include <simdpp/core/detail/i_shift.h>
#include <simdpp/null/math.h>
#include <simdpp/neon/detail/math_shift.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

/// @{
/** Shifts 8-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode


    @par 128-bit version:
    @icost{SSE2-AVX, 4-5}
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 8-9}
    @icost{AVX2, 4-5}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
*/
inline gint8x16 shift_l(gint8x16 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_l(a, count);
#elif SIMDPP_USE_SSE2
    uint16x8 mask, a16;
    mask = uint16x8::ones();
    mask = shift_r(mask, 16-count);
    mask = shift_l(mask, 8);

    a16 = a;
    a16 = shift_l(a16, count);
    a16 = bit_andnot(a16, mask);
    return a16;
#elif SIMDPP_USE_NEON
    int8x16 shift = int8x16::set_broadcast(count);
    return vshlq_u8(a, shift);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = uint8x16::set_broadcast(count);
    return vec_sl((__vector uint8_t)a, (__vector uint8_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
inline gint8x32 shift_l(gint8x32 a, unsigned count)
{
    uint16x16 mask, a16;
    mask = uint16x16::ones();
    mask = shift_r(mask, 16-count);
    mask = shift_l(mask, 8);

    a16 = a;
    a16 = shift_l(a16, count);
    a16 = bit_andnot(a16, mask);
    return a16;
}
#endif

template<unsigned N>
gint8<N> shift_l(gint8<N> a, unsigned count)
{
    SIMDPP_VEC_ARRAY_IMPL2S(gint8<N>, shift_l, a, count);
}
/// @}

/// @{
/** Shifts 16-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 128-bit version:
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
*/
inline gint16x8 shift_l(gint16x8 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_l(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_slli_epi16(a, count);
#elif SIMDPP_USE_NEON
    int16x8 shift = int16x8::set_broadcast(count);
    return vshlq_u16(a, shift);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = uint16x8::set_broadcast(count);
    return vec_sl((__vector uint16_t)a, (__vector uint16_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
inline gint16x16 shift_l(gint16x16 a, unsigned count)
{
    return _mm256_slli_epi16(a, count);
}
#endif

template<unsigned N>
gint16<N> shift_l(gint16<N> a, unsigned count)
{
    SIMDPP_VEC_ARRAY_IMPL2S(gint16<N>, shift_l, a, count);
}
/// @}

/// @{
/** Shifts 32-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 128-bit version:
    @icost{NEON, 1-2}
    @icost{ALTIVEC, 1-4}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @icost{ALTIVEC, 2-5}
*/
inline gint32x4 shift_l(gint32x4 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_l(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_slli_epi32(a, count);
#elif SIMDPP_USE_NEON
    int32x4 shift = int32x4::set_broadcast(count);
    return vshlq_u32(a, shift);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = uint32x4::set_broadcast(count);
    return vec_sl((__vector uint32_t)a, (__vector uint32_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
inline gint32x8 shift_l(gint32x8 a, unsigned count)
{
    return _mm256_slli_epi32(a, count);
}
#endif

template<unsigned N>
gint32<N> shift_l(gint32<N> a, unsigned count)
{
    SIMDPP_VEC_ARRAY_IMPL2S(gint32<N>, shift_l, a, count);
}
/// @}

/// @{
/** Shifts 64-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 128-bit version:
    @icost{NEON, 1-2}
    @unimp{ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @icost{NEON, 2-3}
    @unimp{ALTIVEC}
*/
inline gint64x2 shift_l(gint64x2 a, unsigned count)
{
#if SIMDPP_USE_NULL
    return null::shift_l(a, count);
#elif SIMDPP_USE_SSE2
    return _mm_slli_epi64(a, count);
#elif SIMDPP_USE_NEON
    int64x2 shift = int64x2::set_broadcast(count);
    return vshlq_u64(a, shift);
#else
    return SIMDPP_NOT_IMPLEMENTED2(a, count);
#endif
}

#if SIMDPP_USE_AVX2
inline gint64x4 shift_l(gint64x4 a, unsigned count)
{
    return _mm256_slli_epi64(a, count);
}
#endif

template<unsigned N>
gint64<N> shift_l(gint64<N> a, unsigned count)
{
    SIMDPP_VEC_ARRAY_IMPL2S(gint64<N>, shift_l, a, count);
}
/// @}

namespace detail {

template<unsigned count, unsigned N>
gint8<N> shift_l_8(gint8<N> a)
{
#if SIMDPP_USE_SSE2
    uint8<N> mask = detail::shift_u8_mask<8-count, uint8<N>>()();
    uint16<N/2> a16 = bit_and(a, mask);
    a16 = shift_l<count>(a16);
    return a16;
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

} // namespace detail



/// @{
/** Shifts 8-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode


    @par 128-bit version:
    @icost{SSE2-AVX2, 2-3}
    @icost{NEON, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, 4-5}
    @icost{AVX2,NEON, 2-3}
*/
template<unsigned count>
gint8x16 shift_l(gint8x16 a)
{
    static_assert(count <= 8, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 8) return uint8x16::zero();

#if SIMDPP_USE_NULL
    return shift_l(a, count);
#elif SIMDPP_USE_SSE2
    /*  SSE2-SSE4.1 and AVX-AVX2 instruction sets lack 8-bit shift. We emulate
        it using 16-bit shift.
    */
    return detail::shift_l_8<count>(a);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_l<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint8x16 shift = uint8x16::make_const(count);
    return vec_sl((__vector uint8_t)a, (__vector uint8_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count>
inline gint8x32 shift_l(gint8x32 a)
{
    static_assert(count <= 8, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 8) return uint8x32::zero();

    return shift_l(a, count);
}
#endif

template<unsigned count, unsigned N>
gint8<N> shift_l(gint8<N> a)
{
    static_assert(count <= 8, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 8) return uint8<N>::zero();

    SIMDPP_VEC_ARRAY_IMPL1(gint8<N>, shift_l<count>, a);
}
/// @}

/// @{
/** Shifts 16-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count>
gint16x8 shift_l(gint16x8 a)
{
    static_assert(count <= 16, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 16) return uint16x8::zero();

#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_l(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_l<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint16x8 shift = uint16x8::make_const(count);
    return vec_sl((__vector uint16_t)a, (__vector uint16_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count>
inline gint16x16 shift_l(gint16x16 a)
{
    static_assert(count <= 16, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 16) return uint16x16::zero();

    return shift_l(a, count);
}
#endif

template<unsigned count, unsigned N>
gint16<N> shift_l(gint16<N> a)
{
    static_assert(count <= 16, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 16) return uint16<N>::zero();

    SIMDPP_VEC_ARRAY_IMPL1(gint16<N>, shift_l<count>, a);
}
/// @}

/// @{
/** Shifts 32-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 2-3}
*/
template<unsigned count>
gint32x4 shift_l(gint32x4 a)
{
    static_assert(count <= 32, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 32) return uint32x4::zero();

#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_l(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_l<count>(a);
#elif SIMDPP_USE_ALTIVEC
    uint32x4 shift = uint32x4::make_const(count);
    return vec_sl((__vector uint32_t)a, (__vector uint32_t)shift);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count>
inline gint32x8 shift_l(gint32x8 a)
{
    static_assert(count <= 32, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 32) return uint32x8::zero();

    return shift_l(a, count);
}
#endif

template<unsigned count, unsigned N>
gint32<N> shift_l(gint32<N> a)
{
    static_assert(count <= 32, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 32) return uint32<N>::zero();

    SIMDPP_VEC_ARRAY_IMPL1(gint32<N>, shift_l<count>, a);
}
/// @}

/// @{
/** Shifts 64-bit values left by @a count bits while shifting in zeros.

    @code
    r0 = a0 << count
    ...
    rN = aN << count
    @endcode

    @unimp{ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @unimp{ALTIVEC}
*/
template<unsigned count>
gint64x2 shift_l(gint64x2 a)
{
    static_assert(count <= 64, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 64) return uint64x2::zero();

#if SIMDPP_USE_NULL || SIMDPP_USE_SSE2
    return shift_l(a, count);
#elif SIMDPP_USE_NEON
    return neon::detail::shift_l<count>(a);
#else
    return SIMDPP_NOT_IMPLEMENTED1(a);
#endif
}

#if SIMDPP_USE_AVX2
template<unsigned count>
inline gint64x4 shift_l(gint64x4 a)
{
    static_assert(count <= 64, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 64) return uint64x4::zero();

    return shift_l(a, count);
}
#endif

template<unsigned count, unsigned N>
gint64<N> shift_l(gint64<N> a)
{
    static_assert(count <= 64, "Shift out of bounds");
    if (count == 0) return a;
    if (count == 64) return uint64<N>::zero();

    SIMDPP_VEC_ARRAY_IMPL1(gint64<N>, shift_l<count>, a);
}
/// @}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
