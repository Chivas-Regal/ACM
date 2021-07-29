/****************************************************************************
哈希

有一个字符串，它的首尾是相连的，可以删除它连续的k个字符，如果能使所有相邻的字符不相同，
则为1，否则为0，对于所有的k(0<=k<len),求出对应的结果。

思路：暂且不考虑首尾是否相同，考虑让每个段尽可能的长。将串划分为多段[l1,r1],[l2,r2]...
l2 = r1+1, l3 = r2+1 .....，注意它是环，所以最后一段可能是[li, n], [1, rn]的形式。
分别考虑每一段，判断段内是否存在删除k个连续字符使首尾不相同(前面的划分已保证其他位置相邻字符不同)。
删除k个连续的字符 = 保留j = len-k个连续的字符，我们将问题转化为考虑连续j个字符
需要j成立，则str[l] != str[l+j-1] str[l+1] != str[l+j] .... str[r-j+1] != str[r]
中有一个成立即可，可以看出等式两边分别是一段的前后缀，只需要判断前后缀是否相同即可。
可以利用hash在O(1)时间内判断两段前后缀是否相等。
 
题目链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827370221
*****************************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 2000100;
const int mod = 1000000007;
char str[maxn];
LL hs[maxn], ss[maxn];
int ans[maxn];
LL geths(int l, int r);

int main()
{
    int t, n, i, j, k;
    ss[0] =  1;
    for(i=1;i<=maxn-50;i++)
        ss[i] = ss[i-1]*26%mod;
    scanf("%d", &t);
    while(t--)
    {
        scanf(" %s", str+1);
        n = strlen(str+1);
        for(i=1;i<=n;i++)
        {
            ans[i] = 0;
            str[i+n] = str[i];
        }
        hs[0] = 0;
        for(i=1;i<=2*n;i++)
            hs[i] = (hs[i-1]*26+str[i]-'a'+1)%mod;
        int l = 1, r = 1;
        while(l<=n)
        {
            while(str[r]!=str[r+1] && r-l+1<n)
                r++;
            for(i=0;i<r-l;i++)
                if(geths(l, l+i) != geths(r-i, r))
                    ans[r-l+1-i] = 1;
            l = r = r+1;
        }
        ans[1] = 1;
        for(i=n;i>=1;i--)
            printf("%d", ans[i]);
        printf("\n");
    }
    return 0;
}

LL geths(int l, int r)
{
    LL ks = hs[l-1]*ss[r-l+1]%mod;
    return (hs[r]-ks+mod)%mod;
}