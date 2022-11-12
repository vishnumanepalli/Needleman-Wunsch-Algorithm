#include<bits/stdc++.h>
using namespace std;
#define MAX 1001

int dp[MAX][MAX][3]={0};

int s[4][4]=
{
    10, -1, -3, -4,
    -1,  7, -5, -3,
    -3, -5,  9,  0,
    -4, -3,  0,  8
};

int c(char a)
{
    if(a == 'A')
        return 0;
    else if(a == 'G')
        return 1;
    else if(a == 'C')
        return 2;
    else if(a == 'T')
        return 3;
    else
    {
        cout<<"Wrong Format "<<a<<endl;
        exit(0);
    }
}
void print(int s1,int s2)
{
    for(int i=0; i<=s1; i++)
    {
        for(int j=0; j<=s2; j++)
        {
            cout<<dp[i][j][0]<<" ";
        }
        cout<<endl;
    }
}

int max_score(string s1, string s2, int g)
{
    int s1l = s1.length();
    int s2l = s2.length();
    int x, y, z;
    for(int i=1; i<=s1l; i++)
    {
        dp[i][0][0] = dp[i-1][0][0]-g;
        dp[i][0][1] = i-1;
        dp[i][0][2] = 0;
    }
    for(int i=1; i<=s2l; i++)
    {
        dp[0][i][0] = dp[0][i-1][0]-g;
        dp[0][i][1] = 0;
        dp[0][i][2] = i-1;
    }
    for(int i=1; i<=s1l; i++)
    {
        for(int j=1; j<=s2l; j++)
        {
            x = dp[i-1][j][0]-g;
            y = dp[i-1][j-1][0] + s[c(s1[i-1])][c(s2[j-1])];
            z = dp[i][j-1][0]-g;

            if((y >= x) && (y >= z))
            {
                dp[i][j][0] = y;
                dp[i][j][1] = i-1;
                dp[i][j][2] = j-1;
            }
            else if((x >= y) && (x >= z))
            {
                dp[i][j][0] = x;
                dp[i][j][1] = i-1;
                dp[i][j][2] = j;
            }
            else
            {
                dp[i][j][0] = z;
                dp[i][j][1] = i;
                dp[i][j][2] = j-1;
            }
        }
    }
    return dp[s1l][s2l][0];
}

pair<string,string> path(string s1, string s2)
{
    int s1l = s1.length();
    int s2l = s2.length();
    string f = "", l = "";
    int i = s1l, j = s2l;
    int k, m;
    while((i!=0) || (j!=0))
    {
        k = dp[i][j][1];
        m = dp[i][j][2];
        if((i-k==1) && (j-m==1))
        {
            f = s1[i-1] + f;
            l = s2[j-1] + l;
        }
        else if((i-k==1) && (j-m==0))
        {
            f = s1[i-1] + f;
            l = '_'+l;
        }
        else
        {
            f = '_'+f;
            l = s2[j-1] + l;
        }
        i = k;
        j = m;
    }
    return make_pair(f, l);
}

int main()
{
    string a, b;
    cin>>a>>b;
    string c, d;

    int max_s = max_score(a, b, 5);
    c = path(a, b).first;
    d = path(a, b).second;

    cout<<"\nMaximum score attained - "<<max_s<<endl;
    cout<<"\nAttained Matching of strings"<<endl;
    cout<<"1)\t"<<c<<endl;
    cout<<"2)\t"<<d<<endl;

    //print(a.length(),b.length());

    return 0;
}