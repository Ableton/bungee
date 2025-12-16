// Copyright (C) 2020-2025 Parabola Research Limited
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <bungee/BungeeTypes.h>

#include "../src/Stretcher.h"

#include <cstdint>

namespace Bungee {

// This is the Bungee stretcher class that users should instantiate.
template <class FourierKernel>
struct Stretcher
{
	// Initialises a stretcher instance with the specified sample rates and number of channels.
	// The parameter log2SynthesisHopAdjust influences the granularity of the stretcher. In general, setting
	// this parameter non-zero will reduce output audio quality but a value of -1 or +1 may be desirable
	// under some circumstances.
	// log2SynthesisHopAdjust=-1 doubles granular frequency, reducing latency and possibly improving weak transients.
	// log2SynthesisHopAdjust=1 halves granular frequency, possibly benefiting dense tones.
	inline Stretcher(SampleRates sampleRates, int channelCount, int log2SynthesisHopAdjust = 0) :
		stretcher{sampleRates, channelCount, log2SynthesisHopAdjust}
	{
	}

	// If called with a true parameter, enables verbose diagnostics and checks that report to
	// the system log file on iOS, Mac and Android, or to stderr on other platforms.
	inline void enableInstrumentation(bool enable)
	{
		stretcher.enableInstrumentation(enable);
	}

	// Returns the largest number of frames that might be requested by specifyGrain()
	// This helps the caller to allocate large enough buffers because it is guaranteed that
	// InputChunk::frameCount() will not exceed this number.
	inline int maxInputFrameCount() const
	{
		return stretcher.maxInputFrameCount(true);
	}

	// This function adjusts request.position so that the stretcher has a run in of a few
	// grains before hitting the requested position. Without preroll, the first milliseconds
	// of audio might sound weak or initial transients might be lost.
	inline void preroll(Request &request) const
	{
		stretcher.preroll(request);
	}

	// This function prepares request.position and request.reset for the subsequent grain.
	// Typically called within a granular loop where playback at constant request.speed is desired.
	inline void next(Request &request) const
	{
		stretcher.next(request);
	}

	// Specify a grain of audio and compute the necessary segment of input audio.
	// After calling this function, call analyseGrain.
	inline InputChunk specifyGrain(const Request &request, double bufferStartPosition = 0.)
	{
		return stretcher.specifyGrain(request, bufferStartPosition);
	}

	// Begins processing the grain. The audio data should correspond to the range
	// specified by specifyGrain's return value. After calling this function, call synthesiseGrain.
	// The "muteFrame" parameters specify a number of input frames that are unavailable at the
	// start (muteFrameCountHead) and end (muteFrameCountTail) of the audio data. These frame
	// ranges will not be read from the input buffer and mute, zero-valued frames will be used instead.
	inline void analyseGrain(const float *data, intptr_t channelStride, int muteFrameCountHead = 0, int muteFrameCountTail = 0)
	{
		stretcher.analyseGrain(data, channelStride, muteFrameCountHead, muteFrameCountTail);
	}

	// Complete processing of the grain of audio that was previously set up with calls to specifyGrain and analyseGrain.
	inline void synthesiseGrain(OutputChunk &outputChunk)
	{
		stretcher.synthesiseGrain(outputChunk);
	}

	// Returns true if every grain in the stretcher's pipeline is invalid (its Request::position was NaN).
	inline bool isFlushed() const
	{
		return stretcher.isFlushed();
	}

	Bungee::Internal::Stretcher<FourierKernel> stretcher;
};

} // namespace Bungee
