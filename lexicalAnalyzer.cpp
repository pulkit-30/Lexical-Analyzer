#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "trie.h"

struct Node *LexicalAnalyzer(struct Node *Root)
{
    struct Node *Table = GetNode();
    fstream file;
    string fileName = "./program.txt", word;

    file.open(fileName.c_str(), ios::in);
    while (file >> word)
    {
        vector<string> brokenWords = breakWord(word);
        for (int i = 0; i < brokenWords.size(); i++)
        {
            if (!map(Table, brokenWords[i]))
            {
                int type = search(Root, brokenWords[i]);
                cout << "\t" << brokenWords[i] << "\t";
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

                cout << endl
                     << "|------------------------------------------------|" << endl;

                PerformInsertion(&Table, brokenWords[i], 1);
            }
        }
    }
    file.close();
    return Table;
}

int main()
{
    struct Node *Root = NULL;
    Root = CreateLexicalTrie();
    struct Node *Table = LexicalAnalyzer(Root);
    cout << endl
         << "Successfully created Symbol Table 🎉" << endl;
    cout << "Terminating Program Successfully ✅" << endl
         << "Bye Bye 👋" << endl;

    return 0;
}
