//
//  main.cpp
//  HuffmanEncoder
//
//  Created by Nathan Molby on 11/6/19.
//  Copyright © 2019 Nathan Molby. All rights reserved.
//

#include <iostream>

#include <cassert>

#include "WriteBitFile.h"
#include "ReadBitFile.h"
#include "HuffmanEncoder.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    string inFileName;
    string outFileName;

    if(argc < 2){
        cout << "Enter infile name: ";
        cin >> inFileName;
        cout << "Enter outfile name: ";
        cin >> outFileName;
    } else{
        inFileName = string(argv[1]);
        outFileName = string(argv[2]);
    }
    
    HuffmanEncoder encoder(inFileName, outFileName);
        
    encoder.encode();
    
    return 0;
}
