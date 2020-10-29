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
	void NOP(void);
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
	void INC_BC(void);
	void DEC_BC(void);
	void INC_DE(void);
	void DEC_DE(void);
	void INC_HL(void);
	void DEC_HL(void);
	void INC_SP(void);
	void DEC_SP(void);
	void INC_HLa(void);
	void DEC_HLa(void);
	void INC_A(void);
	void DEC_A(void);
	void LD_FF_a8_A(uint8_t address);
	void LD_FF_Ca_A(void);
	void LD_a16_A(uint16_t address);
	void LD_FF_A_a8(uint8_t address);
	void LD_FF_A_Ca(void);
	void LD_A_a16(uint16_t address);
	void LD_HLa_B(void);
	void LD_HLa_C(void);
	void LD_HLa_D(void);
	void LD_HLa_E(void);
	void LD_HLa_H(void);
	void LD_HLa_L(void);
	void LD_HLa_A(void);
	void LD_B_C(void);
	void LD_B_D(void);
	void LD_B_E(void);
	void LD_B_H(void);
	void LD_B_L(void);
	void LD_B_A(void);
	void LD_C_B(void);
	void LD_C_D(void);
	void LD_C_E(void);
	void LD_C_H(void);
	void LD_C_L(void);
	void LD_C_A(void);
	void LD_D_B(void);
	void LD_D_C(void);
	void LD_D_E(void);
	void LD_D_H(void);
	void LD_D_L(void);
	void LD_D_A(void);
	void LD_E_B(void);
	void LD_E_C(void);
	void LD_E_D(void);
	void LD_E_H(void);
	void LD_E_L(void);
	void LD_E_A(void);
	void LD_H_B(void);
	void LD_H_C(void);
	void LD_H_D(void);
	void LD_H_E(void);
	void LD_H_L(void);
	void LD_H_A(void);
	void LD_L_B(void);
	void LD_L_C(void);
	void LD_L_D(void);
	void LD_L_E(void);
	void LD_L_H(void);
	void LD_L_A(void);
	void LD_A_B(void);
	void LD_A_C(void);
	void LD_A_D(void);
	void LD_A_E(void);
	void LD_A_H(void);
	void LD_A_L(void);
	void PREFIX(uint8_t instuction);
	void XOR_A(void);
	void RLCA(void);
	void RRCA(void);
	void RLA(void);
	void RRA(void);
	inline void jr(uint8_t signed_offset, bool doJump);
	void JR_r8(uint8_t signed_offset);
	void JR_NZ(uint8_t signed_offset);
	void JR_Z(uint8_t signed_offset);
	void JR_NC(uint8_t signed_offset);
	void JR_C(uint8_t signed_offset);
	void LD_B_d8(uint8_t data);
	void LD_C_d8(uint8_t data);
	void LD_D_d8(uint8_t data);
	void LD_E_d8(uint8_t data);
	void LD_H_d8(uint8_t data);
	void LD_L_d8(uint8_t data);
	void LD_A_d8(uint8_t data);
	void CALL_NZ(uint16_t address);
	void CALL_Z(uint16_t address);
	void CALL(uint16_t address);
	void CALL_NC(uint16_t address);
	void CALL_C(uint16_t address);
	void POP_BC(void);
	void PUSH_BC(void);
	void POP_DE(void);
	void PUSH_DE(void);
	void POP_HL(void);
	void PUSH_HL(void);
	void POP_AF(void);
	void PUSH_AF(void);
	inline void conditional_return(bool doReturn);
	void RET_NZ(void);
	void RET_Z(void);
	void RET(void);
	void RET_NC(void);
	void RET_C(void);
	inline void cp(uint8_t value);
	void CP_B(void);
	void CP_C(void);
	void CP_D(void);
	void CP_E(void);
	void CP_H(void);
	void CP_L(void);
	void CP_HLa(void);
	void CP_A(void);
	void CP_d8(uint8_t value);
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

