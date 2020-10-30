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

	const uint16_t& const pc; // TODO Dirty hack
private:
	mutable bool isBootROMRunning = true;
	std::array<uint8_t, 0x100> boot_ROM;
	std::array<uint8_t, 0x8000> ROM;
	std::array<uint8_t, 0x2000> VRAM;
	std::array<uint8_t, 0x2000> ERAM;
	std::array<uint8_t, 0x4000> WRAM;
	std::array<uint8_t, 0xA0> OAM;
	std::array<uint8_t, 0x80> ZRAM;
};

