#pragma once
#include <string>
#include <vector>

class ProcessBlock {
    public:
    ProcessBlock();
    ~ProcessBlock();

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

    bool verbose = false;
    statusCode_e statusCode = Unitialised;
    std::string statusMessage{ "" };
    std::string filename{ "" };
    std::string make{ "" };
    std::string model{ "" };
    uint8_t orientation = 0;
    std::string timestamp{ "" };
    std::string artist{ "" };
    std::vector<unsigned char>* memoryFile;
    bool bigEndian;
    interpolationMethod_e interpolationMethod;
    std::vector<uint16_t>* Red;
    std::vector<uint16_t>* Green;
    std::vector<uint16_t>* Green1;
    std::vector<uint16_t>* Blue;
    std::vector<uint16_t>* interpolatedImage;
    std::string imageDescription;
    uint16_t sony_offset;
    uint16_t sony_length;
    uint16_t sony_key;

    // dcraw variables - function to be determined
    unsigned tiff_bps = 0;
    float iso_speed = 0.0;
    std::vector<uint16_t> cblack{ 4102, 0 };
    unsigned int maximum;
    std::vector<uint16_t> sony_curve;
    std::vector<uint16_t> curve{ 0,0,0,0,0,4095 };

    };