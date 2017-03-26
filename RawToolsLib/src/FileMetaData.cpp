#include "FileMetaData.hpp"

FileMetaData::FileMetaData(FileBuffer &fileBuffer) : _fileBuffer(fileBuffer)
{
  std::cout << "in FileMetaData constructor" << std::endl;

  if (fileBuffer.memoryFile[2] != 0x2A)
  {
    // bad magic number
    std::cout << "bad magic number in file" << std::endl;
    return;
  }

  // process the file
  // TODO: error handling
  parseFile();

  // now get the supposed non-scaled image
  for (auto ifd : tiff_ifd)
  {
    if (ifd.ifd_type == 0)
    {
      raw_ifd = ifd;
      break;
    }
  }
  // clear the ifd vector to save memory
  // TODO: use smart pointer to auto-scope/destruct tiff_ifd
  tiff_ifd.clear();
  std::cout << "raw image in ifd offset" << raw_ifd.file_offset << " "
            << std::endl;
}

FileMetaData::~FileMetaData() {}

void FileMetaData::parseFile()
{
  std::cout << "in FileMetaData::parseFile" << std::endl;
  size_t first_offset = _fileBuffer.getUint16(4);
  uint32_t next_IFD = first_offset;
  do
  {
    next_IFD = processIFD(next_IFD);
  } while (next_IFD != 0);
  std::cout << "IFD count: " << tiff_ifd.size() << std::endl;
}

uint32_t FileMetaData::processIFD(const size_t offset)
{
  uint16_t deCount = _fileBuffer.getUint16(offset);
  size_t o = offset + 2;
  tiff_ifd.emplace_back();
  tiff_ifd.back().file_offset = offset;
  for (int index = 1; index <= deCount; index++)
  {
    processDE((index - 1) * 12 + o, tiff_ifd.back());
  }
  return _fileBuffer.getUint32(offset + 2 + (deCount * 12));
}

void FileMetaData::processDE(const size_t offset, tiff_ifd_s &ifd)
{
  uint16_t tag = _fileBuffer.getUint16(offset);
  uint16_t tag_type = _fileBuffer.getUint16(offset + 2);
  uint32_t tag_count = _fileBuffer.getUint32(offset + 4);
  uint32_t tag_value_offset = _fileBuffer.getUint32(offset + 8);

  std::vector<unsigned char>::iterator b;
  std::vector<unsigned char>::iterator e;
  switch (tag)
  {
  case 0x00FE: // subfileType
  {
    ifd.ifd_type = tag_value_offset;
    break;
  }
  case 5:
    ifd.width = tag_value_offset;
    break;
  case 6:
    ifd.height = tag_value_offset;
    break;
  case 9: // ???
    /*
    // if ((i = get2())) filters = i;  break;
    */
    break;
  case 17:
  case 18: // ???
    /*
    if (type == 3 && len == 1)
            cam_mul[(tag - 17) * 2] = get2() / 256.0;
            */
    break;
  case 23:
  {
    if (tag_type == 3)
    {
      iso_speed = tag_value_offset;
    }
  }
  break;
  case 28:
  case 29:
  case 30:
  {
    cblack.at(tag - 28) = tag_value_offset;
    cblack.at(3) = cblack.at(1);
  }
  break;
  case 36:
  case 37:
  case 38:
    // cam_mul[tag - 36] = get2(); -- this does not make sense cam_mul is [4]
    // long
    break;
  case 0X100:
    ifd.width = tag_value_offset;
    break;
  case 0X101: // image height
    ifd.height = tag_value_offset;
    break;
  case 0x102: // bits per sample
  case 61443:
    ifd.samples = tag_count & 7;
    ifd.bps = tag_value_offset;
    if (tiff_bps < ifd.bps)
    {
      tiff_bps = ifd.bps;
    }
    break;
  case 0x103: // compression
    ifd.comp = tag_value_offset;
    break;
  case 0X10E:
  {
    imageDescription.assign(_fileBuffer.memoryFile.begin() + tag_value_offset,
                            _fileBuffer.memoryFile.begin() + tag_value_offset +
                                tag_count);
  }
  break;
  case 0X10F:
  {
    make.assign(_fileBuffer.memoryFile.begin() + tag_value_offset,
                _fileBuffer.memoryFile.begin() + tag_value_offset + tag_count);
  }
  break;
  case 0x110:
  {
    model.assign(_fileBuffer.memoryFile.begin() + tag_value_offset,
                 _fileBuffer.memoryFile.begin() + tag_value_offset + tag_count);
  }
  break;
  case 274:
    ifd.flip = tag_value_offset;
    break;
    /* case 280:				// Panasonic RW2 offset
					if (type != 4) break;
					load_raw = &CLASS panasonic_load_raw;
					load_flags = 0x2008;
					*/ // note runs into next case 273 (shit
                                           // code)
  case 0x0111:                             // strip offsets
    ifd.offset = tag_value_offset;
    break;
  case 0x116: // rows per strip
    ifd.rowsPerStrip = tag_value_offset;
  case 277: // samples per pixel
    ifd.samples = tag_value_offset;
    break;
  case 279: // strip byte counts
    ifd.stripByteCount = tag_value_offset;
    break;
  case 305: // software
  case 11:
  {
    b = _fileBuffer.memoryFile.begin() + tag_value_offset;
    e = _fileBuffer.memoryFile.begin() + tag_value_offset + tag_count;
    std::string software{b, e};
    if (!software.compare(0, 5, "Adobe") || !software.compare(0, 5, "dcraw") ||
        !software.compare(0, 5, "UFRaw") || !software.compare(0, 6, "Bibble") ||
        !software.compare(0, 10, "Nikon Scan") ||
        !software.compare(0, 26, "Digital Photo Professional"))
    {
      statusCode = NotRawFile;
    }
  }
  break;
  case 306: // DateTime
  {
    timestamp.assign(_fileBuffer.memoryFile.begin() + tag_value_offset,
                     _fileBuffer.memoryFile.begin() + tag_value_offset +
                         tag_count);
  }

  break;
  case 315: // artist
  {
    artist.assign(_fileBuffer.memoryFile.begin() + tag_value_offset,
                  _fileBuffer.memoryFile.begin() + tag_value_offset +
                      tag_count);
  }
  break;
  case 322: // tile width
    ifd.tile_width = tag_value_offset;
    break;
  case 323: // tile length
    ifd.tile_length = tag_value_offset;
    break;
  case 324: // TileOffsets
    ifd.offset = tag_count;
    if (tag_count > 1)
    {
      // ftell( ifp ) : get4();
    }
    if (tag_count == 1)
    { // the image is in one tile (ie: most images)
      ifd.tile_width = ifd.tile_length = 0;
      /* if (len == 4) {
              load_raw = &CLASS sinar_4shot_load_raw;
              is_raw = 5; */
    }
    break;
  case 330:
  {
    uint32_t next_IFD = tag_value_offset;
    do
    {
      next_IFD = processIFD(next_IFD);
    } while (next_IFD != 0);
  }
  break;
  case 400:
    make.assign("Sarnoff");
    maximum = 0xfff;
    break;
  case 0x700:
  {
    ifd.sonyRawFileType = tag_value_offset;
  }
  case 28688:
    // std::for_each(_pb.sony_curve.begin(), _pb.sony_curve.end(), [])
    /*
    for (int c = 0; c < 4; c++) {
            // _pb.sony_curve[c + 1] = get2() >> 2 & 0xfff;
            }
    for (int i = 0; i < 5; i++)
            for (int j = _pb.sony_curve[i] + 1; j <= _pb.sony_curve[i + 1]; j++)
                    _pb.curve[j] = _pb.curve[j - 1] + (1 << i);
                    */
    break;
  case 29184:
    sony_offset = tag_value_offset;
    break;
  case 29185:
    sony_length = tag_value_offset;
    break;
  case 29217:
    sony_key = tag_value_offset;
    break;
  };
}
