/**
 * @file lexicalAnalyzer.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-06-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
// trie header file
#include "trie.h"

void PerformLexicalAnalysis(struct Node *Symbols, struct Node *operators, struct Node *keywords)
{
    fstream file;
    string fileName = "./sample.txt", word;
    file.open(fileName.c_str(), ios::in);

    /**
     * @brief Read each word from file and perform Insertion in Trie
     *
     */
    int count = 0;
    while (file >> word)
    {
        cout << "checking for " << word << endl;
        int flag = 0;
        if (trim(word) == " ")
            continue;
        string cleanWord = clean(word);
        if (cleanWord[0] >= 'a' && cleanWord[0] <= 'z' && cleanWord[cleanWord.length() - 1] >= 'a' && cleanWord[cleanWord.length() - 1] <= 'z')
        {
            if (validIdentifier(cleanWord, Symbols, operators, keywords))
            {
                cout << cleanWord << " is a valid identifier." << endl;
            }
            if (search(&keywords, cleanWord))
            {
                cout << cleanWord << " is a valid keyword." << endl;
            }
        }
        if (search(&operators, word))
        {
            cout << word << " is a valid operator." << endl;
        }
        if (search(&Symbols, word))
        {
            cout
                << word << " is a valid operator." << endl;
        }
        if (cleanWord.length() == 1 && isNumber(word[0]))
        {
            cout
                << cleanWord << " is a valid Number." << endl;
        }
        cout << "-------------------------" << endl;
    }
    file.close();
}

int main()
{
    // create trie for all keywords
    struct Node *KeywordTrie = constructTrieForKeywords();
    // create trie for all symbols
    struct Node *SymbolTrie = constructTrieForSymbols();
    // create trie for all airthmetic operators
    struct Node *OperatorsTrie = constructTrieForOperator();
    // cout << search(&KeywordTrie, "void");
    // cout << validIdentifier("void", SymbolTrie, OperatorsTrie, KeywordTrie);
    PerformLexicalAnalysis(SymbolTrie, OperatorsTrie, KeywordTrie);
    return 0;
}