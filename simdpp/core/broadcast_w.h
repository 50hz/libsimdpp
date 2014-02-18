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

#ifndef LIBSIMDPP_SIMDPP_CORE_BROADCAST_W_H
#define LIBSIMDPP_SIMDPP_CORE_BROADCAST_W_H

#ifndef LIBSIMDPP_SIMD_H
    #error "This file must be included through simd.h"
#endif

#include <simdpp/types.h>
#include <simdpp/core/broadcast.h>
#include <simdpp/core/detail/shuffle128.h>

namespace simdpp {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace SIMDPP_ARCH_NAMESPACE {
#endif

namespace detail {

template<unsigned s, class V>
V v_broadcast_w(V a)
{
    using U = typename V::base_vector_type;
    U one = a[s / U::length];

    one = broadcast<s % U::length>(one);

    for (unsigned i = 0; i < V::vec_length; ++i) {
        a[i] = one;
    }
    return a;
}

} // namespace detail

/// @{
/** Broadcasts the specified 8-bit value to all elements within 128-bit lane

    @code
    r0 = a[s]
    r1 = a[s]
    ...
    rN = a[s]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 5}
    @icost{AVX2, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned s>
gint8x16 broadcast_w(gint8x16 a)
{
    return broadcast<s>(a);
}

#if SIMDPP_USE_AVX2
template<unsigned s>
gint8x32 broadcast_w(gint8x32 a)
{
    static_assert(s < 32, "Access out of bounds");
    gint8x16 lo;
    lo = s < 16 ? sse::extract_lo(a) : sse::extract_hi(a);
    lo = move_l<s % 16>(lo);
    return _mm256_broadcastb_epi8(lo);
}
#endif

template<unsigned s, unsigned N>
gint8<N> broadcast_w(gint8<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return detail::v_broadcast_w<s>(a);
}
/// @}

/// @{
/** Broadcasts the specified 16-bit value to all elements within a int16x8 vector

    @code
    r0 = a[s]
    r1 = a[s]
    ...
    r7 = a[s]
    @endcode

    @par 128-bit version:
    @icost{SSE2-AVX, 5}
    @icost{AVX2, 2}

    @par 256-bit version:
    @icost{SSE2-AVX, 6}
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned s>
gint16x8 broadcast_w(gint16x8 a)
{
    return broadcast<s>(a);
}

#if SIMDPP_USE_AVX2
template<unsigned s>
gint16x16 broadcast_w(gint16x16 a)
{
    static_assert(s < 16, "Access out of bounds");
    gint16x8 lo;
    lo = s < 8 ? sse::extract_lo(a) : sse::extract_hi(a);
    lo = move_l<s % 8>(lo);
    return _mm256_broadcastw_epi16(lo);
}
#endif

template<unsigned s, unsigned N>
gint16<N> broadcast_w(gint16<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return detail::v_broadcast_w<s>(a);
}
/// @}

/// @{
/** Broadcasts the specified 32-bit value to all elements within a int32x4 vector

    @code
    r0 = a[s]
    r1 = a[s]
    r2 = a[s]
    r3 = a[s]
    @endcode

    @par 256-bit version:
    @icost{NEON, ALTIVEC, 2}
*/
template<unsigned s>
gint32x4 broadcast_w(gint32x4 a)
{
    return broadcast<s>(a);
}

#if SIMDPP_USE_AVX2
template<unsigned s>
gint32x8 broadcast_w(gint32x8 a)
{
    static_assert(s < 8, "Access out of bounds");
    a = permute4<s%4,s%4,s%4,s%4>(a);
    a = detail::shuffle128<s/4, s/4>(a, a);
    return a;
}
#endif

template<unsigned s, unsigned N>
gint32<N> broadcast_w(gint32<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return detail::v_broadcast_w<s>(a);
}
/// @}

/// @{
/** Broadcasts the specified 64-bit value to all elements within a int64x2 vector

    @code
    r0 = a[s]
    r1 = a[s]
    @endcode

    @par 128-bit version:
    @icost{ALTIVEC, 1-2}

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, 2}
    @icost{ALTIVEC, 1-2}
*/
template<unsigned s>
gint64x2 broadcast_w(gint64x2 a)
{
    return broadcast<s>(a);
}

#if SIMDPP_USE_AVX2
template<unsigned s>
gint64x4 broadcast_w(gint64x4 a)
{
    static_assert(s < 4, "Access out of bounds");
    return permute4<s,s,s,s>(a);
}
#endif

template<unsigned s, unsigned N>
gint64<N> broadcast_w(gint64<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return detail::v_broadcast_w<s>(a);
}
/// @}

/// @{
/** Broadcasts the specified 32-bit value to all elements within a float32x4 vector

    @code
    r0 = a[s]
    r1 = a[s]
    r2 = a[s]
    r3 = a[s]
    @endcode

    @par 256-bit version:
    @icost{SSE2-AVX, NEON, ALTIVEC, 2}
*/
template<unsigned s>
float32x4 broadcast_w(float32x4 a)
{
    return broadcast<s>(a);
}

#if SIMDPP_USE_AVX
template<unsigned s>
float32x8 broadcast_w(float32x8 a)
{
    static_assert(s < 8, "Access out of bounds");
    a = detail::shuffle128<s/4,s/4>(a, a);
    return permute4<s%4,s%4,s%4,s%4>(a);
}
#endif

template<unsigned s, unsigned N>
float32<N> broadcast_w(float32<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return detail::v_broadcast_w<s>(a);
}
/// @}

/// @{
/** Broadcasts the specified 64-bit value to all elements within a float64x2 vector

    @code
    r0 = a[s]
    r1 = a[s]
    @endcode

    @par 128-bit version:
    @novec{NEON, ALTIVEC}

    @par 256-bit version:
    @icost{SSE2-AVX, 2}
    @novec{NEON, ALTIVEC}
*/
template<unsigned s>
float64x2 broadcast_w(float64x2 a)
{
    return broadcast<s>(a);
}

#if SIMDPP_USE_AVX
template<unsigned s>
float64x4 broadcast_w(float64x4 a)
{
    static_assert(s < 4, "Access out of bounds");
#if SIMDPP_USE_AVX2
    return permute<s,s,s,s>(a);
#else // SIMDPP_USE_AVX
    a = detail::shuffle128<s/2,s/2>(a, a);
    a = permute2<s%2,s%2>(a);
    return a;
#endif
}
#endif

template<unsigned s, unsigned N>
float64<N> broadcast_w(float64<N> a)
{
    static_assert(s < N, "Access out of bounds");
    return detail::v_broadcast_w<s>(a);
}
/// @}
///
#ifndef DOXYGEN_SHOULD_SKIP_THIS
} // namespace SIMDPP_ARCH_NAMESPACE
#endif
} // namespace simdpp

#endif
