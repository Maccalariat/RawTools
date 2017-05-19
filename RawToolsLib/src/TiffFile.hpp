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

    TiffFile(const std::string &fileName, const FileMetaData &metaData, const std::vector<uint16_t> &imageData);

    TiffFile(const FileMetaData &metaData);

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
    const uint16_t de_count = 15;
    const uint16_t SubfileTypeTag = 0x0FE;
    const uint16_t ImageWidthTag = 0x100;
    const uint16_t ImageLengthTag = 0x101;
    const uint16_t BitsPerSampleTag = 0x102;
    const uint16_t CompressionTag = 0x103;
    const uint16_t PhotometricInterpretationTag = 0x106;
    const uint16_t StripOffsetsTag = 0x111;
    const uint16_t RowsPerStripTag = 0x116;
    const uint16_t StripByteCountsTag = 0x117;
    const uint16_t XResolutionTag = 0x11A;
    const uint16_t YResolutionTag = 0x11B;
    const uint16_t ResolutionUnitTag = 0x128;
    const uint16_t SamplesPerPixelTag = 0x115;
    const uint16_t OrientationTag = 0x112;
    const uint16_t PlanarConfigurationTag = 0x11C;
    const uint16_t BYTE = 1;
    const uint16_t ASCII = 2;
    const uint16_t SHORT = 3;
    const uint16_t LONG = 4;
    const uint16_t RATIONAL = 5;
    const uint16_t SBYTE = 6;
    const uint16_t UNDEFINED = 7;
    const uint16_t SSHORT = 8;
    const uint16_t SLONG = 9;
    const uint16_t SRATIONAL = 10;
    const uint16_t FLOAT = 11;
    const uint16_t DOUBLE = 12;
    uint16_t valUint16T = 0;
    uint32_t valueUint32T = 0;

    const uint16_t ZERO = 0;
    const uint16_t TWO = 2;
    const uint16_t ONE = 1;
    const uint16_t THREE = 3;
    const uint16_t FOUR = 4;
    const uint16_t FIVE = 5;
    const uint16_t SIX = 6;
    const uint16_t SEVEN = 7;
    const uint16_t EIGHT = 8;
    const uint16_t NINE = 9;
    const uint16_t TEN = 10;
    const uint16_t ELEVEN = 11;
    const uint16_t TWELVE = 12;
    const uint16_t THIRTEEN = 13;
    const uint16_t FOURTEEN = 14;
    const uint16_t FIFTEEN = 15;
    const uint16_t SIXTEEN = 16;

    // constructor-initialized items.
    // the order matters for -Wreorder
    const FileMetaData &metaData;
    std::vector<uint8_t> tagVector;
    const std::vector<uint16_t> &imageData;

    std::unique_ptr<std::ofstream> outputFile;

    void writeTag(const uint16_t &tag, const uint16_t &type, const uint32_t &count, const uint32_t &value);

};

#endif //PROJECT_TIFFFILE_HPP
