#pragma once
#include "ByteBuffer.hpp"
#include "ARMOpcode.h"

class GBACartridge
{
	ByteBuffer bytes;

	//char entryPoint[4];
	std::unique_ptr<ARMOpcode> entryPoint;
	std::string h_title;
	std::string h_code;
	std::string h_makerCode;
	char h_mainUnitCode;
	char h_softwareVersion;

	
	char bootMode;

public:
	GBACartridge(std::vector<char>& buf)
		: bytes({ buf }) {}

	void Process();

	void Print();
};

