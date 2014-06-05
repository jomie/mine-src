#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
inline bool leq(int a1, int a2,   int b1, int b2) { // lexic. orderfor pairs
    return(a1< b1 || a1 == b1 && a2 <= b2);
}                                                  // and triples
inline bool leq(int a1, int a2, int a3,   int b1, int b2, int b3) {
    return(a1< b1 || a1 == b1 && leq(a2,a3, b2,b3));
}
// stably sort a[0..n-1] to b[0..n-1] with keys in 0..K fromr
static void radixPass(int* a, int* b, int* r, int n, int K)
{// count occurrences
    int* c = new int[K + 1];                          // counterarray
    for (int i = 0;  i<= K;  i++) c[i] = 0;         // resetcounters
    for (int i = 0;  i< n;  i++) c[r[a[i]]]++;    // countoccurences
    for (int i = 0, sum = 0; i <= K;  i++) { // exclusive prefix sums
        int t =c[i];  c[i] = sum;  sum += t;
    }
    for (int i = 0;  i< n;  i++) b[c[r[a[i]]]++] =a[i];      //sort
    delete [] c;
}

// find the suffix array SA of s[0..n-1] in {1..K}^n
// require s[n]=s[n+1]=s[n+2]=0, n>=2
void suffixArray(int* s, int* SA, int n, int K) {
    intn0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2;
    //n0是字符串中模为的下标的个数，n1，n2依此类推
    int* s12  = new int[n02 + 3]; s12[n02]= s12[n02+1]= s12[n02+2]=0;
    int* SA12 = new int[n02 + 3];SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
    int* s0   = new int[n0];
    int* SA0  = new int[n0];

    // generatepositions of mod 1 and mod  2 suffixes
    // the"+(n0-n1)" adds a dummy mod 1 suffix if n%3 == 1
    for (int i=0, j=0; i < n+(n0-n1);  i++) if (i%3 != 0) s12[j++] = i;
    //将所有模不为的下标存入s12中

    // lsb radix sortthe mod 1 and mod 2 triples
    radixPass(s12 , SA12, s+2, n02, K);
    radixPass(SA12, s12 , s+1, n02, K);
    radixPass(s12 , SA12, s  , n02, K);
    //radixPass实际是一个计数排序
    //对后缀的前三个字符进行三次计数排序完成了对SA12数组的基数排序
    //这个排序是初步的，没有将SA12数组真正地排好序，因为：
    //若SA12数组中几个后缀的前三个字符相等，则起始位置靠后的排在后面

    // findlexicographic names of triples
    int name = 0,c0 = -1, c1 = -1, c2 = -1;
    for (int i = 0;  i< n02;  i++) {
        if(s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2) {
            name++; c0 = s[SA12[i]];  c1 =s[SA12[i]+1];  c2 = s[SA12[i]+2];
        }
        //name是计算后缀数组SA12中前三个字符不完全相同的后缀个数
        //这么判断的原因是：SA12有序，故只有相邻后缀的前三个字符才可能相同
        if (SA12[i]% 3 == 1) { s12[SA12[i]/3]      = name; }// left half
        else                  { s12[SA12[i]/3 + n0] = name;} // right half
        //SA12[i]模不是就是，s12保存的是后缀数组SA12中前三个字符的排位
    }

    // recurse if names are not yet unique
    if (name <n02) {
        //如果name等于n02，意味着SA12前三个字母均不相等，即SA12已有序
        //否则，根据s12的后缀数组与SA12等价，对s12的后缀数组进行排序即可
        suffixArray(s12, SA12, n02, name);
        // store uniquenames in s12 using the suffix array
        for (int i = 0;  i< n02;  i++) s12[SA12[i]] = i + 1;
    } else // generate the suffix array of s12 directly
        for (int i = 0;  i< n02;  i++) SA12[s12[i] - 1] = i;
    //s12保存的是后缀数组SA12中前三个字符的排位
    //在所有后缀前三个字符都不一样的情况下，s12就是后缀的排位

    //至此SA12排序完毕
    //SA12[i]是第i小的后缀的序号(序号从到n02)，s12[i]是序号为i的后缀的排位
    //使用后缀序号而不是实际位置的原因是递归调用suffixArray时不能保留该信息

    // stably sort themod 0 suffixes from SA12 by their first character
    for (int i=0, j=0; i < n02;  i++) if (SA12[i] < n0) s0[j++] = 3*SA12[i];
    //将SA12中所有的模为的后缀的实际位置减去按序存储在s0中
    //注意后缀序号到实际位置的转化需将前者乘
    //这意味着首先已经利用模为的后缀对SA0进行了初步排序
    //只需要采用一次计数排序即可对SA0完成基数排序的最后一步
    radixPass(s0, SA0, s, n0, K);

    //最后一步，对有序表SA12和SA0进行归并
    // merge sorted SA0suffixes and sorted SA12 suffixes
    for (int p=0, t=n0-n1,  k=0;  k < n; k++) {
#define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) *3 + 2)
        int i =GetI(); // pos of current offset 12 suffix
        int j =SA0[p]; // pos of current offset 0  suffix
        if (SA12[t]< n0 ?
            leq(s[i],       s12[SA12[t] + n0], s[j],       s12[j/3]) :
            leq(s[i],s[i+1],s12[SA12[t]-n0+1],s[j],s[j+1],s12[j/3+n0]))
        { // suffix fromSA12 is smaller
            SA[k] = i;  t++;
            if (t ==n02) { // done --- only SA0 suffixes left
                for(k++;  p < n0;  p++, k++) SA[k] = SA0[p];
            }
        } else {
            SA[k] = j;  p++;
            if (p ==n0)  { // done--- only SA12 suffixes left
                for(k++;  t < n02;  t++, k++) SA[k] = GetI();
            }
        }
    }
    delete []s12; delete [] SA12; delete[] SA0; delete [] s0;
}
void suffixArrayHeight(int *s, int *SA, int n, int K, int *rank, int *height)
{
    int i, j,h;
    for(i = 0;i < n; i++){
        rank[SA[i]] = i;
        //rank和SA互逆，即SA[rank[i]] == i&&rank[SA[i]] == i
    }
    h = 0;
    for(i = 0;i < n; i++){
        if(rank[i]== 0){
            height[rank[i]] = 0;
        }else{
            j = SA[rank[i] - 1];
            //如果用前缀的第一个字符的下标来标识前缀
            //那么，j是前缀i == SA[rank[i]]的左邻前缀
            while(s[i+ h] == s[j + h]){
                h++;
                //如果没有关于h[i]和h[i+1]的大小关系的定理，h需要从开始
            }
            height[rank[i]] = h;
            //求出了h[i]的值
            if(h> 0)
            {
                h--;
                //h[i+1]的值大于或等于h[i]-1
            }
        }
    }
}
#define maxStrNum 4001
#define maxStrLen 201
#define maxNum (maxStrNum * maxStrLen + 3)
int s[maxNum];
int SA[maxNum];
int rank[maxNum];
int height[maxNum];
int sequence[maxNum];//对应的字符串的序号
#define keyNum ('z' - 'a' + 1)
bool visited[maxStrNum];
char LCS[maxStrLen];
int n;
int N;
bool check(int A)
{
    int i, j,k;
    int temp;
    if(A <=0)
        return true;
    for (i =1;i < n; i++)
    {
        //必有A>0，且height[0]==0,故此i可以不从开始
        if(height[i]< A)
        {
            continue;
        }
        for(j =i + 1; j < n; j++)
        {
            if(height[j]< A)
            {
                break;
            }
        }
        if(j -i + 1 < N)
        {//不可能满足所有字符串都在区间[i - 1, j)中有对应的后缀SA[k]
            i = j;
            continue;
        }
        memset(visited, 0,sizeof(visited));
        for(k =i - 1; k < j; k++){
            //这里k必须从i-1开始而不是i开始，同时要防止i==0时越界
            temp = sequence[SA[k]];
            if(temp!= -1)
                visited[temp] = true;
        }
        for(k =0; k < N; k++){
            if(visited[k]== false)
            {
                break;
            }
        }
        if(k ==N)
        {
            returntrue;
        }
        i = j;
        //必有：height[j]< A || j == n
        //这里不能i = j +1;，因为还有i++
    }
    return false;
}
bool findLeast(int A)
{
    int i, j,k;
    charstr[maxStrLen];
    boolsuccess;
    if(A <=0)
        return true;
    success = false;
    for (i =1;i < n;i++)
    {
        //这里可以知道必有A>0，且height[0]==0
        //故此i可以不从开始
        if(height[i]< A)
        {
            continue;
        }
        for(j =i + 1; j < n; j++)
        {
            if(height[j]< A)
            {
                break;
            }
        }
        if(j -i + 1 < N)
        {//不可能满足所有字符串都在区间[i - 1, j)中有对应的后缀SA[k]
            i = j;
            continue;
        }
        memset(visited, 0,sizeof(visited));
        for(k =i - 1; k < j; k++){
            //这里k必须从i-1开始而不是i开始，同时要防止i==0时越界
            if(k>= 0)
                visited[sequence[SA[k]]] = true;
        }
        for(k =0; k < N; k++){
            if(visited[k]== false)
            {
                break;
            }
        }
        if(k ==N)
        {
            success = true;
            for(k= 0; k < A; k++){
                str[k] = s[SA[i] + k] + 'a' - 1;
            }
            str[A] = NULL;
            if(LCS[0]== NULL || strcmp(str, LCS) < 0)
            {
                strcpy(LCS, str);
            }
        }
        i = j;
        //i = j + 1;
        //必有：height[j]< A || j == n
    }
    returnsuccess;
}
int dichotomize(int top)
{
    int low,high, mid;
    low = 0;
    high = top;
    while(low +1 < high){
        mid = (low + high) / 2;
        if(check(mid))
            low = mid;
        elsehigh = mid - 1;
    }
    if(check(high))
        low = high;
    return low;
}
#define MAX 0x7FFFFFFF
int main()
{
    int i, j;
    int b;
    int min;
    charstr[maxStrLen];
    int len;
    int max;
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(scanf("%d",&N)){
        if(N ==0)
            break;
        n = 0;
        memset(sequence, 0xFF, sizeof(sequence));
        min = MAX;
        for (i= 0; i < N; i++)
        {
            scanf("%s",str);
            len = strlen(str);
            if(min> len)
            {
                min = len;
            }
            for(j = 0; j < len; j++){
                sequence[n] = i;
                s[n++] = str[j] - 'a' + 1;
            }
            if(i < N - 1)
                s[n++]= keyNum + i + 1;
        }
        b = keyNum + N - 1;
        s[n] = s[n+1] = s[n+2] = SA[n] =SA[n+1] = SA[n+2] = 0;
        suffixArray(s, SA, n, b);
        suffixArrayHeight(s, SA, n, b, rank,height);
        max = dichotomize(min);
        if(max== 0){
            cout << "IDENTITY LOST" << endl;
        }else{
            memset(LCS, 0, sizeof(LCS));
            findLeast(max);
            cout << LCS << endl;
        }
    }
    return 1;
}
