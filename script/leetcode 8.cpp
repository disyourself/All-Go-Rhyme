#include "string"
using namespace std;

class Solution
{
  public:
    int
    myAtoi (string s)
    {
        int  ret = 0;
        int  p = 0;
        bool isnegative = false;

        while (p <= s.length () - 1)
        {
            if (s[p] == ' ')
            {
                ++p;
            }
            else if (s[p] == '-')
            {
                ++p;
                isnegative = true;
                break;
            }
            else
                break;
        }

        while (p <= s.length () - 1)
        {
            if (s[p] == ' ')
                break;
            else
            {
                int bit = s[p] - '0';
                ret = ret * 10 + bit;
                ++p;
            }
        }

        if (isnegative)
            ret *= -1;
        return ret;
    }
};


int
main ()
{

    Solution solu;
    string   s = "42";

    printf ("%d\n", solu.myAtoi (s));

    return 0;
}