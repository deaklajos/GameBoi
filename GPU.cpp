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
				memory.interruptFlags.Vblank = true;
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

		lineValues[column] = paletteIndex;

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

	// TODO render sprites
	// Remember if bg turned off, then fill lineValues with 0s
	// only 10 sprites
	for (const MMU::SpriteDescriptor& spriteDescriptor : memory.OAM)
	{
		if (spriteDescriptor.YPositionMinus16 == 0
			|| spriteDescriptor.YPositionMinus16 >= 160
			|| spriteDescriptor.XPositionMinus8 == 0	// Dont test this here, X affects 10 sprite cap
			|| spriteDescriptor.XPositionMinus8 >= 168)	// Dont test this here, X affects 10 sprite cap
			continue;

		constexpr uint16_t spriteBaseAdress = 0x8000;
		constexpr uint16_t spriteSizeInBits = 8 * 8 * 2;
		constexpr uint16_t spriteSizeInBytes = spriteSizeInBits / 8;

		const uint16_t spriteAdress = spriteBaseAdress + spriteDescriptor.tile * spriteSizeInBytes;

		constexpr bool is8x8 = true;
		if (is8x8) // MADNESS FROM HERE!!!
		{ // TODO Refactor
			const int16_t signedSpriteRow = memory.line - (spriteDescriptor.YPositionMinus16 - 16);
			const bool scanLineHitsSprite = signedSpriteRow < 8 && signedSpriteRow >= 0;

			if (!scanLineHitsSprite) // here count hits!!!
				continue;

			const uint8_t spriteRow = signedSpriteRow;

			int val = spriteDescriptor.XPositionMinus8 - 8;
			auto screenfrom = std::clamp(val, 0, 160);
			auto screento = std::clamp(val + 8, 0, 160);
			auto count = screento - screenfrom;
			// if count == 0 out of screen continue
			auto from = 0;
			if (val < 0)
				from = std::abs(val);

			// TODO flip!!!
			for (uint8_t spriteColumn = from; spriteColumn < from + count; spriteColumn++)
			{
				uint16_t spriteRowAdress = spriteAdress + spriteRow * 2;

				// Same code as background!!!
				// TODO Refactor
				uint8_t lineLow = memory.read_8(spriteRowAdress);
				uint8_t lineHigh = memory.read_8(spriteRowAdress + 1);

				uint8_t paletteIndex = 0;
				paletteIndex += (lineLow >> (7 - spriteColumn)) & 1;
				paletteIndex += ((lineHigh >> (7 - spriteColumn)) & 1) << 1;

				uint8_t screenColumn = screenfrom + spriteColumn - from;

				if (paletteIndex == 0)
					continue; // transparent

				if (lineValues[screenColumn] != 0 && spriteDescriptor.isBehind)
					continue; // behind

				lineValues[screenColumn] = paletteIndex;

				const MMU::Palette& palette = memory.spritePalette[spriteDescriptor.palette];

				uint8_t color = 0;
				switch (paletteIndex)
				{
				case 0:
					color = memory.COLORS[palette.Color0];
					break;
				case 1:
					color = memory.COLORS[palette.Color1];
					break;
				case 2:
					color = memory.COLORS[palette.Color2];
					break;
				case 3:
					color = memory.COLORS[palette.Color3];
					break;
				default:
					throw std::logic_error("LoGiC ErRoR!");
					break;
				}

				display.Update(screenColumn, memory.line, color);
			}
		}
	}
}
