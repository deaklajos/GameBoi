#include "Z80.h"

#include <cstring>

void Z80::Reset()
{
	memset(&registers, 0u, sizeof Registers);
}

void Z80::Clock()
{
	auto instruction = Fetch();
	//instruction();
	//timer += instruction.time;
	registers.pc++;
}

Instruction Z80::Fetch()
{
	auto instruction = memory.read_8(registers.pc);
	return Instruction();
}
