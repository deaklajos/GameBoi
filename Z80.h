#pragma once

#include <cstdint>
#include <array>
#include "MMU.h"
#include "GPU.h"

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
	void LD_BCa_A(void);
	void LD_DEa_A(void);
	void LDD_HLa_A(void);
	void LDI_HLa_A(void);
	void LDD_A_HLa(void);
	void LDI_A_HLa(void);
	void LD_A_BCa(void);
	void LD_A_DEa(void);
	void LD_HLa_d8(uint8_t data);
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
	void LD_B_HLa(void);
	void LD_B_A(void);
	void LD_C_B(void);
	void LD_C_D(void);
	void LD_C_E(void);
	void LD_C_H(void);
	void LD_C_L(void);
	void LD_C_HLa(void);
	void LD_C_A(void);
	void LD_D_B(void);
	void LD_D_C(void);
	void LD_D_E(void);
	void LD_D_H(void);
	void LD_D_L(void);
	void LD_D_HLa(void);
	void LD_D_A(void);
	void LD_E_B(void);
	void LD_E_C(void);
	void LD_E_D(void);
	void LD_E_H(void);
	void LD_E_L(void);
	void LD_E_HLa(void);
	void LD_E_A(void);
	void LD_H_B(void);
	void LD_H_C(void);
	void LD_H_D(void);
	void LD_H_E(void);
	void LD_H_L(void);
	void LD_H_HLa(void);
	void LD_H_A(void);
	void LD_L_B(void);
	void LD_L_C(void);
	void LD_L_D(void);
	void LD_L_E(void);
	void LD_L_H(void);
	void LD_L_HLa(void);
	void LD_L_A(void);
	void LD_A_B(void);
	void LD_A_C(void);
	void LD_A_D(void);
	void LD_A_E(void);
	void LD_A_H(void);
	void LD_A_L(void);
	void LD_A_HLa(void);
	inline void bit(uint8_t mask, uint8_t value);
	inline void bit0(uint8_t value);
	inline void bit1(uint8_t value);
	inline void bit2(uint8_t value);
	inline void bit3(uint8_t value);
	inline void bit4(uint8_t value);
	inline void bit5(uint8_t value);
	inline void bit6(uint8_t value);
	inline void bit7(uint8_t value);
	void BIT_0_B(void);
	void BIT_0_C(void);
	void BIT_0_D(void);
	void BIT_0_E(void);
	void BIT_0_H(void);
	void BIT_0_L(void);
	void BIT_0_HLa(void);
	void BIT_0_A(void);
	void BIT_1_B(void);
	void BIT_1_C(void);
	void BIT_1_D(void);
	void BIT_1_E(void);
	void BIT_1_H(void);
	void BIT_1_L(void);
	void BIT_1_HLa(void);
	void BIT_1_A(void);
	void BIT_2_B(void);
	void BIT_2_C(void);
	void BIT_2_D(void);
	void BIT_2_E(void);
	void BIT_2_H(void);
	void BIT_2_L(void);
	void BIT_2_HLa(void);
	void BIT_2_A(void);
	void BIT_3_B(void);
	void BIT_3_C(void);
	void BIT_3_D(void);
	void BIT_3_E(void);
	void BIT_3_H(void);
	void BIT_3_L(void);
	void BIT_3_HLa(void);
	void BIT_3_A(void);
	void BIT_4_B(void);
	void BIT_4_C(void);
	void BIT_4_D(void);
	void BIT_4_E(void);
	void BIT_4_H(void);
	void BIT_4_L(void);
	void BIT_4_HLa(void);
	void BIT_4_A(void);
	void BIT_5_B(void);
	void BIT_5_C(void);
	void BIT_5_D(void);
	void BIT_5_E(void);
	void BIT_5_H(void);
	void BIT_5_L(void);
	void BIT_5_HLa(void);
	void BIT_5_A(void);
	void BIT_6_B(void);
	void BIT_6_C(void);
	void BIT_6_D(void);
	void BIT_6_E(void);
	void BIT_6_H(void);
	void BIT_6_L(void);
	void BIT_6_HLa(void);
	void BIT_6_A(void);
	void BIT_7_B(void);
	void BIT_7_C(void);
	void BIT_7_D(void);
	void BIT_7_E(void);
	void BIT_7_H(void);
	void BIT_7_L(void);
	void BIT_7_HLa(void);
	void BIT_7_A(void);
	inline void res(uint8_t bitMask, uint8_t& value);
	inline void res0(uint8_t& value);
	inline void res1(uint8_t& value);
	inline void res2(uint8_t& value);
	inline void res3(uint8_t& value);
	inline void res4(uint8_t& value);
	inline void res5(uint8_t& value);
	inline void res6(uint8_t& value);
	inline void res7(uint8_t& value);
	void RES_0_B(void);
	void RES_0_C(void);
	void RES_0_D(void);
	void RES_0_E(void);
	void RES_0_H(void);
	void RES_0_L(void);
	void RES_0_HLa(void);
	void RES_0_A(void);
	void RES_1_B(void);
	void RES_1_C(void);
	void RES_1_D(void);
	void RES_1_E(void);
	void RES_1_H(void);
	void RES_1_L(void);
	void RES_1_HLa(void);
	void RES_1_A(void);
	void RES_2_B(void);
	void RES_2_C(void);
	void RES_2_D(void);
	void RES_2_E(void);
	void RES_2_H(void);
	void RES_2_L(void);
	void RES_2_HLa(void);
	void RES_2_A(void);
	void RES_3_B(void);
	void RES_3_C(void);
	void RES_3_D(void);
	void RES_3_E(void);
	void RES_3_H(void);
	void RES_3_L(void);
	void RES_3_HLa(void);
	void RES_3_A(void);
	void RES_4_B(void);
	void RES_4_C(void);
	void RES_4_D(void);
	void RES_4_E(void);
	void RES_4_H(void);
	void RES_4_L(void);
	void RES_4_HLa(void);
	void RES_4_A(void);
	void RES_5_B(void);
	void RES_5_C(void);
	void RES_5_D(void);
	void RES_5_E(void);
	void RES_5_H(void);
	void RES_5_L(void);
	void RES_5_HLa(void);
	void RES_5_A(void);
	void RES_6_B(void);
	void RES_6_C(void);
	void RES_6_D(void);
	void RES_6_E(void);
	void RES_6_H(void);
	void RES_6_L(void);
	void RES_6_HLa(void);
	void RES_6_A(void);
	void RES_7_B(void);
	void RES_7_C(void);
	void RES_7_D(void);
	void RES_7_E(void);
	void RES_7_H(void);
	void RES_7_L(void);
	void RES_7_HLa(void);
	void RES_7_A(void);
	inline void rl(uint8_t& value);
	void RL_B(void);
	void RL_C(void);
	void RL_D(void);
	void RL_E(void);
	void RL_H(void);
	void RL_L(void);
	void RL_HLa(void);
	void RL_A(void);
	inline void sla(uint8_t& value);
	void SLA_B(void);
	void SLA_C(void);
	void SLA_D(void);
	void SLA_E(void);
	void SLA_H(void);
	void SLA_L(void);
	void SLA_HLa(void);
	void SLA_A(void);
	inline void swap(uint8_t& value);
	void SWAP_B(void);
	void SWAP_C(void);
	void SWAP_D(void);
	void SWAP_E(void);
	void SWAP_H(void);
	void SWAP_L(void);
	void SWAP_HLa(void);
	void SWAP_A(void);
	inline void srl(uint8_t& value);
	void SRL_B(void);
	void SRL_C(void);
	void SRL_D(void);
	void SRL_E(void);
	void SRL_H(void);
	void SRL_L(void);
	void SRL_HLa(void);
	void SRL_A(void);
	void PREFIX(uint8_t instructionIndex);
	inline void and_(uint8_t value);
	void AND_B(void);
	void AND_C(void);
	void AND_D(void);
	void AND_E(void);
	void AND_H(void);
	void AND_L(void);
	void AND_HLa(void);
	void AND_A(void);
	void AND_d8(uint8_t value);
	inline void xor_(uint8_t value);
	void XOR_B(void);
	void XOR_C(void);
	void XOR_D(void);
	void XOR_E(void);
	void XOR_H(void);
	void XOR_L(void);
	void XOR_HLa(void);
	void XOR_A(void);
	inline void or_(uint8_t value);
	void OR_B(void);
	void OR_C(void);
	void OR_D(void);
	void OR_E(void);
	void OR_H(void);
	void OR_L(void);
	void OR_HLa(void);
	void OR_A(void);
	void OR_d8(uint8_t value);
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
	inline void jp(uint16_t address, bool doJump);
	void JP_16a(uint16_t address);
	void JP_NZ(uint16_t address);
	void JP_Z(uint16_t address);
	void JP_NC(uint16_t address);
	void JP_C(uint16_t address);
	void JP_HL(void);
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
	inline void add(uint8_t value);
	inline void adc(uint8_t value);
	void ADD_A_B(void);
	void ADD_A_C(void);
	void ADD_A_D(void);
	void ADD_A_E(void);
	void ADD_A_H(void);
	void ADD_A_L(void);
	void ADD_A_HLa(void);
	void ADD_A_A(void);
	void ADC_A_B(void);
	void ADC_A_C(void);
	void ADC_A_D(void);
	void ADC_A_E(void);
	void ADC_A_H(void);
	void ADC_A_L(void);
	void ADC_A_HLa(void);
	void ADC_A_A(void);
	void ADD_A_d8(uint8_t value);
	void ADC_A_d8(uint8_t value);
	void sub(uint8_t value);
	void SUB_B(void);
	void SUB_C(void);
	void SUB_D(void);
	void SUB_E(void);
	void SUB_H(void);
	void SUB_L(void);
	void SUB_HLa(void);
	void SUB_A(void);
	void SUB_d8(uint8_t value);
	void CP_B(void);
	void CP_C(void);
	void CP_D(void);
	void CP_E(void);
	void CP_H(void);
	void CP_L(void);
	void CP_HLa(void);
	void CP_A(void);
	void CP_d8(uint8_t value);
	void DI(void);
	void EI(void);
	void RST_0x0000(void);
	void RST_0x0008(void);
	void RST_0x0010(void);
	void RST_0x0018(void);
	void RST_0x0020(void);
	void RST_0x0028(void);
	void RST_0x0030(void);
	void RST_0x0038(void);
	void CPL(void);
	inline void add_16(uint16_t& accumulator, uint16_t value);
	void ADD_HL_BC(void);
	void ADD_HL_DE(void);
	void ADD_HL_HL(void);
	void ADD_HL_SP(void);
	void DAA(void);
	void unimplemented_op0(void);
	void unimplemented_op1(uint8_t);
	void unimplemented_op2(uint16_t);

	uint16_t pop_16(void);
	void push_16(uint16_t data);
	void HandleVblankInterrupt(void);
	void RETI(void);

private:
	MMU memory;
	GPU gpu;

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

	const std::array<Instruction, 256> instructions;

	struct PrefixInstruction {
		const char* name;
		uint8_t cycleCount;
		void (Z80::* op)(void);
	};

	const std::array<PrefixInstruction, 256> prefixInstructions;

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

