#define MAX_CHILD 26
typedef struct Tree
{
    int count;         //用来标记该节点是个可以形成一个单词，如果count！=0，则从根节点到该节点的路径可以形成一个单词
    struct Tree *child[MAX_CHILD];
    Tree() :count(0)
    {
        for (int i  = 0; i < MAX_CHILD; i++)
            child[i] = NULL;

    }
}Node,*Trie_node;


class CTrie
{
public:
    CTrie()
    {
        root = new Node();
    }
    ~CTrie()
    {
        del(root);
    }

    void insert(const char *str)
    {
        if (!str)
            return;
        Node *tmp = root;

        const  char *p = str;
        while (*p)
        {
            if (tmp->child[*p - 'a'] == NULL)
            {
                Node *t = new Node();
                tmp->child[*p - 'a'] = t;

            }

            tmp = tmp->child[*p - 'a'];
            p++;
        }
         tmp->count++;
    }

    bool searchStr(const char *str)
    {
        if (!str || !root)
            return false;
        const char *p = str;
        Node *tmp = root;
        while(*p)
        {
            if (tmp->child[*p - 'a'])
            {
                tmp = tmp->child[*p - 'a'];
                p++;
            }
            else break;
        }

        if (*p == '\0')
        {
            if (tmp->count == 0)
                cout << "qian zhui" << endl;
            else
                cout << "kllll" << endl;

        }
        else {
          //不在trie树中。
        }
    }



protected:
    void del(Node *root)
    {
        for (int i = 0; i < MAX_CHILD; i++)
        {
            if (root->child[i] != NULL)
                del(root->child[i]);
        }
        free(root);
    }



private:
    Node* root;
};
