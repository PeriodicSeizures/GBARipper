#include "ARMOpcode.h"
#include <string>

ARMOpcode::ARMOpcode(char* buf)
{
	uint_fast32_t opcode;
	std::memcpy(&opcode, buf, 4);

	this->bits = std::bitset<32>(opcode);
}

bool ARMOpcode::match(int index, std::string matcher) {
	// will use _ as wildcard for any
	//auto bits(std::bitset<32>(opcode).to_string());

	for (int i = 0; i < matcher.size(); i++) {
		//std::cout << bits[index-i];
		if (matcher[i] == 'x')
			continue;

		if ((matcher[i] - '0') != bits[index - i]) {
			return false;
		}
	}

	return true;
}

std::string ARMOpcode::Process1() {

	/*
	* B / BL / BLX: 
	*	- 101
	* BX / BLX: 
	*	- 0001.0010.1111.1111.1111
	* 
	* 
	*/

	std::string result;

	// https://www.akkit.org/info/gbatek.htm#arm4branchandbranchwithlinkbblblx
	// https://developer.arm.com/documentation/ddi0406/cb/Application-Level-Architecture/ARM-Instruction-Set-Encoding/ARM-instruction-set-encoding
	if (!match(31, "1111")) {
		if (match(27, "00x")) {
			std::cout << "Data-processing and miscellaneous instructions\n";
		}
		else if (match(27, "010")) {
			std::cout << "Load/store word and unsigned byte\n";
		}
		else if (match(27, "011")) {
			if (bits[4] == 0) {
				std::cout << "Load/store word and unsigned byte\n";
			}
			else {
				std::cout << "Media instructions\n";
			}
		}
		else if (match(27, "10x")) {
			auto Rn(match(19, "1101"));
			if (match(25, "0000x0")) {
				std::cout << "STMDA\n";
			}
			else if (match(25, "0000x1")) {
				std::cout << "LDMDA\n";
			}
			else if (match(25, "0010x0")) {
				std::cout << "STM\n";
			}
			else if (match(25, "001001")) {
				std::cout << "LDM/LDMIA/LDMFD\n";
			}
			else if (match(25, "001011")) {
				if (!Rn) {
					std::cout << "LDM/LDMIA/LDMFD\n";
				} else 
					std::cout << "POP\n";
			}
			else if (match(25, "010000")) {
				std::cout << "STMDB\n";
			}
			else if (match(25, "010010")) {
				if (!Rn) {
					std::cout << "STMDB\n";
				} else 
					std::cout << "PUSH\n";
			}
			else if (match(25, "0100x1")) {
				std::cout << "LDMDB\n";
			}
			else if (match(25, "0110x0")) {
				std::cout << "STMIB\n";
			}
			else if (match(25, "0110x1")) {
				std::cout << "LDMIB\n";
			}
			else if (match(25, "0xx1x0")) {
				std::cout << "STM\n";
			}
			else if (match(25, "0xx1x1")) {
				std::cout << "LDM\n";
			}
			else if (match(25, "10xxxx")) {
				result += "B: 0b";
				// 23 -> 0 is the address
				unsigned i = 23;
				while (i--) {
					result += std::to_string(bits[i]);
				}
			}
			else if (match(25, "11xxxx")) {
				std::cout << "BL, BLX\n";
			}
		}
		else if (match(27, "11x")) {
			std::cout << "Coprocessor and FPU\n";
		}
		else {
			throw std::runtime_error("Unknown op1");
		}
	}
	else {
		std::cout << "simd instructions\n";
	}
	return result;
}

//std::string ARMOpcode::Process1() {
//
//
//
//	return "";
//}