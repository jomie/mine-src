#include <iostream>
#include <stdio.h>


using namespace std;

struct Read {
    float num[9];
    struct Read *next;
    Read():next(NULL)
    {
        for (int i = 0; i < 9; i++)
            num[i] = 0;
    }
};


struct Read * read(char files[][50], int n)
{
    FILE *fp[n];
    for (int i = 0; i < n; i++) {
        fp[i] = fopen(files[i], "r");
    }
    Read *hp = new Read();

    Read *p = hp;
    Read *tmp = NULL;
    int hash[3] = {1, 1, 1};
    int flag = 0;
    int x = 0;
    while(1) {
        tmp = new Read();
        int i ;
        for (i = 0; i < 6; i++) {
            tmp->num[i] = p->num[i + 1];
        }

        for (int j = 0 ; j < 3; j++) {
            if (hash[j] && fscanf(fp[j], "%f ", &(tmp->num[i++])) == EOF)
              {
                  hash[j] = 0;
                  flag++;
              }
        }

        if (flag == 3)
            break;
        p->next = tmp;
        p = tmp;
    }
    return hp;
}

void write(Read *p)
{
    if (p == NULL)
        return;
    char output[] = "tmp_file.txt";
    FILE *outf = fopen(output, "w+");

    Read *tmp = p;

    while (tmp) {
        for (int i = 0; i < 9; i++)
            fprintf(outf, "%.3f ", tmp->num[i]);
        fprintf(outf, "\n");
        tmp = tmp->next;
    }
}


void destory(Read *p)
{
    Read *tmp = NULL;
    while(p) {
        tmp = p ;
        p = p->next;
        delete tmp;
    }

}
int main()
{
    char infile[3][50];
    cout << "please input your files, and the number is 3!" << endl;
    for (int i = 0; i < 3; i++) {
        cin >> infile[i];
    }

    for (int i = 0; i < 3; i++)
        cout << infile[i];

    Read *h = read(infile, 3);
    write(h);
    destory(h);
    return 0;

}
