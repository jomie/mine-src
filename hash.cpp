//����prepareCryptTable���µĺ�������һ������Ϊ0x500����10��������1280����cryptTable[0x500]
void prepareCryptTable()
{
    unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;

    for( index1 = 0; index1 < 0x100; index1++ )
    {
        for( index2 = index1, i = 0; i < 5; i++, index2 += 0x100 )
        {
            unsigned long temp1, temp2;

            seed = (seed * 125 + 3) % 0x2AAAAB;
            temp1 = (seed & 0xFFFF) << 0x10;

            seed = (seed * 125 + 3) % 0x2AAAAB;
            temp2 = (seed & 0xFFFF);

            cryptTable[index2] = ( temp1 | temp2 );
        }
    }
}

//����HashString���º�������lpszFileName �ַ�����hashֵ������dwHashType Ϊhash�����ͣ�
unsigned long HashString(const char *lpszkeyName, unsigned long dwHashType )
{
    unsigned char *key  = (unsigned char *)lpszkeyName;
    unsigned long seed1 = 0x7FED7FED;
    unsigned long seed2 = 0xEEEEEEEE;
    int ch;

    while( *key != 0 )
    {
        ch = *key++;
        seed1 = cryptTable[(dwHashType<<8) + ch] ^ (seed1 + seed2);
        seed2 = ch + seed1 + seed2 + (seed2<<5) + 3;
    }
    return seed1;
}

typedef struct
{
    int nHashA;
    int nHashB;
    char bExists;
   ......
} SOMESTRUCTRUE;
//һ�ֿ��ܵĽṹ�嶨�壿

//����GetHashTablePos��������Ϊ��Hash���в����Ƿ����Ŀ���ַ��������򷵻�Ҫ�����ַ�����Hashֵ������return -1.
int GetHashTablePos( har *lpszString, SOMESTRUCTURE *lpTable )
//lpszStringҪ��Hash���в��ҵ��ַ�����lpTableΪ�洢�ַ���Hashֵ��Hash��
{
    int nHash = HashString(lpszString);  //������������HashString������Ҫ�����ַ���lpszString��Hashֵ��
    int nHashPos = nHash % nTableSize;

    if ( lpTable[nHashPos].bExists  &&  !strcmp( lpTable[nHashPos].pString, lpszString ) )
    {  //����ҵ���Hashֵ�ڱ��д��ڣ���Ҫ���ҵ��ַ�������ж�Ӧλ�õ��ַ�����ͬ��
        return nHashPos;    //�����ҵ���Hashֵ
    }
    else
    {
        return -1;
    }
}

//����GetHashTablePos�У�lpszString ΪҪ��hash���в��ҵ��ַ�����lpTable Ϊ�洢�ַ���hashֵ��hash��nTableSize Ϊhash��ĳ��ȣ�
int GetHashTablePos( char *lpszString, MPQHASHTABLE *lpTable, int nTableSize )
{
    const int  HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;

    int  nHash = HashString( lpszString, HASH_OFFSET );
    int  nHashA = HashString( lpszString, HASH_A );
    int  nHashB = HashString( lpszString, HASH_B );
    int  nHashStart = nHash % nTableSize;
    int  nHashPos = nHashStart;

    while ( lpTable[nHashPos].bExists )
   {
//     ����������ж��ڸñ���ʱ���������ַ������ͱȽ�������hashֵ�Ϳ����ˣ����öԽṹ���е��ַ������бȽϡ�
//         ������ӿ����е��ٶȣ�����hash��ռ�õĿռ䣿���ַ���һ��Ӧ����ʲô���ϣ�
        if ( �� lpTable[nHashPos].nHashA == nHashA
        &&  lpTable[nHashPos].nHashB == nHashB )
       {
            return nHashPos;
       }
       else
       {
            nHashPos = (nHashPos + 1) % nTableSize;
       }

        if (nHashPos == nHashStart)
              break;
    }
     return -1;
}
