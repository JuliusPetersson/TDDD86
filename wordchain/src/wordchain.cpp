/**
 * Console program that returns the shortest wordchain between two word given a dictionary located in /res/dictionary.txt
 *
 * @author Julius Petersson(jelpe622)
 * @author Viktor Palm(vikpa137)
 */



#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>


using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/**
 * Gives takes a word and swap one letter at the time with all possible choices from the alphabet
 *
 * @brief Give all the possible wordcomibination
 * @param String used to create generate neighbours
 * @return neighbour
 */
vector<string> getNeighbours(const string& word){
    vector<string> neighbours;
    //std::numeric_limits<float>::
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


/**
 * @brief "Put dictionary.txt" to the referenced set
 * @param dictionary filled with word from file
 * "param vem äger pekare om pekare" tar över eller ej pekare
 * lämnar pekaren
 * hur länge är ref giltigt
 */
void generateDictionary(set<string>& dictionary){
    string dictWord;
    fstream file;
    file.open("dictionary.txt");
    while (getline(file, dictWord)){
        dictionary.insert(dictWord);
    }

}
/**
 * Function take a stack of any length and prints it in reverse order and destorys the stack meanwhile
 *
 * @brief Prints the content of a stack i reverse order
 * @param stack containing string. This funtion will destroy the stack!
 */
void printStack(stack<string>& workingStack){
    string stringChain;
    int sizeWorkingStack = workingStack.size();
    for (int i = 0; i < sizeWorkingStack; i++){
        stringChain = workingStack.top() + " " + stringChain;
        workingStack.pop();
    }
    cout << stringChain << endl;
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
        workingStack = que.front();
        que.pop();

        if (workingStack.top() == word2){
            printStack(workingStack);
            break;
         } else{

            vector<string> neighbours = getNeighbours(workingStack.top());

                for (vector<string>::iterator it = neighbours.begin(); it < neighbours.end(); it++){

                    if ((dictionary.count(*it)) && !(find(usedWords.begin(), usedWords.end(), *it) != usedWords.end())){                        
                        stack<string> wordStack = workingStack;
                        wordStack.push(*it);
                        que.push(wordStack);
                        usedWords.insert(*it);

                    }
                }
            }
        }

    return 0;
}
