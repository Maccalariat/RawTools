//
// Created by hans on 3/04/17.
//

#include "TiffFile.hpp"

TiffFile::TiffFile(const std::string &fileName, const FileMetaData &metadata) : metaData(metadata)
{
    //outputFile->open(fileName, std::ofstream::out | std::ofstream::binary);
    outputFile = std::make_unique<std::ofstream>();
    try {
        outputFile->open(fileName, std::ofstream::out | std::ofstream::binary);
    } catch (...) {
        // TODO do correct catch, not lazy catch-all
        std::cout << "exception opening file for output: " << fileName << std::endl;
        return;
    }
    std::cout << "opened " << fileName << " for output" << std::endl;
}

void TiffFile::close_file()
{
    outputFile->close();
    outputFile.release();
    std::cout << "closed output file: " << std::endl;
}

void TiffFile::write_file()
{
    if (metaData.bigEndian) {
        outputFile->write("MM", sizeof(uint16_t ));
    } else {
        outputFile->write("II", sizeof(uint16_t ));
    }
    outputFile->write(reinterpret_cast<const char *>(&magic_number), sizeof(magic_number));
    outputFile->write(reinterpret_cast<const char *>(&first_offset), sizeof(first_offset));
    outputFile->write(reinterpret_cast<const char *>(&de_count), sizeof(de_count));
    outputFile->write(reinterpret_cast<const char *>(&ImageWidth), sizeof(uint16_t));
    outputFile->write(reinterpret_cast<const char *>(&SHORT), sizeof(uint16_t));
    outputFile->write(reinterpret_cast<const char *>(&ONE), sizeof(uint16_t));
    outputFile->write(reinterpret_cast<const char *>(&metaData.raw_ifd.width), sizeof(uint32_t));

    close_file();
}
