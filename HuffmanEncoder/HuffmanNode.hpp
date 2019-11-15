//
//  HuffmanNode.hpp
//  HuffmanEncoder
//
//  Created by Nathan Molby on 11/7/19.
//  Copyright © 2019 Nathan Molby. All rights reserved.
//

#ifndef HuffmanNode_hpp
#define HuffmanNode_hpp

#include <stdio.h>
#include <string>
#include <memory>


struct HuffmanNode {
    HuffmanNode(bool isBottomNode, unsigned char character, unsigned int count, std::shared_ptr<HuffmanNode> left = nullptr, std::shared_ptr<HuffmanNode> right = nullptr){
        this->isBottomNode = isBottomNode; this->character = character; this->count = count; this->left = left; this->right = right;
    }
    
    bool isBottomNode;
    unsigned char character;
    unsigned int count;
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;
};

struct HuffmanNodeComparor {
    bool operator()(std::shared_ptr<HuffmanNode>  const& h1, std::shared_ptr<HuffmanNode> const& h2)
    {
        return h1->count > h2->count;
    }
};

#endif /* HuffmanNode_hpp */
