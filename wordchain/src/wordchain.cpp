#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

vector<string> neighbours(const string& word){
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


int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a timee." << endl;

    cout << "Please type two words: ";
    string word1, word2;

    cin >> word1;
    cin >> word2;

    queue<stack<string>> que;
    stack<string> workingStack;
    workingStack.push(word1);
    que.push(workingStack);

    while (!que.empty())
    {
        que.front();
        que.pop();
        if (workingStack.top()==word2){
            workingStack.push(word2);
            for (unsigned int i=0; i<workingStack.size(); i++)
            cout << workingStack.top() << " ";
        }else{

        }
    }

    return 0;
}
