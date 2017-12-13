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
    while(inputChar != -1){
        inputChar = input.get();
        result += encodingMap.find(inputChar)->second;

    }

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
        if(inchar != -1)output.put(inchar);
    }while(inchar != -1);
}

void compress(istream& input, obitstream& output) {
    map<int, int> freqTable = buildFrequencyTable(input);
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    map<int, string> encodingMap = buildEncodingMap(encodingTree);
    input.clear();
    input.seekg(0, ios::beg);
    encodeData(input, encodingMap, output);

}

void decompress(ibitstream& input, ostream& output) {

}

void freeTree(HuffmanNode* node) {
    // TODO: implement this function
}
