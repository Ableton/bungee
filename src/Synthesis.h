// Copyright (C) 2020-2025 Parabola Research Limited
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "Grain.h"

namespace Bungee::Synthesis {

template <class FourierKernel>
void synthesise(int log2SynthesisHop, Grain<FourierKernel> &grain, Grain<FourierKernel> &previous);

} // namespace Bungee::Synthesis

#include "Synthesis.ipp"
