//
// Created by hans on 3/04/17.
//

#ifndef PROJECT_TIFFFILE_HPP
#define PROJECT_TIFFFILE_HPP

#include <fstream>
#include <ostream>
#include <vector>
#include "FileMetaData.hpp"

class TiffFile {
public:

    TiffFile(const std::string &fileName, const FileMetaData &metaData);

    /*!
* This is a hack to simply push out a file for diagnosis
*
*/
    void write_file();

    /*!
     * Close the file
     * Fails silently if file was not open
     */
    void close_file();

private:
    const uint16_t magic_number = 42;
    const uint32_t first_offset = 8;
    const uint16_t de_count = 11;
    const uint16_t ImageWidthTag = 0x100;
    const uint16_t ImageLengthTag = 0x101;
    const uint16_t CompressionTag = 0x103;
    const uint16_t PhotometricInterpretationTag = 0x106;
    const uint16_t StripOffsetsTag = 0x111;
    const uint16_t RowsPerStripTag = 0x116;
    const uint16_t StripByteCountsTag = 0x117;
    const uint16_t XResolutionTag = 0x11A;
    const uint16_t YResolutionTag = 0x11B;
    const uint16_t ResolutionUnitTag = 0x128;
    const uint16_t SHORT = 3;
    const uint16_t ONE = 1;


    std::vector<uint8_t> tagVector;

    std::unique_ptr<std::ofstream> outputFile;
    const FileMetaData &metaData;


    void writeTag(const uint16_t &tag, const uint16_t &type, const uint32_t &count, const uint32_t &value);
};

#endif //PROJECT_TIFFFILE_HPP
