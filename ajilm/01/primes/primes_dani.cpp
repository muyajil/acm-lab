#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n;
        int m;
        cin >> m;
        cin >> n;

        /* Prime sieve for n */
        bool numbers[n+1];
        for(int j = 1; j < n+1; j++)
        {
            numbers[j] = true;
        }
        int p = 1;
        while(p < n+1)
        {
            p++;
            if (!numbers[p])
            {
                continue;
            }
            for (int j = 2 * p; j < n+1; j += p)
            {
                numbers[j] = false;
            }
        }

        /* output */
        numbers[1] = false;
        numbers[0] = false;
        for(;m < n+1;m++)
        {
            if (numbers[m])
            {
                cout << m << endl;
            }
        }
    }
    return 0;
}
