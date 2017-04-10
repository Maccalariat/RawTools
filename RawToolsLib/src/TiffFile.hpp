//
// Created by hans on 3/04/17.
//

#ifndef PROJECT_TIFFFILE_HPP
#define PROJECT_TIFFFILE_HPP

#include <fstream>
#include <ostream>
#include "FileMetaData.hpp"

class TiffFile
{
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
    const uint16_t ImageWidth = 0x100;
    const uint16_t SHORT = 3;
    const uint16_t ONE = 1;

    std::unique_ptr<std::ofstream> outputFile;
    const FileMetaData& metaData;

};

#endif //PROJECT_TIFFFILE_HPP
