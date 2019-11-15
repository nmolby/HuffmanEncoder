//
//  HuffmanDecoder.cpp
//  HuffmanEncoder
//
//  Created by Nathan Molby on 11/7/19.
//  Copyright © 2019 Nathan Molby. All rights reserved.
//

#include "HuffmanDecoder.hpp"


HuffmanDecoder::HuffmanDecoder(std::string inFile, std::string outFile) : _inFile(inFile) , _outFile(outFile) { 
    this->_inFileName = inFile;
    this->_outFileName = outFile;
}

HuffmanDecoder::~HuffmanDecoder() { 
    this->_inFile.close();
    this->_outFile.close();
}

void HuffmanDecoder::decode() { 
    _readHeader();
    _readFile();
}

void HuffmanDecoder::_readHeader() { 
    this->_fileSize = this->_inFile.readUInt();
    unsigned short keyCount = this->_inFile.readUShort();
    for(int i = 0; i < keyCount; i++){
        unsigned char character = this->_inFile.readUShort();
        unsigned short charCount = this->_inFile.readUShort();
        std::bitset<32> bits;
        std::cout << character << " : ";
        
        for(int j = 32 - charCount; j < 32; j++){
            bool bitValue = this->_inFile.readBit() == char(1);
            std::cout << bitValue;
            bits[j] = bitValue;
        }
        std::cout << std::endl;
        BitSet newBitSet(bits, charCount);
        
        this->bitsChar[newBitSet] = character;
    }
}

void HuffmanDecoder::_readFile() {
    std::bitset<32> bits;
    int bitCount = 0;
    BitSet newBitSet(bits, bitCount);
    for(int i = 0; i < this->_fileSize; i++){
        bool nextBitChar = this->_inFile.readBit() == char(1);
        bits >>= 1;
        bits[31] = nextBitChar;
        bitCount++;
        newBitSet = BitSet(bits, bitCount);
        if(this->bitsChar.find(newBitSet) != this->bitsChar.end()){
            this->_outFile.writeUByte(this->bitsChar[newBitSet]);
            bits.reset();
            bitCount = 0;
        }
    }
    
}
