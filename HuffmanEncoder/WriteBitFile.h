//
//  WriteBitFile.h
//  HuffmanCPP
//
//  Created by David M. Reed on 11/3/17.
//  Copyright © 2017 David Reed. All rights reserved.
//

#ifndef WriteBitFile_h
#define WriteBitFile_h

#include <cstdio>
#include <string>

class WriteBitFile {

public:

    WriteBitFile(std::string filename);

    bool writeBit(unsigned char bit);

    bool writeUByte(unsigned char value);

    bool writeUShort(unsigned short value);

    bool writeUInt(unsigned int value);

    bool close();

private:

    bool _finishBits();

    FILE *_fp;
    unsigned char _bitValue;
    unsigned char _numberOfBits;

};

inline WriteBitFile::WriteBitFile(std::string filename)
{
    _fp = fopen(filename.c_str(), "w");
    _bitValue = 0;
    _numberOfBits = 0;
}

inline bool WriteBitFile::writeBit(unsigned char bit)
{
    if (_fp == NULL || !(bit == 0 || bit == 1)) {
        return false;
    }
    _bitValue = (_bitValue << 1) + bit;
    _numberOfBits++;
    if (_numberOfBits == 8) {
        unsigned char value = _bitValue;
        _bitValue = 0;
        _numberOfBits = 0;
        writeUByte(value);
    }

    return true;
}

inline bool WriteBitFile::writeUByte(unsigned char value)
{

    return _finishBits() && fwrite(&value, sizeof(unsigned char), 1, _fp) == 1;
}

inline bool WriteBitFile::writeUShort(unsigned short value)
{
    return _finishBits() && fwrite(&value, sizeof(unsigned short), 1, _fp) == 1;
}

inline bool WriteBitFile::writeUInt(unsigned int value)
{
    return _finishBits() && fwrite(&value, sizeof(unsigned int), 1, _fp) == 1;
}

inline bool WriteBitFile::close()
{
    bool r = _finishBits();
    return r && (fclose(_fp) == 0);
}

inline bool WriteBitFile::_finishBits()
{
    bool result = true;
    if (_numberOfBits != 0) {
        _bitValue = _bitValue << (8 - _numberOfBits);
        _numberOfBits = 0;
        result = writeUByte(_bitValue);
        _bitValue = 0;
    }
    return result;
}

#endif /* WriteBitFile_h */
