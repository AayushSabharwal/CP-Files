#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define ld long double
using namespace std;


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
    if(a == b)
    {
        return "0";
    }
    int na = a.size();
    int nb = b.size();

    while(nb < na)
    {
        nb++;
        b = '0' + b;
    }
    int digits[na];
    memset(digits, 0, sizeof(digits));
    for(int i = na-1; i >= 0; i--)
    {
        int da = a[i] - '0';
        int db = b[i] - '0';
        if(da >= db)
        {
            digits[i] += da - db;
        }
        else
        {
            digits[i-1]--;
            da += 10;
            digits[i] += da - db;
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

// string a / 2. ensure a is even
string sdiv2(string a)
{
    if(a == "0")
    {
        return "0";
    }
    int na = a.size();
    string ans = "";
    int i = 0;
    int carry = 0;
    while(i < na)
    {
        int val = a[i] - '0';
        if(carry)
        {
            val = 10*carry + val;
        }
        if(val == 1)
        {
            val *= 10;
            val += a[i+1] - '0';
            i++;
        }
        carry = val%2;
        val /= 2;
        ans = ans + char(val + '0');
        i++;
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
