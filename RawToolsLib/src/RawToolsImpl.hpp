//
// Created by Hans on 17/03/2017.
//

#ifndef PROJECT__RAWTOOLS_H_H
#define PROJECT__RAWTOOLS_H_H

#include "../include/RawTools.hpp"
#include "FileMetaData.hpp"
#include "FileBuffer.hpp"
#include "TiffFile.hpp"
#include <string>
#include <memory>

class RawTools::RawToolsImpl
{
  public:
  	RawToolsImpl();
    void setFile(std::string& fileName);
    void getMetaData();
    void getBeyer();
    void getInterpolated();
    void getPostProcesed();
    void writeFile(const std::string& fileName);
    void close_file();

  private:
    ///////
    std::string _fileName;
    bool bigEndian;
    std::vector<unsigned char> *memoryFile;
    FileBuffer *_fileBuffer;
    FileMetaData *_fileMetaData;
    void log(std::string message);
    std::vector<uint16_t> beyerMatrix;
};

#endif //PROJECT__RAWTOOLS_H_H
