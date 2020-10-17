#include <iostream>

#include "Z80.h"
#include "Exceptions.h"

int main()
{
	Z80 cpu;

	for (;;)
	{
		cpu.Clock();
	}
}
