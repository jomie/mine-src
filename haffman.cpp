#include "stdio.h"
#include "stdlib.h"

#define m 100


struct ptree              //����������������
{
    int w;                   //������Ȩֵ
    struct ptree *lchild;     //�������ӽ��ָ��
    struct ptree *rchild;     //�������ӽ��ָ��
};


struct pforest              //��������������
{
    struct pforest *link;
    struct ptree *root;
};


int WPL=0;                  //��ʼ��WTLΪ0
struct ptree *hafm();
void travel();
struct pforest *inforest(struct pforest*f, struct ptree *t);


void travel(struct ptree *head,int n)                    

{
    //Ϊ��֤harfm�㷨����ȷ�Խ��еı���
    struct ptree *p;
    p=head;
    if(p!=NULL)
    {
        if((p->lchild)==NULL && (p->rchild)==NULL) //�����Ҷ�ӽ��
        {
            printf("%d ",p->w);
            printf("the hops of the node is: %d/n",n);
            WPL=WPL+n*(p->w);    //����Ȩֵ
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
    for(i=1;i<=n;i++)          //����n��ֻ�и����Ķ�����
    {
        ti=(ptree*)malloc(sizeof(ptree));//�����µĽ��ռ�
        ti->w=w[i];               //����㸳Ȩֵ
        ti->lchild=NULL;
        ti->rchild=NULL;
        f=inforest(f, ti);
        //��Ȩֵ��С�����˳�򽫽����ϵ��µع���һ������

    }//for

    while(((f->link)->link)!=NULL)//�����ж��ö�����
    {
        p1=f->link;
        p2=p1->link;
        f->link=p2->link;           //ȡ��ǰ������
        t1=p1->root;
        t2=p2->root;

        free(p1);                 //�ͷ�p1
        free(p2);                 //�ͷ�p2
        t=(ptree *)malloc(sizeof(ptree));   //�����µĽ��ռ�
        t->w = (t1->w)+(t2->w);        //Ȩ���
        t->lchild=t1;
        t->rchild=t2;             //�����¶�����
        f=inforest(f,t);
    }//while

    p1=f->link;
    t=p1->root;
    free(f);

    return(t);                  //����t

}



pforest *inforest(struct pforest *f,structptree *t)
{

    //��Ȩֵ��С�����˳�򽫽����ϵ��µع���һ������

    struct pforest *p, *q, *r;
    struct ptree *ti;
    r=(pforest *)malloc(sizeof(pforest)); //�����µĽ��ռ�
    r->root=t;
    q=f;
    p=f->link;
    while (p!=NULL)            //Ѱ�Ҳ���λ��

    {

        ti=p->root;
        if(t->w > ti->w)         //���t��Ȩֵ����ti��Ȩֵ
        {
            q=p;
            p=p->link;             //p���Ѱ��
        }//if

        else

            p=NULL;                  //ǿ���˳�ѭ��

    }//while

    r->link=q->link;
    q->link=r;                 //r����q�ĺ���
    return(f);                 //����f

}



void InPut(int &n,int w[m])
{

    printf("please input the sum ofnode/n"); //��ʾ��������

    scanf("%d",&n);      //��������

    printf ("please input weight of everynode/n"); //��ʾ����ÿ������Ȩֵ

    for(int i=1;i<=n;i++)

        scanf("%d",&w[i]);  //����ÿ�����Ȩֵ

}



int main( )

{

    struct ptree *head;

    int n,w[m];

    InPut(n,w);

    head=hafm(n,w);

    travel(head,0);

    printf("The length of the best path isWPL=%d", WPL);//������·��Ȩֵ֮��

    return 1;

}



