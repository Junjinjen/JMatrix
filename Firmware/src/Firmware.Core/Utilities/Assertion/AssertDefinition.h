#pragma once
#ifdef JUNJINJEN_UNIT_TESTING
#include "AssertFailedException.h"
#define JUNJINJEN_ASSERT(x) (!(x) ? throw junjinjen_matrix::firmware::utilities::assertion::AssertFailedException(#x) : (void)0u)
#else
#include <cassert>
#define JUNJINJEN_ASSERT(x) assert(x)
#endif