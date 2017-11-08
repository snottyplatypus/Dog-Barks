#pragma once

namespace db
{
	constexpr unsigned long int str2int(const char* str, int h = 0)
	{
		return !str[h] ? 5381 : (str2int(str, h + 1) * 33ull) ^ str[h];
	}
}