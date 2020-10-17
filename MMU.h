#pragma once

#include <cstdint>
#include <array>

class MMU
{
public:
	uint8_t read_8(uint16_t address) const;
	void write_8(uint16_t address, uint8_t data);

	uint16_t read_16(uint16_t address) const;
	void write_16(uint16_t address, uint16_t data);
};

