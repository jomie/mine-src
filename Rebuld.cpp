struct NODE{
    NODE *pLeft;
    NODE *pRright;
    char chValue;
    NODE(char x): chValue(x), pLeft(NULL), pRright(NULL){}
};

void Rebuild(char *pPreOrder, char *pInOrder, int nTreeLen, NODE **pRoot)
{
    if (!pPreOrder || !pInOrder)
        return ;

    NODE *tmp = new NODE(*pPreOrder);

    if (*pRoot == NULL)
    {
        *pRoot = tmp;        
    }

    if (nTreeLen == 1)
        return; 

    char *pLeftEnd = pInOrder;
    int nTreeLeft = 0;

    while (*pPreOrder != *pLeftEnd){
        if (!pLeftEnd)
            return;

        nTreeLeft++;
        if (nTreeLen < nTreeLeft)
            break;
        pLeftEnd++;
    }

    nTreeLeft = (int)(pLeftEnd - pInOrder);

    int nTreeRight = nTreeLen - nTreeLeft - 1;

    if (nTreeLeft > 0)
        Rebuild(pPreOrder + 1, pInOrder, nTreeLeft, &(*pRoot->left));

    if (nTreeRight > 0)
        Rebuild(pPreOrder + nTreeLeft + 1, pInOrder + nTreeLeft + 1, &(*pRoot->right));

}
