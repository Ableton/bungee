// Copyright (C) 2020-2025 Parabola Research Limited
// SPDX-License-Identifier: MPL-2.0

#include "bungee/KissFFT.h"

#include "Assert.h"

#include "kiss_fftr.h"

namespace Bungee::Fourier {

template <bool isInverse>
Kiss::Kernel<isInverse>::Kernel(int log2TransformLength) :
	implementation{kiss_fftr_alloc(1 << log2TransformLength, isInverse, nullptr, nullptr)}
{
}

template <bool isInverse>
Kiss::Kernel<isInverse>::~Kernel()
{
	KISS_FFT_FREE(implementation);
}

template <bool isInverse>
void Kiss::Kernel<isInverse>::forward(int log2TransformLength, float *t, std::complex<float> *f) const
{
	static_assert(sizeof(*f) == sizeof(kiss_fft_cpx));
	BUNGEE_ASSERT1(!isInverse);
	kiss_fftr((kiss_fftr_cfg)implementation, t, (kiss_fft_cpx *)f);
}
template <bool isInverse>
void Kiss::Kernel<isInverse>::inverse(int log2TransformLength, float *t, std::complex<float> *f) const
{
	static_assert(sizeof(*f) == sizeof(kiss_fft_cpx));
	BUNGEE_ASSERT1(isInverse);
	kiss_fftri((kiss_fftr_cfg)implementation, (kiss_fft_cpx *)f, t);
}

template class Kiss::Kernel<false>;
template class Kiss::Kernel<true>;

} // namespace Bungee::Fourier
