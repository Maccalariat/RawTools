#pragma once

#include <iostream>
#include <map>
#include <algorithm>
#include "FileBuffer.hpp"


///!
/// @brief holds the metadata for an image file
/// @param fileBuffer the fileBuffer class that holds the file in memory
/// @TODO I think processBlock and this file overlap in function
class FileMetaData {
private:
    ///////
    std::string filename;
    ///!
    /// @brief the structure of an ifd (with critical information only)
    struct tiff_ifd_s {
        size_t file_offset = 0;
        uint16_t ifd_type = 0;
        uint32_t width = 0;
        uint32_t height = 0;
        int bps = 0;
        int comp = 0;
        int phint = 0;
        size_t offset = 0;
        int flip = 0;
        int samples = 0;
        uint32_t stripByteCount = 0;
        int tile_width = 0;
        int tile_length = 0;
        float shutter = 0;
        uint32_t sonyRawFileType = 0;
        uint32_t rowsPerStrip = 0;
        uint32_t xResolution = 0;
        uint32_t yResolution = 0;
        uint32_t resolutionUnit = 0;
    };

    enum interpolationMethod_e {
        none = 0,
        AHD = 1
    };
    enum statusCode_e {
        Unitialised = 0,
        OK = 1,
        BadFileName = -1,
        NotRawFile = -2,
        Broken = -9
    };

    void parseFile();

    uint32_t processIFD(const size_t offset);

    void processDE(const size_t offset, tiff_ifd_s &ifd);

    FileBuffer &_fileBuffer;

    struct DE_s {
        uint16_t tag;
        uint16_t tag_type;
        uint32_t tag_value;
        uint32_t tag_value_offset;
    };

    std::vector<tiff_ifd_s> tiff_ifd;

    union twoBytes_u {
        char bytesArray[2];
        uint16_t twoBytesUint;
    } twoBytes;

    const std::vector<std::string> corp{"AgfaPhoto", "Canon", "Casio", "Epson", "Fujifilm",
                                        "Mamiya", "Minolta", "Motorola", "Kodak", "Konica", "Leica", "Nikon", "Nokia",
                                        "Olympus",
                                        "Ricoh", "Pentax", "Phase One", "Samsung", "Sigma", "Sinar", "Sony"};


    const std::map<uint16_t, std::string> compression{
            {1,     "COMPRESSION_NONE"},
            {2,     "COMPRESSION_CCITTRLE"},
            {3,     "COMPRESSION_CCITTFAX3_ COMPRESSION_CCITT_T4"},
            {4,     "COMPRESSION_CCITTFAX4_ COMPRESSION_CCITT_T4"},
            {5,     "COMPRESSION_LZW"},
            {6,     "COMPRESSION_OJPEG"},
            {7,     "COMPRESSION_JPEG"},
            {32766, "COMPRESSION_NEXT"},
            {32771, "COMPRESSION_CCITTRLEW"},
            {32773, "COMPRESSION_PACKBITS"},
            {32809, "COMPRESSION_THUNDERSCAN"},
            {32895, "COMPRESSION_IT8CTPAD"},
            {32896, "COMPRESSION_IT8LW"},
            {32897, "COMPRESSION_IT8MP"},
            {32898, "COMPRESSION_IT8BL"},
            {32908, "COMPRESSION_PIXARFILM"},
            {32909, "COMPRESSION_PIXARLOG"},
            {32946, "COMPRESSION_DEFLATE"},
            {8,     "COMPRESSION_ADOBE_DEFLATE"},
            {32947, "COMPRESSION_DCS"},
            {34661, "COMPRESSION_JBIG"},
            {34676, "COMPRESSION_SGILOG"},
            {34677, "COMPRESSION_SGILOG24"},
            {34712, "COMPRESSION_JP2000"}
    };
    //////
public:
    //////
    FileMetaData(FileBuffer &fileBuffer);

    ~FileMetaData();

    bool bigEndian;
    tiff_ifd_s raw_ifd;

    bool verbose = false;
    statusCode_e statusCode = Unitialised;
    std::string statusMessage{""};
    std::string make{""};
    std::string model{""};
    uint8_t orientation = 0;
    std::string timestamp{""};
    std::string artist{""};

    interpolationMethod_e interpolationMethod;
    std::vector<uint16_t> *Red;
    std::vector<uint16_t> *Green;
    std::vector<uint16_t> *Green1;
    std::vector<uint16_t> *Blue;
    std::vector<uint16_t> *interpolatedImage;
    std::string imageDescription;
    uint16_t sony_offset;
    uint16_t sony_length;
    uint16_t sony_key;

    // dcraw variables - function to be determined
    unsigned tiff_bps = 0;
    float iso_speed = 0.0;
    std::vector<uint16_t> cblack{4102, 0};
    unsigned int maximum;
    std::vector<uint16_t> sony_curve;
    std::vector<uint16_t> curve{0, 0, 0, 0, 0, 4095};
};

/*!
@brief tagMap is a list of the tags that we are interested in
*/
const std::vector<uint16_t> tagMap{
        257, 256, 259,
};
