// Copyright (C) 2020-2025 Parabola Research Limited
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include "Assert.h"
#include "Grains.h"
#include "Input.h"
#include "Instrumentation.h"
#include "Output.h"
#include "Timing.h"

#include <bungee/BungeeTypes.h>

#include <memory>

namespace Bungee::Internal {

template <class FourierKernel>
struct Stretcher :
	Timing,
	Instrumentation
{
	Fourier::Transforms<FourierKernel> transforms;
	Input<FourierKernel> input;
	Grains<FourierKernel> grains;
	Output<FourierKernel> output;
	Eigen::ArrayXXf previousWindowedInput;
	Eigen::ArrayXcf temporary;

	Stretcher(SampleRates sampleRates, int channelCount, int log2SynthesisHopAdjust);

	void enableInstrumentation(bool enable);

	InputChunk specifyGrain(const Request &request, double bufferStartPosition);

	void analyseGrain(const float *inputAudio, std::ptrdiff_t stride, int muteFrameCountHead, int muteFrameCountTail);

	void synthesiseGrain(OutputChunk &outputChunk);

	bool isFlushed() const;
};

} // namespace Bungee::Internal

#include "Stretcher.ipp"
