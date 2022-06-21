struct Node
{
    char data;
    int we;
    struct Node *Next[256];
};

/**
 * @brief Get the Node object
 *
 * @return struct Node*
 */
struct Node *GetNode()
{
    struct Node *newNode = new (struct Node);
    newNode->we = 0;
    for (int i = 0; i < 256; i++)
    {
        newNode->Next[i] = NULL;
    }
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
void Insert(struct Node **Start, struct Node **P, char data, int we)
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
        }
        else
        {
            newNode = (*P)->Next[data];
            if (we)
            {
                newNode->we = 1;
            }
        }
    }
    else
    {
        // we don't know where we want to insert, so start from root Node
        newNode->data = data;
        newNode->we = we;
        (*Start)->Next[data] = newNode;
    }
    (*P) = newNode;
}

/**
 * @brief This function perform the Insertion process to insert each character in Trie with the help of Insert function
 *
 * @param Start
 * @param word
 */
void PerformInsertion(struct Node **Start, string word)
{
    int len = word.length();
    struct Node *P = NULL;
    int i = 0;
    if ((*Start)->Next[word[i]])
    {
        P = (*Start)->Next[word[i]];
        i++;
    }
    while (i < len)
    {
        Insert(Start, &P, word[i], (i == (len - 1)));
        i++;
    }
}

/**
 * @brief This function counts the unique words present in the Trie
 *
 * @param Start : root pointer of Trie
 * @param count : count pointer ton count the number of unique words
 * @param total : total number of expected symbols, default 256
 */

void countUniqueWord(struct Node *Start, int *count, int total = 256)
{
    // for all the 26 letters
    for (int i = 0; i < total; i++)
    {
        // word has next letter
        if (Start->Next[i])
        {
            if (Start->Next[i]->we == 1)
            {
                (*count)++;
            }
            countUniqueWord(Start->Next[i], count, total);
        }
    }
}

/**
 * @brief
 *
 * @param word will return a string having no punctuation marks
 * @return string
 */
string clean(string word)
{
    string s = "";
    int i = 0;
    while (i < word.length())
    {
        if ((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= '0' && word[i] <= '9'))
        {
            s += word[i];
        }
        i++;
    }
    return s;
}
/**
 * @brief To convert a upper case letter to lower case
 *
 * @param word
 * @return string
 */
string convertToLowerCase(string word)
{
    string s = "";
    int i = 0;
    while (i < word.length())
    {
        s += (char)tolower(word[i]);
        i++;
    }
    return s;
}

int search(struct Node **Start, string word)
{
    struct Node *P = *Start;
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
    if (flag)
        return 0;
    else
    {
        if (P->we == 1)
        {

            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int search(struct Node **Start, char word)
{
    struct Node *P = *Start;
    int flag = 0;
    int i = 0;
    if (P->Next[word])
    {
        return 1;
    }
    return 0;
}

/**
 * @brief To construct trie for valid keywords
 *
 * @return struct Node*
 */

struct Node *constructTrieForKeywords()
{
    struct Node *Keyword = GetNode();
    fstream file;
    string fileName = "./keywords.txt", word;
    file.open(fileName.c_str(), ios::in);

    /**
     * @brief Read each word from file and perform Insertion in Trie
     *
     */
    int count = 0;
    while (file >> word)
    {
        count++;
        // to convert upper case letter to lower case
        word = convertToLowerCase(word);
        // to clean word form punctuation marks
        word = clean(word);
        // pre-check for any whitespace
        if (word != " ")
            PerformInsertion(&Keyword, word);
    }
    file.close();
    return Keyword;
}

/**
 * @brief To construct trie for valid symbols
 *
 * @return struct Node*
 */
struct Node *constructTrieForSymbols()
{
    struct Node *Keyword = GetNode();
    fstream file;
    string fileName = "./symbols.txt", word;
    file.open(fileName.c_str(), ios::in);

    /**
     * @brief Read each word from file and perform Insertion in Trie
     *
     */
    int count = 0;
    while (file >> word)
    {
        if (word != " ")
            PerformInsertion(&Keyword, word);
    }
    file.close();
    return Keyword;
}

/**
 * @brief to construct trie  for valid Operators
 *
 * @return struct Node*
 */
struct Node *constructTrieForOperator()
{
    struct Node *Keyword = GetNode();
    fstream file;
    string fileName = "./operators.txt", word;
    file.open(fileName.c_str(), ios::in);

    /**
     * @brief Read each word from file and perform Insertion in Trie
     *
     */
    int count = 0;
    while (file >> word)
    {
        if (word != " ")
            PerformInsertion(&Keyword, word);
    }
    file.close();
    return Keyword;
}

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

bool validIdentifier(string str, struct Node *Symbol, struct Node *Operator, struct Node *Keyword) // check if the given identifier is valid or not
{
    if (isNumber(str[0]) || search(&Symbol, str[0]) == 1 || search(&Operator, str[0]) == 1)
    {
        return false;
    } // if first character of string is a digit or a special character, identifier is not valid
    int i, len = str.length();
    if (len == 1)
    {
        return true;
    } // if length is one, validation is already completed, hence return true
    else
    {
        for (i = 1; i < len; i++) // identifier cannot contain special characters
        {
            if (search(&Symbol, str[i]) == 1 || search(&Operator, str[i]) == 1)
            {
                return false;
            }
        }
        if (search(&Keyword, str) == 1)
        {
            return false;
        }
    }
    return true;
}

string trim(string str)
{
    string s = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (int(str[i]) != 32)
            s += str[i];
    }
    return s;
}