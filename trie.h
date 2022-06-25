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
 * @brief check for a numerical value
 *
 * @param str
 * @return true if numerical value
 * @return false
 */

bool isNumber(char str)
{
    if (str == '0' || str == '1' || str == '2' ||
        str == '3' || str == '4' || str == '5' ||
        str == '6' || str == '7' || str == '8' ||
        str == '9')
    {
        return 1;
    }
    return 0;
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
 * @brief Create a Lexical Trie object
 *
 * @return struct Node*
 */
struct Node *CreateLexicalTrie()
{
    string files[3] = {
        "operators.txt",
        "symbols.txt",
        "keywords.txt",
    };
    // create Root node
    struct Node *Root = GetNode();

    // file instance
    fstream file;
    string fileName, word;
    int i = 0;
    while (i < 4)
    {
        fileName = "./utils/" + files[i];
        file.open(fileName.c_str(), ios::in);
        while (file >> word)
        {
            PerformInsertion(&Root, word, (i + 1));
        }
        file.close();
        i++;
    }
    return Root;
}

/**
 * @brief To break word: separate symbols and characters
 *
 * @param word
 * @return vector<string>
 */
vector<string> breakWord(string word)
{
    vector<string> brokenWord;
    int len = word.length();
    int i = 0;
    string str = "";
    while (i < len)
    {
        if (word[i] != ' ')
        {
            if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') || word[i] == '_' || isNumber(word[i]))
            {
                str += word[i];
            }
            else
            {
                string s(1, word[i]);
                if (str != "")
                    brokenWord.push_back(str);
                brokenWord.push_back(s);
                str = "";
                s = "";
            }
        }
        i++;
    }
    if (str != "")
        brokenWord.push_back(str);
    return brokenWord;
}

/**
 * @brief
 *
 * @param word
 * @return true
 * @return false
 */
bool validIdentifier(string word)
{
    int len = word.length(), flag = 0;
    if (len == 1)
        return true;
    if (isNumber(word[0]) || !((word[0] >= 'a' && word[0] <= 'z') || (word[0] >= 'A' && word[0] <= 'Z') || word[0] == '_'))
        return false;
    for (int i = 1; i < len; i++)
    {
        if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z') || word[i] == '_' || isNumber(word[i]))
            continue;
        else
        {
            flag = 1;
            break;
        }
    }

    if (flag)
        return false;
    else
        return true;
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
    if (!validIdentifier(word))
        return -1;
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
    if (word.length() == 1 && isNumber(word[0]))
        return 4;
    return 5;
}

/**
 * @brief map a word in the given Trie
 *
 * @param Start
 * @param word
 * @return int --> searchResult[0/1]
 */
int map(struct Node *Root, string word)
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
        return 1;
    return 0;
}
