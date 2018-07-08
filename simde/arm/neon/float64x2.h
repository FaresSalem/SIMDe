/* Copyright (c) 2018 Evan Nemerson <evan@nemerson.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#if !defined(SIMDE__INSIDE_NEON_H)
#  error Do not include simde/arm/neon/float64x2.h directly; use simde/arm/neon.h.
#endif

#if !defined(SIMDE__NEON_FLOAT64X2_H)
#define SIMDE__NEON_FLOAT64X2_H

#if defined(SIMDE_NEON64_NATIVE)
#  if defined(HEDLEY_GCC_VERSION) && !HEDLEY_GCC_VERSION_CHECK(4,9,0)
#  else
#    define SIMDE_NEON_HAVE_FLOAT64X1
#  endif
#endif

typedef union {
#if defined(SIMDE__ENABLE_GCC_VEC_EXT)
  simde_float64   f64 __attribute__((__vector_size__(16)));
#else
  simde_float64   f64[2];
#endif

#if defined(SIMDE_NEON_HAVE_FLOAT64X1)
  float64x2_t     n;
#endif

#if defined(SIMDE_NEON_MMX)
  __m64           mmx[2];
#endif
#if defined(SIMDE_NEON_SSE2)
  __m128d         sse;
#endif
} simde_float64x2_t;

#if defined(SIMDE_NEON_HAVE_FLOAT64X1)
HEDLEY_STATIC_ASSERT(sizeof(float64x2_t) == sizeof(simde_float64x2_t), "float64x2_t size doesn't match simde_float64x2_t size");
#endif
HEDLEY_STATIC_ASSERT(16 == sizeof(simde_float64x2_t), "simde_float64x2_t size incorrect");

SIMDE__FUNCTION_ATTRIBUTES
simde_float64x2_t
simde_vld1q_f64 (simde_float64 const ptr[2]) {
  simde_float64x2_t r;
#if defined(SIMDE_NEON_HAVE_FLOAT64X1)
  r.n = vld1q_f64(ptr);
#else
  SIMDE__VECTORIZE
  for (size_t i = 0 ; i < (sizeof(r.f64) / sizeof(r.f64[0])) ; i++) {
    r.f64[i] = ptr[i];
  }
#endif
  return r;
}

SIMDE__FUNCTION_ATTRIBUTES
simde_float64x2_t
simde_x_vloadq_f64 (simde_float64 l0, simde_float64 l1) {
  simde_float64 v[] = { l0, l1 };
  return simde_vld1q_f64(v);
}

SIMDE__FUNCTION_ATTRIBUTES
simde_float64x2_t
simde_vdupq_n_f64 (simde_float64 value) {
  simde_float64x2_t r;
#if defined(SIMDE_NEON_HAVE_FLOAT64X1)
  r.n = vdupq_n_f64(value);
#else
  SIMDE__VECTORIZE
  for (size_t i = 0 ; i < (sizeof(r.f64) / sizeof(r.f64[0])) ; i++) {
    r.f64[i] = value;
  }
#endif
  return r;
}

#endif