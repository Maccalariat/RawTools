//
// Created by hans on 3/04/17.
//

#include "TiffFile.hpp"

TiffFile::TiffFile(const std::string &fileName) {
    outputFile->open(fileName, std::ofstream::binary);

}

void TiffFile::close_file() {
    outputFile->close();
};

