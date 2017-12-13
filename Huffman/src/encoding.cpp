// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: remove this comment header

#include "encoding.h"
#include "queue"
#include "HuffmanNode.h"
// TODO: include any other headers you need

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;
    int inputChar = 0;
    while(inputChar != -1){
        inputChar = input.get();
        map<int, int>::iterator it = freqTable.find(inputChar);
        if(it != freqTable.end()){
            (it->second)++;
        }else{
            freqTable.insert(std::pair<int,int>(inputChar,1));
        }
    }freqTable.insert(std::pair<int,int>(inputChar,1));
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
    std::cout << "hej jag existerar"<<std::endl;

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
