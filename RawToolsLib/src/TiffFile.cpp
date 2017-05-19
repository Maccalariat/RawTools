//
// Created by hans on 3/04/17.
//

#include "TiffFile.hpp"

TiffFile::TiffFile(const std::string &fileName,
                   const FileMetaData &metadata,
                   const std::vector<uint16_t> &imageVector)
        : metaData(metadata),
          tagVector(4, 0),
          imageData(imageVector) {


    outputFile = std::make_unique<std::ofstream>();
    try {
        outputFile->open(fileName, std::ofstream::out | std::ofstream::binary);
    } catch (...) {
        // TODO do correct catch, not lazy catch-all
        std::cout << "exception opening file for output: " << fileName << std::endl;
        return;
    }

    std::cout << "opened " << fileName << " for output" << std::endl;
}

void TiffFile::close_file() {
    //outputFile->close();
    //outputFile.release();
    std::cout << "closed output file: " << std::endl;
}

void TiffFile::write_file() {
    uint32_t dataOffset = static_cast<uint32_t>(8 + 2 + (de_count * 12) + 4);
    if (metaData.bigEndian) {
        outputFile->write("MM", sizeof(uint16_t));
    } else {
        outputFile->write("II", sizeof(uint16_t));
    }
    outputFile->write(reinterpret_cast<const char *>(&magic_number), sizeof(magic_number));
    outputFile->write(reinterpret_cast<const char *>(&first_offset), sizeof(first_offset));
    outputFile->write(reinterpret_cast<const char *>(&de_count), sizeof(de_count));
// IFD0 Tags
    writeTag(SubfileTypeTag, LONG, ONE, ZERO);
    writeTag(ImageWidthTag, SHORT, ONE, metaData.raw_ifd.ImageWidth);
    writeTag(ImageLengthTag, SHORT, ONE, metaData.raw_ifd.ImageHeight);
    // writeTag(BitsPerSampleTag, SHORT, ONE, 16);
    writeTag(BitsPerSampleTag, SHORT, THREE, dataOffset);
    dataOffset += (sizeof(uint16_t) * 3);
    writeTag(XResolutionTag, RATIONAL, ONE, dataOffset);
    dataOffset += (sizeof(valueUint32T) * 2);
    writeTag(YResolutionTag, RATIONAL, ONE, dataOffset);
    dataOffset += (sizeof(valueUint32T) * 2);
    writeTag(PlanarConfigurationTag, SHORT, ONE, ONE);
    writeTag(ResolutionUnitTag, SHORT, ONE, TWO);
    writeTag(CompressionTag, SHORT, ONE, ONE); // force uncompressed right now
    writeTag(PhotometricInterpretationTag, SHORT, ONE, TWO);
    writeTag(StripOffsetsTag, SHORT, ONE, dataOffset);
    writeTag(OrientationTag, SHORT, ONE, 8);
    writeTag(SamplesPerPixelTag, SHORT, ONE, THREE);
    writeTag(RowsPerStripTag, LONG, ONE, metaData.raw_ifd.ImageHeight);
    writeTag(StripByteCountsTag, LONG, ONE, metaData.raw_ifd.ImageWidth * metaData.raw_ifd.ImageHeight * 6);
// four bytes of zero to end the IFD
    valueUint32T = 0;
    outputFile->write(reinterpret_cast<const char *>(&valueUint32T), sizeof(valueUint32T));
// that's all the tags folks, now write the data (in the correct order
// BitsPerSampleTag
    outputFile->write(reinterpret_cast<const char *>(&SIXTEEN), sizeof(uint16_t));
    outputFile->write(reinterpret_cast<const char *>(&SIXTEEN), sizeof(uint16_t));
    outputFile->write(reinterpret_cast<const char *>(&SIXTEEN), sizeof(uint16_t));
// XResolution
    valueUint32T = 300;
    outputFile->write(reinterpret_cast<const char *>(&valueUint32T), sizeof(valueUint32T));
    valueUint32T = 1;
    outputFile->write(reinterpret_cast<const char *>(&valueUint32T), sizeof(valueUint32T));
// YResolution
    valueUint32T = 300;
    outputFile->write(reinterpret_cast<const char *>(&valueUint32T), sizeof(valueUint32T));
    valueUint32T = 1;
    outputFile->write(reinterpret_cast<const char *>(&valueUint32T), sizeof(valueUint32T));
// now the image data

    outputFile->write(reinterpret_cast<const char *>(&imageData[0]),
                      metaData.raw_ifd.ImageWidth * metaData.raw_ifd.ImageHeight * 6);

    close_file();

}

void TiffFile::writeTag(const uint16_t &tag, const uint16_t &type,
                        const uint32_t &count, const uint32_t &value) {
    outputFile->write(reinterpret_cast<const char *>(&tag), 2);
    outputFile->write(reinterpret_cast<const char *>(&type), 2);
    outputFile->write(reinterpret_cast<const char *>(&count), 4);
    outputFile->write(reinterpret_cast<const char *>(&value), 4);
}

