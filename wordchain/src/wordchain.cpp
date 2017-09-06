#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";


int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";

    string word1, word2;

    cin >> word1;
    cin >> word2;
    queue<stack<string>> que;
    stack<string> workingStack;
    workingStack.push(word1);
    que.push(workingStack);
    cout << workingStack.top()<<endl;
    while (!que.empty()){

        que.front();
        que.pop();
        if (workingStack.top()==word2){
        }
    }

    return 0;
}
