#include <iostream>
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

int main()
{
    struct Node *Root = GetNode();
    cout << "Successfully created Root Node 🎉";
    // free memory at the end
    delete (Root);
    return 0;
}