/********************************************************************************
博弈论

A和B在进行取石子游戏，每次可以从一堆中去任意正整数数量的式子，对A的操作有限制。每堆
石子有两个值ai,bi，ai代表石子数量，bi代表对A的限制。bi==0无限制；bi==1，A只能从此堆中取
奇数个；bi==2，A只能从此堆中取偶数个。A先手，谁必胜。

思路：首先只考虑bi==0的那部分石子，求出其异或和sig。考虑bi!=0，第i组，ai与bi的奇偶
性不同，显然A是没办法一次把这堆取完的，则此时无论B面对的sig是必胜态还是必败态，都可以
操作A无法取完的那堆保证B必胜。如果有多堆bi!=0，且他们奇偶性相同，B可以操作某堆，使形成
上一条的局面。注意初始ai == 1 && bi == 1时，A可以任取，所以将其作为bi==0来考虑。
结合上面考虑A必胜的情况。
不存在bi!=0的组，显然sig!=0，A必胜；
只存在一组bi!=0，且那组bi与ai奇偶性相同，sig==0，则A可以取完那组，B面临sig==0，A必胜
只存在一组bi==1，且ai为偶数，则a可以直接将其取剩下一个，bi=1,ai'=1,B先手，若sig=1，A必胜。

题目链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827370091
********************************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-7
 
using namespace std;
typedef long long LL;   
typedef pair<LL, int> P;
const int maxn = 100010;
const int mod = 998244353;
int a[maxn], b[maxn];

int main()
{
    int t, n, i, j, k, sig, n1, n2, n3;
    scanf("%d", &t);
    while(t--)
    {
        n1 = n2 = n3 = sig = 0;
        scanf("%d", &n);
        for(i=0;i<n;i++)
            scanf("%d", &a[i]);
        for(i=0;i<n;i++)
            scanf("%d", &b[i]);
        for(i=0;i<n;i++){
            if(b[i] == 0)sig ^= a[i];
            else if(b[i] == 1 && a[i] == 1)sig ^= 1;
            else if(a[i]%2 == b[i]%2)n1++;
            else {
                n2++;
                if(b[i] == 1)n3++;
            }
        }
        if(n1 == 0 && n2 == 0 && sig)
            printf("Alice\n");
        else if(n1 == 1 && n2 == 0 && sig == 0)
            printf("Alice\n");
        else if(n2 == 1 && n1 == 0 && n3 == 1 && sig == 1)
            printf("Alice\n");
        else printf("Bob\n");
    }
    return 0;
}