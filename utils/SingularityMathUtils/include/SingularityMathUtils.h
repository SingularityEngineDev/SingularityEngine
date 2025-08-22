#ifndef _SNGL_MATH_UTILS_SINGULARITYMATHUTILS_H_INCLUDED_
#define _SNGL_MATH_UTILS_SINGULARITYMATHUTILS_H_INCLUDED_

#include <type_traits>
#include <stdint.h>

namespace sngl::math_utils
{
	template <typename T> requires std::is_arithmetic_v<T>
	inline T nextPoT(T n)
	{
		uint64_t pow = 1;
		while (pow < n)
			pow <<= 1;

		return pow;
	}
}

#endif