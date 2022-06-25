#include <iostream>
#include <string>
using namespace std;

/**
 * @brief Node Structure
 * data: character
 * type: 1 = operator, 2 = symbol, 3 = keywords
 * Next: all children Nodes
 */
struct Node
{
    char data;
    int type;
    int we;
    struct Node *Next[128];
};

struct Node *GetNode()
{
    struct Node *newNode = new (Node);
    newNode->we = 0;

    for (int i = 0; i < 128; i++)
        newNode->Next[i] = NULL;

    return newNode;
}

/**
 * @brief Insert a character in trie
 *
 * @param Start
 * @param P
 * @param data
 * @param we
 */
void Insert(struct Node **Start, struct Node **P, char data, int we, int type)
{
    struct Node *newNode = GetNode();
    // we know where we want to insert
    if ((*P))
    {
        // we don't know where we want to insert, so start from root Node
        if (!(*P)->Next[data])
        {
            newNode->data = data;
            (*P)->Next[data] = newNode;
            newNode->we = we;
            newNode->type = type;
        }
        else
        {
            newNode = (*P)->Next[data];
            newNode->type = type;
            if (we)
                newNode->we = 1;
        }
    }
    else
    {
        // we don't know where we want to insert, so start from root Node
        newNode->data = data;
        newNode->we = we;
        newNode->type = type;
        (*Start)->Next[data] = newNode;
    }
    (*P) = newNode;
}

/**
 * @brief This function perform the Insertion process to insert each character in
 *        Trie with the help of Insert function
 *
 * @param Start
 * @param word
 * @param type identify what type of data is being stored
 */
void PerformInsertion(struct Node **Start, string word, int type)
{
    int len = word.length();
    struct Node *P = NULL;
    int i = 0;
    if ((*Start)->Next[word[i]])
    {
        P = (*Start)->Next[word[i]];
        if (++i == len - 1)
            (*Start)->Next[word[i]]->we = 1;
    }
    while (i < len)
    {
        Insert(Start, &P, word[i], (i == (len - 1)), type);
        i++;
    }
}

/**
 * @brief Search a word in the given Trie
 *
 * @param Start
 * @param word
 * @return int --> searchResult[0/1]
 */
int search(struct Node *Root, string word)
{
    struct Node *P = Root;
    int flag = 0;
    int i = 0;
    while (i < word.length())
    {
        if (P->Next[word[i]])
        {
            P = P->Next[word[i]];
        }
        else
        {
            flag = 1;
            break;
        }
        i++;
    }
    if (!flag && P->we == 1)
        return P->type;
    return 0;
}

int main()
{
    struct Node *Root = GetNode();
    string word;
    int run = 1;
    while (run)
    {
        cout << "0. exit\n1. Enter a word\n2. search a word\n";
        cin >> run;
        switch (run)
        {
        case 1:
            cout << "Enter a word to Insert" << endl;
            cin >> word;
            // let for example, type be -1
            PerformInsertion(&Root, word, 1);
            break;
        case 2:
            cout << "Enter word to be searched " << endl;
            cin >> word;
            if (search(Root, word))
            {
                cout << "Successfully found your word 🎉" << endl;
            }
            else
            {
                cout << "Not found your word!!" << endl;
            }
            break;
        }
    }
    return 0;
}