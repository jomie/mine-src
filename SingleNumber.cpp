class Solution {
public:
    int singleNumber(int A[], int n) {
        int tmp = 0;
        for (int i  = 0; i < n ; i++)
        {
            tmp ^= A[i];
        }
        return tmp;
    }

    int singleNumberII(int A[], int n) {
        int bitcount[32] = {0};
         int sign = 0;
         int tmp = 0;
         for (int i = 0; i < n; i++)
         {
             tmp = A[i];
             if (tmp < 0)
             {
                 tmp = -tmp;
                 sign = (sign + 1) % 3;
             }

             for (int j = 0; j < 32; j++)
             {

                 bitcount[j] = (bitcount[j] + (tmp & 0x1)) % 3;
                  tmp >>= 1;
             }
         }

         int res = 0;
         tmp = 1;

         for (int i = 0; i < 32; i++)
         {
             res += (tmp * bitcount[i]);
            tmp <<= 1;
         }

         return sign==0 ? res: res*-1;
    }


};


