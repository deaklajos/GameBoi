#pragma once

#include <cstdint>

#include "Display.h"
#include "MMU.h"

class GPU
{
public:
	GPU(const uint64_t& cycles, MMU& memory);
	void Clock();

private:
	void ScanLine();

	Display display;
	MMU& memory;

	enum Mode
	{
		ScanlineOAM,
		ScanlineVRAM,
		HorizontalBlank,
		VerticalBlank,
	} mode = ScanlineOAM; //Maybe?

	const uint64_t& cycles; // TODO Dirty hack
	uint64_t last_cycles = 0; // TODO could be smaler
	uint64_t gpu_cycles = 0; // TODO could be smaler
	uint8_t lineValues[160];
};

