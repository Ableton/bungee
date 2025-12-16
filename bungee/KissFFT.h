// Copyright (C) 2020-2025 Parabola Research Limited
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <complex>

namespace Bungee::Fourier {

struct Kiss
{
	template <bool isInverse>
	struct Kernel
	{
		void *implementation;

		Kernel(int log2TransformLength);
		~Kernel();

		void forward(int log2TransformLength, float *t, std::complex<float> *f) const;
		void inverse(int log2TransformLength, float *t, std::complex<float> *f) const;
	};

	typedef Kernel<false> Forward;
	typedef Kernel<true> Inverse;
};

} // namespace Bungee::Fourier
