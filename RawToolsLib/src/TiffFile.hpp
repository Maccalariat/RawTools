//
// Created by hans on 3/04/17.
//

#ifndef PROJECT_TIFFFILE_HPP
#define PROJECT_TIFFFILE_HPP

#include <fstream>
// #include <stdint-gcc.h>

class TiffFile {
public:
    struct tiff_header {
        uint16_t byte_order {0x4949};
        uint16_t magic_number {42};
        uint32_t first_offset {};
    };
    std::ofstream * outputFile;

    TiffFile(const std::string& fileName);
    void close_file();
};


#endif //PROJECT_TIFFFILE_HPP
