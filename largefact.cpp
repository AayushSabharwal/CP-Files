#include<bits/stdc++.h>


#define forn(i,a,b) for (int i = a; i <b; i++)
#define fornn(i,a,b) for (int i = a; i <=b; i++)

#define MAX 10000



typedef long long ll;


using namespace std;

#define WINPAUSE system("pause")

int multiply(int x,int a[],int size)
{  int carry=0;
    for(int i=0;i<size;i++)
    {
        int o=a[i]*x+carry;
        carry=o/10;
        a[i]=o%10;


    }
    while(carry>0)
    {
        a[size]=carry%10;
        size++;
        carry/=10;
    }
    return size;
}
string getString(char x) 
{ 
     
    string s(1, x); 
  
    return s;    
}
string factorial(int x)
{
    int a[MAX];
    a[0]=1;
    int size=1;
    fornn(i,2,x)
    {
        size=multiply(i,a,size);
    }
    string s="";
    forn(i,0,size)
    { char c='0'+a[i];
        s=getString(c)+s;
    }
    //reverse(s.begin(),s.end());
    return s;
}

