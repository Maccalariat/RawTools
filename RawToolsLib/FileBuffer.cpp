#include "FileBuffer.h"


FileBuffer::FileBuffer(ProcessBlock& processBlock) {

	std::ifstream inputFile;

	// _processBlock = processBlock;
	inputFile.open(processBlock.filename, std::ios::binary | std::ios::in);
	if (inputFile.bad()) {
		processBlock.statusCode = processBlock.OK;
		processBlock.statusMessage.assign("problem opening the file. Terminal");
		inputFile.close();
		return;
		}
	inputFile.seekg(0);
	std::streampos begin = inputFile.tellg();
	inputFile.seekg(0, std::ios::end);
	std::streampos end = inputFile.tellg();

	if (end) {
		inputFile.seekg(0);
		memoryFile.resize(end);
		inputFile.read((char *) &memoryFile[0], end);
		}
	else {
		processBlock.statusCode = processBlock.BadFileName;
		processBlock.statusMessage.assign("the file has zero length. Terminal");
		inputFile.close();
		return;
		}

	inputFile.close();
	processBlock.bigEndian = getEndian();
	bigEndian = processBlock.bigEndian;
	}


FileBuffer::~FileBuffer() {
	}

bool FileBuffer::getEndian() {

	uint16_t endian = (memoryFile[0] << 8) | memoryFile[1];

	if (endian == 0x4949) { // 'II'
		return false;
		}
	else {
		if (endian == 0x4D4D) { // 'MM'
			return true;
			}
		}
	return false;
	}


// given an offset, return the endian-correct unit16 value
uint16_t FileBuffer::getUint16(const size_t offset) {
	if (bigEndian) {
		return ((memoryFile[offset] << 8) | memoryFile[offset + 1]);
		}
	else {
		return ((memoryFile[offset + 1] << 8) | memoryFile[offset]);
		}
	}

// given an offset, return the endian-correct unit32 value
uint32_t FileBuffer::getUint32(const size_t offset) {
	uint32_t fValue = (memoryFile[offset] << 24 |
					   memoryFile[offset + 1] << 16 |
					   memoryFile[offset + 2] << 8) |
		memoryFile[offset + 3];

	if (bigEndian) {
		return fValue;
		}
	else {
		return _byteswap_ulong(fValue);
		}
	}

unsigned char FileBuffer::getUChar(const size_t offset) {
	return 0;
	}

