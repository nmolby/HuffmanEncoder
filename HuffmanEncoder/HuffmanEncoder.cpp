//
//  HuffmanEncoder.cpp
//  HuffmanEncoder
//
//  Created by Nathan Molby on 11/7/19.
//  Copyright © 2019 Nathan Molby. All rights reserved.
//

#include "HuffmanEncoder.hpp"
#include <iostream>

//public method to begin encoding process
void HuffmanEncoder::encode() {
    _getCharCountMap();
    _getPriorityQueue();
    _getCharBitMap();
    _encodeFile();
}

//creates the dictionary of character -> character count
void HuffmanEncoder::_getCharCountMap() {
    unsigned char nextChar;
    //reads the entire file byte by byte
    for(int i = 0; i < _inFile.fileSizeInBytes(); i++){
        nextChar = _inFile.readUByte();
        //if character is not in map, add it to map
        if(this->charCountMap.find(nextChar) == this->charCountMap.end()){
            this->charCountMap[nextChar] = 0;
        }
        //increment character count
        this->charCountMap[nextChar] += 1;
    }
}

//creates priority queue and binary tree
void HuffmanEncoder::_getPriorityQueue() {
    //adds every node to the priority queue
    for(auto const& character: this->charCountMap){
        HuffmanNode newNode(true, character.first, character.second);
        this->_priorityQueue.push(std::make_shared<HuffmanNode>(newNode));
    }
    
    //continually takes the top two out of the priority queue and creates a new node with them
    //until there is only one node in the queue
    while(this->_priorityQueue.size() > 1){
        auto left = _priorityQueue.top();
        _priorityQueue.pop();
        auto right = _priorityQueue.top();
        _priorityQueue.pop();
        HuffmanNode newNode(false, 'a', left->count + right->count, left, right);
        _priorityQueue.push(std::make_shared<HuffmanNode>(newNode) );
    }
}

//creates the char -> bits map for every character
void HuffmanEncoder::_getCharBitMap() {
    std::bitset<32> bits;
    _getCharBitMapHelper(_priorityQueue.top(), bits, 0);
}

//gets the bits for a given node if bottom node
//else, recursively searches left and right nodes
void HuffmanEncoder::_getCharBitMapHelper(std::shared_ptr<HuffmanNode> toExplore, std::bitset<32> bits, unsigned int bitSize) {
    if(toExplore){
        //if it is a bottom node, assign the character to a new bitset with current bits/bitsize
        if(toExplore->isBottomNode){
            BitSet newBitSet(bits, bitSize);
            
            this->charBits[toExplore->character] = newBitSet;
        //otherwise, recursively call left and right children with according bits
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

//constructs a new HuffmanEncoder, inFile, and outFile
HuffmanEncoder::HuffmanEncoder(std::string inFile, std::string outFile) : _inFile(inFile) , _outFile(outFile) {
    this->_inFileName = inFile;
    this->_outFileName = outFile;

}

//encodes the entire file
void HuffmanEncoder::_encodeFile() {
    unsigned int totalFileSize = 0;
    for(auto const& character: this->charCountMap){
        totalFileSize += this->charBits[character.first].bitCount * character.second;
    }
    
    //writes header in form of
    // [total file size] [number of chars] {for each char: [char byte] [encoded bits]}
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
    
    //writes every char in file using encoded bits
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
