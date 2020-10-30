#pragma once

#include <cstdint>

#include "Display.h"

class GPU
{
public:
	GPU(const uint64_t& const cycles);
	void Clock();

private:
	void ScanLine();

	Display display;

	enum Mode
	{
		ScanlineOAM,
		ScanlineVRAM,
		HorizontalBlank,
		VerticalBlank,
	} mode = HorizontalBlank;

	const uint64_t& const cycles; // TODO Dirty hack
	uint64_t last_cycles = 0; // TODO could be smaler
	uint64_t gpu_cycles = 0; // TODO could be smaler
	uint8_t line = 0;
};

