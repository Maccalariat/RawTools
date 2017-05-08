//
// Created by Hans on 17/03/2017.
//

#ifndef PROJECT__RAWTOOLS_H_H
#define PROJECT__RAWTOOLS_H_H

#include "../include/RawTools.hpp"
#include "FileBuffer.hpp"
#include "FileMetaData.hpp"
#include "TiffFile.hpp"
#include <memory>
#include <string>
#include <list>
#include <math.h>

class RawTools::RawToolsImpl {
public:
    RawToolsImpl();

    void setFile(std::string &fileName);

    void parseMetaData();

    std::vector<uint16_t> getBeyer();

    std::vector<uint16_t> getInterpolated(const int pattern, const std::vector<uint16_t> &inputImage);

    void getPostProcessed();

    void writeFile(const std::string &fileName);

    void close_file();

    private:
    ///////
    std::string _fileName;
    bool bigEndian;
    std::vector<unsigned char> *memoryFile;
    FileBuffer *_fileBuffer;
    FileMetaData *_fileMetaData;
    std::vector<uint16_t> beyerMatrix;


    void log(std::string message);

    void gamma_curve(double pwr, double ts, int mode, int imax);
    void nearest_neighbour(std::vector<uint16_t> &image);


};

#endif // PROJECT__RAWTOOLS_H_H
