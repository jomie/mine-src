long sum1s(long number)
{
    if (number = 0)
        return 0;
    if (number < 0)
        number = -number;

    long count = 0;
    long iFactor = 1;
    long iLowNum = 0;
    long iCurrNum = 0;
    long iHigherNum = 0;

    while (number/iFactor)
    {
        iLowNum = number - (number / iFactor) * iFactor;
        iCurrNum = number / iFactor % 10;
        iHigherNum = number /(iFactor * 10);

        switch(iCurrNum)
        {
        case 0:
            count += iHigherNum * iFactor;
            break;
        case 1:
            count += iHigherNum *  iFactor+ iLowNum + 1;
            break;
        default:
            count += (iHigherNum + 1) * iFactor;
            break;
        }
        iFactor *= 10;
    }
    return count;
}
