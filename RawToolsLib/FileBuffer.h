#pragma once
#include <fstream>
#include <vector>
#include <memory>
#include "ProcessBlock.h"


class FileBuffer  {
	public:
	std::vector<unsigned char> memoryFile;
	
	FileBuffer(ProcessBlock& processBlock);
	~FileBuffer();
	
	// given an offset, return the endian-correct unit16 value
	uint16_t getUint16(const size_t offset);
	uint32_t getUint32(const size_t offset);
	unsigned char getUChar(const size_t offset);

	std::vector<uint8_t> getBlock(const size_t offset);

	private:
    bool bigEndian;
    bool getEndian();

};
