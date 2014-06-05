class Solution {
public:
    string addBinary(string a, string b) {
        int alen = a.size();
        int blen = b.size();
        if (!alen && !blen)
            return a;
        if (alen && !blen)
            return a;
        if (!alen && blen)
            return b;

        int forwards = 0;
        string result;
        int ai , bi;

        for ( ai = 0, bi = 0; ai < alen && bi < blen; ai++, bi++)
        {
            if (a[ai] = '0' && b[bi] == '0')
            {
                if (forwards == 0)
                    result.push_back('0');
                else {
                    result.push_back('1');
                    forwards = 0;
                }
            }else if (a[ai] == '1' && b[bi] == '1')
            {
                if (forwards == 0)
                {
                    result.push_back('0');
                    forwards = 1;
                }else {
                    result.push_back('1');
                }
            }else if ((a[ai] == '0' && b[bi] == '1') ||
                      (a[ai] == '1' && b[bi] == '0'))
            {
                if (forwards == 0)
                {
                    result.push_back('1');
                }else
                {
                    result.push_back('0');
                }

            }else {
                return NULL;
            }

        }
        while (ai < alen)
        {
            if (forwards == 0)
            {
                result.push_back(a[ai]);
            } else
            {
                if (a[ai] == '0')
                {
                    result.push_back('1');
                    forwards = 0;
                }else {
                    result.push_back('0');
                }
            }
        }
        while (bi < blen)
        {
            if (forwards == 0)
            {
                result.push_back(b[bi]);
            } else
            {
                if (b[bi] == '0')
                {
                    result.push_back('1');
                    forwards = 0;
                }else {
                    result.push_back('0');
                }
            }
        }

        bi = result.size() - 1;
        ai = 0;
        char tmp ;
        while (ai < bi)
        {
            tmp = result[ai];
            result[ai] = result[bi];
            result[bi] = tmp;
            ai++;
            bi--;
        }

    }
};
