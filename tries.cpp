#define MAX_CHILD 26
typedef struct Tree
{
    int count;         //������Ǹýڵ��Ǹ������γ�һ�����ʣ����count��=0����Ӹ��ڵ㵽�ýڵ��·�������γ�һ������
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
          //����trie���С�
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
