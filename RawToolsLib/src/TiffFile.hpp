//
// Created by hans on 3/04/17.
//

#ifndef PROJECT_TIFFFILE_HPP
#define PROJECT_TIFFFILE_HPP

#include <fstream>
#include <ostream>
#include "FileMetaData.hpp"


class TiffFile {
public:

    uint16_t byte_order{0x4949};
    uint16_t magic_number{42};
    uint32_t first_offset{8};

    uint16_t ImageWidth;
    uint16_t ImageLength;
    uint16_t BitsPerSample;
    uint16_t Compression;
    uint16_t PhotometricInterpretation;
    uint16_t StripOffsets;
    uint16_t RowsPerStrip;
    uint16_t StripByteCounts;
    float XResolution;
    float YResolution;

    std::ofstream *outputFile;

    TiffFile(const std::string &fileName, FileMetaData metaData);

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
};


#endif //PROJECT_TIFFFILE_HPP
