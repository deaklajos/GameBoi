#include "Z80.h"

#include <cstring>
#include <functional>
#include <iostream>
#include "Exceptions.h"


void Z80::unimplemented_op0(void)
{
	UNIMPLEMENTED();
}

void Z80::unimplemented_op1(uint8_t)
{
	UNIMPLEMENTED();
}

void Z80::unimplemented_op2(uint16_t)
{
	UNIMPLEMENTED();
}

void Z80::HandleVblankInterrupt(void)
{
	memory.interruptMaster = false;

	push_16(registers.pc);

	registers.pc = 0x0040;

	cycles += 12;
}

void Z80::RETI(void)
{
	memory.interruptMaster = true;

	registers.pc = pop_16();

	cycles += 12;
}

void Z80::NOP(void)
{}

void Z80::LD_SP_d16(uint16_t data)
{
	registers.sp = data;
}

void Z80::LD_BC_d16(uint16_t data)
{
	registers.bc = data;
}

void Z80::LD_DE_d16(uint16_t data)
{
	registers.de = data;
}

void Z80::LD_HL_d16(uint16_t data)
{
	registers.hl = data;
}

void Z80::LD_BCa_A(void) {
	memory.write_8(registers.bc, registers.a);
}

void Z80::LD_DEa_A(void) {
	memory.write_8(registers.de, registers.a);
}

void Z80::LDD_HLa_A(void) {
	memory.write_8(registers.hl, registers.a);
	registers.hl--;
}

void Z80::LDI_HLa_A(void) {
	memory.write_8(registers.hl, registers.a);
	registers.hl++;
}

void Z80::LDD_A_HLa(void) {
	registers.a = memory.read_8(registers.hl);
	registers.hl--;
}

void Z80::LDI_A_HLa(void) {
	registers.a = memory.read_8(registers.hl);
	registers.hl++;
}

void Z80::LD_A_BCa(void)
{
	registers.a = memory.read_8(registers.bc);
}

void Z80::LD_A_DEa(void)
{
	registers.a = memory.read_8(registers.de);
}

void Z80::LD_HLa_d8(uint8_t data)
{
	memory.write_8(registers.hl, data);
}

// is this required?
// bitfields maybe?
#define ZERO_FLAG 0x80u
#define SUBTRACT_FLAG 0x40u
#define HALF_CARRY_FLAG 0x20u
#define CARRY_FLAG 0x10u

inline void Z80::inc(uint8_t& value)
{
	if ((value & 0x0f) == 0x0f)
		registers.f |= HALF_CARRY_FLAG;		// SET
	else
		registers.f &= ~HALF_CARRY_FLAG;	// CLEAR

	registers.f &= ~SUBTRACT_FLAG;	// CLEAR

	value++;

	if (value == 0)
		registers.f |= ZERO_FLAG;	// SET
	else
		registers.f &= ~ZERO_FLAG;	// CLEAR
}

inline void Z80::dec(uint8_t& value)
{
	if ((value & 0x0f) == 0)
		registers.f |= HALF_CARRY_FLAG;		// SET
	else
		registers.f &= ~HALF_CARRY_FLAG;	// CLEAR

	registers.f |= SUBTRACT_FLAG;	// SET

	value--;

	if (value == 0)
		registers.f |= ZERO_FLAG;	// SET
	else
		registers.f &= ~ZERO_FLAG;	// CLEAR
}

void Z80::INC_B(void)
{
	inc(registers.b);
}

void Z80::DEC_B(void)
{
	dec(registers.b);
}

void Z80::INC_C(void)
{
	inc(registers.c);
}

void Z80::DEC_C(void)
{
	dec(registers.c);
}

void Z80::INC_D(void)
{
	inc(registers.d);
}

void Z80::DEC_D(void)
{
	dec(registers.d);
}

void Z80::INC_E(void)
{
	inc(registers.e);
}

void Z80::DEC_E(void)
{
	dec(registers.e);
}

void Z80::INC_H(void)
{
	inc(registers.h);
}

void Z80::DEC_H(void)
{
	dec(registers.h);
}

void Z80::INC_L(void)
{
	inc(registers.l);
}

void Z80::DEC_L(void)
{
	dec(registers.l);
}

void Z80::INC_BC(void)
{
	registers.bc++;
}

void Z80::DEC_BC(void)
{
	registers.bc--;
}

void Z80::INC_DE(void)
{
	registers.de++;
}

void Z80::DEC_DE(void)
{
	registers.de--;
}

void Z80::INC_HL(void)
{
	registers.hl++;
}

void Z80::DEC_HL(void)
{
	registers.hl--;
}

void Z80::INC_SP(void)
{
	registers.af++;
}

void Z80::DEC_SP(void)
{
	registers.af--;
}

void Z80::INC_HLa(void)
{
	uint8_t value = memory.read_8(registers.hl);
	inc(value);
	memory.write_8(registers.hl, value);
}

void Z80::DEC_HLa(void)
{
	uint8_t value = memory.read_8(registers.hl);
	dec(value);
	memory.write_8(registers.hl, value);
}

void Z80::INC_A(void)
{
	inc(registers.a);
}

void Z80::DEC_A(void)
{
	dec(registers.a);
}

void Z80::LD_FF_a8_A(uint8_t address)
{
	memory.write_8((uint16_t)0xff00u + address, registers.a);
}

void Z80::LD_FF_Ca_A(void)
{
	memory.write_8((uint16_t)0xff00u + registers.c, registers.a);
}

void Z80::LD_a16_A(uint16_t address)
{
	memory.write_8(address, registers.a);
}

void Z80::LD_FF_A_a8(uint8_t address)
{
	registers.a = memory.read_8((uint16_t)0xff00u + address);
}

void Z80::LD_FF_A_Ca(void)
{
	registers.a = memory.read_8((uint16_t)0xff00u + registers.c);
}

void Z80::LD_A_a16(uint16_t address)
{
	registers.a = memory.read_8(address);
}

void Z80::LD_HLa_B(void)
{
	memory.write_8(registers.hl, registers.b);
}

void Z80::LD_HLa_C(void)
{
	memory.write_8(registers.hl, registers.c);
}

void Z80::LD_HLa_D(void)
{
	memory.write_8(registers.hl, registers.d);
}

void Z80::LD_HLa_E(void)
{
	memory.write_8(registers.hl, registers.e);
}

void Z80::LD_HLa_H(void)
{
	memory.write_8(registers.hl, registers.h);
}

void Z80::LD_HLa_L(void)
{
	memory.write_8(registers.hl, registers.l);
}

void Z80::LD_HLa_A(void)
{
	memory.write_8(registers.hl, registers.a);
}

void Z80::LD_B_C(void)
{
	registers.b = registers.c;
}

void Z80::LD_B_D(void)
{
	registers.b = registers.d;
}

void Z80::LD_B_E(void)
{
	registers.b = registers.e;
}

void Z80::LD_B_H(void)
{
	registers.b = registers.h;
}

void Z80::LD_B_L(void)
{
	registers.b = registers.l;
}

void Z80::LD_B_HLa(void)
{
	registers.b = memory.read_8(registers.hl);
}

void Z80::LD_B_A(void)
{
	registers.b = registers.a;
}

void Z80::LD_C_B(void)
{
	registers.c = registers.b;
}

void Z80::LD_C_D(void)
{
	registers.c = registers.d;
}

void Z80::LD_C_E(void)
{
	registers.c = registers.e;
}

void Z80::LD_C_H(void)
{
	registers.c = registers.h;
}

void Z80::LD_C_L(void)
{
	registers.c = registers.l;
}

void Z80::LD_C_HLa(void)
{
	registers.c = memory.read_8(registers.hl);
}

void Z80::LD_C_A(void)
{
	registers.c = registers.a;
}

void Z80::LD_D_B(void)
{
	registers.d = registers.b;
}

void Z80::LD_D_C(void)
{
	registers.d = registers.c;
}

void Z80::LD_D_E(void)
{
	registers.d = registers.e;
}

void Z80::LD_D_H(void)
{
	registers.d = registers.h;
}

void Z80::LD_D_L(void)
{
	registers.d = registers.l;
}

void Z80::LD_D_HLa(void)
{
	registers.d = memory.read_8(registers.hl);
}

void Z80::LD_D_A(void)
{
	registers.d = registers.a;
}

void Z80::LD_E_B(void)
{
	registers.e = registers.b;
}

void Z80::LD_E_C(void)
{
	registers.e = registers.c;
}

void Z80::LD_E_D(void)
{
	registers.e = registers.d;
}

void Z80::LD_E_H(void)
{
	registers.e = registers.h;
}

void Z80::LD_E_L(void)
{
	registers.e = registers.l;
}

void Z80::LD_E_HLa(void)
{
	registers.e = memory.read_8(registers.hl);
}

void Z80::LD_E_A(void)
{
	registers.e = registers.a;
}

void Z80::LD_H_B(void)
{
	registers.h = registers.b;
}

void Z80::LD_H_C(void)
{
	registers.h = registers.c;
}

void Z80::LD_H_D(void)
{
	registers.h = registers.d;
}

void Z80::LD_H_E(void)
{
	registers.h = registers.e;
}

void Z80::LD_H_L(void)
{
	registers.h = registers.l;
}

void Z80::LD_H_HLa(void)
{
	registers.h = memory.read_8(registers.hl);
}

void Z80::LD_H_A(void)
{
	registers.h = registers.a;
}

void Z80::LD_L_B(void)
{
	registers.l = registers.b;
}

void Z80::LD_L_C(void)
{
	registers.l = registers.c;
}

void Z80::LD_L_D(void)
{
	registers.l = registers.d;
}

void Z80::LD_L_E(void)
{
	registers.l = registers.e;
}

void Z80::LD_L_H(void)
{
	registers.l = registers.h;
}

void Z80::LD_L_HLa(void)
{
	registers.l = memory.read_8(registers.hl);
}

void Z80::LD_L_A(void)
{
	registers.l = registers.a;
}

void Z80::LD_A_B(void)
{
	registers.a = registers.b;
}

void Z80::LD_A_C(void)
{
	registers.a = registers.c;
}

void Z80::LD_A_D(void)
{
	registers.a = registers.d;
}

void Z80::LD_A_E(void)
{
	registers.a = registers.e;
}

void Z80::LD_A_H(void)
{
	registers.a = registers.h;
}

void Z80::LD_A_L(void)
{
	registers.a = registers.l;
}

void Z80::LD_A_HLa(void)
{
	registers.a = memory.read_8(registers.hl);
}

inline void Z80::bit(uint8_t mask, uint8_t value)
{
	registers.f |= HALF_CARRY_FLAG;	// SET
	registers.f &= ~SUBTRACT_FLAG;	// CLEAR

	if (mask & value)
		registers.f &= ~ZERO_FLAG;	// CLEAR
	else
		registers.f |= ZERO_FLAG;	// SET
}

inline void Z80::bit0(uint8_t value) { bit(1, value); }
inline void Z80::bit1(uint8_t value) { bit((1 << 1), value); }
inline void Z80::bit2(uint8_t value) { bit((1 << 2), value); }
inline void Z80::bit3(uint8_t value) { bit((1 << 3), value); }
inline void Z80::bit4(uint8_t value) { bit((1 << 4), value); }
inline void Z80::bit5(uint8_t value) { bit((1 << 5), value); }
inline void Z80::bit6(uint8_t value) { bit((1 << 6), value); }
inline void Z80::bit7(uint8_t value) { bit((1 << 7), value); }

void Z80::BIT_0_B(void)		{ bit0(registers.b); }
void Z80::BIT_0_C(void)		{ bit0(registers.c); }
void Z80::BIT_0_D(void)		{ bit0(registers.d); }
void Z80::BIT_0_E(void)		{ bit0(registers.e); }
void Z80::BIT_0_H(void)		{ bit0(registers.h); }
void Z80::BIT_0_L(void)		{ bit0(registers.l); }
void Z80::BIT_0_HLa(void)	{ bit0(memory.read_8(registers.hl)); }
void Z80::BIT_0_A(void)		{ bit0(registers.a); }

void Z80::BIT_1_B(void)		{ bit1(registers.b); }
void Z80::BIT_1_C(void)		{ bit1(registers.c); }
void Z80::BIT_1_D(void)		{ bit1(registers.d); }
void Z80::BIT_1_E(void)		{ bit1(registers.e); }
void Z80::BIT_1_H(void)		{ bit1(registers.h); }
void Z80::BIT_1_L(void)		{ bit1(registers.l); }
void Z80::BIT_1_HLa(void)	{ bit1(memory.read_8(registers.hl)); }
void Z80::BIT_1_A(void)		{ bit1(registers.a); }

void Z80::BIT_2_B(void)		{ bit2(registers.b); }
void Z80::BIT_2_C(void)		{ bit2(registers.c); }
void Z80::BIT_2_D(void)		{ bit2(registers.d); }
void Z80::BIT_2_E(void)		{ bit2(registers.e); }
void Z80::BIT_2_H(void)		{ bit2(registers.h); }
void Z80::BIT_2_L(void)		{ bit2(registers.l); }
void Z80::BIT_2_HLa(void)	{ bit2(memory.read_8(registers.hl)); }
void Z80::BIT_2_A(void)		{ bit2(registers.a); }

void Z80::BIT_3_B(void)		{ bit3(registers.b); }
void Z80::BIT_3_C(void)		{ bit3(registers.c); }
void Z80::BIT_3_D(void)		{ bit3(registers.d); }
void Z80::BIT_3_E(void)		{ bit3(registers.e); }
void Z80::BIT_3_H(void)		{ bit3(registers.h); }
void Z80::BIT_3_L(void)		{ bit3(registers.l); }
void Z80::BIT_3_HLa(void)	{ bit3(memory.read_8(registers.hl)); }
void Z80::BIT_3_A(void)		{ bit3(registers.a); }

void Z80::BIT_4_B(void)		{ bit4(registers.b); }
void Z80::BIT_4_C(void)		{ bit4(registers.c); }
void Z80::BIT_4_D(void)		{ bit4(registers.d); }
void Z80::BIT_4_E(void)		{ bit4(registers.e); }
void Z80::BIT_4_H(void)		{ bit4(registers.h); }
void Z80::BIT_4_L(void)		{ bit4(registers.l); }
void Z80::BIT_4_HLa(void)	{ bit4(memory.read_8(registers.hl)); }
void Z80::BIT_4_A(void)		{ bit4(registers.a); }

void Z80::BIT_5_B(void)		{ bit5(registers.b); }
void Z80::BIT_5_C(void)		{ bit5(registers.c); }
void Z80::BIT_5_D(void)		{ bit5(registers.d); }
void Z80::BIT_5_E(void)		{ bit5(registers.e); }
void Z80::BIT_5_H(void)		{ bit5(registers.h); }
void Z80::BIT_5_L(void)		{ bit5(registers.l); }
void Z80::BIT_5_HLa(void)	{ bit5(memory.read_8(registers.hl)); }
void Z80::BIT_5_A(void)		{ bit5(registers.a); }

void Z80::BIT_6_B(void)		{ bit6(registers.b); }
void Z80::BIT_6_C(void)		{ bit6(registers.c); }
void Z80::BIT_6_D(void)		{ bit6(registers.d); }
void Z80::BIT_6_E(void)		{ bit6(registers.e); }
void Z80::BIT_6_H(void)		{ bit6(registers.h); }
void Z80::BIT_6_L(void)		{ bit6(registers.l); }
void Z80::BIT_6_HLa(void)	{ bit6(memory.read_8(registers.hl)); }
void Z80::BIT_6_A(void)		{ bit6(registers.a); }

void Z80::BIT_7_B(void)		{ bit7(registers.b); }
void Z80::BIT_7_C(void)		{ bit7(registers.c); }
void Z80::BIT_7_D(void)		{ bit7(registers.d); }
void Z80::BIT_7_E(void)		{ bit7(registers.e); }
void Z80::BIT_7_H(void)		{ bit7(registers.h); }
void Z80::BIT_7_L(void)		{ bit7(registers.l); }
void Z80::BIT_7_HLa(void)	{ bit7(memory.read_8(registers.hl)); }
void Z80::BIT_7_A(void)		{ bit7(registers.a); }

inline void Z80::res(uint8_t bitMask, uint8_t& value) {
	value &= (~bitMask);
}

inline void Z80::res0(uint8_t& value) { res(1, value); }
inline void Z80::res1(uint8_t& value) { res((1 << 1), value); }
inline void Z80::res2(uint8_t& value) { res((1 << 2), value); }
inline void Z80::res3(uint8_t& value) { res((1 << 3), value); }
inline void Z80::res4(uint8_t& value) { res((1 << 4), value); }
inline void Z80::res5(uint8_t& value) { res((1 << 5), value); }
inline void Z80::res6(uint8_t& value) { res((1 << 6), value); }
inline void Z80::res7(uint8_t& value) { res((1 << 7), value); }

void Z80::RES_0_B(void) { res0(registers.b); }
void Z80::RES_0_C(void) { res0(registers.c); }
void Z80::RES_0_D(void) { res0(registers.d); }
void Z80::RES_0_E(void) { res0(registers.e); }
void Z80::RES_0_H(void) { res0(registers.h); }
void Z80::RES_0_L(void) { res0(registers.l); }
void Z80::RES_0_A(void) { res0(registers.a); }
					    
void Z80::RES_1_B(void) { res1(registers.b); }
void Z80::RES_1_C(void) { res1(registers.c); }
void Z80::RES_1_D(void) { res1(registers.d); }
void Z80::RES_1_E(void) { res1(registers.e); }
void Z80::RES_1_H(void) { res1(registers.h); }
void Z80::RES_1_L(void) { res1(registers.l); }
void Z80::RES_1_A(void) { res1(registers.a); }
					    
void Z80::RES_2_B(void) { res2(registers.b); }
void Z80::RES_2_C(void) { res2(registers.c); }
void Z80::RES_2_D(void) { res2(registers.d); }
void Z80::RES_2_E(void) { res2(registers.e); }
void Z80::RES_2_H(void) { res2(registers.h); }
void Z80::RES_2_L(void) { res2(registers.l); }
void Z80::RES_2_A(void) { res2(registers.a); }
					    
void Z80::RES_3_B(void) { res3(registers.b); }
void Z80::RES_3_C(void) { res3(registers.c); }
void Z80::RES_3_D(void) { res3(registers.d); }
void Z80::RES_3_E(void) { res3(registers.e); }
void Z80::RES_3_H(void) { res3(registers.h); }
void Z80::RES_3_L(void) { res3(registers.l); }
void Z80::RES_3_A(void) { res3(registers.a); }
					    
void Z80::RES_4_B(void) { res4(registers.b); }
void Z80::RES_4_C(void) { res4(registers.c); }
void Z80::RES_4_D(void) { res4(registers.d); }
void Z80::RES_4_E(void) { res4(registers.e); }
void Z80::RES_4_H(void) { res4(registers.h); }
void Z80::RES_4_L(void) { res4(registers.l); }
void Z80::RES_4_A(void) { res4(registers.a); }
					    
void Z80::RES_5_B(void) { res5(registers.b); }
void Z80::RES_5_C(void) { res5(registers.c); }
void Z80::RES_5_D(void) { res5(registers.d); }
void Z80::RES_5_E(void) { res5(registers.e); }
void Z80::RES_5_H(void) { res5(registers.h); }
void Z80::RES_5_L(void) { res5(registers.l); }
void Z80::RES_5_A(void) { res5(registers.a); }
					    
void Z80::RES_6_B(void) { res6(registers.b); }
void Z80::RES_6_C(void) { res6(registers.c); }
void Z80::RES_6_D(void) { res6(registers.d); }
void Z80::RES_6_E(void) { res6(registers.e); }
void Z80::RES_6_H(void) { res6(registers.h); }
void Z80::RES_6_L(void) { res6(registers.l); }
void Z80::RES_6_A(void) { res6(registers.a); }
					    
void Z80::RES_7_B(void) { res7(registers.b); }
void Z80::RES_7_C(void) { res7(registers.c); }
void Z80::RES_7_D(void) { res7(registers.d); }
void Z80::RES_7_E(void) { res7(registers.e); }
void Z80::RES_7_H(void) { res7(registers.h); }
void Z80::RES_7_L(void) { res7(registers.l); }
void Z80::RES_7_A(void) { res7(registers.a); }

void Z80::RES_0_HLa(void) {
	uint8_t value = memory.read_8(registers.hl);
	res0(value);
	memory.write_8(registers.hl, value);
}

void Z80::RES_1_HLa(void) {
	uint8_t value = memory.read_8(registers.hl);
	res1(value);
	memory.write_8(registers.hl, value);
}

void Z80::RES_2_HLa(void) {
	uint8_t value = memory.read_8(registers.hl);
	res2(value);
	memory.write_8(registers.hl, value);
}

void Z80::RES_3_HLa(void) {
	uint8_t value = memory.read_8(registers.hl);
	res3(value);
	memory.write_8(registers.hl, value);
}

void Z80::RES_4_HLa(void) {
	uint8_t value = memory.read_8(registers.hl);
	res4(value);
	memory.write_8(registers.hl, value);
}

void Z80::RES_5_HLa(void) {
	uint8_t value = memory.read_8(registers.hl);
	res5(value);
	memory.write_8(registers.hl, value);
}

void Z80::RES_6_HLa(void) {
	uint8_t value = memory.read_8(registers.hl);
	res6(value);
	memory.write_8(registers.hl, value);
}

void Z80::RES_7_HLa(void) {
	uint8_t value = memory.read_8(registers.hl);
	res7(value);
	memory.write_8(registers.hl, value);
}

inline void Z80::rl(uint8_t &value)
{
	registers.f &= ~SUBTRACT_FLAG;		// CLEAR
	registers.f &= ~HALF_CARRY_FLAG;	// CLEAR

	uint8_t carry = (value & (1u << 7)) >> 7;
	if (carry)
		registers.f |= CARRY_FLAG;	// SET
	else
		registers.f &= ~CARRY_FLAG;	// CLEAR

	value <<= 1;
	value |= carry;

	if (value)
		registers.f &= ~ZERO_FLAG;	// CLEAR
	else
		registers.f |= ZERO_FLAG;	// SET
}

void Z80::RL_B(void)	{ rl(registers.b); }
void Z80::RL_C(void)	{ rl(registers.c); }
void Z80::RL_D(void)	{ rl(registers.d); }
void Z80::RL_E(void)	{ rl(registers.e); }
void Z80::RL_H(void)	{ rl(registers.h); }
void Z80::RL_L(void)	{ rl(registers.l); }
void Z80::RL_A(void)	{ rl(registers.a); }
void Z80::RL_HLa(void)
{
	uint8_t value = memory.read_8(registers.hl);
	rl(value);
	memory.write_8(registers.hl, value);
}

inline void Z80::sla(uint8_t& value)
{
	registers.f &= ~SUBTRACT_FLAG;		// CLEAR
	registers.f &= ~HALF_CARRY_FLAG;	// CLEAR

	uint8_t carry = (value & (1u << 7)) >> 7;
	if (carry)
		registers.f |= CARRY_FLAG;	// SET
	else
		registers.f &= ~CARRY_FLAG;	// CLEAR

	value <<= 1;

	if (value)
		registers.f &= ~ZERO_FLAG;	// CLEAR
	else
		registers.f |= ZERO_FLAG;	// SET
}

void Z80::SLA_B(void) { sla(registers.b); }
void Z80::SLA_C(void) { sla(registers.c); }
void Z80::SLA_D(void) { sla(registers.d); }
void Z80::SLA_E(void) { sla(registers.e); }
void Z80::SLA_H(void) { sla(registers.h); }
void Z80::SLA_L(void) { sla(registers.l); }
void Z80::SLA_A(void) { sla(registers.a); }
void Z80::SLA_HLa(void) {
	uint8_t value = memory.read_8(registers.hl);
	sla(value);
	memory.write_8(registers.hl, value);
}

inline void Z80::swap(uint8_t& value)
{
	value = (((value & 0xf) << 4) | ((value & 0xf0) >> 4));

	if (value == 0)
		registers.f = ZERO_FLAG;	// SET
	else
		registers.f = 0;			// CLEAR
}

void Z80::SWAP_B(void) { swap(registers.b); }
void Z80::SWAP_C(void) { swap(registers.c); }
void Z80::SWAP_D(void) { swap(registers.d); }
void Z80::SWAP_E(void) { swap(registers.e); }
void Z80::SWAP_H(void) { swap(registers.h); }
void Z80::SWAP_L(void) { swap(registers.l); }
void Z80::SWAP_A(void) { swap(registers.a); }
void Z80::SWAP_HLa(void)
{
	uint8_t value = memory.read_8(registers.hl);
	swap(value);
	memory.write_8(registers.hl, value);
}

inline void Z80::srl(uint8_t& value)
{
	registers.f &= ~SUBTRACT_FLAG;		// CLEAR
	registers.f &= ~HALF_CARRY_FLAG;	// CLEAR

	uint8_t carry = (value & 1u);
	if (carry)
		registers.f |= CARRY_FLAG;	// SET
	else
		registers.f &= ~CARRY_FLAG;	// CLEAR

	value >>= 1;

	if (value)
		registers.f &= ~ZERO_FLAG;	// CLEAR
	else
		registers.f |= ZERO_FLAG;	// SET
}

void Z80::SRL_B(void) { srl(registers.b); }
void Z80::SRL_C(void) { srl(registers.c); }
void Z80::SRL_D(void) { srl(registers.d); }
void Z80::SRL_E(void) { srl(registers.e); }
void Z80::SRL_H(void) { srl(registers.h); }
void Z80::SRL_L(void) { srl(registers.l); }
void Z80::SRL_A(void) { srl(registers.a); }
void Z80::SRL_HLa(void) {
	uint8_t value = memory.read_8(registers.hl);
	srl(value);
	memory.write_8(registers.hl, value);
}

void Z80::PREFIX(uint8_t instructionIndex)
{
	const PrefixInstruction& instruction = prefixInstructions[instructionIndex];
	(this->*instruction.op)();

	cycles += instruction.cycleCount;
}

inline void Z80::and_(uint8_t value)
{
	registers.a &= value;

	registers.f = HALF_CARRY_FLAG; // SET+CLEAR

	if (registers.a == 0)
		registers.f |= ZERO_FLAG; // SET
}

void Z80::AND_B(void)
{
	and_(registers.b);
}

void Z80::AND_C(void)
{
	and_(registers.c);
}

void Z80::AND_D(void)
{
	and_(registers.d);
}

void Z80::AND_E(void)
{
	and_(registers.e);
}

void Z80::AND_H(void)
{
	and_(registers.h);
}

void Z80::AND_L(void)
{
	and_(registers.l);
}

void Z80::AND_HLa(void)
{
	and_(memory.read_8(registers.hl));
}

void Z80::AND_A(void)
{
	and_(registers.a);
}

void Z80::AND_d8(uint8_t value)
{
	and_(value);
}

inline void Z80::xor_(uint8_t value)
{
	registers.a ^= value;

	if (registers.a == 0)
		registers.f = ZERO_FLAG; // SET+CLEAR
	else
		registers.f = 0; // CLEAR
}

void Z80::XOR_B(void)
{
	xor_(registers.b);
}

void Z80::XOR_C(void)
{
	xor_(registers.c);
}

void Z80::XOR_D(void)
{
	xor_(registers.d);
}

void Z80::XOR_E(void)
{
	xor_(registers.e);
}

void Z80::XOR_H(void)
{
	xor_(registers.h);
}

void Z80::XOR_L(void)
{
	xor_(registers.l);
}

void Z80::XOR_HLa(void)
{
	xor_(memory.read_8(registers.hl));
}

void Z80::XOR_A(void)
{
	xor_(registers.a);
}

void Z80::XOR_d8(uint8_t value)
{
	xor_(value);
}

inline void Z80::or_(uint8_t value)
{
	registers.a |= value;

	if (registers.a == 0)
		registers.f = ZERO_FLAG;
	else
		registers.f = 0;
}

void Z80::OR_B(void)
{
	or_(registers.b);
}

void Z80::OR_C(void)
{
	or_(registers.c);
}

void Z80::OR_D(void)
{
	or_(registers.d);
}

void Z80::OR_E(void)
{
	or_(registers.e);
}

void Z80::OR_H(void)
{
	or_(registers.h);
}

void Z80::OR_L(void)
{
	or_(registers.l);
}

void Z80::OR_HLa(void)
{
	or_(memory.read_8(registers.hl));
}

void Z80::OR_A(void)
{
	or_(registers.a);
}

void Z80::OR_d8(uint8_t value)
{
	or_(value);
}

void Z80::RLCA(void)
{
	registers.f &= ~ZERO_FLAG;			// CLEAR
	registers.f &= ~SUBTRACT_FLAG;		// CLEAR
	registers.f &= ~HALF_CARRY_FLAG;	// CLEAR

	uint8_t carry = (registers.a & (1u << 7)) >> 7;

	if (carry)
		registers.f |= CARRY_FLAG;	// SET
	else
		registers.f &= ~CARRY_FLAG;	// CLEAR

	registers.a <<= 1;
	registers.a |= carry;
}

void Z80::RRCA(void)
{
	registers.f &= ~ZERO_FLAG;			// CLEAR
	registers.f &= ~SUBTRACT_FLAG;		// CLEAR
	registers.f &= ~HALF_CARRY_FLAG;	// CLEAR

	uint8_t carry = registers.a & 1u;

	if (carry)
		registers.f |= CARRY_FLAG;	// SET
	else
		registers.f &= ~CARRY_FLAG;	// CLEAR

	registers.a >>= 1;
	registers.a |= (carry << 7);
}

void Z80::RLA(void)
{
	registers.f &= ~ZERO_FLAG;			// CLEAR
	registers.f &= ~SUBTRACT_FLAG;		// CLEAR
	registers.f &= ~HALF_CARRY_FLAG;	// CLEAR

	uint8_t carry_flag = (registers.f & CARRY_FLAG) ? 1u : 0u;
	uint8_t carry = (registers.a & (1u << 7)) >> 7;

	if (carry)
		registers.f |= CARRY_FLAG;	// SET
	else
		registers.f &= ~CARRY_FLAG;	// CLEAR

	registers.a <<= 1;
	registers.a |= carry_flag;
}

void Z80::RRA(void)
{
	registers.f &= ~ZERO_FLAG;			// CLEAR
	registers.f &= ~SUBTRACT_FLAG;		// CLEAR
	registers.f &= ~HALF_CARRY_FLAG;	// CLEAR

	uint8_t carry_flag = (registers.f & CARRY_FLAG) ? 1u : 0u;
	uint8_t carry = registers.a & 1u;

	if (carry)
		registers.f |= CARRY_FLAG;	// SET
	else
		registers.f &= ~CARRY_FLAG;	// CLEAR

	registers.a >>= 1;
	registers.a |= (carry_flag << 7);
}

inline void Z80::jr(uint8_t signed_offset, bool doJump)
{
	int8_t offset = signed_offset;

	if (doJump)
	{
		registers.pc += offset;
		cycles += 12;
	}
	else
		cycles += 8;
}

void Z80::JR_r8(uint8_t signed_offset)
{
	jr(signed_offset, true);
}

void Z80::JR_NZ(uint8_t signed_offset)
{
	jr(signed_offset, !(registers.f & ZERO_FLAG));
}

void Z80::JR_Z(uint8_t signed_offset)
{
	jr(signed_offset, registers.f & ZERO_FLAG);
}

void Z80::JR_NC(uint8_t signed_offset)
{
	jr(signed_offset, !(registers.f & CARRY_FLAG));
}

void Z80::JR_C(uint8_t signed_offset)
{
	jr(signed_offset, registers.f & CARRY_FLAG);
}

inline void Z80::jp(uint16_t address, bool doJump)
{
	if (doJump)
	{
		registers.pc = address;
		cycles += 16;
	}
	else
		cycles += 12;
}

void Z80::JP_16a(uint16_t address)
{
	jp(address, true);
}

void Z80::JP_NZ(uint16_t address)
{
	jp(address, !(registers.f & ZERO_FLAG));
}

void Z80::JP_Z(uint16_t address)
{
	jp(address, registers.f & ZERO_FLAG);
}

void Z80::JP_NC(uint16_t address)
{
	jp(address, !(registers.f & CARRY_FLAG));
}

void Z80::JP_C(uint16_t address)
{
	jp(address, registers.f & CARRY_FLAG);
}

void Z80::JP_HL(void)
{
	registers.pc = registers.hl;
}

void Z80::LD_B_d8(uint8_t data)
{
	registers.b = data;
}

void Z80::LD_C_d8(uint8_t data)
{
	registers.c = data;
}

void Z80::LD_D_d8(uint8_t data)
{
	registers.d = data;
}

void Z80::LD_E_d8(uint8_t data)
{
	registers.e = data;
}

void Z80::LD_H_d8(uint8_t data)
{
	registers.h = data;
}

void Z80::LD_L_d8(uint8_t data)
{
	registers.l = data;
}

void Z80::LD_A_d8(uint8_t data)
{
	registers.a = data;
}

void Z80::CALL_NZ(uint16_t address)
{
	if (registers.f & ZERO_FLAG)
		cycles += 12;
	else
	{
		CALL(address);
		cycles += 24;
	}
}

void Z80::CALL_Z(uint16_t address)
{
	if (registers.f & ZERO_FLAG)
	{
		CALL(address);
		cycles += 24;
	}
	else
		cycles += 12;
}

void Z80::CALL(uint16_t address)
{
	push_16(registers.pc);
	registers.pc = address;
}

void Z80::CALL_NC(uint16_t address)
{
	if (registers.f & CARRY_FLAG)
		cycles += 12;
	else
	{
		CALL(address);
		cycles += 24;
	}
}

void Z80::CALL_C(uint16_t address)
{
	if (registers.f & CARRY_FLAG)
	{
		CALL(address);
		cycles += 24;
	}
	else
		cycles += 12;
}

uint16_t Z80::pop_16(void)
{
	uint16_t value = memory.read_16(registers.sp);
	registers.sp += 2;

	return value;
}

void Z80::push_16(uint16_t data)
{ // TODO Bottom of stack left unused?
	registers.sp -= 2;
	memory.write_16(registers.sp, data);
}

void Z80::POP_BC(void)
{
	registers.bc = pop_16();
}

void Z80::PUSH_BC(void)
{
	push_16(registers.bc);
}

void Z80::POP_DE(void)
{
	registers.de = pop_16();
}

void Z80::PUSH_DE(void)
{
	push_16(registers.de);
}

void Z80::POP_HL(void)
{
	registers.hl = pop_16();
}

void Z80::PUSH_HL(void)
{
	push_16(registers.hl);
}

void Z80::POP_AF(void)
{
	registers.af = pop_16();
}

void Z80::PUSH_AF(void)
{
	push_16(registers.af);
}

inline void Z80::conditional_return(bool doReturn)
{
	if (doReturn)
	{
		registers.pc = pop_16();
		cycles += 20;
	}
	else
		cycles += 8;
}

void Z80::RET_NZ(void)
{
	conditional_return(!(registers.f & ZERO_FLAG));
}

void Z80::RET_Z(void)
{
	conditional_return(registers.f & ZERO_FLAG);
}

void Z80::RET(void)
{
	registers.pc = pop_16();
}

void Z80::RET_NC(void)
{
	conditional_return(!(registers.f & CARRY_FLAG));
}

void Z80::RET_C(void)
{
	conditional_return(registers.f & CARRY_FLAG);
}

inline void Z80::cp(uint8_t value)
{
	if (registers.a == value)
		registers.f |= ZERO_FLAG;	// SET
	else
		registers.f &= ~ZERO_FLAG;	// CLEAR

	registers.f |= SUBTRACT_FLAG;	// SET

	if ((value & 0x0f) > (registers.a & 0x0f))
		registers.f |= HALF_CARRY_FLAG;	// SET
	else
		registers.f &= ~HALF_CARRY_FLAG;	// CLEAR

	if (value > registers.a)
		registers.f |= CARRY_FLAG;	// SET
	else
		registers.f &= ~CARRY_FLAG;	// CLEAR
}

inline void Z80::add(uint8_t value)
{
	if (((registers.a + value) & 0xFF) < registers.a)
		registers.f |= CARRY_FLAG;	// SET
	else
		registers.f &= ~CARRY_FLAG;	// CLEAR

	if (((registers.a + value) & 0x0F) < (registers.a & 0x0F))
		registers.f |= HALF_CARRY_FLAG;	// SET
	else
		registers.f &= ~HALF_CARRY_FLAG;	// CLEAR

	registers.a += value;

	if (registers.a == 0)
		registers.f |= ZERO_FLAG;	// SET
	else
		registers.f &= ~ZERO_FLAG;	// CLEAR

	registers.f &= ~SUBTRACT_FLAG;	// CLEAR
}

inline void Z80::adc(uint8_t value)
{
	const uint8_t carry = (registers.f & CARRY_FLAG) ? 1 : 0; // TODO clear up flags and use bitfields
	add(value + carry);
}

void Z80::ADD_A_B(void)
{
	add(registers.b);
}

void Z80::ADD_A_C(void)
{
	add(registers.c);
}

void Z80::ADD_A_D(void)
{
	add(registers.d);
}

void Z80::ADD_A_E(void)
{
	add(registers.e);
}

void Z80::ADD_A_H(void)
{
	add(registers.h);
}

void Z80::ADD_A_L(void)
{
	add(registers.l);
}

void Z80::ADD_A_HLa(void)
{
	add(memory.read_8(registers.hl));
}

void Z80::ADD_A_A(void)
{
	add(registers.a);
}

void Z80::ADC_A_B(void)
{
	adc(registers.b);
}

void Z80::ADC_A_C(void)
{
	adc(registers.c);
}

void Z80::ADC_A_D(void)
{
	adc(registers.d);
}


void Z80::ADC_A_E(void)
{
	adc(registers.e);
}


void Z80::ADC_A_H(void)
{
	adc(registers.h);
}


void Z80::ADC_A_L(void)
{
	adc(registers.l);
}

void Z80::ADC_A_HLa(void)
{
	adc(memory.read_8(registers.hl));
}

void Z80::ADC_A_A(void)
{
	adc(registers.a);
}

void Z80::ADD_A_d8(uint8_t value)
{
	add(value);
}

void Z80::ADC_A_d8(uint8_t value)
{
	adc(value);
}

inline void Z80::sub(uint8_t value)
{
	cp(value);
	registers.a -= value;
}

void Z80::SUB_B(void)
{
	sub(registers.b);
}

void Z80::SUB_C(void)
{
	sub(registers.c);
}

void Z80::SUB_D(void)
{
	sub(registers.d);
}

void Z80::SUB_E(void)
{
	sub(registers.e);
}

void Z80::SUB_H(void)
{
	sub(registers.h);
}

void Z80::SUB_L(void)
{
	sub(registers.l);
}

void Z80::SUB_HLa(void)
{
	sub(memory.read_8(registers.hl));
}

void Z80::SUB_A(void)
{
	sub(registers.a);
}

void Z80::SUB_d8(uint8_t value)
{
	sub(value);
}

void Z80::CP_B(void)
{
	cp(registers.b);
}

void Z80::CP_C(void)
{
	cp(registers.c);
}

void Z80::CP_D(void)
{
	cp(registers.d);
}

void Z80::CP_E(void)
{
	cp(registers.e);
}

void Z80::CP_H(void)
{
	cp(registers.h);
}

void Z80::CP_L(void)
{
	cp(registers.l);
}

void Z80::CP_HLa(void)
{
	cp(memory.read_8(registers.hl));
}

void Z80::CP_A(void)
{
	cp(registers.a);
}

void Z80::CP_d8(uint8_t value)
{
	cp(value);
}

void Z80::DI(void)
{
	memory.interruptMaster = false;
}

void Z80::EI(void)
{
	memory.interruptMaster = true;
}

void Z80::RST_0x0000(void)
{
	push_16(registers.pc);
	registers.pc = 0x0000;
}

void Z80::RST_0x0008(void)
{
	push_16(registers.pc);
	registers.pc = 0x0008;
}

void Z80::RST_0x0010(void)
{
	push_16(registers.pc);
	registers.pc = 0x0010;
}

void Z80::RST_0x0018(void)
{
	push_16(registers.pc);
	registers.pc = 0x0018;
}

void Z80::RST_0x0020(void)
{
	push_16(registers.pc);
	registers.pc = 0x0020;
}

void Z80::RST_0x0028(void)
{
	push_16(registers.pc);
	registers.pc = 0x0028;
}

void Z80::RST_0x0030(void)
{
	push_16(registers.pc);
	registers.pc = 0x0030;
}

void Z80::RST_0x0038(void)
{
	push_16(registers.pc);
	registers.pc = 0x0038;
}

void Z80::CPL(void)
{
	registers.a = ~registers.a;
	registers.f |= (SUBTRACT_FLAG | HALF_CARRY_FLAG);
}

inline void Z80::add_16(uint16_t& accumulator, uint16_t value)
{
	if (((accumulator + value) & 0xFFFF) < accumulator)
		registers.f |= CARRY_FLAG;	// SET
	else
		registers.f &= ~CARRY_FLAG;	// CLEAR

	if (((accumulator + value) & 0x0F) < (accumulator & 0x0F))
		registers.f |= HALF_CARRY_FLAG;	// SET
	else
		registers.f &= ~HALF_CARRY_FLAG;	// CLEAR

	accumulator += value;

	registers.f &= ~SUBTRACT_FLAG;	// CLEAR
}

void Z80::ADD_HL_BC(void) { add_16(registers.hl, registers.bc); }
void Z80::ADD_HL_DE(void) { add_16(registers.hl, registers.de); }
void Z80::ADD_HL_HL(void) { add_16(registers.hl, registers.hl); }
void Z80::ADD_HL_SP(void) { add_16(registers.hl, registers.sp); }

// from: https://forums.nesdev.com/viewtopic.php?t=15944
void Z80::DAA(void)
{
	// note: assumes a is a uint8_t and wraps from 0xff to 0
	if (!(registers.f & SUBTRACT_FLAG)) {  // after an addition, adjust if (half-)carry occurred or if result is out of bounds
		if ((registers.f & CARRY_FLAG) || registers.a > 0x99)
		{
			registers.a += 0x60;
			registers.f |= CARRY_FLAG;	// SET
		}

		if ((registers.f & HALF_CARRY_FLAG) || (registers.a & 0x0f) > 0x09) {
			registers.a += 0x6;
		}
	}
	else {  // after a subtraction, only adjust if (half-)carry occurred
		if ((registers.f & CARRY_FLAG)) { registers.a -= 0x60; }
		if ((registers.f & HALF_CARRY_FLAG)) { registers.a -= 0x6; }
	}
	// these flags are always updated
	if (registers.a == 0) // the usual z flag
		registers.f |= ZERO_FLAG;	// SET

	registers.f &= ~HALF_CARRY_FLAG;	// CLEAR // h flag is always cleared
}


// TODO CLEAN UP INSTRUCTION TIMING AND USE T CYCLES!!!
// instruction names from: https://cturt.github.io/cinoop.html
Z80::Z80() : instructions({ {
		{ "NOP",						4,	1,	{.op0 = &Z80::NOP				}},	// 0x00
		{ "LD BC, 0x%04X",				12,	3,	{.op2 = &Z80::LD_BC_d16			}},	// 0x01
		{ "LD (BC), A",					8,	1,	{.op0 = &Z80::LD_BCa_A			}},	// 0x02
		{ "INC BC",						8,	1,	{.op0 = &Z80::INC_BC			}},	// 0x03
		{ "INC B",						4,	1,	{.op0 = &Z80::INC_B				}},	// 0x04
		{ "DEC B",						4,	1,	{.op0 = &Z80::DEC_B				}},	// 0x05
		{ "LD B, 0x%02X",				8,	2,	{.op1 = &Z80::LD_B_d8			}},	// 0x06
		{ "RLCA",						4,	1,	{.op0 = &Z80::RLCA				}},	// 0x07
		{ "LD (0x%04X), SP",			10,	3,	{.op2 = &Z80::unimplemented_op2 }},	// 0x08
		{ "ADD HL, BC",					8,	1,	{.op0 = &Z80::ADD_HL_BC			}},	// 0x09
		{ "LD A, (BC)",					8,	1,	{.op0 = &Z80::LD_A_BCa			}},	// 0x0a
		{ "DEC BC",						8,	1,	{.op0 = &Z80::DEC_BC			}},	// 0x0b
		{ "INC C",						4,	1,	{.op0 = &Z80::INC_C				}},	// 0x0c
		{ "DEC C",						4,	1,	{.op0 = &Z80::DEC_C				}},	// 0x0d
		{ "LD C, 0x%02X",				8,	2,	{.op1 = &Z80::LD_C_d8			}},	// 0x0e
		{ "RRCA",						4,	1,	{.op0 = &Z80::RRCA				}},	// 0x0f
		{ "STOP",						2,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0x10
		{ "LD DE, 0x%04X",				12,	3,	{.op2 = &Z80::LD_DE_d16			}},	// 0x11
		{ "LD (DE), A",					8,	1,	{.op0 = &Z80::LD_DEa_A			}},	// 0x12
		{ "INC DE",						8,	1,	{.op0 = &Z80::INC_DE			}},	// 0x13
		{ "INC D",						4,	1,	{.op0 = &Z80::INC_D				}},	// 0x14
		{ "DEC D",						4,	1,	{.op0 = &Z80::DEC_D				}},	// 0x15
		{ "LD D, 0x%02X",				8,	2,	{.op1 = &Z80::LD_D_d8			}},	// 0x16
		{ "RLA",						4,	1,	{.op0 = &Z80::RLA				}},	// 0x17
		{ "JR 0x%02X",					0,	2,	{.op1 = &Z80::JR_r8				}},	// 0x18
		{ "ADD HL, DE",					8,	1,	{.op0 = &Z80::ADD_HL_DE			}},	// 0x19
		{ "LD A, (DE)",					8,	1,	{.op0 = &Z80::LD_A_DEa			}},	// 0x1a
		{ "DEC DE",						8,	1,	{.op0 = &Z80::DEC_DE			}},	// 0x1b
		{ "INC E",						4,	1,	{.op0 = &Z80::INC_E				}},	// 0x1c
		{ "DEC E",						4,	1,	{.op0 = &Z80::DEC_E				}},	// 0x1d
		{ "LD E, 0x%02X",				8,	2,	{.op1 = &Z80::LD_E_d8			}},	// 0x1e
		{ "RRA",						4,	1,	{.op0 = &Z80::RRA				}},	// 0x1f
		{ "JR NZ, 0x%02X",				0,	2,	{.op1 = &Z80::JR_NZ				}},	// 0x20
		{ "LD HL, 0x%04X",				12,	3,	{.op2 = &Z80::LD_HL_d16			}},	// 0x21
		{ "LDI (HL), A",				8,	1,	{.op0 = &Z80::LDI_HLa_A			}},	// 0x22
		{ "INC HL",						8,	1,	{.op0 = &Z80::INC_HL			}},	// 0x23
		{ "INC H",						4,	1,	{.op0 = &Z80::INC_H				}},	// 0x24
		{ "DEC H",						4,	1,	{.op0 = &Z80::DEC_H				}},	// 0x25
		{ "LD H, 0x%02X",				8,	2,	{.op1 = &Z80::LD_H_d8			}},	// 0x26
		{ "DAA",						4,	1,	{.op0 = &Z80::DAA				}},	// 0x27
		{ "JR Z, 0x%02X",				0,	2,	{.op1 = &Z80::JR_Z				}},	// 0x28
		{ "ADD HL, HL",					8,	1,	{.op0 = &Z80::ADD_HL_HL			}},	// 0x29
		{ "LDI A, (HL)",				8,	1,	{.op0 = &Z80::LDI_A_HLa			}},	// 0x2a
		{ "DEC HL",						8,	1,	{.op0 = &Z80::DEC_HL			}},	// 0x2b
		{ "INC L",						4,	1,	{.op0 = &Z80::INC_L				}},	// 0x2c
		{ "DEC L",						4,	1,	{.op0 = &Z80::DEC_L				}},	// 0x2d
		{ "LD L, 0x%02X",				8,	2,	{.op1 = &Z80::LD_L_d8			}},	// 0x2e
		{ "CPL",						4,	1,	{.op0 = &Z80::CPL				}},	// 0x2f
		{ "JR NC, 0x%02X",				0,	2,	{.op1 = &Z80::JR_NC				}},	// 0x30
		{ "LD SP, 0x%04X",				12,	3,	{.op2 = &Z80::LD_SP_d16			}},	// 0x31
		{ "LDD (HL), A",				8,	1,	{.op0 = &Z80::LDD_HLa_A			}},	// 0x32
		{ "INC SP",						8,	1,	{.op0 = &Z80::INC_SP			}},	// 0x33
		{ "INC (HL)",					12,	1,	{.op0 = &Z80::INC_HLa			}},	// 0x34
		{ "DEC (HL)",					12,	1,	{.op0 = &Z80::DEC_HLa			}},	// 0x35
		{ "LD (HL), 0x%02X",			12,	2,	{.op1 = &Z80::LD_HLa_d8			}},	// 0x36
		{ "SCF",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x37
		{ "JR C, 0x%02X",				0,	2,	{.op1 = &Z80::JR_C				}},	// 0x38
		{ "ADD HL, SP",					8,	1,	{.op0 = &Z80::ADD_HL_SP			}},	// 0x39
		{ "LDD A, (HL)",				8,	1,	{.op0 = &Z80::LDD_A_HLa			}},	// 0x3a
		{ "DEC SP",						8,	1,	{.op0 = &Z80::DEC_SP			}},	// 0x3b
		{ "INC A",						4,	1,	{.op0 = &Z80::INC_A				}},	// 0x3c
		{ "DEC A",						4,	1,	{.op0 = &Z80::DEC_A				}},	// 0x3d
		{ "LD A, 0x%02X",				8,	2,	{.op1 = &Z80::LD_A_d8			}},	// 0x3e
		{ "CCF",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x3f
		{ "LD B, B",					4,	1,	{.op0 = &Z80::NOP				}},	// 0x40
		{ "LD B, C",					4,	1,	{.op0 = &Z80::LD_B_C			}},	// 0x41
		{ "LD B, D",					4,	1,	{.op0 = &Z80::LD_B_D			}},	// 0x42
		{ "LD B, E",					4,	1,	{.op0 = &Z80::LD_B_E			}},	// 0x43
		{ "LD B, H",					4,	1,	{.op0 = &Z80::LD_B_H			}},	// 0x44
		{ "LD B, L",					4,	1,	{.op0 = &Z80::LD_B_L			}},	// 0x45
		{ "LD B, (HL)",					8,	1,	{.op0 = &Z80::LD_B_HLa			}},	// 0x46
		{ "LD B, A",					4,	1,	{.op0 = &Z80::LD_B_A			}},	// 0x47
		{ "LD C, B",					4,	1,	{.op0 = &Z80::LD_C_B			}},	// 0x48
		{ "LD C, C",					4,	1,	{.op0 = &Z80::NOP				}},	// 0x49
		{ "LD C, D",					4,	1,	{.op0 = &Z80::LD_C_D			}},	// 0x4a
		{ "LD C, E",					4,	1,	{.op0 = &Z80::LD_C_E			}},	// 0x4b
		{ "LD C, H",					4,	1,	{.op0 = &Z80::LD_C_H			}},	// 0x4c
		{ "LD C, L",					4,	1,	{.op0 = &Z80::LD_C_L			}},	// 0x4d
		{ "LD C, (HL)",					8,	1,	{.op0 = &Z80::LD_C_HLa			}},	// 0x4e
		{ "LD C, A",					4,	1,	{.op0 = &Z80::LD_C_A			}},	// 0x4f
		{ "LD D, B",					4,	1,	{.op0 = &Z80::LD_D_B			}},	// 0x50
		{ "LD D, C",					4,	1,	{.op0 = &Z80::LD_D_C			}},	// 0x51
		{ "LD D, D",					4,	1,	{.op0 = &Z80::NOP				}},	// 0x52
		{ "LD D, E",					4,	1,	{.op0 = &Z80::LD_D_E			}},	// 0x53
		{ "LD D, H",					4,	1,	{.op0 = &Z80::LD_D_H			}},	// 0x54
		{ "LD D, L",					4,	1,	{.op0 = &Z80::LD_D_L			}},	// 0x55
		{ "LD D, (HL)",					8,	1,	{.op0 = &Z80::LD_D_HLa			}},	// 0x56
		{ "LD D, A",					4,	1,	{.op0 = &Z80::LD_D_A			}},	// 0x57
		{ "LD E, B",					4,	1,	{.op0 = &Z80::LD_E_B			}},	// 0x58
		{ "LD E, C",					4,	1,	{.op0 = &Z80::LD_E_C			}},	// 0x59
		{ "LD E, D",					4,	1,	{.op0 = &Z80::LD_E_D			}},	// 0x5a
		{ "LD E, E",					4,	1,	{.op0 = &Z80::NOP				}},	// 0x5b
		{ "LD E, H",					4,	1,	{.op0 = &Z80::LD_E_H			}},	// 0x5c
		{ "LD E, L",					4,	1,	{.op0 = &Z80::LD_E_L			}},	// 0x5d
		{ "LD E, (HL)",					8,	1,	{.op0 = &Z80::LD_E_HLa			}},	// 0x5e
		{ "LD E, A",					4,	1,	{.op0 = &Z80::LD_E_A			}},	// 0x5f
		{ "LD H, B",					4,	1,	{.op0 = &Z80::LD_H_B			}},	// 0x60
		{ "LD H, C",					4,	1,	{.op0 = &Z80::LD_H_C			}},	// 0x61
		{ "LD H, D",					4,	1,	{.op0 = &Z80::LD_H_D			}},	// 0x62
		{ "LD H, E",					4,	1,	{.op0 = &Z80::LD_H_E			}},	// 0x63
		{ "LD H, H",					4,	1,	{.op0 = &Z80::NOP				}},	// 0x64
		{ "LD H, L",					4,	1,	{.op0 = &Z80::LD_H_L			}},	// 0x65
		{ "LD H, (HL)",					8,	1,	{.op0 = &Z80::LD_H_HLa			}},	// 0x66
		{ "LD H, A",					4,	1,	{.op0 = &Z80::LD_H_A			}},	// 0x67
		{ "LD L, B",					4,	1,	{.op0 = &Z80::LD_L_B			}},	// 0x68
		{ "LD L, C",					4,	1,	{.op0 = &Z80::LD_L_C			}},	// 0x69
		{ "LD L, D",					4,	1,	{.op0 = &Z80::LD_L_D			}},	// 0x6a
		{ "LD L, E",					4,	1,	{.op0 = &Z80::LD_L_E			}},	// 0x6b
		{ "LD L, H",					4,	1,	{.op0 = &Z80::LD_L_H			}},	// 0x6c
		{ "LD L, L",					4,	1,	{.op0 = &Z80::NOP				}},	// 0x6d
		{ "LD L, (HL)",					8,	1,	{.op0 = &Z80::LD_L_HLa			}},	// 0x6e
		{ "LD L, A",					4,	1,	{.op0 = &Z80::LD_L_A			}},	// 0x6f
		{ "LD (HL), B",					8,	1,	{.op0 = &Z80::LD_HLa_B			}},	// 0x70
		{ "LD (HL), C",					8,	1,	{.op0 = &Z80::LD_HLa_C			}},	// 0x71
		{ "LD (HL), D",					8,	1,	{.op0 = &Z80::LD_HLa_D			}},	// 0x72
		{ "LD (HL), E",					8,	1,	{.op0 = &Z80::LD_HLa_E			}},	// 0x73
		{ "LD (HL), H",					8,	1,	{.op0 = &Z80::LD_HLa_H			}},	// 0x74
		{ "LD (HL), L",					8,	1,	{.op0 = &Z80::LD_HLa_L			}},	// 0x75
		{ "HALT",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x76
		{ "LD (HL), A",					8,	1,	{.op0 = &Z80::LD_HLa_A			}},	// 0x77
		{ "LD A, B",					4,	1,	{.op0 = &Z80::LD_A_B			}},	// 0x78
		{ "LD A, C",					4,	1,	{.op0 = &Z80::LD_A_C			}},	// 0x79
		{ "LD A, D",					4,	1,	{.op0 = &Z80::LD_A_D			}},	// 0x7a
		{ "LD A, E",					4,	1,	{.op0 = &Z80::LD_A_E			}},	// 0x7b
		{ "LD A, H",					4,	1,	{.op0 = &Z80::LD_A_H			}},	// 0x7c
		{ "LD A, L",					4,	1,	{.op0 = &Z80::LD_A_L			}},	// 0x7d
		{ "LD A, (HL)",					8,	1,	{.op0 = &Z80::LD_A_HLa			}},	// 0x7e
		{ "LD A, A",					4,	1,	{.op0 = &Z80::NOP				}},	// 0x7f
		{ "ADD A, B",					4,	1,	{.op0 = &Z80::ADD_A_B			}},	// 0x80
		{ "ADD A, C",					4,	1,	{.op0 = &Z80::ADD_A_C			}},	// 0x81
		{ "ADD A, D",					4,	1,	{.op0 = &Z80::ADD_A_D			}},	// 0x82
		{ "ADD A, E",					4,	1,	{.op0 = &Z80::ADD_A_E			}},	// 0x83
		{ "ADD A, H",					4,	1,	{.op0 = &Z80::ADD_A_H			}},	// 0x84
		{ "ADD A, L",					4,	1,	{.op0 = &Z80::ADD_A_L			}},	// 0x85
		{ "ADD A, (HL)",				8,	1,	{.op0 = &Z80::ADD_A_HLa			}},	// 0x86
		{ "ADD A",						4,	1,	{.op0 = &Z80::ADD_A_A			}},	// 0x87
		{ "ADC B",						4,	1,	{.op0 = &Z80::ADC_A_B			}},	// 0x88
		{ "ADC C",						4,	1,	{.op0 = &Z80::ADC_A_C			}},	// 0x89
		{ "ADC D",						4,	1,	{.op0 = &Z80::ADC_A_D			}},	// 0x8a
		{ "ADC E",						4,	1,	{.op0 = &Z80::ADC_A_E			}},	// 0x8b
		{ "ADC H",						4,	1,	{.op0 = &Z80::ADC_A_H			}},	// 0x8c
		{ "ADC L",						4,	1,	{.op0 = &Z80::ADC_A_L			}},	// 0x8d
		{ "ADC (HL)",					8,	1,	{.op0 = &Z80::ADC_A_HLa			}},	// 0x8e
		{ "ADC A",						4,	1,	{.op0 = &Z80::ADC_A_A			}},	// 0x8f
		{ "SUB B",						4,	1,	{.op0 = &Z80::SUB_B				}},	// 0x90
		{ "SUB C",						4,	1,	{.op0 = &Z80::SUB_C				}},	// 0x91
		{ "SUB D",						4,	1,	{.op0 = &Z80::SUB_D				}},	// 0x92
		{ "SUB E",						4,	1,	{.op0 = &Z80::SUB_E				}},	// 0x93
		{ "SUB H",						4,	1,	{.op0 = &Z80::SUB_H				}},	// 0x94
		{ "SUB L",						4,	1,	{.op0 = &Z80::SUB_L				}},	// 0x95
		{ "SUB (HL)",					8,	1,	{.op0 = &Z80::SUB_HLa			}},	// 0x96
		{ "SUB A",						4,	1,	{.op0 = &Z80::SUB_A				}},	// 0x97
		{ "SBC B",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x98
		{ "SBC C",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x99
		{ "SBC D",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x9a
		{ "SBC E",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x9b
		{ "SBC H",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x9c
		{ "SBC L",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x9d
		{ "SBC (HL)",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x9e
		{ "SBC A",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x9f
		{ "AND B",						4,	1,	{.op0 = &Z80::AND_B				}},	// 0xa0
		{ "AND C",						4,	1,	{.op0 = &Z80::AND_C				}},	// 0xa1
		{ "AND D",						4,	1,	{.op0 = &Z80::AND_D				}},	// 0xa2
		{ "AND E",						4,	1,	{.op0 = &Z80::AND_E				}},	// 0xa3
		{ "AND H",						4,	1,	{.op0 = &Z80::AND_H				}},	// 0xa4
		{ "AND L",						4,	1,	{.op0 = &Z80::AND_L				}},	// 0xa5
		{ "AND (HL)",					8,	1,	{.op0 = &Z80::AND_HLa			}},	// 0xa6
		{ "AND A",						4,	1,	{.op0 = &Z80::AND_A				}},	// 0xa7
		{ "XOR B",						4,	1,	{.op0 = &Z80::XOR_B				}},	// 0xa8
		{ "XOR C",						4,	1,	{.op0 = &Z80::XOR_C				}},	// 0xa9
		{ "XOR D",						4,	1,	{.op0 = &Z80::XOR_D				}},	// 0xaa
		{ "XOR E",						4,	1,	{.op0 = &Z80::XOR_E				}},	// 0xab
		{ "XOR H",						4,	1,	{.op0 = &Z80::XOR_H				}},	// 0xac
		{ "XOR L",						4,	1,	{.op0 = &Z80::XOR_L				}},	// 0xad
		{ "XOR (HL)",					8,	1,	{.op0 = &Z80::XOR_HLa			}},	// 0xae
		{ "XOR A",						4,	1,	{.op0 = &Z80::XOR_A				}},	// 0xaf
		{ "OR B",						4,	1,	{.op0 = &Z80::OR_B				}},	// 0xb0
		{ "OR C",						4,	1,	{.op0 = &Z80::OR_C				}},	// 0xb1
		{ "OR D",						4,	1,	{.op0 = &Z80::OR_D				}},	// 0xb2
		{ "OR E",						4,	1,	{.op0 = &Z80::OR_E				}},	// 0xb3
		{ "OR H",						4,	1,	{.op0 = &Z80::OR_H				}},	// 0xb4
		{ "OR L",						4,	1,	{.op0 = &Z80::OR_L				}},	// 0xb5
		{ "OR (HL)",					8,	1,	{.op0 = &Z80::OR_HLa			}},	// 0xb6
		{ "OR A",						4,	1,	{.op0 = &Z80::OR_A				}},	// 0xb7
		{ "CP B",						4,	1,	{.op0 = &Z80::CP_B				}},	// 0xb8
		{ "CP C",						4,	1,	{.op0 = &Z80::CP_C				}},	// 0xb9
		{ "CP D",						4,	1,	{.op0 = &Z80::CP_D				}},	// 0xba
		{ "CP E",						4,	1,	{.op0 = &Z80::CP_E				}},	// 0xbb
		{ "CP H",						4,	1,	{.op0 = &Z80::CP_H				}},	// 0xbc
		{ "CP L",						4,	1,	{.op0 = &Z80::CP_L				}},	// 0xbd
		{ "CP (HL)",					8,	1,	{.op0 = &Z80::CP_HLa			}},	// 0xbe
		{ "CP A",						4,	1,	{.op0 = &Z80::CP_A				}},	// 0xbf
		{ "RET NZ",						0,	1,	{.op0 = &Z80::RET_NZ			}},	// 0xc0
		{ "POP BC",						12,	1,	{.op0 = &Z80::POP_BC			}},	// 0xc1
		{ "JP NZ, 0x%04X",				0,	3,	{.op2 = &Z80::JP_NZ				}},	// 0xc2
		{ "JP 0x%04X",					0,	3,	{.op2 = &Z80::JP_16a			}},	// 0xc3
		{ "CALL NZ, 0x%04X",			0,	3,	{.op2 = &Z80::CALL_NZ			}},	// 0xc4
		{ "PUSH BC",					16,	1,	{.op0 = &Z80::PUSH_BC			}},	// 0xc5
		{ "ADD A, 0x%02X",				8,	2,	{.op1 = &Z80::ADD_A_d8			}},	// 0xc6
		{ "RST 0x00",					16,	1,	{.op0 = &Z80::RST_0x0000		}},	// 0xc7
		{ "RET Z",						0,	1,	{.op0 = &Z80::RET_Z				}},	// 0xc8
		{ "RET",						16,	1,	{.op0 = &Z80::RET				}},	// 0xc9
		{ "JP Z, 0x%04X",				0,	3,	{.op2 = &Z80::JP_Z				}},	// 0xca
		{ "CB %02X",					0,	2,	{.op1 = &Z80::PREFIX			}},	// 0xcb
		{ "CALL Z, 0x%04X",				0,	3,	{.op2 = &Z80::CALL_Z			}},	// 0xcc
		{ "CALL 0x%04X",				24,	3,	{.op2 = &Z80::CALL				}},	// 0xcd
		{ "ADC 0x%02X",					8,	2,	{.op1 = &Z80::ADC_A_d8			}},	// 0xce
		{ "RST 0x08",					16,	1,	{.op0 = &Z80::RST_0x0008		}},	// 0xcf
		{ "RET NC",						0,	1,	{.op0 = &Z80::RET_NC			}},	// 0xd0
		{ "POP DE",						12,	1,	{.op0 = &Z80::POP_DE			}},	// 0xd1
		{ "JP NC, 0x%04X",				0,	3,	{.op2 = &Z80::JP_NC				}},	// 0xd2
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xd3
		{ "CALL NC, 0x%04X",			0,	3,	{.op2 = &Z80::CALL_NC			}},	// 0xd4
		{ "PUSH DE",					16,	1,	{.op0 = &Z80::PUSH_DE			}},	// 0xd5
		{ "SUB 0x%02X",					8,	2,	{.op1 = &Z80::SUB_d8			}},	// 0xd6
		{ "RST 0x10",					16,	1,	{.op0 = &Z80::RST_0x0010		}},	// 0xd7
		{ "RET C",						0,	1,	{.op0 = &Z80::RET_C				}},	// 0xd8
		{ "RETI",						0,	1,	{.op0 = &Z80::RETI				}},	// 0xd9
		{ "JP C, 0x%04X",				0,	3,	{.op2 = &Z80::JP_C				}},	// 0xda
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xdb
		{ "CALL C, 0x%04X",				0,	3,	{.op2 = &Z80::CALL_C			}},	// 0xdc
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xdd
		{ "SBC 0x%02X",					4,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0xde
		{ "RST 0x18",					16,	1,	{.op0 = &Z80::RST_0x0018		}},	// 0xdf
		{ "LD (0xFF00 + 0x%02X), A",	12,	2,	{.op1 = &Z80::LD_FF_a8_A		}},	// 0xe0
		{ "POP HL",						12,	1,	{.op0 = &Z80::POP_HL			}},	// 0xe1
		{ "LD (0xFF00 + C), A",			8,	1,	{.op0 = &Z80::LD_FF_Ca_A		}},	// 0xe2
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xe3
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xe4
		{ "PUSH HL",					16,	1,	{.op0 = &Z80::PUSH_HL			}},	// 0xe5
		{ "AND 0x%02X",					8,	2,	{.op1 = &Z80::AND_d8			}},	// 0xe6
		{ "RST 0x20",					16,	1,	{.op0 = &Z80::RST_0x0020		}},	// 0xe7
		{ "ADD SP,0x%02X",				8,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0xe8
		{ "JP HL",						4,	1,	{.op0 = &Z80::JP_HL				}},	// 0xe9
		{ "LD (0x%04X), A",				16,	3,	{.op2 = &Z80::LD_a16_A			}},	// 0xea
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xeb
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xec
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xed
		{ "XOR 0x%02X",					8,	2,	{.op1 = &Z80::XOR_d8			}},	// 0xee
		{ "RST 0x28",					16,	1,	{.op0 = &Z80::RST_0x0028		}},	// 0xef
		{ "LD A, (0xFF00 + 0x%02X)",	12,	2,	{.op1 = &Z80::LD_FF_A_a8		}},	// 0xf0
		{ "POP AF",						12,	1,	{.op0 = &Z80::POP_AF			}},	// 0xf1
		{ "LD A, (0xFF00 + C)",			8,	1,	{.op0 = &Z80::LD_FF_A_Ca		}},	// 0xf2
		{ "DI",							4,	1,	{.op0 = &Z80::DI				}},	// 0xf3
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xf4
		{ "PUSH AF",					16,	1,	{.op0 = &Z80::PUSH_AF			}},	// 0xf5
		{ "OR 0x%02X",					8,	2,	{.op1 = &Z80::OR_d8				}},	// 0xf6
		{ "RST 0x30",					16,	1,	{.op0 = &Z80::RST_0x0030		}},	// 0xf7
		{ "LD HL, SP+0x%02X",			6,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0xf8
		{ "LD SP, HL",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xf9
		{ "LD A, (0x%04X)",				16,	3,	{.op2 = &Z80::LD_A_a16			}},	// 0xfa
		{ "EI",							4,	1,	{.op0 = &Z80::EI				}},	// 0xfb
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xfc
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xfd
		{ "CP 0x%02X",					8,	2,	{.op1 = &Z80::CP_d8				}},	// 0xfe
		{ "RST 0x38",					16,	1,	{.op0 = &Z80::RST_0x0038		}}	// 0xff
	} }),
	prefixInstructions({ {
		{ "RLC B",		8,	&Z80::unimplemented_op0 },	// 0x00
		{ "RLC C",		8,	&Z80::unimplemented_op0 },	// 0x01
		{ "RLC D",		8,	&Z80::unimplemented_op0 },	// 0x02
		{ "RLC E",		8,	&Z80::unimplemented_op0 },	// 0x03
		{ "RLC H",		8,	&Z80::unimplemented_op0 },	// 0x04
		{ "RLC L",		8,	&Z80::unimplemented_op0 },	// 0x05
		{ "RLC (HL)",	16,	&Z80::unimplemented_op0 },	// 0x06
		{ "RLC A",		8,	&Z80::unimplemented_op0 },	// 0x07
		{ "RRC B",		8,	&Z80::unimplemented_op0 },	// 0x08
		{ "RRC C",		8,	&Z80::unimplemented_op0 },	// 0x09
		{ "RRC D",		8,	&Z80::unimplemented_op0 },	// 0x0a
		{ "RRC E",		8,	&Z80::unimplemented_op0 },	// 0x0b
		{ "RRC H",		8,	&Z80::unimplemented_op0 },	// 0x0c
		{ "RRC L",		8,	&Z80::unimplemented_op0 },	// 0x0d
		{ "RRC (HL)",	16,	&Z80::unimplemented_op0 },	// 0x0e
		{ "RRC A",		8,	&Z80::unimplemented_op0 },	// 0x0f
		{ "RL B",		8,	&Z80::RL_B				},	// 0x10
		{ "RL C",		8,	&Z80::RL_C				},	// 0x11
		{ "RL D",		8,	&Z80::RL_D				},	// 0x12
		{ "RL E",		8,	&Z80::RL_E				},	// 0x13
		{ "RL H",		8,	&Z80::RL_H				},	// 0x14
		{ "RL L",		8,	&Z80::RL_L				},	// 0x15
		{ "RL (HL)",	16,	&Z80::RL_HLa			},	// 0x16
		{ "RL A",		8,	&Z80::RL_A				},	// 0x17
		{ "RR B",		8,	&Z80::unimplemented_op0 },	// 0x18
		{ "RR C",		8,	&Z80::unimplemented_op0 },	// 0x19
		{ "RR D",		8,	&Z80::unimplemented_op0 },	// 0x1a
		{ "RR E",		8,	&Z80::unimplemented_op0 },	// 0x1b
		{ "RR H",		8,	&Z80::unimplemented_op0 },	// 0x1c
		{ "RR L",		8,	&Z80::unimplemented_op0 },	// 0x1d
		{ "RR (HL)",	16,	&Z80::unimplemented_op0 },	// 0x1e
		{ "RR A",		8,	&Z80::unimplemented_op0 },	// 0x1f
		{ "SLA B",		8,	&Z80::SLA_B				},	// 0x20
		{ "SLA C",		8,	&Z80::SLA_C				},	// 0x21
		{ "SLA D",		8,	&Z80::SLA_D				},	// 0x22
		{ "SLA E",		8,	&Z80::SLA_E				},	// 0x23
		{ "SLA H",		8,	&Z80::SLA_H				},	// 0x24
		{ "SLA L",		8,	&Z80::SLA_L				},	// 0x25
		{ "SLA (HL)",	16,	&Z80::SLA_HLa			},	// 0x26
		{ "SLA A",		8,	&Z80::SLA_A				},	// 0x27
		{ "SRA B",		8,	&Z80::unimplemented_op0 },	// 0x28
		{ "SRA C",		8,	&Z80::unimplemented_op0 },	// 0x29
		{ "SRA D",		8,	&Z80::unimplemented_op0 },	// 0x2a
		{ "SRA E",		8,	&Z80::unimplemented_op0 },	// 0x2b
		{ "SRA H",		8,	&Z80::unimplemented_op0 },	// 0x2c
		{ "SRA L",		8,	&Z80::unimplemented_op0 },	// 0x2d
		{ "SRA (HL)",	16,	&Z80::unimplemented_op0 },	// 0x2e
		{ "SRA A",		8,	&Z80::unimplemented_op0 },	// 0x2f
		{ "SWAP B",		8,	&Z80::SWAP_B			},	// 0x30
		{ "SWAP C",		8,	&Z80::SWAP_C			},	// 0x31
		{ "SWAP D",		8,	&Z80::SWAP_D			},	// 0x32
		{ "SWAP E",		8,	&Z80::SWAP_E			},	// 0x33
		{ "SWAP H",		8,	&Z80::SWAP_H			},	// 0x34
		{ "SWAP L",		8,	&Z80::SWAP_L			},	// 0x35
		{ "SWAP (HL)",	16,	&Z80::SWAP_HLa			},	// 0x36
		{ "SWAP A",		8,	&Z80::SWAP_A			},	// 0x37
		{ "SRL B",		8,	&Z80::SRL_B				},	// 0x38
		{ "SRL C",		8,	&Z80::SRL_C				},	// 0x39
		{ "SRL D",		8,	&Z80::SRL_D				},	// 0x3a
		{ "SRL E",		8,	&Z80::SRL_E				},	// 0x3b
		{ "SRL H",		8,	&Z80::SRL_H				},	// 0x3c
		{ "SRL L",		8,	&Z80::SRL_L				},	// 0x3d
		{ "SRL (HL)",	16,	&Z80::SRL_HLa			},	// 0x3e
		{ "SRL A",		8,	&Z80::SRL_A				},	// 0x3f
		{ "BIT0 B",		8,	&Z80::BIT_0_B			},	// 0x40
		{ "BIT0 C",		8,	&Z80::BIT_0_C			},	// 0x41
		{ "BIT0 D",		8,	&Z80::BIT_0_D			},	// 0x42
		{ "BIT0 E",		8,	&Z80::BIT_0_E			},	// 0x43
		{ "BIT0 H",		8,	&Z80::BIT_0_H			},	// 0x44
		{ "BIT0 L",		8,	&Z80::BIT_0_L			},	// 0x45
		{ "BIT0 (HL)",	12,	&Z80::BIT_0_HLa			},	// 0x46
		{ "BIT0 A",		8,	&Z80::BIT_0_A			},	// 0x47
		{ "BIT1 B",		8,	&Z80::BIT_1_B			},	// 0x48
		{ "BIT1 C",		8,	&Z80::BIT_1_C			},	// 0x49
		{ "BIT1 D",		8,	&Z80::BIT_1_D			},	// 0x4a
		{ "BIT1 E",		8,	&Z80::BIT_1_E			},	// 0x4b
		{ "BIT1 H",		8,	&Z80::BIT_1_H			},	// 0x4c
		{ "BIT1 L",		8,	&Z80::BIT_1_L			},	// 0x4d
		{ "BIT1 (HL)",	12,	&Z80::BIT_1_HLa			},	// 0x4e
		{ "BIT1 A",		8,	&Z80::BIT_1_A			},	// 0x4f
		{ "BIT2 B",		8,	&Z80::BIT_2_B			},	// 0x50
		{ "BIT2 C",		8,	&Z80::BIT_2_C			},	// 0x51
		{ "BIT2 D",		8,	&Z80::BIT_2_D			},	// 0x52
		{ "BIT2 E",		8,	&Z80::BIT_2_E			},	// 0x53
		{ "BIT2 H",		8,	&Z80::BIT_2_H			},	// 0x54
		{ "BIT2 L",		8,	&Z80::BIT_2_L			},	// 0x55
		{ "BIT2 (HL)",	12,	&Z80::BIT_2_HLa			},	// 0x56
		{ "BIT2 A",		8,	&Z80::BIT_2_A			},	// 0x57
		{ "BIT3 B",		8,	&Z80::BIT_3_B			},	// 0x58
		{ "BIT3 C",		8,	&Z80::BIT_3_C			},	// 0x59
		{ "BIT3 D",		8,	&Z80::BIT_3_D			},	// 0x5a
		{ "BIT3 E",		8,	&Z80::BIT_3_E			},	// 0x5b
		{ "BIT3 H",		8,	&Z80::BIT_3_H			},	// 0x5c
		{ "BIT3 L",		8,	&Z80::BIT_3_L			},	// 0x5d
		{ "BIT3 (HL)",	12,	&Z80::BIT_3_HLa			},	// 0x5e
		{ "BIT3 A",		8,	&Z80::BIT_3_A			},	// 0x5f
		{ "BIT4 B",		8,	&Z80::BIT_4_B			},	// 0x60
		{ "BIT4 C",		8,	&Z80::BIT_4_C			},	// 0x61
		{ "BIT4 D",		8,	&Z80::BIT_4_D			},	// 0x62
		{ "BIT4 E",		8,	&Z80::BIT_4_E			},	// 0x63
		{ "BIT4 H",		8,	&Z80::BIT_4_H			},	// 0x64
		{ "BIT4 L",		8,	&Z80::BIT_4_L			},	// 0x65
		{ "BIT4 (HL)",	12,	&Z80::BIT_4_HLa			},	// 0x66
		{ "BIT4 A",		8,	&Z80::BIT_4_A			},	// 0x67
		{ "BIT5 B",		8,	&Z80::BIT_5_B			},	// 0x68
		{ "BIT5 C",		8,	&Z80::BIT_5_C			},	// 0x69
		{ "BIT5 D",		8,	&Z80::BIT_5_D			},	// 0x6a
		{ "BIT5 E",		8,	&Z80::BIT_5_E			},	// 0x6b
		{ "BIT5 H",		8,	&Z80::BIT_5_H			},	// 0x6c
		{ "BIT5 L",		8,	&Z80::BIT_5_L			},	// 0x6d
		{ "BIT5 (HL)",	12,	&Z80::BIT_5_HLa			},	// 0x6e
		{ "BIT5 A",		8,	&Z80::BIT_5_A			},	// 0x6f
		{ "BIT6 B",		8,	&Z80::BIT_6_B			},	// 0x70
		{ "BIT6 C",		8,	&Z80::BIT_6_C			},	// 0x71
		{ "BIT6 D",		8,	&Z80::BIT_6_D			},	// 0x72
		{ "BIT6 E",		8,	&Z80::BIT_6_E			},	// 0x73
		{ "BIT6 H",		8,	&Z80::BIT_6_H			},	// 0x74
		{ "BIT6 L",		8,	&Z80::BIT_6_L			},	// 0x75
		{ "BIT6 (HL)",	12,	&Z80::BIT_6_HLa			},	// 0x76
		{ "BIT6 A",		8,	&Z80::BIT_6_A			},	// 0x77
		{ "BIT7 B",		8,	&Z80::BIT_7_B			},	// 0x78
		{ "BIT7 C",		8,	&Z80::BIT_7_C			},	// 0x79
		{ "BIT7 D",		8,	&Z80::BIT_7_D			},	// 0x7a
		{ "BIT7 E",		8,	&Z80::BIT_7_E			},	// 0x7b
		{ "BIT7 H",		8,	&Z80::BIT_7_H			},	// 0x7c
		{ "BIT7 L",		8,	&Z80::BIT_7_L			},	// 0x7d
		{ "BIT7 (HL)",	12,	&Z80::BIT_7_HLa			},	// 0x7e
		{ "BIT7 A",		8,	&Z80::BIT_7_A			},	// 0x7f
		{ "RES0 B",		8,	&Z80::RES_0_B			},	// 0x80
		{ "RES0 C",		8,	&Z80::RES_0_C			},	// 0x81
		{ "RES0 D",		8,	&Z80::RES_0_D			},	// 0x82
		{ "RES0 E",		8,	&Z80::RES_0_E			},	// 0x83
		{ "RES0 H",		8,	&Z80::RES_0_H			},	// 0x84
		{ "RES0 L",		8,	&Z80::RES_0_L			},	// 0x85
		{ "RES0 (HL)",	16,	&Z80::RES_0_HLa			},	// 0x86
		{ "RES0 A",		8,	&Z80::RES_0_A			},	// 0x87
		{ "RES1 B",		8,	&Z80::RES_1_B			},	// 0x88
		{ "RES1 C",		8,	&Z80::RES_1_C			},	// 0x89
		{ "RES1 D",		8,	&Z80::RES_1_D			},	// 0x8a
		{ "RES1 E",		8,	&Z80::RES_1_E			},	// 0x8b
		{ "RES1 H",		8,	&Z80::RES_1_H			},	// 0x8c
		{ "RES1 L",		8,	&Z80::RES_1_L			},	// 0x8d
		{ "RES1 (HL)",	16,	&Z80::RES_1_HLa			},	// 0x8e
		{ "RES1 A",		8,	&Z80::RES_1_A			},	// 0x8f
		{ "RES2 B",		8,	&Z80::RES_2_B			},	// 0x90
		{ "RES2 C",		8,	&Z80::RES_2_C			},	// 0x91
		{ "RES2 D",		8,	&Z80::RES_2_D			},	// 0x92
		{ "RES2 E",		8,	&Z80::RES_2_E			},	// 0x93
		{ "RES2 H",		8,	&Z80::RES_2_H			},	// 0x94
		{ "RES2 L",		8,	&Z80::RES_2_L			},	// 0x95
		{ "RES2 (HL)",	16,	&Z80::RES_2_HLa			},	// 0x96
		{ "RES2 A",		8,	&Z80::RES_2_A			},	// 0x97
		{ "RES3 B",		8,	&Z80::RES_3_B			},	// 0x98
		{ "RES3 C",		8,	&Z80::RES_3_C			},	// 0x99
		{ "RES3 D",		8,	&Z80::RES_3_D			},	// 0x9a
		{ "RES3 E",		8,	&Z80::RES_3_E			},	// 0x9b
		{ "RES3 H",		8,	&Z80::RES_3_H			},	// 0x9c
		{ "RES3 L",		8,	&Z80::RES_3_L			},	// 0x9d
		{ "RES3 (HL)",	16,	&Z80::RES_3_HLa			},	// 0x9e
		{ "RES3 A",		8,	&Z80::RES_3_A			},	// 0x9f
		{ "RES4 B",		8,	&Z80::RES_4_B			},	// 0xa0
		{ "RES4 C",		8,	&Z80::RES_4_C			},	// 0xa1
		{ "RES4 D",		8,	&Z80::RES_4_D			},	// 0xa2
		{ "RES4 E",		8,	&Z80::RES_4_E			},	// 0xa3
		{ "RES4 H",		8,	&Z80::RES_4_H			},	// 0xa4
		{ "RES4 L",		8,	&Z80::RES_4_L			},	// 0xa5
		{ "RES4 (HL)",	16,	&Z80::RES_4_HLa			},	// 0xa6
		{ "RES4 A",		8,	&Z80::RES_4_A			},	// 0xa7
		{ "RES5 B",		8,	&Z80::RES_5_B			},	// 0xa8
		{ "RES5 C",		8,	&Z80::RES_5_C			},	// 0xa9
		{ "RES5 D",		8,	&Z80::RES_5_D			},	// 0xaa
		{ "RES5 E",		8,	&Z80::RES_5_E			},	// 0xab
		{ "RES5 H",		8,	&Z80::RES_5_H			},	// 0xac
		{ "RES5 L",		8,	&Z80::RES_5_L			},	// 0xad
		{ "RES5 (HL)",	16,	&Z80::RES_5_HLa			},	// 0xae
		{ "RES5 A",		8,	&Z80::RES_5_A			},	// 0xaf
		{ "RES6 B",		8,	&Z80::RES_6_B			},	// 0xb0
		{ "RES6 C",		8,	&Z80::RES_6_C			},	// 0xb1
		{ "RES6 D",		8,	&Z80::RES_6_D			},	// 0xb2
		{ "RES6 E",		8,	&Z80::RES_6_E			},	// 0xb3
		{ "RES6 H",		8,	&Z80::RES_6_H			},	// 0xb4
		{ "RES6 L",		8,	&Z80::RES_6_L			},	// 0xb5
		{ "RES6 (HL)",	16,	&Z80::RES_6_HLa			},	// 0xb6
		{ "RES6 A",		8,	&Z80::RES_6_A			},	// 0xb7
		{ "RES7 B",		8,	&Z80::RES_7_B			},	// 0xb8
		{ "RES7 C",		8,	&Z80::RES_7_C			},	// 0xb9
		{ "RES7 D",		8,	&Z80::RES_7_D			},	// 0xba
		{ "RES7 E",		8,	&Z80::RES_7_E			},	// 0xbb
		{ "RES7 H",		8,	&Z80::RES_7_H			},	// 0xbc
		{ "RES7 L",		8,	&Z80::RES_7_L			},	// 0xbd
		{ "RES7 (HL)",	16,	&Z80::RES_7_HLa			},	// 0xbe
		{ "RES7 A",		8,	&Z80::RES_7_A			},	// 0xbf
		{ "SET0 B",		8,	&Z80::unimplemented_op0 },	// 0xc0
		{ "SET0 C",		8,	&Z80::unimplemented_op0 },	// 0xc1
		{ "SET0 D",		8,	&Z80::unimplemented_op0 },	// 0xc2
		{ "SET0 E",		8,	&Z80::unimplemented_op0 },	// 0xc3
		{ "SET0 H",		8,	&Z80::unimplemented_op0 },	// 0xc4
		{ "SET0 L",		8,	&Z80::unimplemented_op0 },	// 0xc5
		{ "SET0 (HL)",	16,	&Z80::unimplemented_op0 },	// 0xc6
		{ "SET0 A",		8,	&Z80::unimplemented_op0 },	// 0xc7
		{ "SET1 B",		8,	&Z80::unimplemented_op0 },	// 0xc8
		{ "SET1 C",		8,	&Z80::unimplemented_op0 },	// 0xc9
		{ "SET1 D",		8,	&Z80::unimplemented_op0 },	// 0xca
		{ "SET1 E",		8,	&Z80::unimplemented_op0 },	// 0xcb
		{ "SET1 H",		8,	&Z80::unimplemented_op0 },	// 0xcc
		{ "SET1 L",		8,	&Z80::unimplemented_op0 },	// 0xcd
		{ "SET1 (HL)",	16,	&Z80::unimplemented_op0 },	// 0xce
		{ "SET1 A",		8,	&Z80::unimplemented_op0 },	// 0xcf
		{ "SET2 B",		8,	&Z80::unimplemented_op0 },	// 0xd0
		{ "SET2 C",		8,	&Z80::unimplemented_op0 },	// 0xd1
		{ "SET2 D",		8,	&Z80::unimplemented_op0 },	// 0xd2
		{ "SET2 E",		8,	&Z80::unimplemented_op0 },	// 0xd3
		{ "SET2 H",		8,	&Z80::unimplemented_op0 },	// 0xd4
		{ "SET2 L",		8,	&Z80::unimplemented_op0 },	// 0xd5
		{ "SET2 (HL)",	16,	&Z80::unimplemented_op0 },	// 0xd6
		{ "SET2 A",		8,	&Z80::unimplemented_op0 },	// 0xd7
		{ "SET3 B",		8,	&Z80::unimplemented_op0 },	// 0xd8
		{ "SET3 C",		8,	&Z80::unimplemented_op0 },	// 0xd9
		{ "SET3 D",		8,	&Z80::unimplemented_op0 },	// 0xda
		{ "SET3 E",		8,	&Z80::unimplemented_op0 },	// 0xdb
		{ "SET3 H",		8,	&Z80::unimplemented_op0 },	// 0xdc
		{ "SET3 L",		8,	&Z80::unimplemented_op0 },	// 0xdd
		{ "SET3 (HL)",	16,	&Z80::unimplemented_op0 },	// 0xde
		{ "SET3 A",		8,	&Z80::unimplemented_op0 },	// 0xdf
		{ "SET4 B",		8,	&Z80::unimplemented_op0 },	// 0xe0
		{ "SET4 C",		8,	&Z80::unimplemented_op0 },	// 0xe1
		{ "SET4 D",		8,	&Z80::unimplemented_op0 },	// 0xe2
		{ "SET4 E",		8,	&Z80::unimplemented_op0 },	// 0xe3
		{ "SET4 H",		8,	&Z80::unimplemented_op0 },	// 0xe4
		{ "SET4 L",		8,	&Z80::unimplemented_op0 },	// 0xe5
		{ "SET4 (HL)",	16,	&Z80::unimplemented_op0 },	// 0xe6
		{ "SET4 A",		8,	&Z80::unimplemented_op0 },	// 0xe7
		{ "SET5 B",		8,	&Z80::unimplemented_op0 },	// 0xe8
		{ "SET5 C",		8,	&Z80::unimplemented_op0 },	// 0xe9
		{ "SET5 D",		8,	&Z80::unimplemented_op0 },	// 0xea
		{ "SET5 E",		8,	&Z80::unimplemented_op0 },	// 0xeb
		{ "SET5 H",		8,	&Z80::unimplemented_op0 },	// 0xec
		{ "SET5 L",		8,	&Z80::unimplemented_op0 },	// 0xed
		{ "SET5 (HL)",	16,	&Z80::unimplemented_op0 },	// 0xee
		{ "SET5 A",		8,	&Z80::unimplemented_op0 },	// 0xef
		{ "SET6 B",		8,	&Z80::unimplemented_op0 },	// 0xf0
		{ "SET6 C",		8,	&Z80::unimplemented_op0 },	// 0xf1
		{ "SET6 D",		8,	&Z80::unimplemented_op0 },	// 0xf2
		{ "SET6 E",		8,	&Z80::unimplemented_op0 },	// 0xf3
		{ "SET6 H",		8,	&Z80::unimplemented_op0 },	// 0xf4
		{ "SET6 L",		8,	&Z80::unimplemented_op0 },	// 0xf5
		{ "SET6 (HL)",	16,	&Z80::unimplemented_op0 },	// 0xf6
		{ "SET6 A",		8,	&Z80::unimplemented_op0 },	// 0xf7
		{ "SET7 B",		8,	&Z80::unimplemented_op0 },	// 0xf8
		{ "SET7 C",		8,	&Z80::unimplemented_op0 },	// 0xf9
		{ "SET7 D",		8,	&Z80::unimplemented_op0 },	// 0xfa
		{ "SET7 E",		8,	&Z80::unimplemented_op0 },	// 0xfb
		{ "SET7 H",		8,	&Z80::unimplemented_op0 },	// 0xfc
		{ "SET7 L",		8,	&Z80::unimplemented_op0 },	// 0xfd
		{ "SET7 (HL)",	16,	&Z80::unimplemented_op0 },	// 0xfe
		{ "SET7 A",		8,	&Z80::unimplemented_op0 }	// 0xff
	} }),
	memory(registers.pc),
	gpu(cycles, memory)
{
	Reset();
}

Z80::~Z80()
{
}

void Z80::Reset()
{
	memset(&registers, 0u, sizeof Registers);
	cycles = 0;
}

#include <set>
void Z80::Clock()
{
	//static uint16_t debug_pc_max = 0x0000;
	//static uint16_t debug_pc_min = 0xffff;
	//debug_pc_max = std::max(registers.pc, debug_pc_max);
	//debug_pc_min = std::min(registers.pc, debug_pc_min);

	static bool pc_set_enable = false;
	static std::set<uint16_t> pc_set;

	//if (registers.pc == 0x02d3) {
	//	pc_set_enable = true;
	//}

	if (pc_set_enable)
		pc_set.insert(registers.pc);

	uint8_t instructionIndex = memory.read_8(registers.pc);
	const Instruction& instruction = instructions[instructionIndex];
	registers.pc++;
	
	if (instruction.instructionLength == 1) {
		(this->*instruction.op0)();
	}
	else if (instruction.instructionLength == 2) {
		uint8_t operand = memory.read_8(registers.pc);
		registers.pc++;

		(this->*instruction.op1)(operand);
	}
	else if (instruction.instructionLength == 3) {
		uint16_t operand = memory.read_16(registers.pc);
		registers.pc += 2;

		(this->*instruction.op2)(operand);
	}
	else
		throw std::logic_error("Wrong instruction length!");

	cycles += instruction.cycleCount;

	gpu.Clock();

	MMU::InterruptFlags interruptsToHandle;
	interruptsToHandle.value = (memory.interruptEnable.value & memory.interruptFlags.value);
	if (memory.interruptMaster && interruptsToHandle.value)
	{
		if (interruptsToHandle.Vblank) {
			memory.interruptFlags.Vblank = false;

			HandleVblankInterrupt();
		}
	}
}
