// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
// TODO: include any other headers you need

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    int inputChar = input.get();
    map<int, int>::iterator it = freqTable.find(inputChar);
    if(it != freqTable.end()){
        (it->second)++;
    }else{
        freqTable.insert(std::pair<int,int>(inputChar,1));
    }
    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    // TODO: implement this function
    return nullptr;
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    // TODO: implement this function
    map<int, string> encodingMap;
    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    // TODO: implement this function
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    // TODO: implement this function
}

void compress(istream& input, obitstream& output) {
    // TODO: implement this function
}

void decompress(ibitstream& input, ostream& output) {
    // TODO: implement this function
}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
