#include "Z80.h"

#include <cstring>
#include <functional>
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

void Z80::LDD_HLa_A(void)
{
	memory.write_8(registers.hl, registers.a);
	registers.hl--;
}

void Z80::LDI_HLa_A(void)
{
	memory.write_8(registers.hl, registers.a);
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

void Z80::LD_FF_C_A(void)
{
	memory.write_8((uint16_t)0xff00u + registers.c, registers.a);
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

void Z80::PREFIX(uint8_t instuction)
{
	/*printf("0x%02X", instuction);*/

	if (instuction == 0x7C) // BIT 7, H
	{
		registers.f |= HALF_CARRY_FLAG;	// SET
		registers.f &= ~SUBTRACT_FLAG;	// CLEAR

		if ((1u << 7) & registers.h)
			registers.f |= ZERO_FLAG;	// SET
		else
			registers.f &= ~ZERO_FLAG;	// CLEAR

		cycles += 8;
	}
	else if (instuction == 0x4F) // BIT 1, A
	{
		registers.f |= HALF_CARRY_FLAG;	// SET
		registers.f &= ~SUBTRACT_FLAG;	// CLEAR

		if ((1u) & registers.h)
			registers.f |= ZERO_FLAG;	// SET
		else
			registers.f &= ~ZERO_FLAG;	// CLEAR

		cycles += 8;
	}
	else if (instuction == 0x11) // RL C
	{
		registers.f &= ~SUBTRACT_FLAG;		// CLEAR
		registers.f &= ~HALF_CARRY_FLAG;	// CLEAR

		uint8_t carry = (registers.c & (1u << 7)) >> 7;
		if (carry)
			registers.f |= CARRY_FLAG;	// SET
		else
			registers.f &= ~CARRY_FLAG;	// CLEAR

		registers.c <<= 1;
		registers.c += carry;

		cycles += 8;
	}
	else
	{
		UNIMPLEMENTED();
	}
}

void Z80::XOR_A(void)
{
	registers.a ^= registers.a;

	if (registers.a == 0)
		registers.f = ZERO_FLAG;
	else
		registers.f = 0;
}

void Z80::JR_NZ(uint8_t signed_offset)
{
	int8_t offset = signed_offset;

	if (registers.f & ZERO_FLAG)
	{
		registers.pc += offset;
		cycles += 12;
	}
	else
		cycles += 8;
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
{
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

// TODO CLEAN UP INSTRUCTION TIMING AND USE T CYCLES!!!
// instruction table is a modified version of: https://cturt.github.io/cinoop.html
Z80::Z80() : instructions({ {
		{ "NOP",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x00
		{ "LD BC, 0x%04X",				12,	3,	{.op2 = &Z80::LD_BC_d16			}},	// 0x01
		{ "LD (BC), A",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x02
		{ "INC BC",						4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x03
		{ "INC B",						4,	1,	{.op0 = &Z80::INC_B				}},	// 0x04
		{ "DEC B",						4,	1,	{.op0 = &Z80::DEC_B				}},	// 0x05
		{ "LD B, 0x%02X",				8,	2,	{.op1 = &Z80::LD_B_d8			}},	// 0x06
		{ "RLCA",						4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x07
		{ "LD (0x%04X), SP",			10,	3,	{.op2 = &Z80::unimplemented_op2 }},	// 0x08
		{ "ADD HL, BC",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x09
		{ "LD A, (BC)",					8,	1,	{.op0 = &Z80::LD_A_BCa			}},	// 0x0a
		{ "DEC BC",						4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x0b
		{ "INC C",						4,	1,	{.op0 = &Z80::INC_C				}},	// 0x0c
		{ "DEC C",						4,	1,	{.op0 = &Z80::DEC_C				}},	// 0x0d
		{ "LD C, 0x%02X",				8,	2,	{.op1 = &Z80::LD_C_d8			}},	// 0x0e
		{ "RRCA",						4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x0f
		{ "STOP",						2,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0x10
		{ "LD DE, 0x%04X",				12,	3,	{.op2 = &Z80::LD_DE_d16			}},	// 0x11
		{ "LD (DE), A",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x12
		{ "INC DE",						4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x13
		{ "INC D",						4,	1,	{.op0 = &Z80::INC_D				}},	// 0x14
		{ "DEC D",						4,	1,	{.op0 = &Z80::DEC_D				}},	// 0x15
		{ "LD D, 0x%02X",				8,	2,	{.op1 = &Z80::LD_D_d8			}},	// 0x16
		{ "RLA",						4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x17
		{ "JR 0x%02X",					4,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0x18
		{ "ADD HL, DE",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x19
		{ "LD A, (DE)",					8,	1,	{.op0 = &Z80::LD_A_DEa			}},	// 0x1a
		{ "DEC DE",						4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x1b
		{ "INC E",						4,	1,	{.op0 = &Z80::INC_E				}},	// 0x1c
		{ "DEC E",						4,	1,	{.op0 = &Z80::DEC_E				}},	// 0x1d
		{ "LD E, 0x%02X",				8,	2,	{.op1 = &Z80::LD_E_d8			}},	// 0x1e
		{ "RRA",						4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x1f
		{ "JR NZ, 0x%02X",				0,	2,	{.op1 = &Z80::JR_NZ				}},	// 0x20
		{ "LD HL, 0x%04X",				12,	3,	{.op2 = &Z80::LD_HL_d16			}},	// 0x21
		{ "LDI (HL), A",				8,	1,	{.op0 = &Z80::LDI_HLa_A			}},	// 0x22
		{ "INC HL",						4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x23
		{ "INC H",						4,	1,	{.op0 = &Z80::INC_H				}},	// 0x24
		{ "DEC H",						4,	1,	{.op0 = &Z80::DEC_H				}},	// 0x25
		{ "LD H, 0x%02X",				8,	2,	{.op1 = &Z80::LD_H_d8			}},	// 0x26
		{ "DAA",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x27
		{ "JR Z, 0x%02X",				0,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0x28
		{ "ADD HL, HL",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x29
		{ "LDI A, (HL)",				4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x2a
		{ "DEC HL",						4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x2b
		{ "INC L",						4,	1,	{.op0 = &Z80::INC_L				}},	// 0x2c
		{ "DEC L",						4,	1,	{.op0 = &Z80::DEC_L				}},	// 0x2d
		{ "LD L, 0x%02X",				8,	2,	{.op1 = &Z80::LD_L_d8			}},	// 0x2e
		{ "CPL",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x2f
		{ "JR NC, 0x%02X",				4,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0x30
		{ "LD SP, 0x%04X",				12,	3,	{.op2 = &Z80::LD_SP_d16			}},	// 0x31
		{ "LDD (HL), A",				8,	1,	{.op0 = &Z80::LDD_HLa_A			}},	// 0x32
		{ "INC SP",						4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x33
		{ "INC (HL)",					12,	1,	{.op0 = &Z80::INC_HLa			}},	// 0x34
		{ "DEC (HL)",					12,	1,	{.op0 = &Z80::DEC_HLa			}},	// 0x35
		{ "LD (HL), 0x%02X",			6,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0x36
		{ "SCF",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x37
		{ "JR C, 0x%02X",				0,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0x38
		{ "ADD HL, SP",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x39
		{ "LDD A, (HL)",				4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x3a
		{ "DEC SP",						4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x3b
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
		{ "LD B, (HL)",					8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x46
		{ "LD B, A",					4,	1,	{.op0 = &Z80::LD_B_A			}},	// 0x47
		{ "LD C, B",					4,	1,	{.op0 = &Z80::LD_C_B			}},	// 0x48
		{ "LD C, C",					4,	1,	{.op0 = &Z80::NOP				}},	// 0x49
		{ "LD C, D",					4,	1,	{.op0 = &Z80::LD_C_D			}},	// 0x4a
		{ "LD C, E",					4,	1,	{.op0 = &Z80::LD_C_E			}},	// 0x4b
		{ "LD C, H",					4,	1,	{.op0 = &Z80::LD_C_H			}},	// 0x4c
		{ "LD C, L",					4,	1,	{.op0 = &Z80::LD_C_L			}},	// 0x4d
		{ "LD C, (HL)",					8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x4e
		{ "LD C, A",					4,	1,	{.op0 = &Z80::LD_D_A			}},	// 0x4f
		{ "LD D, B",					4,	1,	{.op0 = &Z80::LD_D_B			}},	// 0x50
		{ "LD D, C",					4,	1,	{.op0 = &Z80::LD_D_C			}},	// 0x51
		{ "LD D, D",					4,	1,	{.op0 = &Z80::NOP				}},	// 0x52
		{ "LD D, E",					4,	1,	{.op0 = &Z80::LD_D_E			}},	// 0x53
		{ "LD D, H",					4,	1,	{.op0 = &Z80::LD_D_H			}},	// 0x54
		{ "LD D, L",					4,	1,	{.op0 = &Z80::LD_D_L			}},	// 0x55
		{ "LD D, (HL)",					8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x56
		{ "LD D, A",					4,	1,	{.op0 = &Z80::LD_D_A			}},	// 0x57
		{ "LD E, B",					4,	1,	{.op0 = &Z80::LD_E_B			}},	// 0x58
		{ "LD E, C",					4,	1,	{.op0 = &Z80::LD_E_C			}},	// 0x59
		{ "LD E, D",					4,	1,	{.op0 = &Z80::LD_E_D			}},	// 0x5a
		{ "LD E, E",					4,	1,	{.op0 = &Z80::NOP				}},	// 0x5b
		{ "LD E, H",					4,	1,	{.op0 = &Z80::LD_E_H			}},	// 0x5c
		{ "LD E, L",					4,	1,	{.op0 = &Z80::LD_E_L			}},	// 0x5d
		{ "LD E, (HL)",					8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x5e
		{ "LD E, A",					4,	1,	{.op0 = &Z80::LD_E_A			}},	// 0x5f
		{ "LD H, B",					4,	1,	{.op0 = &Z80::LD_H_B			}},	// 0x60
		{ "LD H, C",					4,	1,	{.op0 = &Z80::LD_H_C			}},	// 0x61
		{ "LD H, D",					4,	1,	{.op0 = &Z80::LD_H_D			}},	// 0x62
		{ "LD H, E",					4,	1,	{.op0 = &Z80::LD_H_E			}},	// 0x63
		{ "LD H, H",					4,	1,	{.op0 = &Z80::NOP				}},	// 0x64
		{ "LD H, L",					4,	1,	{.op0 = &Z80::LD_H_L			}},	// 0x65
		{ "LD H, (HL)",					8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x66
		{ "LD H, A",					4,	1,	{.op0 = &Z80::LD_H_A			}},	// 0x67
		{ "LD L, B",					4,	1,	{.op0 = &Z80::LD_L_B			}},	// 0x68
		{ "LD L, C",					4,	1,	{.op0 = &Z80::LD_L_C			}},	// 0x69
		{ "LD L, D",					4,	1,	{.op0 = &Z80::LD_L_D			}},	// 0x6a
		{ "LD L, E",					4,	1,	{.op0 = &Z80::LD_L_E			}},	// 0x6b
		{ "LD L, H",					4,	1,	{.op0 = &Z80::LD_L_H			}},	// 0x6c
		{ "LD L, L",					4,	1,	{.op0 = &Z80::NOP				}},	// 0x6d
		{ "LD L, (HL)",					8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x6e
		{ "LD L, A",					4,	1,	{.op0 = &Z80::LD_D_A			}},	// 0x6f
		{ "LD (HL), B",					8,	1,	{.op0 = &Z80::LD_HLa_B			}},	// 0x70
		{ "LD (HL), C",					8,	1,	{.op0 = &Z80::LD_HLa_C			}},	// 0x71
		{ "LD (HL), D",					8,	1,	{.op0 = &Z80::LD_HLa_D			}},	// 0x72
		{ "LD (HL), E",					8,	1,	{.op0 = &Z80::LD_HLa_E			}},	// 0x73
		{ "LD (HL), H",					8,	1,	{.op0 = &Z80::LD_HLa_H			}},	// 0x74
		{ "LD (HL), L",					8,	1,	{.op0 = &Z80::LD_HLa_L			}},	// 0x75
		{ "HALT",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x76
		{ "LD (HL), A",					8,	1,	{.op0 = &Z80::LD_HLa_L			}},	// 0x77
		{ "LD A, B",					4,	1,	{.op0 = &Z80::LD_A_B			}},	// 0x78
		{ "LD A, C",					4,	1,	{.op0 = &Z80::LD_A_C			}},	// 0x79
		{ "LD A, D",					4,	1,	{.op0 = &Z80::LD_A_D			}},	// 0x7a
		{ "LD A, E",					4,	1,	{.op0 = &Z80::LD_A_E			}},	// 0x7b
		{ "LD A, H",					4,	1,	{.op0 = &Z80::LD_A_H			}},	// 0x7c
		{ "LD A, L",					4,	1,	{.op0 = &Z80::LD_A_L			}},	// 0x7d
		{ "LD A, (HL)",					8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x7e
		{ "LD A, A",					4,	1,	{.op0 = &Z80::NOP				}},	// 0x7f
		{ "ADD A, B",					2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x80
		{ "ADD A, C",					2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x81
		{ "ADD A, D",					2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x82
		{ "ADD A, E",					2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x83
		{ "ADD A, H",					2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x84
		{ "ADD A, L",					2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x85
		{ "ADD A, (HL)",				4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x86
		{ "ADD A",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x87
		{ "ADC B",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x88
		{ "ADC C",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x89
		{ "ADC D",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x8a
		{ "ADC E",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x8b
		{ "ADC H",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x8c
		{ "ADC L",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x8d
		{ "ADC (HL)",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x8e
		{ "ADC A",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x8f
		{ "SUB B",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x90
		{ "SUB C",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x91
		{ "SUB D",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x92
		{ "SUB E",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x93
		{ "SUB H",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x94
		{ "SUB L",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x95
		{ "SUB (HL)",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x96
		{ "SUB A",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x97
		{ "SBC B",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x98
		{ "SBC C",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x99
		{ "SBC D",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x9a
		{ "SBC E",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x9b
		{ "SBC H",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x9c
		{ "SBC L",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x9d
		{ "SBC (HL)",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x9e
		{ "SBC A",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0x9f
		{ "AND B",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xa0
		{ "AND C",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xa1
		{ "AND D",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xa2
		{ "AND E",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xa3
		{ "AND H",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xa4
		{ "AND L",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xa5
		{ "AND (HL)",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xa6
		{ "AND A",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xa7
		{ "XOR B",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xa8
		{ "XOR C",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xa9
		{ "XOR D",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xaa
		{ "XOR E",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xab
		{ "XOR H",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xac
		{ "XOR L",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xad
		{ "XOR (HL)",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xae
		{ "XOR A",						4,	1,	{.op0 = &Z80::XOR_A				}},	// 0xaf
		{ "OR B",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xb0
		{ "OR C",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xb1
		{ "OR D",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xb2
		{ "OR E",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xb3
		{ "OR H",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xb4
		{ "OR L",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xb5
		{ "OR (HL)",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xb6
		{ "OR A",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xb7
		{ "CP B",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xb8
		{ "CP C",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xb9
		{ "CP D",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xba
		{ "CP E",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xbb
		{ "CP H",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xbc
		{ "CP L",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xbd
		{ "CP (HL)",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xbe
		{ "CP A",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xbf
		{ "RET NZ",						0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xc0
		{ "POP BC",						12,	1,	{.op0 = &Z80::POP_BC			}},	// 0xc1
		{ "JP NZ, 0x%04X",				0,	3,	{.op2 = &Z80::unimplemented_op2 }},	// 0xc2
		{ "JP 0x%04X",					6,	3,	{.op2 = &Z80::unimplemented_op2 }},	// 0xc3
		{ "CALL NZ, 0x%04X",			0,	3,	{.op2 = &Z80::CALL_NZ			}},	// 0xc4
		{ "PUSH BC",					16,	1,	{.op0 = &Z80::PUSH_BC			}},	// 0xc5
		{ "ADD A, 0x%02X",				4,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0xc6
		{ "RST 0x00",					8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xc7
		{ "RET Z",						0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xc8
		{ "RET",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xc9
		{ "JP Z, 0x%04X",				0,	3,	{.op2 = &Z80::unimplemented_op2 }},	// 0xca
		{ "CB %02X",					0,	2,	{.op1 = &Z80::PREFIX			}},	// 0xcb
		{ "CALL Z, 0x%04X",				0,	3,	{.op2 = &Z80::CALL_Z			}},	// 0xcc
		{ "CALL 0x%04X",				24,	3,	{.op2 = &Z80::CALL				}},	// 0xcd
		{ "ADC 0x%02X",					4,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0xce
		{ "RST 0x08",					8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xcf
		{ "RET NC",						0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xd0
		{ "POP DE",						12,	1,	{.op0 = &Z80::POP_DE			}},	// 0xd1
		{ "JP NC, 0x%04X",				0,	3,	{.op2 = &Z80::unimplemented_op2 }},	// 0xd2
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xd3
		{ "CALL NC, 0x%04X",			0,	3,	{.op2 = &Z80::CALL_NC			}},	// 0xd4
		{ "PUSH DE",					16,	1,	{.op0 = &Z80::PUSH_DE			}},	// 0xd5
		{ "SUB 0x%02X",					4,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0xd6
		{ "RST 0x10",					8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xd7
		{ "RET C",						0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xd8
		{ "RETI",						8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xd9
		{ "JP C, 0x%04X",				0,	3,	{.op2 = &Z80::unimplemented_op2 }},	// 0xda
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xdb
		{ "CALL C, 0x%04X",				0,	3,	{.op2 = &Z80::CALL_C			}},	// 0xdc
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xdd
		{ "SBC 0x%02X",					4,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0xde
		{ "RST 0x18",					8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xdf
		{ "LD (0xFF00 + 0x%02X), A",	12,	2,	{.op1 = &Z80::LD_FF_a8_A		}},	// 0xe0
		{ "POP HL",						12,	1,	{.op0 = &Z80::POP_HL			}},	// 0xe1
		{ "LD (0xFF00 + C), A",			8,	1,	{.op0 = &Z80::LD_FF_C_A			}},	// 0xe2
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xe3
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xe4
		{ "PUSH HL",					16,	1,	{.op0 = &Z80::POP_HL			}},	// 0xe5
		{ "AND 0x%02X",					4,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0xe6
		{ "RST 0x20",					8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xe7
		{ "ADD SP,0x%02X",				8,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0xe8
		{ "JP HL",						2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xe9
		{ "LD (0x%04X), A",				8,	3,	{.op2 = &Z80::unimplemented_op2 }},	// 0xea
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xeb
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xec
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xed
		{ "XOR 0x%02X",					4,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0xee
		{ "RST 0x28",					8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xef
		{ "LD A, (0xFF00 + 0x%02X)",	6,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0xf0
		{ "POP AF",						12,	1,	{.op0 = &Z80::POP_AF			}},	// 0xf1
		{ "LD A, (0xFF00 + C)",			4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xf2
		{ "DI",							2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xf3
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xf4
		{ "PUSH AF",					16,	1,	{.op0 = &Z80::PUSH_AF			}},	// 0xf5
		{ "OR 0x%02X",					4,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0xf6
		{ "RST 0x30",					8,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xf7
		{ "LD HL, SP+0x%02X",			6,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0xf8
		{ "LD SP, HL",					4,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xf9
		{ "LD A, (0x%04X)",				8,	3,	{.op2 = &Z80::unimplemented_op2 }},	// 0xfa
		{ "EI",							2,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xfb
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xfc
		{ "UNKNOWN",					0,	1,	{.op0 = &Z80::unimplemented_op0 }},	// 0xfd
		{ "CP 0x%02X",					4,	2,	{.op1 = &Z80::unimplemented_op1 }},	// 0xfe
		{ "RST 0x38",					8,	1,	{.op0 = &Z80::unimplemented_op0 }}	// 0xff
	} }),
	memory(registers.pc)
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

void Z80::Clock()
{
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
}
