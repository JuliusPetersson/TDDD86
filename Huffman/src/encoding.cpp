// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "queue"
#include "HuffmanNode.h"
#include <cmath>
// TODO: include any other headers you need

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    int inputChar = input.get();

    while(inputChar != -1){
        ++freqTable[inputChar];
        inputChar = input.get();
    }
    freqTable.insert(std::pair<int,int>(PSEUDO_EOF,1));
    return freqTable;
}

struct compare{
    bool operator()(const HuffmanNode* n1, const HuffmanNode* n2){
        return  *n1 < *n2;
    }
};

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    map<int, int>::const_iterator it;
    priority_queue<HuffmanNode*,vector<HuffmanNode*>, compare> prioQueue;
    HuffmanNode* node = new HuffmanNode(NOT_A_CHAR, 0, nullptr, nullptr);

    for (it = freqTable.begin(); it != freqTable.end(); it++){
        prioQueue.push(new HuffmanNode(it->first, it->second, nullptr, nullptr));
    }

    while(prioQueue.size() > 1){
        node = new HuffmanNode(NOT_A_CHAR, 0, nullptr, nullptr);
        node->zero = prioQueue.top();
        prioQueue.pop();
        node->one = prioQueue.top();
        prioQueue.pop();
        node->count = node->one->count + node->zero->count;
        prioQueue.push(node);
    }

    return prioQueue.top();
}

map<int, string> buildRestOfEncodingMap(HuffmanNode* encodingTree, string prefix){
    if(encodingTree->isLeaf()){
        map<int, string> done;
        done.insert(std::pair<int, string>(encodingTree->character, prefix));
        return done;
    }
    else{
        map<int, string> zero, one;

        zero = buildRestOfEncodingMap(encodingTree->zero, prefix + "0");
        one = buildRestOfEncodingMap(encodingTree->one, prefix + "1");

        for (std::pair<int, string> element : one){
            zero.insert(element);
        }

        return zero;
    }
}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;

    encodingMap = buildRestOfEncodingMap(encodingTree, "");

    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    int inputChar = 0;
    string result;
    while(!(inputChar == -1 || inputChar == PSEUDO_EOF)){
        inputChar = input.get();
        if(inputChar != -1){
            result += encodingMap.find(inputChar)->second;
        }
    }

    result += encodingMap.find(PSEUDO_EOF)->second;

    for (char c : result){
        if(c == '1'){
            output.writeBit(1);
        }
        else{
            output.writeBit(0);
        }
    }

}

int findChar(ibitstream& input, HuffmanNode* encodingTree){
    if(encodingTree->isLeaf()){
        return encodingTree->character;
    }
    else{
        int in = input.readBit();

        if(in == 1) return findChar(input, encodingTree->one);
        else return findChar(input, encodingTree->zero);
    }
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    int inchar = 0;
    do{
        inchar = findChar(input, encodingTree);
        output.put(inchar);
    }while(!(inchar == -1 || inchar == PSEUDO_EOF));
}

void writeNrAsBitStream(int i, int nr, obitstream& output){
    if(nr < 9){
        writeNrAsBitStream(i/2, nr+1, output);
        output.writeBit(i%2);
    }
}

void nrToByteStream(int i, obitstream& output){
    writeNrAsBitStream(i, 0, output);

}

void encodeHeader(HuffmanNode* encodingTree, obitstream& output){
    if(encodingTree->isLeaf()){
        output.writeBit(0);
        nrToByteStream(encodingTree->character, output);
    }
    else{
        output.writeBit(1);
        encodeHeader(encodingTree->zero, output);
        encodeHeader(encodingTree->one, output);
    }
}


int readByte(ibitstream& input){
    int out = 0;
    for (int i = 9; i > 0; i--){
        out += input.readBit()*pow(2, i-1);
    }
    return out;
}

HuffmanNode* decodeHeader(ibitstream& input){
    int i = input.readBit();
    HuffmanNode* n = new HuffmanNode();
    if(i == 0){
        n->character = readByte(input);
        n->count = 0;
        n->zero = nullptr;
        n->one = nullptr;
    }
    else{
        n->character = NOT_A_CHAR;
        n->count = 0;
        n->zero = decodeHeader(input);
        n->one = decodeHeader(input);
    }
    return n;
}

void compress(istream& input, obitstream& output) {
    map<int, int> freqTable = buildFrequencyTable(input);
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    map<int, string> encodingMap = buildEncodingMap(encodingTree);

    printSideways(encodingTree);

    encodeHeader(encodingTree, output);
    input.clear();
    input.seekg(0, ios::beg);
    encodeData(input, encodingMap, output);
}

void decompress(ibitstream& input, ostream& output) {
    HuffmanNode* encodingTree = decodeHeader(input);
    printSideways(encodingTree);
    decodeData(input, encodingTree, output);
}

void freeTree(HuffmanNode* node) {
    if(node != nullptr){
        freeTree(node->one);
        freeTree(node->zero);
    }

    delete node;
}
