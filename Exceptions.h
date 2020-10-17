#pragma once

#include <stdexcept>

#define UNIMPLEMENTED() throw std::logic_error("Unimplemented!")

//#include <cassert>
//
//#define DEBUG_BREAK() assert(!"A is not equal to B")