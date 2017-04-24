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

void RawTools::getMetaData() { pImpl->getMetaData(); }

void RawTools::getBeyer() { pImpl->getBeyer(); }

void RawTools::writeFile(const std::string &fileName) {
  pImpl->writeFile(fileName);
}

void RawTools::close_file() { pImpl->close_file(); }

void RawTools::getInterpolated() {}

void RawTools::getPostProcesed() {}

///////////////////////////////////////////////////////////////////////////////
// Implementation Definitions
///////////////////////////////////////////////////////////////////////////////
RawTools::RawToolsImpl::RawToolsImpl() {}

void RawTools::RawToolsImpl::setFile(std::string &fileName) {
  _fileName = fileName;
}

void RawTools::RawToolsImpl::getMetaData() {
  _fileBuffer = new FileBuffer(_fileName);
  _fileMetaData = new FileMetaData(*_fileBuffer);
}

void RawTools::RawToolsImpl::getBeyer() {
  log(std::string("in getBeyer"));
  beyerMatrix.resize(_fileMetaData->raw_ifd.height *
                     _fileMetaData->raw_ifd.width);

  // right now, I assume it is for a sony
  //	if (_fileMetaData->make == "SONY") {

  uint32_t val;
  uint16_t max, min, imax, imin, sh;
  std::vector<uint16_t> valueC(13);

  // walk through the filebuffer in 32-byte chunks and interleave
  // them into the output vector
  // ignore rows/columns since the algorithm is cfa agnostic

  size_t bmIndex = 0; // index into beyerMatrix
  size_t rawBegin = _fileMetaData->raw_ifd.offset;
  size_t rawEnd = rawBegin + _fileMetaData->raw_ifd.stripByteCount -1;
  size_t chunk = 0;

  while (bmIndex <= rawEnd) {
    // get the first group of max/min and offsets
    val = _fileBuffer->getUint32(chunk);
    max = static_cast<uint16_t>(0x7FF & val);         // maximum value
    min = static_cast<uint16_t>(0x7FF & (val >> 11)); // minimum value
    imax = static_cast<uint16_t>(0x0F & (val >> 22));
    imin = static_cast<uint16_t>(0x0F & (val >> 26));
    // calculate the scale factor. (next largest power of 2)
    // TODO figure this code out
    for (sh = 0; sh < 4 && 0x80 << sh <= max - min; sh++)
      ;
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
    valueC[13] = static_cast<uint16_t>((((val >> 1) & 0x7F) << sh) + min);

    //) we've got the Delta bytes, now merge them into the final vector
    for (size_t i = 0, io = 0; i < 16; ++i) {
      if ((i == imax) | (i == imin)) {
		  (i == imax) ? beyerMatrix[bmIndex] = max : beyerMatrix[bmIndex] = min;
	  } else {
            beyerMatrix[bmIndex] = valueC[io];
            ++io;
      }
      bmIndex += 2;
    }
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
	valueC[13] = static_cast<uint16_t>((((val >> 1) & 0x7F) << sh) + min);
	
	//) we've got the Delta bytes, now merge them into the final vector
	for (size_t i = 0, io = 0; i < 16; ++i) {
        if ((i == imax) | (i == imin)) {
			(i == imax) ? beyerMatrix[bmIndex] = max : beyerMatrix[bmIndex] = min;
		} else {
			beyerMatrix[bmIndex] = valueC[io];
			++io;
		}
		bmIndex += 2;
	}	
	std::cout << "processed beyer" << std::endl;
  }
}

void RawTools::RawToolsImpl::getInterpolated() {}

void RawTools::RawToolsImpl::getPostProcesed() {}

void RawTools::RawToolsImpl::writeFile(const std::string &fileName) {
  auto tiff_file = std::make_unique<TiffFile>(fileName, *_fileMetaData);
  tiff_file->write_file();
}

void RawTools::RawToolsImpl::close_file() {}

void RawTools::RawToolsImpl::log(const std::string message) {
  std::cout << message.c_str() << std::endl;
}
