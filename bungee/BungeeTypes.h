// Copyright (C) 2020-2025 Parabola Research Limited
// SPDX-License-Identifier: MPL-2.0

#pragma once

#include <cstdint>

namespace Bungee {

// An object of type Request is passed to the audio stretcher every time an audio grain is processed.
struct Request
{
	// Frame-offset within the input audio of the centre-point of the current audio grain.
	// NaN signifies an invalid grain that produces no audio output and may be used for flushing.
	double position;

	// Output audio speed. Value of 1 means speed should be unchanged relative to the input audio.
	// Used by Stretcher's internal algorithms only when it's not possible to determine speed by
	// subtracting Request::position of previous grain from Request::position of current grain.
	double speed;

	// Adjustment as a frequency multiplier with a value of 1 meaning no pitch adjustment
	double pitch;

	// Set to have the stretcher forget all previous grains and restart on this grain.
	bool reset;
};

// Information to describe a chunk of  audio that the audio stretcher requires as input for the current grain.
// Note that input chunks of consecutive grains often overlap and are usually centred on the grain's
// Request::position.
struct InputChunk
{
	// Frame offsets relative to the start of the audio track
	int begin;
	int end;
};

// Describes a chunk of audio output
// Output chunks do not overlap and can be appended for seamless playback
struct OutputChunk
{
	float *data; // audio output data, not aligned and not interleaved
	int frameCount;
	intptr_t channelStride; // nth audio channel audio starts at data[n * channelStride]
	static constexpr int begin = 0, end = 1;
	const struct Request *request[2]; // request[0] corresponds to the first frame of data, request[1] corresponds to the frame after the last frame of data.
};

// Stretcher audio sample rates, in Hz
struct SampleRates
{
	int input;
	int output;
};

} // namespace Bungee
