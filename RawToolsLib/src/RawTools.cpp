#include "RawToolsImpl.hpp"

////////////////////////////////////////////////////////////////////////////////
// API Definitions
////////////////////////////////////////////////////////////////////////////////

RawTools::RawTools() : pImpl(std::make_unique<RawToolsImpl>()) {}

RawTools::~RawTools() = default;

RawTools::RawTools(RawTools &&) noexcept = default;

RawTools &RawTools::operator=(RawTools &&) noexcept = default;

// pass through of calls
void RawTools::setFile(std::string &fileName) { pImpl->setFile(fileName); }

void RawTools::parseMetaData() { pImpl->parseMetaData(); }

std::vector<uint16_t> RawTools::getBeyer() { return pImpl->getBeyer(); }

void RawTools::writeFile(const std::string &fileName, const std::vector<uint16_t> &image) {
    pImpl->writeFile(fileName, image);
}

void RawTools::close_file() { pImpl->close_file(); }

std::vector<uint16_t> RawTools::getInterpolated(const int pattern, const std::vector<uint16_t> &inputImage) {
    return pImpl->getInterpolated(pattern, inputImage);
}

void RawTools::getPostProcesed() {
    pImpl->getPostProcessed();
}

///////////////////////////////////////////////////////////////////////////////
// Implementation Definitions
///////////////////////////////////////////////////////////////////////////////
RawTools::RawToolsImpl::RawToolsImpl() {
    createGamma(1.8);
}

void RawTools::RawToolsImpl::setFile(std::string &fileName) {
    _fileName = fileName;
}

void RawTools::RawToolsImpl::parseMetaData() {
    _fileBuffer = new FileBuffer(_fileName);
    _fileMetaData = new FileMetaData(*_fileBuffer);
}

std::vector<uint16_t> RawTools::RawToolsImpl::getBeyer() {
    log(std::string("in getBeyer"));

    beyerMatrix.resize(_fileMetaData->raw_ifd.ImageHeight *
                       _fileMetaData->raw_ifd.ImageWidth);

    // right now, I assume it is for a sony
    //	if (_fileMetaData->make == "SONY") {

    uint32_t val;
    uint16_t max, min, imax, imin, sh;
    std::vector<uint16_t> valueC(14);

    // walk through the filebuffer in 32-byte chunks and interleave
    // them into the output vector
    // ignore rows/columns since the algorithm is cfa structure agnostic

    size_t bmIndex = 0; // index into beyerMatrix
    size_t rawBegin = _fileMetaData->raw_ifd.offset;
    size_t chunk = rawBegin;

    while (bmIndex <= beyerMatrix.size() - 1) {
        // get the first group of max/min and offsets
        // 255 * (Red(colour)   / 255) ^ gammaCorrection
        val = _fileBuffer->getUint32(chunk);
        max = static_cast<uint16_t>(0x7FF & val);         // maximum value
        min = static_cast<uint16_t>(0x7FF & (val >> 11)); // minimum value
        imax = static_cast<uint16_t>(0x0F & (val >> 22));
        imin = static_cast<uint16_t>(0x0F & (val >> 26));
        // calculate the scale factor. (next largest power of 2) TODO: figure this code out
        for (sh = 0; sh < 4 && 0x80 << sh <= max - min; sh++);
        // now get the delta (7-bit) bytes
        val = _fileBuffer->getUint32(chunk + 3);
        valueC[0] = static_cast<uint16_t>((((val >> 6) & 0x7F) << sh) + min);
        valueC[1] = static_cast<uint16_t>((((val >> 13) & 0x7F) << sh) + min);
        valueC[2] = static_cast<uint16_t>((((val >> 20) & 0x7F) << sh) + min);
        val = _fileBuffer->getUint32(chunk + 6);
        valueC[3] = static_cast<uint16_t>((((val >> 3) & 0x7F) << sh) + min);
        valueC[4] = static_cast<uint16_t>((((val >> 10) & 0x7F) << sh) + min);
        valueC[5] = static_cast<uint16_t>((((val >> 17) & 0x7F) << sh) + min);
        valueC[6] = static_cast<uint16_t>((((val >> 24) & 0x7F) << sh) + min);
        val = _fileBuffer->getUint32(chunk + 9);
        valueC[7] = static_cast<uint16_t>((((val >> 7) & 0x7F) << sh) + min);
        valueC[8] = static_cast<uint16_t>((((val >> 14) & 0x7F) << sh) + min);
        valueC[9] = static_cast<uint16_t>((((val >> 21) & 0x7F) << sh) + min);
        val = _fileBuffer->getUint32(chunk + 12);
        valueC[10] = static_cast<uint16_t>((((val >> 4) & 0x7F) << sh) + min);
        valueC[11] = static_cast<uint16_t>((((val >> 11) & 0x7F) << sh) + min);
        valueC[12] = static_cast<uint16_t>((((val >> 18) & 0x7F) << sh) + min);
        valueC[13] = static_cast<uint16_t>((((val >> 25) & 0x7F) << sh) + min);

        //) we've got the Delta bytes, now merge them into the final vector
        for (size_t i = 0, vIdx = 0; i < 16; ++i, bmIndex += 2) {
            if (i == imax) {
                beyerMatrix[bmIndex] = max;
                continue;
            }
            if (i == imin) {
                beyerMatrix[bmIndex] = min;
                continue;
            }
            beyerMatrix[bmIndex] = valueC[vIdx++];
        }
        // reset the index for second interleave
        bmIndex = bmIndex - 31;

        // get the second group of max/min and offsets
        chunk += 16;
        val = _fileBuffer->getUint32(chunk);
        max = static_cast<uint16_t>(0x7FF & val);         // maximum value
        min = static_cast<uint16_t>(0x7FF & (val >> 11)); // minimum value
        imax = static_cast<uint16_t>(0x0F & (val >> 22));
        imin = static_cast<uint16_t>(0x0F & (val >> 26));
        // calculate the scale factor. (next largest power of 2)
        // TODO figure this code out
        for (sh = 0; sh < 4 && 0x80 << sh <= max - min; sh++);
        // now get the delta (7-bit) bytes
        val = _fileBuffer->getUint32(chunk + 3);
        valueC[0] = static_cast<uint16_t>((((val >> 6) & 0x7F) << sh) + min);
        valueC[1] = static_cast<uint16_t>((((val >> 13) & 0x7F) << sh) + min);
        valueC[2] = static_cast<uint16_t>((((val >> 20) & 0x7F) << sh) + min);
        val = _fileBuffer->getUint32(chunk + 6);
        valueC[3] = static_cast<uint16_t>((((val >> 3) & 0x7F) << sh) + min);
        valueC[4] = static_cast<uint16_t>((((val >> 10) & 0x7F) << sh) + min);
        valueC[5] = static_cast<uint16_t>((((val >> 17) & 0x7F) << sh) + min);
        valueC[6] = static_cast<uint16_t>((((val >> 24) & 0x7F) << sh) + min);
        val = _fileBuffer->getUint32(chunk + 9);
        valueC[7] = static_cast<uint16_t>((((val >> 7) & 0x7F) << sh) + min);
        valueC[8] = static_cast<uint16_t>((((val >> 14) & 0x7F) << sh) + min);
        valueC[9] = static_cast<uint16_t>((((val >> 21) & 0x7F) << sh) + min);
        val = _fileBuffer->getUint32(chunk + 12);
        valueC[10] = static_cast<uint16_t>((((val >> 4) & 0x7F) << sh) + min);
        valueC[11] = static_cast<uint16_t>((((val >> 11) & 0x7F) << sh) + min);
        valueC[12] = static_cast<uint16_t>((((val >> 18) & 0x7F) << sh) + min);
        valueC[13] = static_cast<uint16_t>((((val >> 25) & 0x7F) << sh) + min);

        //) we've got the Delta bytes, now merge them into the final vector
        for (size_t i = 0, vIdx = 0; i < 16; ++i, bmIndex += 2) {
            if (i == imax) {
                beyerMatrix[bmIndex] = max;
                continue;
            }
            if (i == imin) {
                beyerMatrix[bmIndex] = min;
                continue;
            }
            beyerMatrix[bmIndex] = valueC[vIdx++];
        }
        bmIndex -= 1;
        chunk += 16;
    }
    std::cout << "processed beyer" << std::endl;
    return beyerMatrix;
}

std::vector<uint16_t> RawTools::RawToolsImpl::getInterpolated(const int pattern,
                                                              const std::vector<uint16_t> &inputImage) {
    // basic interpolation to drive the process.
    // get smarter later
    auto image = std::vector<uint16_t>();
    if (pattern == 0) {

    }
    if (pattern == 0) { // nearest neighbour
        image.resize(inputImage.size() * 3 * 2);
        nearest_neighbour(image);
    }
    return image;
}

void RawTools::RawToolsImpl::getPostProcessed() {
    return;
}

void RawTools::RawToolsImpl::writeFile(const std::string &fileName, const std::vector<uint16_t> &image) {
    auto tiff_file = std::make_unique<TiffFile>(fileName, *_fileMetaData, image);
    tiff_file->write_file();
}

void RawTools::RawToolsImpl::close_file() {}

void RawTools::RawToolsImpl::log(const std::string message) {
    std::cout << message.c_str() << std::endl;
}

void
RawTools::RawToolsImpl::nearest_neighbour(std::vector<uint16_t> &image) {
    // my simple first-implementation of nearest neighbour demosaicing.
    // I assume an GBG
    //             RGR input matrix pattern
    // And produce a RGB triplet output array

    // process the beyerMatix to gamma-scale it into GBeyerMatrix
    std::vector<uint16_t> GbeyerMatrix(beyerMatrix);
    for (size_t i = 0; i < GbeyerMatrix.size(); i++) {
        GbeyerMatrix[i] = gammaTable[GbeyerMatrix[i]];
    }
    auto rowCount = _fileMetaData->raw_ifd.ImageHeight;
    auto columnCount = _fileMetaData->raw_ifd.ImageWidth;
    size_t byteswritten = 0;
    size_t imagePos = 0;
    for (uint32_t row = 0; row < rowCount; row++) {
        auto cRow = row * columnCount;
        if (row & 0x1) { // odd rowCount -> RGRGRG
            for (uint32_t pos = cRow; pos < cRow + columnCount;) {
                auto prevRow = pos - columnCount;
                //std::cout << std::endl;
                //std::cout << row << " , " << column;
                //std::cout << " R";
                image.at(imagePos++) = GbeyerMatrix.at(pos);        // R
                image.at(imagePos++) = GbeyerMatrix.at(pos + 1);        // G
                image.at(imagePos++) = GbeyerMatrix.at(prevRow + 1);    // B
                //std::cout << " G";
                pos++;
                image.at(imagePos++) = GbeyerMatrix.at(pos - 1);  // R
                image.at(imagePos++) = GbeyerMatrix.at(pos);        // G
                image.at(imagePos++) = GbeyerMatrix.at(prevRow + 1);    // B
                pos++;
                byteswritten += 12;
            }
        } else { // even rowCount -> GBGBGB
            for (uint32_t pos = cRow; pos < cRow + columnCount;) {
                auto nextRow = pos + columnCount;
                image.at(imagePos++) = GbeyerMatrix.at(nextRow);     // R
                image.at(imagePos++) = GbeyerMatrix.at(pos);     // G
                image.at(imagePos++) = GbeyerMatrix.at(pos + 1); // B
                pos++;
                // next pixel "B"
                image.at(imagePos++) = GbeyerMatrix.at(nextRow);    // R
                image.at(imagePos++) = GbeyerMatrix.at(pos - 1);        // G
                image.at(imagePos++) = GbeyerMatrix.at(pos);    // B
                pos++;
                byteswritten += 12;
            }
        }
    }
    std::cout << "image byte size = " << byteswritten << std::endl;
    std::cout << "image buffer size = " << image.size() << std::endl;
}

void RawTools::RawToolsImpl::createGamma(double d) {
    // do the gamma calculations
    const double gammaCorrection = 1 / d;
    const uint16_t mVal = std::numeric_limits<uint16_t>::max();
    gammaTable.resize(std::numeric_limits<uint16_t>::max());
    for (auto i = 0; i < mVal; i++) {
        gammaTable[i] = pow(mVal * (i / mVal), gammaCorrection);
    }
}


