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
	void LD_BC_d16(uint16_t data);
	void LD_DE_d16(uint16_t data);
	void LD_HL_d16(uint16_t data);
	void LDD_HLa_A(void);
	void LDI_HLa_A(void);
	void LD_A_BCa(void);
	void LD_A_DEa(void);
	inline void inc(uint8_t& value);
	inline void dec(uint8_t& value);
	void INC_B(void);
	void DEC_B(void);
	void INC_C(void);
	void DEC_C(void);
	void INC_D(void);
	void DEC_D(void);
	void INC_E(void);
	void DEC_E(void);
	void INC_H(void);
	void DEC_H(void);
	void INC_L(void);
	void DEC_L(void);
	void INC_HLa(void);
	void DEC_HLa(void);
	void INC_A(void);
	void DEC_A(void);
	void LD_FF_a8_A(uint8_t address);
	void LD_FF_C_A(void);
	void LD_HLa_B(void);
	void LD_HLa_C(void);
	void LD_HLa_D(void);
	void LD_HLa_E(void);
	void LD_HLa_H(void);
	void LD_HLa_L(void);
	void LD_HLa_A(void);
	void PREFIX(uint8_t instuction);
	void XOR_A(void);
	void JR_NZ(uint8_t signed_offset);
	void LD_C_d8(uint8_t data);
	void LD_E_d8(uint8_t data);
	void LD_L_d8(uint8_t data);
	void LD_A_d8(uint8_t data);
	void CALL_NZ(uint16_t address);
	void CALL_Z(uint16_t address);
	void CALL(uint16_t address);
	void CALL_NC(uint16_t address);
	void CALL_C(uint16_t address);
	void unimplemented_op0(void);
	void unimplemented_op1(uint8_t);
	void unimplemented_op2(uint16_t);

	uint16_t pop_16(void);
	void push_16(uint16_t data);

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

