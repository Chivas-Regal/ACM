/********************************************************************************
ST表

有一个长度为n的序列，有m个询问，每个询问包含两个整数L,R,求区间[L,R]内最长的子串，子串不能
包含重复的元素。

思路：区间元素长度最长的子串，可以预处理出每个左端点i，满足区间元素互异，最多能到达的位置
r[i]。则len[i] = r[i]-i+1。注意：数组r是非递减的。
对于询问区间[L,R]， 其结果分两种情况，一种是完整的[i,r[i]]的区间，另一种是[i,R]的区间。
即结果可能是一个完整的最长子串也可能是最长子串的一部分。所以考虑[L,R]区间内，分别以每个点为
起点。设pos为最靠左的r[i]>R的位置，即r[pos]>R && r[pos-1]<=R. 
当L<=i<pos,即r[i]<R，可以利用ST表来找区间的长度(len[i])最大值；
当pos<=i<=R,则所有的只能取部分，每个i对应长度为R-i+1，显然当i==pos时，长度最大。
对于每个询问按上述处理即可，注意pos可能不在[L,R]区间内的情况。

题目链接：http://poj.org/problem?id=3419
*************************************************************************/
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
const int maxn = 200100;
const int mod = 1000000007;
map<int,int> mp;
int a[maxn], len[maxn], r[maxn], st[maxn][20], b[maxn*10];
void st_init(int n);
int get(int l, int r);

int main()
{
    int n, m, i, j, k, rmax, mid = 1000000;
    scanf("%d %d", &n, &m);
    for(i=0;i<n;i++)
        scanf("%d", &a[i]);
    rmax = n-1;
    for(i=n-1;i>=0;i--)
    {
        if(b[mid+a[i]] != 0)rmax = min(rmax, b[mid+a[i]]-1);
        r[i] = rmax;
        b[mid+a[i]] = i;
        st[i][0] = rmax-i+1;
    }
    st_init(n);
    while(m--)
    {
        int L, R, ans = 0;
        scanf("%d %d", &L, &R);
        int pos = upper_bound(r, r+n, R)-r;
        if(pos-1>=L)ans = get(L, pos-1);
        ans = max(ans, R-max(pos,L)+1);
        printf("%d\n", ans);
    }
    return 0;
}

int get(int l, int r)
{
    int k = log(1.0*r-l+1)/log(2.0);
    return max(st[l][k], st[r-(1<<k)+1][k]);
}

void st_init(int n)
{
    int i, j;
    for(j=1;j<19;j++)
        for(i=0;i<n;i++)
            if(i+(1<<j)-1<n)
                st[i][j] = max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
            else break;
}