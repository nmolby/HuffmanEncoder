//
//  HuffmanEncoder.hpp
//  HuffmanEncoder
//
//  Created by Nathan Molby on 11/7/19.
//  Copyright © 2019 Nathan Molby. All rights reserved.
//

#ifndef HuffmanEncoder_hpp
#define HuffmanEncoder_hpp

#include <stdio.h>
#include <string>
#include <unordered_map>
#include <queue>
#include "ReadBitFile.h"
#include "WriteBitFile.h"
#include "HuffmanNode.hpp"
#include "BitSet.hpp"

class HuffmanEncoder {
public:
    HuffmanEncoder(std::string inFile, std::string outFile);
    ~HuffmanEncoder();
    
    void close();
    
    void encode();
    
private:
    std::unordered_map<unsigned char, unsigned int> charCountMap;
    std::unordered_map<unsigned char, BitSet> charBits;
    
    void _getCharCountMap();
    void _getPriorityQueue();
    void _getCharBitMap();
    void _encodeFile();
    void _getCharBitMapHelper(std::shared_ptr<HuffmanNode>, std::bitset<32>, unsigned int);
    
    std::string _inFileName;
    std::string _outFileName;
    
    std::priority_queue<std::shared_ptr<HuffmanNode>, std::vector<std::shared_ptr<HuffmanNode>>, HuffmanNodeComparor> _priorityQueue;
    
    ReadBitFile _inFile;
    WriteBitFile _outFile;
};

#endif /* HuffmanEncoder_hpp */
