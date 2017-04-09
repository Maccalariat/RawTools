//
// Created by hans on 3/04/17.
//

#include "TiffFile.hpp"

TiffFile::TiffFile(const std::string &fileName, FileMetaData metadata) {
    outputFile->open(fileName, std::ofstream::binary);
}


void TiffFile::close_file() {
    outputFile->close();
    outputFile = nullptr;
}


void TiffFile::write_file() {
    outputFile->write(reinterpret_cast<const char *>(&byte_order), sizeof(byte_order));
    outputFile->write(reinterpret_cast<const char *>(&magic_number), sizeof(magic_number));
    outputFile->write(reinterpret_cast<const char *>(&first_offset), sizeof(first_offset));
    outputFile->write(reinterpret_cast<const char *>(1), sizeof(uint16_t));

    close_file();
}

