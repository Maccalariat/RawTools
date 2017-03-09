#pragma once
#include <iostream>
#include "FileMetaData.h"
#include "ProcessBlock.h"
#include "FileBuffer.h"

class RawTools {
	/// the public API for RawTools
	/// This is a 'primitive' collection of atomic api calls on an unsuspecting raw file
	/// The typical processing sequence is:
	/// 1. getMetaData (this is required as the first step
	/// 2. GetBeyer (this retrieves the colour channel information
	/// 3. getInterpolated (this interpolates the image)
public:
	//////
	ProcessBlock* processBlock;
	RawTools();
	void getMetaData();
	void getBeyer();
	void getInterpolated();
	void getPostProcesed();
	~RawTools();

private:
	///////
	FileBuffer* _fileBuffer;
	FileMetaData* _fileMetaData;
	void log(std::string message);
	std::vector<uint16_t>beyerMatrix;
		

};
