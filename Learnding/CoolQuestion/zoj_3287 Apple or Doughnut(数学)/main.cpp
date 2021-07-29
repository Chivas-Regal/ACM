/**********************************************************************************
数学

现在有一个由1*1*1的立方体堆成的立体图形，保证图形是实心的，同时所有的立方体是连通的。立体
图形的中间可能有不规则的洞，如果有则输出“DOUGHNUT”，否则输出“APPLE"。

思路：如果没有洞，则图案赢个是个简单立体图形，可以利用简单多面体的欧拉公式
点数+面数-边数 = 2
关键在于点、边、面数量的统计
点：一个小立方体有8个点，依次判断每个点是否完全在立体图形内，如果该点由八个不同的小立方体所
共同占有，则该点在完全在立体图形内，不计数，否则点数+1.
边：一个小立方体有12条边，将每个点依附于点来考虑，每个点只考虑其i+1、j+1、k+1方向的边，避免重复
计数，同理，如果一个边被四个不同的立方体共同占有，不计数。
面：一个小立方体有六个面，判断它六个面的方向相邻的是否有小立方体，如果有，则不计数。
然后利用公式判断即可。


题目链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827368143
***********************************************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<set>
#include<queue>
#include<stack>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 100100;
const int mod = 1000000007;
int A, B, C, a[12][12][12];
bool exist(int i, int j, int k);
int getpoint();
int getface();
int getedg();

int main()
{
    int n, i, j, k;
    while(~scanf("%d %d %d", &A, &B, &C))
    {
        memset(a, 0, sizeof(a));
        for(i=1;i<=A;i++)
            for(j=1;j<=B;j++)
                for(k=1;k<=C;k++)
                    scanf("%d", &a[i][j][k]);
        int po = getpoint(), ed=getedg(), fa=getface();
        if(po + fa - ed == 2)printf("APPLE\n");
        else printf("DOUGHNUT\n");
    }
    return 0;
}
//判断a[i][j][k]是否存在小立方体
bool exist(int i, int j, int k)
{
    if(i>=1 && i<= A && j>=1 && j<=B && k>=1 && k<=C && a[i][j][k] == 1)
        return 1;
    return 0;
}

int getpoint()
{
    int pnum = 0, i, j, k;
    for(i=0;i<=A;i++)
        for(j=0;j<=B;j++)
            for(k=0;k<=C;k++)
            {
                int ex = 0;
                ex += exist(i,j,k), ex+=exist(i,j+1,k);
                ex += exist(i,j,k+1), ex+=exist(i,j+1,k+1);  
                ex += exist(i+1,j,k), ex+=exist(i+1,j+1,k);
                ex += exist(i+1,j,k+1), ex+=exist(i+1,j+1,k+1);
                if(ex > 0 && ex<8)pnum++;
            }
    return pnum;
}

int getedg()
{
    int ednum = 0, i, j, k;
    for(i=0;i<=A;i++)
        for(j=0;j<=B;j++)
            for(k=0;k<=C;k++)
            {
                int ex = 0;
                ex += exist(i+1,j,k);ex+=exist(i+1,j+1,k);
                ex += exist(i+1,j+1,k+1);ex+=exist(i+1,j,k+1);
                if(ex>0 && ex<4)ednum++;
                
                ex = 0;
                ex += exist(i,j+1,k);ex+=exist(i+1,j+1,k);
                ex += exist(i+1,j+1,k+1);ex+=exist(i,j+1,k+1);
                if(ex>0 && ex<4)ednum++;

                ex = 0;
                ex += exist(i, j, k+1);ex+=exist(i+1,j,k+1);
                ex += exist(i+1, j+1, k+1);ex+=exist(i,j+1,k+1);
                if(ex>0 && ex<4)ednum++;
            }
    return ednum;
}

int getface()
{
    int fnum=0, i, j, k;
    for(i=1;i<=A;i++)
        for(j=1;j<=B;j++)
            for(k=1;k<=C;k++)
                if(a[i][j][k] == 1)
                {
                    fnum += 6;
                    fnum -= exist(i-1, j, k);fnum -=exist(i+1,j,k);
                    fnum -= exist(i, j-1, k);fnum -=exist(i, j+1, k);
                    fnum -= exist(i, j, k-1);fnum -= exist(i, j, k+1);
                }
    return fnum;
}