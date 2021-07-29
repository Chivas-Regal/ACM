/******************************************************************************
博弈论

有大小为n*20的棋盘，有一些棋子在棋盘上，A,B两人轮流对棋盘进行操作，每次操作可以选择一个棋子
将其移动，如果它右边相邻的格子为空，则移动至右边相邻的格子，若有其他棋子，则可以直接跳过其他
棋子，移动至他们右边的格子。A先手，是否存在必胜策略。

思路:因为每次操作只能将棋子右移，所以可以将n行分开来看，单独考虑每一行。因为每一行的大小
为20，最多有2^20种状态，而且每种状态最多可以有可以向20个其他的状态转移，所以可以先求出
每种状态的SG函数。
对于n行，每一行对应一个SG值，每个SG值可以转换到小于它的非负整数，其实相当于nim博弈，对
n个SG值异或即可。

题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=5724
***************************************************************************/
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
const int maxn = 1<<21;
const int mod = 10007;
int a[30], b[30], sg[maxn];
void init();

int main()
{
    init();
    for(int i=0;i<=21;i++)
        a[i] = (1<<i);
    int t, n, m, sig, i, j, x, up;
    scanf("%d", &t);
    while(t--)
    {
        sig = 0, up = 0;
        scanf("%d", &n);
        while(n--)
        {
            x = 0;
            scanf("%d", &m);
            for(i=0;i<m;i++)
            {
                scanf("%d", &j);
                x += a[20-j];
            }
            sig ^= sg[x];
        }
        if(sig)printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}
//预处理求每种状态的SG值
void init()
{
    memset(sg, 0, sizeof(sg));
    int i, j, k, x, top, sum = 1<<20;
    for(i=0;i<=23;i++)
        a[i] = 1<<i;
    for(i=2;i<sum;i++)
    {
        memset(b, 0, sizeof(b));
        for(j=19;j>=0;j--)
            if(i & (1<<j))
            {
                for(k=j-1;k>=0;k--)
                    if((i & (1<<k)) == 0)break;
                if(k<0)break;
                x = i - (1<<j) + (1<<k);
                b[sg[x]] = 1;
            }
        for(j=0;;j++)
            if(b[j] == 0){
                sg[i] = j;break;
            }
    }
        
}