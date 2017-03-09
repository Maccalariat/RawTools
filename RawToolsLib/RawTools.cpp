#include "RawTools.h"


RawTools::RawTools( )
{
    processBlock = new ProcessBlock( );
    processBlock->statusCode = processBlock->OK;
    processBlock->filename.clear( );
}

RawTools:: ~RawTools( )
{
}

void RawTools::getMetaData( )
{
    _fileBuffer = new FileBuffer( *processBlock );
    _fileMetaData = new FileMetaData( *_fileBuffer, *processBlock );
}

void RawTools::getBeyer( )
{
    if ( processBlock->verbose ) {
        log( std::string( "in getBeyer" ) );
    }
    beyerMatrix.resize( _fileMetaData->raw_ifd.height * _fileMetaData->raw_ifd.width );

    // right now, I assume it is for a sony
//	if (_fileMetaData->make == "SONY") {

    uint32_t  val;
    uint16_t max, min, imax, imin;
    const std::vector<uint8_t>offsets = { 19, 12, 5, 22, 15, 8,1,18,11,4,20,13,7 };
    std::vector<uint16_t>chunkV( 32, 0 );
    std::vector<uint8_t>valueD( 14, 0 );
    // walk through the filebuffer in 32-byte chunks and interleave
    // them into the output vector
    // ignore rows/columns since the algorithm is cfa agnostic

    size_t bmIndex = 0;
    for ( auto chunk = _fileMetaData->raw_ifd.offset;
          chunk <= _fileMetaData->raw_ifd.stripByteCount;
          chunk += 16 ) {
        // get the first group of color
        val = _fileBuffer->getUint32( chunk );
        max = static_cast<uint16_t>(val >> 21);  // maximum value
        min = static_cast<uint16_t>(val >> 16); // minimum value
        imax = static_cast<uint16_t>(val >> 6);
        imin = static_cast<uint16_t>(val >> 2);
        int x = -1;
        for ( size_t o = 3; o <= 12; o += 3 ) {
            val = _fileBuffer->getUint32( chunk + o );
            valueD[ ++x ] = static_cast<uint16_t>(0xFF00 & (val >> offsets[ x ]));
            valueD[ ++x ] = static_cast<uint16_t>(0xFF00 & (val >> offsets[ x ]));
            valueD[ ++x ] = static_cast<uint16_t>(0xFF00 & (val >> offsets[ x ]));
        }
    }
    std::cout << "processed beyer" << std::endl;
}


void RawTools::getInterpolated( )
{

}

void RawTools::getPostProcesed( )
{

}

void RawTools::log( const std::string message )
{
    std::cout << message.c_str( ) << std::endl;
}