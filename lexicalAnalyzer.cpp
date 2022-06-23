#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "trie.h"

void LexicalAnalyzer(struct Node *Root)
{
    fstream file;
    string fileName = "./program.txt", word;

    file.open(fileName.c_str(), ios::in);
    while (file >> word)
    {
        vector<string> brokenWords = breakWord(word);
        for (int i = 0; i < brokenWords.size(); i++)
        {
            int type = search(Root, brokenWords[i]);
            cout << brokenWords[i] << " ";
            if (type == 1)
                cout << "is a valid Operator" << endl;
            else if (type == 2)
                cout << "is a valid Symbol" << endl;
            else if (type == 3)
                cout << "is a valid Keyword" << endl;
            else if (type == 4)
                cout << "is a valid Number" << endl;
            else if (type == 5)
                cout << "is a valid identifier" << endl;
            else
                cout << " is not a valid identifier" << endl;
            cout << "---------------------------------------" << endl;
        }
    }
    file.close();
}

int main()
{
    struct Node *Root = NULL;
    Root = CreateLexicalTrie();
    LexicalAnalyzer(Root);
    return 0;
}
