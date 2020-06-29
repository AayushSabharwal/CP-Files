#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ld long double
using namespace std;

/* #region Math operations */
// a^b
ll fastexp(ll a, ll b)
{
    if(b == 0)
    {
        return a;
    }
    if(b%2 == 0)
    {
        return pow(fastexp(a, b/2), 2);
    }
    else
    {
        return pow(fastexp(a, b/2), 2) * a;
    }
}

//(a^b)%m
ll fastexpmodm(ll a, ll b, ll m)
{
    ll ans = 1;
    a%=m;
    if(a == 0) return 0;
    while(b)
    {
        if(b%2)
        {
            ans = (ans*b)%m;
        }
        b/=2;
        a = (a*a)%m;
    }
}

//n!
unordered_map<ull, ull> factcache;
ull fact(ull n)
{
    if(n <= 1)
    {
        return 1;
    }
    
    if(factcache.find(n) == factcache.end())
    {
        ll ans = n * fact(n-1);
        factcache[n] = ans;
    }
    return factcache[n];
}
/* #endregion */

