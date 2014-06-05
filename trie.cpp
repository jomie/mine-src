//////////////////////////////////////////////////////////////////////////////////////
//Version II

//此函数只考虑26个英文字母的情况
#include<iostream>
#include<cstring>
using namespace std;

#define MAX_CHILD 26


typedef struct Tree
{
    int count;         //用来标记该节点是个可以形成一个单词，如果count！=0，则从根节点到该节点的路径可以形成一个单词
    struct Tree *child[MAX_CHILD];
}Node,*Trie_node;


Node* CreateTrie()                             //创建trie节点树
{
    Node *node=(Node*)malloc(sizeof(Node));
    memset(node,0,sizeof(Node));
    return node;
}



void insert_node(Trie_node root,char *str)      //trie树插入结点
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


void search_str(Trie_node root,char *str)             //查找串是否在该trie树中
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
            cout<<"该字符串不在trie树中，但该串是某个单词的前缀\n";
        else
            cout<<"该字符串在该trie树中\n";
    }
    else
        cout<<"该字符串不在trie树中\n";
}


void del(Trie_node root)      //释放整个字典树占的堆空间
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
    cout<<"请输入要创建的trie树的大小：";
    cin>>n;
    Trie_node root=NULL;
    root=CreateTrie();
    if(root==NULL)
        cout<<"创建trie树失败";
    for(i=0;i<n;i++)
    {
        scanf("%s",str);
        insert_node(root,str);
    }
    cout<<"trie树已建立完成\n";
    cout<<"请输入要查询的字符串:";
    while(scanf("%s",str)!=NULL)
    {
        search_str(root,str);

    }
    return 0;


}

//////////////////////////////////////////////////////////////////////////////////////
//Version III

/*
Name: Trie树的基本实现
Author: MaiK
Description: Trie树的基本实现 ,包括查找 插入和删除操作*/
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
