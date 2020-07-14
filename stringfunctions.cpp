#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ld long double
#define inarray(a, n) for(int i = 0; i < n; i++) cin>>a[i];
#define PAUSE system("pause")
using namespace std;

//splits s by delimiter
vector<string> split(string s, char delim = ' ')
{
    vector<string> ans;
    int n = s.size();
    int prev = 0;
    while(s[0] == delim)
    {
        s = s.substr(1);
        n--;
    }
    for(int i = 0; i < n; i++)
    {
        if(s[i] == delim)
        {
            if(prev == i-1)
            {
                prev = i;
                continue;
            }
            ans.push_back(s.substr(prev, i-prev));
            prev = i;
        }
    }
    return ans;
}

//checks if s is a number
bool is_number(string s)
{
    auto it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}