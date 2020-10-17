#pragma once

#include <cstdint>
#include <array>
#include "MMU.h"

class Z80
{
public:
	Z80();
	~Z80();

	void Reset();
	void Clock();

	uint64_t cycles;

private:
	void LD_SP_d16(uint16_t data);
	void unimplemented_op0(void);
	void unimplemented_op1(uint8_t);
	void unimplemented_op2(uint16_t);

private:
	MMU memory;

	struct Instruction {
		const char* name;
		uint8_t cycleCount;
		uint8_t instructionLength;
		union
		{
			void (Z80::*op0)(void);
			void (Z80::*op1)(uint8_t);
			void (Z80::*op2)(uint16_t);
		};
	};

	std::array<Instruction, 256> instructions;

	struct Registers {
		struct {
			union {
				struct {
					uint8_t f;
					uint8_t a;
				};
				uint16_t af;
			};
		};

		struct {
			union {
				struct {
					uint8_t c;
					uint8_t b;
				};
				uint16_t bc;
			};
		};

		struct {
			union {
				struct {
					uint8_t e;
					uint8_t d;
				};
				uint16_t de;
			};
		};

		struct {
			union {
				struct {
					uint8_t l;
					uint8_t h;
				};
				uint16_t hl;
			};
		};

		uint16_t sp;
		uint16_t pc;
	} registers;

};

