/****************************************************************************
数论

初始一个序列n个数，从1到n，序列pi指在初始序列基础上将第i个元素移动至首位。pos(pi, val)
代表序列pi值为val的数的位置。给出m个数，对于每个pi，求出|pos(pi,x1)-pos(pi,x2)|+....
+|pos(pi,xm-1)-pos(pi,xm)|。

思路：首先求出初始序列的结果，考虑将i移动首位会对那些部分产生影响。设pos(pi, val1),pos(pi, val2)
中位置靠左的为l,靠右的为r，距离为r-l。
l == i,则移动后距离为r-1，与初始状态相比此状态应多 r-1-(r-l) = l-1的距离
r == i,l的位置变为l+1，移动后距离为l+1-1，与初始状态相比次状态应多l+1-1-(r-l)=2*l-r
l<i<r, 移动后，中间少了个元素，所以距离减-1
i<l || i>r，无影响。

计算出所有的[l,r]，按照上述规则求出与初始状态的差即可，l<i<r的情况可以利用前缀和维护。

题目链接：http://codeforces.com/problemset/problem/1234/E
******************************************************************************/
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
const int maxn = 200100;
const int mod = 998244353;
int a[maxn], c[maxn];
LL ans[maxn], b[maxn];

int main()
{
    int n, m, i, j, k;
    scanf("%d %d", &n, &m);
    for(i=0;i<m;i++)
        scanf("%d", &a[i]);
    for(i=1;i<m;i++){
        j = max(a[i], a[i-1]), k = min(a[i], a[i-1]);
        ans[1] += j-k;
        if(j == k)continue;
        b[k] += k-1, b[j] += k-(j-k);
        c[k+1]--, c[j]++;
    }
    for(i=2;i<=n;i++)
        c[i] += c[i-1];
    for(i=2;i<=n;i++)
        ans[i] = ans[1]+b[i]+c[i];
    for(i=1;i<=n;i++)
        printf("%I64d ", ans[i]);
    return 0;
}