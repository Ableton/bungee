// Copyright (C) 2020-2025 Parabola Research Limited
// SPDX-License-Identifier: MPL-2.0

#include "Window.h"
#include "Assert.h"
#include "Fourier.h"

#include <Eigen/Core>

#include <cmath>

namespace Bungee::Window {

template <bool add>
void Apply::special(const Eigen::Ref<const Eigen::ArrayXf> &window, const Eigen::Ref<const Eigen::ArrayXXf> &input, Eigen::Ref<Eigen::ArrayXXf> output)
{
	if constexpr (add)
		output += input.colwise() * window;
	else
		output = input.colwise() * window;
}

template void Apply::special<false>(const Eigen::Ref<const Eigen::ArrayXf> &window, const Eigen::Ref<const Eigen::ArrayXXf> &input, Eigen::Ref<Eigen::ArrayXXf> output);
template void Apply::special<true>(const Eigen::Ref<const Eigen::ArrayXf> &window, const Eigen::Ref<const Eigen::ArrayXXf> &input, Eigen::Ref<Eigen::ArrayXXf> output);

} // namespace Bungee::Window
