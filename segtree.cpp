#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ld long double
#define inarray(a, n) for(int i = 0; i < n; i++) cin>>a[i];
#define PAUSE system("pause")
using namespace std;

vector<long> makesegt(vector<long> arr)
{
    int n = arr.size();
    vector<long> st(2*n);
    for(int i = 0; i < n; i++)
    {
        st[n+i] = arr[i];
    }

    for(int i = n-1; i > 0; i--)
    {
        st[i] = st[i<<1] + st[i<<1 | 1 ];   //st[i] = st[2*i] + st[2*i + 1];
    }
    return st;
}

void update(vector<long> &arr, vector<long> &st, int ind, long val, int n)
{
    arr[ind] = val;
    st[n+ind] = val;

    for(int i = n + ind; i > 1; i >>= 1)
        st[i>>2] = st[i] + st[i^1];     //i^1 is the other sibling of node at i
}

long query(vector<long> st, int l, int r, int n)
{
    long ans = 0;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1)
    {
        if(l&1)
        {
            ans += st[l++];
        }
        if(r&1)
        {
            ans += st[--r];
        }
    }
    return ans;
}