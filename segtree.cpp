#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ld long double
#define inarray(a, n) for(int i = 0; i < n; i++) cin>>a[i];
#define PAUSE system("pause")
using namespace std;

ll fastexp(ll a, ll b)
{
    ll ans = 1;
    while(b)
    {
        if(b&1)
        {
            ans *= a;
        }
        b >>= 1;
        a = a*a;
    }
    return ans;
}

long constructstreeutil(vector<long> arr, vector<long> &stree, int s, int e, int i)
{
    if(s == e)
    {
        stree[i] = arr[s];
        return arr[s];
    }

    int mid = s + (e-s)/2;
    stree[i] = constructstreeutil(arr, stree, s, mid, 2*i + 1) + constructstreeutil(arr, stree, mid+1, e, 2*i+2);
    return stree[i];
}  

vector<long> constructstree(vector<long> arr)
{
    int n = arr.size();
    int height = ceil(log2(n));
    vector<long> stree(2*fastexp(2, height) - 1);
    
    constructstreeutil(arr, stree, 0, n-1, 0);
    return stree;
}

// get sum from l to r. i is current index in stree, s and e are the left and right bounds of that node
long evalstreeutil(vector<long> stree, int l, int r, int i, int s, int e)
{
    if(l <= s && e <= r)
    {
        return stree[i];
    }
    if(e < l || r < s)
    {
        return 0;
    }

    int mid = s + (e-s)/2;
    return evalstreeutil(stree, l, r, 2*i + 1, s, mid) + evalstreeutil(stree, l, r, 2*i + 2, mid+1, e);
}

// get sum from l to r. n is size of array
long evalstree(vector<long> stree, int n, int l, int r)
{
    evalstreeutil(stree, l, r, 0, 0, n - 1);
}

void updatestreeutil(vector<long> &stree, int nodeI, int arrI, long diff, int s, int e)
{
    if(s > arrI || e < arrI)
    {
        return;
    }

    stree[nodeI] += diff;
    if(s == e)
    {
        return;
    }
    int mid = s + (e-s)/2;
    updatestreeutil(stree, 2*nodeI + 1, arrI, diff, s, mid);
    updatestreeutil(stree, 2*nodeI + 2, arrI, diff, mid+1, e);
}

// update stree by changing arr[arrI] to val. n = arr.size() 
void updatestree(vector<long> &stree, vector<long> &arr, int n, int arrI, long val)
{
    long diff = val - arr[arrI];
    arr[arrI] += diff;
    updatestreeutil(stree, 0, arrI, diff, 0, n-1);
}

