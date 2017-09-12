#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

vector<string> getNeighbours(const string& word){
    vector<string> neighbours;
    for (unsigned i = 0; i<word.size(); i++)
    {
        for (char j:ALPHABET)
        {
            string tempWord = word;
            tempWord[i] = j;
            neighbours.push_back(tempWord);
        }
    }
    return neighbours;
}

void generateDictionary(set<string>& dictionary){
    string dictWord;
    fstream file;
    file.open("dictionary.txt");
    while (getline(file, dictWord)){
        dictionary.insert(dictWord);
    }

}


int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a timee." << endl;

    cout << "Please type two words: ";

    string word1, word2;
    cin >> word1;
    cin >> word2;

    set<string> dictionary;
    generateDictionary(dictionary);

    queue<stack<string>> que;
    stack<string> workingStack;
    set<string> usedWords;
    workingStack.push(word1);
    que.push(workingStack);

    while (!que.empty()){
        que.front();
        que.pop();
        if (workingStack.top()==word2){
            workingStack.push(word2);
         } else {
            vector<string> neighbours = getNeighbours(word1);
            vector<string> wordstack;

                for (vector<string>::iterator it = neighbours.begin(); it < neighbours.end(); it++){

                    if ((dictionary.count(*it)) && !(find(usedWords.begin(), usedWords.end(), *it) != usedWords.end())){
                        wordstack.push_back(*it);
                        usedWords.insert(*it);
                    }

            }
            for (unsigned int i=0 ; i<wordstack.size();i++){
                cout << wordstack.at(i) << endl;

            }

            }
        }



    return 0;
}
