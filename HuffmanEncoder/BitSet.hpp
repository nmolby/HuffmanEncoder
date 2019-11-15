//
//  BitSet.hpp
//  HuffmanEncoder
//
//  Created by Nathan Molby on 11/7/19.
//  Copyright © 2019 Nathan Molby. All rights reserved.
//

#ifndef BitSet_hpp
#define BitSet_hpp

#include <stdio.h>
#include <bitset>

struct BitSet {
    BitSet(std::bitset<32> bits, unsigned short bitCount) {this->bits = bits; this->bitCount = bitCount;};
    BitSet() {};

    bool operator==(const BitSet &other) const
    { return (bits == other.bits) && (bitCount == other.bitCount);
    }
    
    std::bitset<32> bits;
    unsigned short bitCount;
};

namespace std {

  template <>
  struct hash<BitSet>
  {
    std::size_t operator()(const BitSet& b) const
    {
      using std::size_t;
      using std::hash;
      using std::string;

      return (std::hash<std::bitset<32>>()(b.bits))
        ^ (std::hash<unsigned short>()(b.bitCount));
    }
  };

}

#endif /* BitSet_hpp */
