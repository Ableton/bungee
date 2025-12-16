// Copyright (C) 2020-2025 Parabola Research Limited
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "Assert.h"
#include "Dispatch.h"
#include "Fourier.h"

#include <Eigen/Core>

#include <initializer_list>

namespace Bungee::Window {

template <class FourierKernel>
Eigen::ArrayXf fromFrequencyDomainCoefficients(Fourier::Transforms<FourierKernel> &transforms, int log2Size, float gain, std::initializer_list<float> coefficients)
{
	Eigen::ArrayXcf frequencyDomain(Fourier::binCount(log2Size));

	std::size_t row = 0;
	for (auto c : coefficients)
		if (row < frequencyDomain.rows())
			frequencyDomain.coeffRef(row++) = c * gain;

	frequencyDomain.bottomRows(frequencyDomain.rows() - row).setZero();

	Eigen::ArrayXf window(Fourier::transformLength(log2Size));
	transforms.prepareInverse(log2Size);
	transforms.inverse(log2Size, window, frequencyDomain);
	return window;
}

struct Apply
{
	template <bool add>
	static void special(const Eigen::Ref<const Eigen::ArrayXf> &window, const Eigen::Ref<const Eigen::ArrayXXf> &input, Eigen::Ref<Eigen::ArrayXXf> output);
};

typedef Dispatch<Apply, 2> DispatchApply;

} // namespace Bungee::Window
