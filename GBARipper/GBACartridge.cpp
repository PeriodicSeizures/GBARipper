#include <iostream>
#include "GBACartridge.h"

void GBACartridge::Process() {

	//char buf[12];
	std::vector<char> vec(12);

	auto buf(vec.data());

	bytes.Read(buf, 4);
	entryPoint = std::make_unique<ARMOpcode>(buf);

	bytes.offset += 156;

	bytes.Read(buf, 12);
	this->h_title = std::string(buf, 12);

	bytes.Read(buf, 4);
	this->h_code = std::string(buf, 4);

	bytes.Read(buf, 2);
	this->h_makerCode = std::string(buf, 2);

	// fixed value
	bytes.offset += 1;

	// unit code
	bytes.Read(&h_mainUnitCode, 1);

	// device type
	bytes.offset += 1;

	// reserved area
	bytes.offset += 7;

	// software version
	bytes.Read(&h_softwareVersion, 1);

	// complement check
	bytes.offset += 1;

	//reserved for multiboot
	bytes.offset += 2;

	// entry point
	//bytes.Read(entryPoint, 4);	// ARM opcode
	bytes.offset += 4;

	// boot mode
	bytes.Read(&bootMode, 1);

	// slave id number
	bytes.offset += 1;

	// unused
	bytes.offset += 26;

	// joybus mode entry point
	bytes.offset += 4;			// ARM opcode

	/**
	* 
	*/

}

void GBACartridge::Print() {
	std::cout << entryPoint->Process1() << "\n";
	//std::cout << "Entry point: " << std::string
	std::cout << "Title: " << h_title << std::endl;
	std::cout << "Game Code: " << h_code << std::endl;
	std::cout << "Maker Code: " << h_makerCode << std::endl;
	std::cout << "Unit Code: " << h_mainUnitCode << std::endl;
	std::cout << "Version: " << h_softwareVersion << std::endl;
}