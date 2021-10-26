#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include "GBACartridge.h"

int main() {

	std::ifstream gbafile;

	gbafile.open("GBACRAFT_3DSage_v1-0.gba", std::ios::binary);
	if (!gbafile.is_open())
		throw std::runtime_error("Couldnt open file");

	gbafile.seekg(0, gbafile.end);
	int length = gbafile.tellg();
	gbafile.seekg(0, gbafile.beg);

	std::vector<char> buf(length);

	gbafile.read(buf.data(), length);

	GBACartridge cartridge(buf);
	cartridge.Process();

	cartridge.Print();

	return 0;
}