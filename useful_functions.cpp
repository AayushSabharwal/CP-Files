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

/* #region BigIntegers */
// add string representations of numbers
string sadd(string a, string b)
{
    int na = a.size();
    int nb = b.size();
    while(na < nb)
    {
        na++;
        a = '0' + a;
    }
    while(nb < na)
    {
        nb++;
        b = '0' + b;
    }

    string ans = "";
    int ind = na - 1;
    int carry = 0;
    while(ind >= 0)
    {
        int val = a[ind] + b[ind] - 2 * '0' + carry;
        carry = val/10;
        ans = char(val%10 + '0') + ans;
        ind--;
    }
    if(carry)
    {
        ans = char(carry + '0') + ans;
    }
    return ans;
}

// string a - string b. Doesn't do negative, ensure a > b
string ssub(string a, string b)
{
    int na = a.size();
    int nb = b.size();

    while(nb < na)
    {
        nb++;
        b = '0' + b;
    }
    int digits[na];
    memset(digits, 0, sizeof(digits));
    for(int i = 0; i < nb; i++)
    {
        int da = a[na - 1 - i] - '0';
        int db = b[nb - 1 - i] - '0';
        if(da >= db)
        {
            digits[na - 1 - i] += da - db;
        }
        else
        {
            da += 10;
            digits[na - 2 - i]--;
            digits[na - 1 - i] += da - db;
        }
    }
    for(int i = 1; i < na; i++)
    {
        if(digits[i] == -1)
        {
            digits[i-1]--;
            digits[i] = 9;
        }
    }
    string ans = "";
    for(int i = 0; i < na; i++)
    {
        ans = ans + char(digits[i] + '0');
    }
    while(ans[0] == '0')
    {
        ans = ans.substr(1, ans.size() - 1);
    }
    return ans;
}

// add all string represented numbers in list
string saddall(list<string> all)
{
    int nall = all.size();
    while(nall >= 2)
    {
        string a = all.front();
        all.pop_front();
        string b = all.front();
        all.pop_front();
        a = sadd(a, b);
        all.push_back(a);
        nall--;
    }
    return all.front();
}

// add all string represented numbers in vector
string saddall(vector<string> all)
{
    return saddall(list<string>(all.begin(), all.end()));
}

// multiply string representations of numbers
string smul(string a, string b)
{
    int na = a.size();
    int nb = b.size();
    if(na > nb)
    {
        swap(na, nb);
        swap(a, b);
    }

    list<string> nums;
    for(int i = na-1; i >= 0; i--)
    {
        int da = a[i] - '0';
        int carry = 0;
        string num;
        for(int j = 0; j < na - 1 - i; j++)
        {
            num = num + '0';
        }

        for(int j = nb - 1; j >= 0; j--)
        {
            int db = b[j] - '0';
            int val = da * db + carry;
            num = char(val%10 + '0') + num;
            carry = val/10;
        }
        while(carry)
        {
            num = char(carry%10 + '0') + num;
            carry/=10;
        }
        nums.push_back(num);
    }

    return saddall(nums);
}

// n!
unordered_map<string, string> sfactcache;
string sfact(string n)
{
    if(n == "1" || n == "0")
    {
        return "1";
    }
    
    if(sfactcache.find(n) == sfactcache.end())
    {
        string ans = smul(n, sfact(ssub(n, "1")));
        sfactcache[n] = ans;
    }
    return sfactcache[n];
}
/* #endregion */

