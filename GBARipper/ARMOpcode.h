#pragma once
#include <iostream>
#include <bitset>

class ARMOpcode
{
	//static_assert(sizeof(uint_fast32_t) == 4, "uint_fast32_t is not 4 bytes on this platform");
	//unsigned char bytes[4];

	//uint_fast32_t opcode;

	std::bitset<32> bits;

	#define GEN(count) (0 ^ ((1 << (count)) - 1))

	// indexing start at 1
	// #define SET_BITS(n, l, r) (n | (((1 << l - 1)) - 1) ^ ((1 << r) - 1)));

	#define BITS(index, count) ((opcode >> ((index) - (count) + 1)) & GEN(count))

	#define COND (BITS(31, 4))

	/**
	 * @brief Compare bits of the opcode at index with count, against matcher (x for wildcard)
	 * @param index 
	 * @param count 
	 * @param matcher 
	 * @return 
	*/
	bool match(int index, std::string matcher);
	//bool MATCH(uint_fast32_t bits, std::string matcher);

	//#define IS_COND(match) ((bytes[3] >> 4) == match)
	//#define COND ((bytes[3] >> 4) & 0b1111)
	//#define CPSR_C ((COND >> 3) & 0b1)
	//#define CPSR_N ((COND >> 2) & 0b1)
	//#define CPSR_Z ((COND >> 1) & 0b1)
	//#define CPSR_V ((COND >> 0) & 0b1)

	//#define CPSR_EQ (CPSR_Z)
	//#define CPSR_NE (~CPSR_Z)
	//#define CPSR_CS (CPSR_C)
	//#define CPSR_CC (~CPSR_C)
	//#define CPSR_MI (CPSR_N)
	//#define CPSR_PL (~CPSR_N)
	//#define CPSR_VS (CPSR_V)
	//#define CPSR_VC (~CPSR_N)
	//#define CPSR_HI (CPSR_C & ~CPSR_Z)
	//#define CPSR_LS (~CPSR_C | CPSR_Z)
	//#define CPSR_GE (CPSR_N == CPSR_V)
	//#define CPSR_LT (CPSR_C ^ CPSR_V)
	//#define CPSR_GT (~CPSR_Z & (CPSR_N == CPSR_V))
	//#define CPSR_LE (CPSR_Z | (CPSR_N ^ CPSR_V))
	//#define CPSR_AL
	//#define CPSR_NV

	/*
	* Starting at index 'i',
	* Return 'len' bits, decrementing
	*/
	//#define BITS(i, len) ((bytes[i/8] >> (i % 8)) & (0b1 << (len - 1)))

	//#define OP1 ((bytes[3] >> 1) & 0b111)

public:
	ARMOpcode(char* buf);

	std::string Process1();
	//std::string Process2();
};

