#include "GPU.h"

GPU::GPU(const uint64_t& cycles, MMU& memory) :
	cycles{ cycles },
	memory{ memory }
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
			memory.line++;

			if (memory.line == 143)
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
			memory.line++;

			if (memory.line > 153) // 10 lines
			{
				mode = ScanlineOAM;
				memory.line = 0;
			}
		}
		break;
	}
}

void GPU::ScanLine()
{
	uint16_t mapOffset = memory.gpuControl.backgroundTileMap ? 0x1C00 : 0x1800;

	// TODO could "memory.line + memory.scrollY" overflow?
	uint16_t yTileOffset = ((memory.line + memory.scrollY) & 255) / 8 * 32;

	for (uint16_t column = 0; column < 160; column++)
	{
		uint16_t xTileOffset = (memory.scrollX + column) / 8;

		uint16_t yOffset = (memory.line + memory.scrollY) & 7;
		uint16_t xOffset = (memory.scrollX + column) & 7;

		uint16_t tileIndex = memory.VRAM[mapOffset + yTileOffset + xTileOffset];

		if (memory.gpuControl.backgroundTileSet == 0)
			if (tileIndex < 128)
				tileIndex += 256;

		uint16_t tileAddress = tileIndex * 8 * 2;
		uint16_t lineOffset = yOffset * 2;

		// TODO could process the whole tile line from here
		uint8_t lineLow = memory.VRAM[tileAddress + lineOffset];
		uint8_t lineHigh = memory.VRAM[tileAddress + lineOffset + 1];

		uint8_t paletteIndex = 0;
		paletteIndex += (lineLow >> (7 - xOffset)) & 1;
		paletteIndex += ((lineHigh >> (7 - xOffset)) & 1) << 1;

		uint8_t color = 0;
		switch (paletteIndex)
		{
		case 0:
			color = memory.COLORS[memory.backgroundPalette.Color0];
			break;
		case 1:
			color = memory.COLORS[memory.backgroundPalette.Color1];
			break;
		case 2:
			color = memory.COLORS[memory.backgroundPalette.Color2];
			break;
		case 3:
			color = memory.COLORS[memory.backgroundPalette.Color3];
			break;
		default:
			throw std::logic_error("LoGiC ErRoR!");
			break;
		}

		display.Update(column, memory.line, color);
	}
}
