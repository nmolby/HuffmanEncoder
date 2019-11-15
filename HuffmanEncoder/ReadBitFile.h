//
//  ReadBitFile.h
//  HuffmanCPP
//
//  Created by David M. Reed on 11/3/17.
//  Copyright © 2017 David Reed. All rights reserved.
//

#ifndef ReadBitFile_h
#define ReadBitFile_h

#include <cstdio>
#include <string>

class ReadBitFile {

public:
    ReadBitFile(std::string filename);

    unsigned long fileSizeInBytes() const { return _fileSizeInBytes; }

    unsigned char readBit();
    unsigned char readUByte();
    unsigned short readUShort();
    unsigned int readUInt();

    bool close();

private:
    FILE *_fp;
    unsigned char _bitValue;
    unsigned char _numberOfBits;
    unsigned long _fileSizeInBytes;

    void _resetBits();
};

inline ReadBitFile::ReadBitFile(std::string filename)
{
    _fp = fopen(filename.c_str(), "r");
    fseek(_fp, 0L, SEEK_END);
    _fileSizeInBytes = ftell(_fp);
    fseek(_fp, 0L, SEEK_SET);
    _bitValue = 0;
    _numberOfBits = 0;
}

inline unsigned char ReadBitFile::readBit()
{
    if (_numberOfBits == 0) {
        _bitValue = readUByte();
        _numberOfBits = 8;
    }

    // get the left most bit
    unsigned char b = (_bitValue & 128) >> 7;
    // shift so leftmost bit is ready for next call
    _bitValue = (_bitValue << 1);
    _numberOfBits--;
    return b;
}

inline unsigned char ReadBitFile::readUByte()
{
    _resetBits();
    unsigned char value;
    fread(&value, sizeof(unsigned char), 1, _fp);
    return value;
}

inline unsigned short ReadBitFile::readUShort()
{
    _resetBits();
    unsigned short value;
    fread(&value, sizeof(unsigned short), 1, _fp);
    return value;
}

inline unsigned int ReadBitFile::readUInt()
{
    _resetBits();
    unsigned int value;
    fread(&value, sizeof(unsigned int), 1, _fp);
    return value;
}

inline bool ReadBitFile::close()
{
    return fclose(_fp) == 0;
}

inline void ReadBitFile::_resetBits()
{
    _bitValue = 0;
    _numberOfBits = 0;
}

#endif /* ReadBitFile_h */
