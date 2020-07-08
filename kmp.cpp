#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ld long double
#define inarray(a, n) for(int i = 0; i < n; i++) cin>>a[i];
#define PAUSE system("pause")
using namespace std;

void findlps(string pat, int n, vector<int> &lps)
{
    int prev = 0;
    lps = vector<int>(n, 0);
    int i = 1;
    while(i < n)
    {
        if(pat[i] == pat[prev])
        {
            lps[i++] = ++prev;
        }
        else
        {
            if(prev != 0)
            {
                prev = lps[prev-1];
            }
            else
            {
                lps[i++] = 0;
            }
        }
    }
}

void kmp(string s, string pat, int ns, int npat, vector<int> lps, vector<int> &matches)
{
    int i = 0, j = 0;
    while(i < ns)
    {
        if(pat[j] == s[i])
        {
            i++, j++;
        }

        if(j == npat)
        {
            matches.push_back(i-j);
            j = lps[j-1];
        }
        else if(i < ns && pat[j] != s[i])
        {
            if(j)
            {
                j = lps[j-1];
            }
            else
            {
                i++;
            }
        }
    }
}