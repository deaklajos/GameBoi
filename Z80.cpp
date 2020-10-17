#include "Z80.h"

#include <cstring>
#include <functional>
#include "Exceptions.h"


struct Instruction {
	const char* name;
	uint8_t cycleCount;
	uint8_t instructionLength;
	union
	{
		void (*op0)(void);
		void (*op1)(uint8_t);
		void (*op2)(uint16_t);
	};
};

void Z80::Reset()
{
	memset(&registers, 0u, sizeof Registers);
}

static void unimplemented_op0(void)
{
	UNIMPLEMENTED();
}

static void unimplemented_op1(uint8_t)
{
	UNIMPLEMENTED();
}

static void unimplemented_op2(uint16_t)
{
	UNIMPLEMENTED();
}

void Z80::Clock()
{
	auto instruction = Fetch();
	//instruction();
	//timer += instruction.time;
	registers.pc++;
}

int Z80::Fetch()
{
	auto instruction = memory.read_8(registers.pc);
	return int();
}

// instruction table is a modified version of: https://cturt.github.io/cinoop.html
const struct Instruction instructions[256] = {
	{ "NOP",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x00
	{ "LD BC, 0x%04X",				6,	3,	{ .op2 = unimplemented_op2 }},		// 0x01
	{ "LD (BC), A",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x02
	{ "INC BC",						4,	1,	{ .op0 = unimplemented_op0 }},		// 0x03
	{ "INC B",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x04
	{ "DEC B",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x05
	{ "LD B, 0x%02X",				4,	2,	{ .op1 = unimplemented_op1 }},		// 0x06
	{ "RLCA",						4,	1,	{ .op0 = unimplemented_op0 }},		// 0x07
	{ "LD (0x%04X), SP",			10,	3,	{ .op2 = unimplemented_op2 }},		// 0x08
	{ "ADD HL, BC",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x09
	{ "LD A, (BC)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x0a
	{ "DEC BC",						4,	1,	{ .op0 = unimplemented_op0 }},		// 0x0b
	{ "INC C",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x0c
	{ "DEC C",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x0d
	{ "LD C, 0x%02X",				4,	2,	{ .op1 = unimplemented_op1 }},		// 0x0e
	{ "RRCA",						4,	1,	{ .op0 = unimplemented_op0 }},		// 0x0f
	{ "STOP",						2,	2,	{ .op1 = unimplemented_op1 }},		// 0x10
	{ "LD DE, 0x%04X",				6,	3,	{ .op2 = unimplemented_op2 }},		// 0x11
	{ "LD (DE), A",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x12
	{ "INC DE",						4,	1,	{ .op0 = unimplemented_op0 }},		// 0x13
	{ "INC D",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x14
	{ "DEC D",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x15
	{ "LD D, 0x%02X",				4,	2,	{ .op1 = unimplemented_op1 }},		// 0x16
	{ "RLA",						4,	1,	{ .op0 = unimplemented_op0 }},		// 0x17
	{ "JR 0x%02X",					4,	2,	{ .op1 = unimplemented_op1 }},		// 0x18
	{ "ADD HL, DE",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x19
	{ "LD A, (DE)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x1a
	{ "DEC DE",						4,	1,	{ .op0 = unimplemented_op0 }},		// 0x1b
	{ "INC E",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x1c
	{ "DEC E",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x1d
	{ "LD E, 0x%02X",				4,	2,	{ .op1 = unimplemented_op1 }},		// 0x1e
	{ "RRA",						4,	1,	{ .op0 = unimplemented_op0 }},		// 0x1f
	{ "JR NZ, 0x%02X",				0,	2,	{ .op1 = unimplemented_op1 }},		// 0x20
	{ "LD HL, 0x%04X",				6,	3,	{ .op2 = unimplemented_op2 }},		// 0x21
	{ "LDI (HL), A",				4,	1,	{ .op0 = unimplemented_op0 }},		// 0x22
	{ "INC HL",						4,	1,	{ .op0 = unimplemented_op0 }},		// 0x23
	{ "INC H",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x24
	{ "DEC H",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x25
	{ "LD H, 0x%02X",				4,	2,	{ .op1 = unimplemented_op1 }},		// 0x26
	{ "DAA",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x27
	{ "JR Z, 0x%02X",				0,	2,	{ .op1 = unimplemented_op1 }},		// 0x28
	{ "ADD HL, HL",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x29
	{ "LDI A, (HL)",				4,	1,	{ .op0 = unimplemented_op0 }},		// 0x2a
	{ "DEC HL",						4,	1,	{ .op0 = unimplemented_op0 }},		// 0x2b
	{ "INC L",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x2c
	{ "DEC L",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x2d
	{ "LD L, 0x%02X",				4,	2,	{ .op1 = unimplemented_op1 }},		// 0x2e
	{ "CPL",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x2f
	{ "JR NC, 0x%02X",				4,	2,	{ .op1 = unimplemented_op1 }},		// 0x30
	{ "LD SP, 0x%04X",				6,	3,	{ .op2 = unimplemented_op2 }},		// 0x31
	{ "LDD (HL), A",				4,	1,	{ .op0 = unimplemented_op0 }},		// 0x32
	{ "INC SP",						4,	1,	{ .op0 = unimplemented_op0 }},		// 0x33
	{ "INC (HL)",					6,	1,	{ .op0 = unimplemented_op0 }},		// 0x34
	{ "DEC (HL)",					6,	1,	{ .op0 = unimplemented_op0 }},		// 0x35
	{ "LD (HL), 0x%02X",			6,	2,	{ .op1 = unimplemented_op1 }},		// 0x36
	{ "SCF",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x37
	{ "JR C, 0x%02X",				0,	2,	{ .op1 = unimplemented_op1 }},		// 0x38
	{ "ADD HL, SP",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x39
	{ "LDD A, (HL)",				4,	1,	{ .op0 = unimplemented_op0 }},		// 0x3a
	{ "DEC SP",						4,	1,	{ .op0 = unimplemented_op0 }},		// 0x3b
	{ "INC A",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x3c
	{ "DEC A",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x3d
	{ "LD A, 0x%02X",				4,	2,	{ .op1 = unimplemented_op1 }},		// 0x3e
	{ "CCF",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x3f
	{ "LD B, B",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x40
	{ "LD B, C",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x41
	{ "LD B, D",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x42
	{ "LD B, E",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x43
	{ "LD B, H",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x44
	{ "LD B, L",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x45
	{ "LD B, (HL)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x46
	{ "LD B, A",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x47
	{ "LD C, B",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x48
	{ "LD C, C",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x49
	{ "LD C, D",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x4a
	{ "LD C, E",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x4b
	{ "LD C, H",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x4c
	{ "LD C, L",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x4d
	{ "LD C, (HL)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x4e
	{ "LD C, A",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x4f
	{ "LD D, B",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x50
	{ "LD D, C",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x51
	{ "LD D, D",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x52
	{ "LD D, E",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x53
	{ "LD D, H",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x54
	{ "LD D, L",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x55
	{ "LD D, (HL)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x56
	{ "LD D, A",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x57
	{ "LD E, B",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x58
	{ "LD E, C",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x59
	{ "LD E, D",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x5a
	{ "LD E, E",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x5b
	{ "LD E, H",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x5c
	{ "LD E, L",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x5d
	{ "LD E, (HL)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x5e
	{ "LD E, A",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x5f
	{ "LD H, B",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x60
	{ "LD H, C",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x61
	{ "LD H, D",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x62
	{ "LD H, E",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x63
	{ "LD H, H",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x64
	{ "LD H, L",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x65
	{ "LD H, (HL)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x66
	{ "LD H, A",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x67
	{ "LD L, B",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x68
	{ "LD L, C",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x69
	{ "LD L, D",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x6a
	{ "LD L, E",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x6b
	{ "LD L, H",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x6c
	{ "LD L, L",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x6d
	{ "LD L, (HL)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x6e
	{ "LD L, A",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x6f
	{ "LD (HL), B",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x70
	{ "LD (HL), C",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x71
	{ "LD (HL), D",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x72
	{ "LD (HL), E",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x73
	{ "LD (HL), H",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x74
	{ "LD (HL), L",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x75
	{ "HALT",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x76
	{ "LD (HL), A",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x77
	{ "LD A, B",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x78
	{ "LD A, C",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x79
	{ "LD A, D",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x7a
	{ "LD A, E",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x7b
	{ "LD A, H",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x7c
	{ "LD A, L",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x7d
	{ "LD A, (HL)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x7e
	{ "LD A, A",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x7f
	{ "ADD A, B",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x80
	{ "ADD A, C",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x81
	{ "ADD A, D",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x82
	{ "ADD A, E",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x83
	{ "ADD A, H",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x84
	{ "ADD A, L",					2,	1,	{ .op0 = unimplemented_op0 }},		// 0x85
	{ "ADD A, (HL)",				4,	1,	{ .op0 = unimplemented_op0 }},		// 0x86
	{ "ADD A",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x87
	{ "ADC B",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x88
	{ "ADC C",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x89
	{ "ADC D",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x8a
	{ "ADC E",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x8b
	{ "ADC H",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x8c
	{ "ADC L",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x8d
	{ "ADC (HL)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x8e
	{ "ADC A",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x8f
	{ "SUB B",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x90
	{ "SUB C",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x91
	{ "SUB D",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x92
	{ "SUB E",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x93
	{ "SUB H",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x94
	{ "SUB L",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x95
	{ "SUB (HL)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x96
	{ "SUB A",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x97
	{ "SBC B",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x98
	{ "SBC C",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x99
	{ "SBC D",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x9a
	{ "SBC E",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x9b
	{ "SBC H",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x9c
	{ "SBC L",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x9d
	{ "SBC (HL)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0x9e
	{ "SBC A",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0x9f
	{ "AND B",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xa0
	{ "AND C",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xa1
	{ "AND D",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xa2
	{ "AND E",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xa3
	{ "AND H",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xa4
	{ "AND L",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xa5
	{ "AND (HL)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0xa6
	{ "AND A",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xa7
	{ "XOR B",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xa8
	{ "XOR C",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xa9
	{ "XOR D",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xaa
	{ "XOR E",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xab
	{ "XOR H",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xac
	{ "XOR L",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xad
	{ "XOR (HL)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0xae
	{ "XOR A",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xaf
	{ "OR B",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xb0
	{ "OR C",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xb1
	{ "OR D",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xb2
	{ "OR E",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xb3
	{ "OR H",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xb4
	{ "OR L",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xb5
	{ "OR (HL)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0xb6
	{ "OR A",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xb7
	{ "CP B",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xb8
	{ "CP C",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xb9
	{ "CP D",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xba
	{ "CP E",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xbb
	{ "CP H",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xbc
	{ "CP L",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xbd
	{ "CP (HL)",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0xbe
	{ "CP A",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xbf
	{ "RET NZ",						0,	1,	{ .op0 = unimplemented_op0 }},		// 0xc0
	{ "POP BC",						6,	1,	{ .op0 = unimplemented_op0 }},		// 0xc1
	{ "JP NZ, 0x%04X",				0,	3,	{ .op2 = unimplemented_op2 }},		// 0xc2
	{ "JP 0x%04X",					6,	3,	{ .op2 = unimplemented_op2 }},		// 0xc3
	{ "CALL NZ, 0x%04X",			0,	3,	{ .op2 = unimplemented_op2 }},		// 0xc4
	{ "PUSH BC",					8,	1,	{ .op0 = unimplemented_op0 }},		// 0xc5
	{ "ADD A, 0x%02X",				4,	2,	{ .op1 = unimplemented_op1 }},		// 0xc6
	{ "RST 0x00",					8,	1,	{ .op0 = unimplemented_op0 }},		// 0xc7
	{ "RET Z",						0,	1,	{ .op0 = unimplemented_op0 }},		// 0xc8
	{ "RET",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xc9
	{ "JP Z, 0x%04X",				0,	3,	{ .op2 = unimplemented_op2 }},		// 0xca
	{ "CB %02X",					0,	2,	{ .op1 = unimplemented_op1 }},		// 0xcb
	{ "CALL Z, 0x%04X",				0,	3,	{ .op2 = unimplemented_op2 }},		// 0xcc
	{ "CALL 0x%04X",				6,	3,	{ .op2 = unimplemented_op2 }},		// 0xcd
	{ "ADC 0x%02X",					4,	2,	{ .op1 = unimplemented_op1 }},		// 0xce
	{ "RST 0x08",					8,	1,	{ .op0 = unimplemented_op0 }},		// 0xcf
	{ "RET NC",						0,	1,	{ .op0 = unimplemented_op0 }},		// 0xd0
	{ "POP DE",						6,	1,	{ .op0 = unimplemented_op0 }},		// 0xd1
	{ "JP NC, 0x%04X",				0,	3,	{ .op2 = unimplemented_op2 }},		// 0xd2
	{ "UNKNOWN",					0,	1,	{ .op0 = unimplemented_op0 }},		// 0xd3
	{ "CALL NC, 0x%04X",			0,	3,	{ .op2 = unimplemented_op2 }},		// 0xd4
	{ "PUSH DE",					8,	1,	{ .op0 = unimplemented_op0 }},		// 0xd5
	{ "SUB 0x%02X",					4,	2,	{ .op1 = unimplemented_op1 }},		// 0xd6
	{ "RST 0x10",					8,	1,	{ .op0 = unimplemented_op0 }},		// 0xd7
	{ "RET C",						0,	1,	{ .op0 = unimplemented_op0 }},		// 0xd8
	{ "RETI",						8,	1,	{ .op0 = unimplemented_op0 }},		// 0xd9
	{ "JP C, 0x%04X",				0,	3,	{ .op2 = unimplemented_op2 }},		// 0xda
	{ "UNKNOWN",					0,	1,	{ .op0 = unimplemented_op0 }},		// 0xdb
	{ "CALL C, 0x%04X",				0,	3,	{ .op2 = unimplemented_op2 }},		// 0xdc
	{ "UNKNOWN",					0,	1,	{ .op0 = unimplemented_op0 }},		// 0xdd
	{ "SBC 0x%02X",					4,	2,	{ .op1 = unimplemented_op1 }},		// 0xde
	{ "RST 0x18",					8,	1,	{ .op0 = unimplemented_op0 }},		// 0xdf
	{ "LD (0xFF00 + 0x%02X), A",	6,	2,	{ .op1 = unimplemented_op1 }},		// 0xe0
	{ "POP HL",						6,	1,	{ .op0 = unimplemented_op0 }},		// 0xe1
	{ "LD (0xFF00 + C), A",			4,	1,	{ .op0 = unimplemented_op0 }},		// 0xe2
	{ "UNKNOWN",					0,	1,	{ .op0 = unimplemented_op0 }},		// 0xe3
	{ "UNKNOWN",					0,	1,	{ .op0 = unimplemented_op0 }},		// 0xe4
	{ "PUSH HL",					8,	1,	{ .op0 = unimplemented_op0 }},		// 0xe5
	{ "AND 0x%02X",					4,	2,	{ .op1 = unimplemented_op1 }},		// 0xe6
	{ "RST 0x20",					8,	1,	{ .op0 = unimplemented_op0 }},		// 0xe7
	{ "ADD SP,0x%02X",				8,	2,	{ .op1 = unimplemented_op1 }},		// 0xe8
	{ "JP HL",						2,	1,	{ .op0 = unimplemented_op0 }},		// 0xe9
	{ "LD (0x%04X), A",				8,	3,	{ .op2 = unimplemented_op2 }},		// 0xea
	{ "UNKNOWN",					0,	1,	{ .op0 = unimplemented_op0 }},		// 0xeb
	{ "UNKNOWN",					0,	1,	{ .op0 = unimplemented_op0 }},		// 0xec
	{ "UNKNOWN",					0,	1,	{ .op0 = unimplemented_op0 }},		// 0xed
	{ "XOR 0x%02X",					4,	2,	{ .op1 = unimplemented_op1 }},		// 0xee
	{ "RST 0x28",					8,	1,	{ .op0 = unimplemented_op0 }},		// 0xef
	{ "LD A, (0xFF00 + 0x%02X)",	6,	2,	{ .op1 = unimplemented_op1 }},		// 0xf0
	{ "POP AF",						6,	1,	{ .op0 = unimplemented_op0 }},		// 0xf1
	{ "LD A, (0xFF00 + C)",			4,	1,	{ .op0 = unimplemented_op0 }},		// 0xf2
	{ "DI",							2,	1,	{ .op0 = unimplemented_op0 }},		// 0xf3
	{ "UNKNOWN",					0,	1,	{ .op0 = unimplemented_op0 }},		// 0xf4
	{ "PUSH AF",					8,	1,	{ .op0 = unimplemented_op0 }},		// 0xf5
	{ "OR 0x%02X",					4,	2,	{ .op1 = unimplemented_op1 }},		// 0xf6
	{ "RST 0x30",					8,	1,	{ .op0 = unimplemented_op0 }},		// 0xf7
	{ "LD HL, SP+0x%02X",			6,	2,	{ .op1 = unimplemented_op1 }},		// 0xf8
	{ "LD SP, HL",					4,	1,	{ .op0 = unimplemented_op0 }},		// 0xf9
	{ "LD A, (0x%04X)",				8,	3,	{ .op2 = unimplemented_op2 }},		// 0xfa
	{ "EI",							2,	1,	{ .op0 = unimplemented_op0 }},		// 0xfb
	{ "UNKNOWN",					0,	1,	{ .op0 = unimplemented_op0 }},		// 0xfc
	{ "UNKNOWN",					0,	1,	{ .op0 = unimplemented_op0 }},		// 0xfd
	{ "CP 0x%02X",					4,	2,	{ .op1 = unimplemented_op1 }},		// 0xfe
	{ "RST 0x38",					8,	1,	{ .op0 = unimplemented_op0 }}		// 0xff
};
