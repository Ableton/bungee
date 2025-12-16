// Copyright (C) 2020-2025 Parabola Research Limited
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "Grain.h"

#include <memory>
#include <vector>

namespace Bungee {

template <class FourierKernel>
struct Grains
{
	std::vector<std::unique_ptr<Grain<FourierKernel>>> vector;

	Grains(size_t n) :
		vector(n)
	{
	}

	void rotate()
	{
		std::unique_ptr<Grain<FourierKernel>> grain = std::move(vector.front());
		for (int i = 0; i < vector.size() - 1; ++i)
			vector[i] = std::move(vector[i + 1]);
		vector.back() = std::move(grain);
	}

	bool flushed() const
	{
		for (auto &grain : vector)
			if (!std::isnan(grain->request.position))
				return false;
		return true;
	}

	inline Grain<FourierKernel> &operator[](size_t i)
	{
		return *vector[3 - i];
	}
};

} // namespace Bungee
