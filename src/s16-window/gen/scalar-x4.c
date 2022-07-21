// Auto-generated file. Do not edit!
//   Template: src/s16-window/scalar.c.in
//   Generator: tools/xngen
//
// Copyright 2022 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include <xnnpack/math.h>
#include <xnnpack/window.h>


void xnn_s16_window_ukernel__scalar_x4(
    size_t rows,
    size_t channels,
    const int16_t* input,
    const int16_t* weights,
    uint32_t shift,
    int16_t* output) {

  assert(rows > 0);
  assert(channels > 0);
  assert(input != NULL);
  assert(weights != NULL);
  assert(shift < 32);
  assert(output != NULL);

  size_t i = rows;
  do {
    const int16_t* w = weights;
    size_t n = channels;
    for (; n >= 4; n -= 4) {
      const int16_t i0 = input[0];
      const int16_t i1 = input[1];
      const int16_t i2 = input[2];
      const int16_t i3 = input[3];
      input += 4;

      const int16_t w0 = w[0];
      const int16_t w1 = w[1];
      const int16_t w2 = w[2];
      const int16_t w3 = w[3];
      w += 4;

      int32_t vout0 = (int32_t) i0 * (int32_t) w0;
      int32_t vout1 = (int32_t) i1 * (int32_t) w1;
      int32_t vout2 = (int32_t) i2 * (int32_t) w2;
      int32_t vout3 = (int32_t) i3 * (int32_t) w3;

      vout0 = asr_s32(vout0, shift);
      vout1 = asr_s32(vout1, shift);
      vout2 = asr_s32(vout2, shift);
      vout3 = asr_s32(vout3, shift);

      vout0 = math_max_s32(vout0, INT16_MIN);
      vout1 = math_max_s32(vout1, INT16_MIN);
      vout2 = math_max_s32(vout2, INT16_MIN);
      vout3 = math_max_s32(vout3, INT16_MIN);

      vout0 = math_min_s32(vout0, INT16_MAX);
      vout1 = math_min_s32(vout1, INT16_MAX);
      vout2 = math_min_s32(vout2, INT16_MAX);
      vout3 = math_min_s32(vout3, INT16_MAX);

      output[0] = (int16_t)(vout0);
      output[1] = (int16_t)(vout1);
      output[2] = (int16_t)(vout2);
      output[3] = (int16_t)(vout3);

      output += 4;
    }

    if XNN_UNLIKELY(n != 0) {
      do {
        int32_t vout = ((int32_t) input[0] * (int32_t) w[0]);
        ++input;
        ++w;
        vout = asr_s32(vout, shift);
        vout = math_max_s32(vout, INT16_MIN);
        vout = math_min_s32(vout, INT16_MAX);
        output[0] = (int16_t)(vout);
        ++output;
      } while (--n != 0);
    }
  } while (--i != 0);
}