#include "stdio.h"
#include "stdlib.h"

#define m 100


struct ptree              //定义二叉树结点类型
{
    int w;                   //定义结点权值
    struct ptree *lchild;     //定义左子结点指针
    struct ptree *rchild;     //定义右子结点指针
};


struct pforest              //定义链表结点类型
{
    struct pforest *link;
    struct ptree *root;
};


int WPL=0;                  //初始化WTL为0
struct ptree *hafm();
void travel();
struct pforest *inforest(struct pforest*f, struct ptree *t);


void travel(struct ptree *head,int n)                    

{
    //为验证harfm算法的正确性进行的遍历
    struct ptree *p;
    p=head;
    if(p!=NULL)
    {
        if((p->lchild)==NULL && (p->rchild)==NULL) //如果是叶子结点
        {
            printf("%d ",p->w);
            printf("the hops of the node is: %d/n",n);
            WPL=WPL+n*(p->w);    //计算权值
        }//if
        travel(p->lchild,n+1);
        travel(p->rchild,n+1);
    }//if
}//travel


struct ptree *hafm(int n, int w[m])
{
    struct pforest *p1,*p2,*f;
    struct ptree *ti,*t,*t1,*t2;
    int i;

    f=(pforest *)malloc(sizeof(pforest));
    f->link=NULL;
    for(i=1;i<=n;i++)          //产生n棵只有根结点的二叉树
    {
        ti=(ptree*)malloc(sizeof(ptree));//开辟新的结点空间
        ti->w=w[i];               //给结点赋权值
        ti->lchild=NULL;
        ti->rchild=NULL;
        f=inforest(f, ti);
        //按权值从小到大的顺序将结点从上到下地挂在一颗树上

    }//for

    while(((f->link)->link)!=NULL)//至少有二棵二叉树
    {
        p1=f->link;
        p2=p1->link;
        f->link=p2->link;           //取出前两棵树
        t1=p1->root;
        t2=p2->root;

        free(p1);                 //释放p1
        free(p2);                 //释放p2
        t=(ptree *)malloc(sizeof(ptree));   //开辟新的结点空间
        t->w = (t1->w)+(t2->w);        //权相加
        t->lchild=t1;
        t->rchild=t2;             //产生新二叉树
        f=inforest(f,t);
    }//while

    p1=f->link;
    t=p1->root;
    free(f);

    return(t);                  //返回t

}



pforest *inforest(struct pforest *f,structptree *t)
{

    //按权值从小到大的顺序将结点从上到下地挂在一颗树上

    struct pforest *p, *q, *r;
    struct ptree *ti;
    r=(pforest *)malloc(sizeof(pforest)); //开辟新的结点空间
    r->root=t;
    q=f;
    p=f->link;
    while (p!=NULL)            //寻找插入位置

    {

        ti=p->root;
        if(t->w > ti->w)         //如果t的权值大于ti的权值
        {
            q=p;
            p=p->link;             //p向后寻找
        }//if

        else

            p=NULL;                  //强迫退出循环

    }//while

    r->link=q->link;
    q->link=r;                 //r接在q的后面
    return(f);                 //返回f

}



void InPut(int &n,int w[m])
{

    printf("please input the sum ofnode/n"); //提示输入结点数

    scanf("%d",&n);      //输入结点数

    printf ("please input weight of everynode/n"); //提示输入每个结点的权值

    for(int i=1;i<=n;i++)

        scanf("%d",&w[i]);  //输入每个结点权值

}



int main( )

{

    struct ptree *head;

    int n,w[m];

    InPut(n,w);

    head=hafm(n,w);

    travel(head,0);

    printf("The length of the best path isWPL=%d", WPL);//输出最佳路径权值之和

    return 1;

}



