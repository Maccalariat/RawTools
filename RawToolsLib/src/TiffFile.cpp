//
// Created by hans on 3/04/17.
//

#include "TiffFile.hpp"

TiffFile::TiffFile(const std::string &fileName, const FileMetaData &metadata) : metaData(metadata),
                                                                                tagVector(4, 0) {
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

void TiffFile::close_file() {
    outputFile->close();
    outputFile.release();
    std::cout << "closed output file: " << std::endl;
}

void TiffFile::write_file() {
    if (metaData.bigEndian) {
        outputFile->write("MM", sizeof(uint16_t));
    } else {
        outputFile->write("II", sizeof(uint16_t));
    }
    outputFile->write(reinterpret_cast<const char *>(&magic_number), sizeof(magic_number));
    outputFile->write(reinterpret_cast<const char *>(&first_offset), sizeof(first_offset));
    outputFile->write(reinterpret_cast<const char *>(&de_count), sizeof(de_count));
    writeTag(ImageWidthTag, SHORT, ONE, metaData.raw_ifd.width);
    writeTag(ImageLengthTag, SHORT, ONE, metaData.raw_ifd.height);
    writeTag(CompressionTag, SHORT, ONE, ONE); // force uncompressed right now
    writeTag(PhotometricInterpretationTag, SHORT, ONE, ONE); // TODO figure this out - forced to BlackIsZero
    writeTag(StripOffsetsTag, SHORT, ONE, sizeof(magic_number) +
    sizeof(first_offset) +
    sizeof(de_count)+
    120);
    writeTag(RowsPerStripTag, SHORT, ONE, metaData.raw_ifd.rowsPerStrip);
    writeTag(StripByteCountsTag, SHORT, ONE, metaData.raw_ifd.stripByteCount);
    writeTag(XResolutionTag, SHORT, ONE, metaData.raw_ifd.xResolution);
    writeTag(YResolutionTag, SHORT, ONE, metaData.raw_ifd.yResolution);
    writeTag(ResolutionUnitTag, SHORT, ONE, metaData.raw_ifd.resolutionUnit);
    outputFile->write(reinterpret_cast<const char*>(&metaData.Green), sizeof(metaData.Green));


    close_file();
}

void TiffFile::writeTag(const uint16_t &tag, const uint16_t &type, const uint32_t &count, const uint32_t &value) {
    outputFile->write(reinterpret_cast<const char *>(&tag), 2);
    outputFile->write(reinterpret_cast<const char *>(&type), 2);
    outputFile->write(reinterpret_cast<const char *>(&count), 4);
    outputFile->write(reinterpret_cast<const char *>(&value), 4);
}
