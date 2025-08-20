#ifndef _UUIDV4_H_INCLUDED_
#define _UUIDV4_H_INCLUDED_

#include <stdint.h>
#include <random>
#include <string>

struct alignas(8) UUIDv4
{
	UUIDv4() : high(0), low(0) {}
	UUIDv4(uint64_t _high, uint64_t _low) : high(_high), low(_low) {}

	uint64_t high;
	uint64_t low;

	inline std::string toString() const
	{
		constexpr char FORMAT[] = "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x";
		char string[37];

		const uint8_t* b = reinterpret_cast<const uint8_t*>(this);

		std::snprintf(string, sizeof(string), FORMAT,
			b[0], b[1], b[2], b[3],
			b[4], b[5],
			b[6], b[7],
			b[8], b[9],
			b[10], b[11], b[12], b[13], b[14], b[15]
		);

		return std::string(string);
	}

	static inline UUIDv4 Generate()
	{
		std::random_device dev;
		std::mt19937_64 gen(dev());
		std::uniform_int_distribution<uint64_t> dist(0, UINT64_MAX);

		UUIDv4 uuid{ dist(gen), dist(gen) };

		// UUID is a 128-bit format (16 bytes)
		// 7th byte is 

		uint8_t* bytes = reinterpret_cast<uint8_t*>(&uuid);
		bytes[6] &= 0x0F;
		bytes[6] |= 0x40;
		bytes[8] &= 0x3F;
		bytes[8] |= 0x80;

		return uuid;
	}
};

#endif