#include<bits/stdc++.h>
using namespace std;
#define MAX 1001

float dp[MAX][MAX]={0};
float up_g[MAX][MAX]={0};
float lw_g[MAX][MAX]={0};

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
        exit(10);
    }
}

float gap(int k)
{
    return 5*k+0.5;
}

void print(int s1,int s2)
{
    for(int i=0; i<=s1; i++)
    {
        for(int j=0; j<=s2; j++)
        {
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for(int i=0; i<=s1; i++)
    {
        for(int j=0; j<=s2; j++)
        {
            cout<<up_g[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for(int i=0; i<=s1; i++)
    {
        for(int j=0; j<=s2; j++)
        {
            cout<<lw_g[i][j]<<" ";
        }
        cout<<endl;
    }
}

float max_score(string s1, string s2)
{
    int s1l = s1.length();
    int s2l = s2.length();
    for(int i=1; i<=s1l; i++)
    {
        dp[i][0] = 0-gap(i);
        up_g[i][0] = 0-gap(i);
        lw_g[i][0] = 0-gap(i);
    }
    for(int i=1; i<=s2l; i++)
    {
        dp[0][i] = 0-gap(i);
        lw_g[0][i] = 0-gap(i);
        up_g[0][i] = 0-gap(i);
    }
    for(int i=1; i<=s1l; i++)
    {
        for(int j=1; j<=s2l; j++)
        {
            dp[i][j] = s[c(s1[i-1])][c(s2[j-1])]+max(dp[i-1][j-1],max(up_g[i-1][j-1],lw_g[i-1][j-1]));
            up_g[i][j]=-1*INT_MAX;
            lw_g[i][j]=-1*INT_MAX;
            for(int k=1;k<=i;k++)
            {
                up_g[i][j]=max(up_g[i][j],max(dp[i-k][j]-gap(k),lw_g[i-k][j]-gap(k)));
            }
            for(int k=1;k<=j;k++)
            {
                lw_g[i][j]=max(lw_g[i][j],max(dp[i][j-k]-gap(k),up_g[i][j-k]-gap(k)));
            }
        }
    }
    return max(dp[s1l][s2l],max(lw_g[s1l][s2l],up_g[s1l][s2l]));
}

pair<string,string> path(string s1, string s2,float val)
{
    int i = s1.length();
    int j = s2.length();
    string f = "", l = "";
    while((i!=0) || (j!=0))
    {
        for(int k=1;k<=i;k++)
        {
            if((val == dp[i-k][j]-gap(k)) or (val == lw_g[i-k][j]-gap(k)))
            {
                int e = k;
                while(e--)
                {
                    f = s1[i-1] + f;
                    l = '_'+l;
                    i--;
                }
                val+=gap(k);
                break;
            }
        }
        for(int k=1;k<=j;k++)
        {
            if ((val == dp[i][j-k]-gap(k)) or (val == up_g[i][j-k]-gap(k)))
            {
                int e = k;
                while(e--)
                {
                    f = '_' + f;
                    l = s2[j-1] + l;
                    j--;
                }
                val+=gap(k);
                break;
            }
        }
        if(val==dp[i][j] )
        {
            f = s1[i-1] + f;
            l = s2[j-1] + l;
            val-=s[c(s1[i-1])][c(s2[j-1])];
            i = i-1;
            j =j-1;
        }
        //cout<<val<<endl;
    }
    return make_pair(f, l);
}

int main()
{
    string a, b;
    cin>>a>>b;
    string c, d;

    float max_s = max_score(a, b);
    cout<<"\nMaximum score attained - "<<max_s<<endl;
    //print(a.length(),b.length());
    c = path(a, b, max_s).first;
    d = path(a, b, max_s).second;

    
    cout<<"\nAttained Matching of strings"<<endl;
    cout<<"1)\t"<<c<<endl;
    cout<<"2)\t"<<d<<endl;

    return 0;
}
//LINEAR __VERSION_