//
//  HuffmanEncoder.cpp
//  HuffmanEncoder
//
//  Created by Nathan Molby on 11/7/19.
//  Copyright © 2019 Nathan Molby. All rights reserved.
//

#include "HuffmanEncoder.hpp"
#include <iostream>

void HuffmanEncoder::encode() {
    _getCharCountMap();
    _getPriorityQueue();
    _getCharBitMap();
    _encodeFile();
}

void HuffmanEncoder::_getCharCountMap() {
    unsigned char nextChar;
    for(int i = 0; i < _inFile.fileSizeInBytes(); i++){
        nextChar = _inFile.readUByte();
        if(this->charCountMap.find(nextChar) == this->charCountMap.end()){
            this->charCountMap[nextChar] = 0;
        }
        this->charCountMap[nextChar] += 1;
    }
    std::cout << nextChar << int(nextChar);
}

void HuffmanEncoder::_getPriorityQueue() {
    for(auto const& character: this->charCountMap){
        HuffmanNode newNode(true, character.first, character.second);
        this->_priorityQueue.push(std::make_shared<HuffmanNode>(newNode));
    }
    
    while(this->_priorityQueue.size() > 1){
        auto left = _priorityQueue.top();
        _priorityQueue.pop();
        auto right = _priorityQueue.top();
        _priorityQueue.pop();
        HuffmanNode newNode(false, 'a', left->count + right->count, left, right);
        _priorityQueue.push(std::make_shared<HuffmanNode>(newNode) );
    }
}

void HuffmanEncoder::_getCharBitMap() {
    std::bitset<32> bits;
    _getCharBitMapHelper(_priorityQueue.top(), bits, 0);
}

void HuffmanEncoder::_getCharBitMapHelper(std::shared_ptr<HuffmanNode> toExplore, std::bitset<32> bits, unsigned int bitSize) {
    if(toExplore){
        if(toExplore->isBottomNode){
            BitSet newBitSet(bits, bitSize);
            
            this->charBits[toExplore->character] = newBitSet;
        } else{
            std::bitset<32> leftBits(bits);
            leftBits >>= 1;
            _getCharBitMapHelper(toExplore->left, leftBits, bitSize + 1);
            std::bitset<32> rightBits(bits);
            rightBits >>= 1;
            rightBits[31] = 1;
            _getCharBitMapHelper(toExplore->right, rightBits, bitSize + 1);
        }
    }
}

HuffmanEncoder::HuffmanEncoder(std::string inFile, std::string outFile) : _inFile(inFile) , _outFile(outFile) {
    this->_inFileName = inFile;
    this->_outFileName = outFile;

}

void HuffmanEncoder::_encodeFile() {
    unsigned int totalFileSize = 0;
    for(auto const& character: this->charCountMap){
        totalFileSize += this->charBits[character.first].bitCount * character.second;
    }
    
    this->_outFile.writeUInt(totalFileSize);
    this->_outFile.writeUShort(this->charBits.size());
    for(auto const& character: this->charBits){
        this->_outFile.writeUShort(character.first);
        this->_outFile.writeUShort(character.second.bitCount);
        for(int i = 32 - character.second.bitCount; i < 32; i++){
            this->_outFile.writeBit(character.second.bits[i]);
        }
    }
    
    this->_inFile.close();
    this->_inFile = ReadBitFile(this->_inFileName);
    
    unsigned char nextChar;
    for(int i = 0; i < _inFile.fileSizeInBytes(); i++){
        nextChar = _inFile.readUByte();
        BitSet newBitSet = this->charBits[nextChar];
        
        for(int i = 32 - newBitSet.bitCount; i < 32; i++){
            this->_outFile.writeBit(newBitSet.bits[i]);
        }
        
    }
    
}
void HuffmanEncoder::close() {
    this->_inFile.close();
    this->_outFile.close();
}


HuffmanEncoder::~HuffmanEncoder() { 
    this->close();
}






