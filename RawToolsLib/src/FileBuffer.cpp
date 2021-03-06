#include "FileBuffer.hpp"

FileBuffer::FileBuffer(std::string &fileName)
{
    std::ifstream inputFile;

    // _processBlock = processBlock;
    inputFile.open(fileName.c_str(), std::ios::binary | std::ios::in);
    if (inputFile.bad())
    {
        inputFile.close();
        return;
    }
    inputFile.seekg(0);
    inputFile.seekg(0, std::ios::end);
    std::streampos end = inputFile.tellg();

    if (end)
    {
        inputFile.seekg(0);
        memoryFile.resize(static_cast<size_t>(end));
        inputFile.read((char *)&memoryFile[0], end);
    }
    else
    {
        std::cout << "the file has zero length. Terminal" << std::endl;
        inputFile.close();
        return;
    }

    inputFile.close();
    bigEndian = getEndian();
}

FileBuffer::~FileBuffer()
{
}

bool FileBuffer::getEndian()
{

    uint16_t endian;
    endian = static_cast<uint16_t>((memoryFile[0] << 8) | memoryFile[1]);

    if (endian == 0x4949)
    { // 'II'
        return false;
    }
    else
    {
        if (endian == 0x4D4D)
        { // 'MM'
            return true;
        }
    }
    std::cout << "invalid endian indicator" << std::endl;
    return false;
}

// given an offset, return the endian-correct unit16 value
uint16_t FileBuffer::getUint16(const size_t offset)
{
    if (bigEndian)
    {
        return static_cast<uint16_t>(((memoryFile[offset] << 8) | memoryFile[offset + 1]));
    }
    else
    {
        return static_cast<uint16_t>(((memoryFile[offset + 1] << 8) | memoryFile[offset]));
    }
}

// given an offset, return the endian-correct unit32 value
uint32_t FileBuffer::getUint32(const size_t offset)
{
    uint32_t fValue = (memoryFile[offset] << 24 |
                       memoryFile[offset + 1] << 16 |
                       memoryFile[offset + 2] << 8) |
                      memoryFile[offset + 3];

    if (bigEndian)
    {
        return fValue;
    }
    else
    {
#ifdef _WIN32
        return _byteswap_ulong(fValue);
#else
        return __builtin_bswap32(fValue);
#endif
    }
}
