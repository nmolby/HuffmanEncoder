//
//  HuffmanDecoder.hpp
//  HuffmanEncoder
//
//  Created by Nathan Molby on 11/7/19.
//  Copyright © 2019 Nathan Molby. All rights reserved.
//

#ifndef HuffmanDecoder_hpp
#define HuffmanDecoder_hpp

#include <stdio.h>
#include <string>
#include <unordered_map>
#include <queue>
#include <iostream>
#include "ReadBitFile.h"
#include "WriteBitFile.h"
#include "HuffmanNode.hpp"
#include "BitSet.hpp"

class HuffmanDecoder {
public:
    HuffmanDecoder(std::string inFile, std::string outFile);
    ~HuffmanDecoder();
    
    void decode();
    
private:
    std::unordered_map<BitSet, unsigned char> bitsChar;
    
    unsigned int _fileSize;
    
    void _readHeader();
    void _readFile();

    
    std::string _inFileName;
    std::string _outFileName;
        
    ReadBitFile _inFile;
    WriteBitFile _outFile;
};

#endif /* HuffmanDecoder_hpp */
