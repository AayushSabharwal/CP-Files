#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ld long double
using namespace std;

/* #region Prime numbers */
void sieve(ll n, vector<ll> &primes)
{
    if(n <= 1)
    {
        primes = vector<ll>();
        return;
    }

    bool p[n+1];
    memset(p, true, sizeof p);
    p[0] = false;
    p[1] = false;
    for(int i = 2; i <= n; i++)
    {
        if(p[i])
        {
            primes.push_back(i);
            for(int j = i * i; j <= n; j+=i)
            {
                p[j] = false;
            }
        }
    }
}

void segsieve(ll n, vector<ll> &primes, ll knowtill = -1)
{
    ll srtn = floor(sqrt(n)) + 1;
    bool starts = false;
    if(primes.empty())
    {
        sieve(srtn, primes);
        starts = true;
    }
    int pn = primes.size();
    ll low, high;
    if(starts)
    {
        low = srtn;
    }
    else
    {
        low = primes[pn - 1];
    }
    if(knowtill != -1 && low < knowtill)
    {
        low = knowtill+1;
    }
    high = low + srtn;
    while(low < n)
    {
        if(high > n)
        {
            high = n;
        }
        bool p[high - low + 1];
        memset(p, true, sizeof(p));
        for(int i = 0; i < pn; i++)
        {
            ll first = floor(low / primes[i]) * primes[i];
            if(first < low)
            {
                first += primes[i];
            }

            for(ll j = first; j <= high; j += primes[i])
            {
                p[j-low] = false;
            }
        }

        for(int i = low; i <= high; i++)
        {
            if(p[i - low])
            {
                primes.push_back(i);
            }
        }

        low += srtn;
        high += srtn;
    }

}

bool isprime(ll n)
{
    if(n == 2)
    {
        return true;
    }
    if(n%2 == 0)
    {
        return false;
    }

    bool ans = true;
    ll l = sqrtl(n)+1;
    for(int i = 3; i < l; i+=2)
    {
        if(n%i == 0)
        {
            ans = false;
            break;
        }
    }
    return ans;
}
/* #endregion */
