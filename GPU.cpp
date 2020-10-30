#include "GPU.h"

GPU::GPU(const uint64_t& const cycles) : cycles{ cycles }
{
}

void GPU::Clock()
{
	gpu_cycles += cycles - last_cycles;
	last_cycles = cycles;

	switch (mode)
	{
	case ScanlineOAM:
		if (gpu_cycles >= 80)
		{
			gpu_cycles -= 80;
			mode = ScanlineVRAM;
		}
		break;

	case ScanlineVRAM:
		if (gpu_cycles >= 172)
		{
			gpu_cycles -= 172;
			mode = HorizontalBlank;

			ScanLine();
		}
		break;

	case HorizontalBlank:
		if (gpu_cycles >= 204)
		{
			gpu_cycles -= 204;
			line++;

			if (line == 143)
			{
				mode = VerticalBlank;
				display.Show();
			}
			else
			{
				mode = ScanlineOAM;
			}
		}
		break;

	case VerticalBlank:
		if (gpu_cycles >= 456) // TODO could be just simply 4560
		{
			gpu_cycles -= 456;
			line++;

			if (line > 153) // 10 lines
			{
				mode = ScanlineOAM;
				line = 0;
			}
		}
		break;
	}
}

void GPU::ScanLine()
{
}
