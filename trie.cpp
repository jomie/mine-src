//////////////////////////////////////////////////////////////////////////////////////
//Version II

//�˺���ֻ����26��Ӣ����ĸ�����
#include<iostream>
#include<cstring>
using namespace std;

#define MAX_CHILD 26


typedef struct Tree
{
    int count;         //������Ǹýڵ��Ǹ������γ�һ�����ʣ����count��=0����Ӹ��ڵ㵽�ýڵ��·�������γ�һ������
    struct Tree *child[MAX_CHILD];
}Node,*Trie_node;


Node* CreateTrie()                             //����trie�ڵ���
{
    Node *node=(Node*)malloc(sizeof(Node));
    memset(node,0,sizeof(Node));
    return node;
}



void insert_node(Trie_node root,char *str)      //trie��������
{
    if(root ==NULL || *str=='\0')
        return;
    Node *t=root;

    char *p=str;

    while(*p!='\0')
    {
        if(t->child[*p-'a']==NULL)
        {
            Node *tmp=CreateTrie();
            t->child[*p-'a']=tmp;
        }
        t=t->child[*p-'a'];
        p++;
    }
    t->count++;
}


void search_str(Trie_node root,char *str)             //���Ҵ��Ƿ��ڸ�trie����
{
    if(NULL==root || *str=='\0')
    {
        printf("trie is empty or str is null\n");
        return;
    }

    char *p=str;
    Node *t=root;
    while(*p!='\0')
    {
        if(t->child[*p-'a']!=NULL)
        {
            t=t->child[*p-'a'];
            p++;
        }
        else
            break;
    }
    if(*p=='\0')
    {
        if(t->count==0)
            cout<<"���ַ�������trie���У����ô���ĳ�����ʵ�ǰ׺\n";
        else
            cout<<"���ַ����ڸ�trie����\n";
    }
    else
        cout<<"���ַ�������trie����\n";
}


void del(Trie_node root)      //�ͷ������ֵ���ռ�Ķѿռ�
{
    int i;
    for(i=0;i<MAX_CHILD;i++)
    {
        if(root->child[i]!=NULL)
            del(root->child[i]);
    }
    free(root);
}




int main()
{
    int i,n;
    char str[20];
    cout<<"������Ҫ������trie���Ĵ�С��";
    cin>>n;
    Trie_node root=NULL;
    root=CreateTrie();
    if(root==NULL)
        cout<<"����trie��ʧ��";
    for(i=0;i<n;i++)
    {
        scanf("%s",str);
        insert_node(root,str);
    }
    cout<<"trie���ѽ������\n";
    cout<<"������Ҫ��ѯ���ַ���:";
    while(scanf("%s",str)!=NULL)
    {
        search_str(root,str);

    }
    return 0;


}

//////////////////////////////////////////////////////////////////////////////////////
//Version III

/*
Name: Trie���Ļ���ʵ��
Author: MaiK
Description: Trie���Ļ���ʵ�� ,�������� �����ɾ������*/
#include<algorithm>
#include<iostream>
using namespace std;

const int sonnum=26,base='a';
struct Trie
{
    int num;//to remember how many word can reach here,that is to say,prefix
    bool terminal;//If terminal==true ,the current point has no following point
    struct Trie *son[sonnum];//the following point
};
Trie *NewTrie()// create a new node
{
    Trie *temp=new Trie;
    temp->num=1;temp->terminal=false;
    for(int i=0;i<sonnum;++i)temp->son[i]=NULL;
    return temp;
}
void Insert(Trie *pnt,char *s,int len)// insert a new word to Trie tree
{
    Trie *temp=pnt;
    for(int i=0;i<len;++i)
    {
        if(temp->son[s[i]-base]==NULL)temp->son[s[i]-base]=NewTrie();
        else temp->son[s[i]-base]->num++;
        temp=temp->son[s[i]-base];
    }
    temp->terminal=true;
}
void Delete(Trie *pnt)// delete the whole tree
{
    if(pnt!=NULL)
    {
        for(int i=0;i<sonnum;++i)if(pnt->son[i]!=NULL)Delete(pnt->son[i]);
        delete pnt;
        pnt=NULL;
    }
}
Trie* Find(Trie *pnt,char *s,int len)//trie to find the current word
{
    Trie *temp=pnt;
    for(int i=0;i<len;++i)
        if(temp->son[s[i]-base]!=NULL)temp=temp->son[s[i]-base];
    else return NULL;
    return temp;
}
