#ifndef PROJECT_RAWTOOLS_H_H
#define PROJECT_RAWTOOLS_H_H

#include <string>
#include <memory>
#include <vector>
#include <limits>
#include <algorithm>

/// the public API for RawTools
/// This is a 'primitive' collection of atomic api calls on an unsuspecting raw
/// file
/// The typical processing sequence is:
/// 1. getMetaData (this is required as the first step
/// 2. GetBeyer (this retrieves the colour channel information
/// 3. getInterpolated (this interpolates the image)
class RawTools {
public:
    RawTools();

    ~RawTools();

    RawTools(RawTools &&op) noexcept;

    RawTools &operator=(RawTools &&op) noexcept;

    // public methods
    void setFile(std::string &fileName);

    void parseMetaData();

    std::vector<uint16_t> getBeyer();

    std::vector<uint16_t> getInterpolated(const int pattern, const std::vector<uint16_t> &inputImage);

    void getPostProcesed();

    void writeFile(const std::string &fileName, const std::vector<uint16_t> &image);

    void close_file();

private:
    class RawToolsImpl; // forward declaration
    std::unique_ptr<RawToolsImpl> pImpl;

    const float gammaCorrection = 1 / 1.8;
    static std::vector<uint16_t>gammaTable;
};

#endif // PROJECT_RAWTOOLS_H_H
