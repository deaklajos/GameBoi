#pragma once

#include <cstdint>
#include <array>

class MMU
{
public:
	MMU(const uint16_t& pc);
	~MMU();
	uint8_t read_8(uint16_t address) const;
	void write_8(uint16_t address, uint8_t data);

	uint16_t read_16(uint16_t address) const;
	void write_16(uint16_t address, uint16_t data);

	const uint16_t& pc; // TODO Dirty hack

	// GPU stuff, TODO not here? UGLY!!!
	uint8_t scrollY = 0;
	uint8_t scrollX = 0;
	uint8_t line = 0;
	const uint8_t COLORS[4] = { 255, 192, 96, 0 }; // TODO satatic?
	struct BackgroundPalette {
		union {
			struct {
				uint8_t Color0 : 2;
				uint8_t Color1 : 2;
				uint8_t Color2 : 2;
				uint8_t Color3 : 2;
			};
			uint8_t value;
		};
	}backgroundPalette;
	struct GPUControl {
		union {
			struct {
				uint8_t backgroundEnable	: 1;
				uint8_t spriteEnable		: 1;
				uint8_t spriteSize			: 1;
				uint8_t backgroundTileMap	: 1;
				uint8_t backgroundTileSet	: 1;
				uint8_t windowEnable		: 1;
				uint8_t windowTileMap		: 1;
				uint8_t displayEnable		: 1;
			};
			uint8_t value;
		};
	}gpuControl;

	struct InterruptFlags {
		union {
			struct {
				bool Vblank : 1;
				bool LCDStatus : 1;
				bool timer : 1;
				bool serial : 1;
				bool joypad : 1;
				bool : 3;
			};
			uint8_t value;
		};
	};
	InterruptFlags	interruptEnable;
	InterruptFlags	interruptFlags;
	bool			interruptMaster = false;

	std::array<uint8_t, 0x2000> VRAM;
private:
	mutable bool isBootROMRunning = true;
	std::array<uint8_t, 0x100> boot_ROM;
	std::array<uint8_t, 0x8000> ROM;
	std::array<uint8_t, 0x2000> ERAM;
	std::array<uint8_t, 0x4000> WRAM;
	std::array<uint8_t, 0xA0> OAM;
	std::array<uint8_t, 0x80> ZRAM;
};

