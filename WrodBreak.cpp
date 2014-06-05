class Solution {
public:
    bool dictContain(unordered_set<string> &dict, string s)
    {
        unordered_set<string>::iterator ite = dict.find(s);
        if(ite != dict.end())
            return true;
        else return false;
    }

    bool wordBreak(string s, unordered_set<string> &dict)
    {
        // Note: The Solution object is instantiated only once and is reused by each test case.
        if(dict.empty())
            return false;
        const int len = s.size();
        bool canBreak[len]; //canBreak[i] = true ��ʾs[0~i]�Ƿ���break
        memset(canBreak, 0, sizeof(bool)*len);
        for(int i = 1; i <= len; i++)
        {
            if(canBreak[i-1] == false && dictContain(dict, s.substr(0, i)))
                canBreak[i-1] = true;

            if(canBreak[i-1] == true)
            {
                if(i == len)return true;
                for(int j = 1; j <= len - i; j++)
                {
                    if(canBreak[j+i-1] == false && dictContain(dict,s.substr(i, j)))
                        canBreak[j+i-1] = true;

                    if(j == len - i && canBreak[j+i-1] == true)return true;

                }
            }

        }

        return false;
    }


};
