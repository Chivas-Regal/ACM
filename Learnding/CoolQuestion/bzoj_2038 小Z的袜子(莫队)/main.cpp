//朴素莫队算法
//有n个数，在[l,r]任取两个数，求两个数相同的概率 
//莫队算法入门，有m个离线询问
//如果知道[l,r],那么可以通过移动一次l或r求[l-1,r]
//[l+1,r],[l,r-1],[l,r+1]，如果严格按照l递增排列
//对于[1,10][2,2][3,10][4,4]这种基本等于完全暴力的做法
//莫队算法就是将区间n划分成块，对于l在同一个块里的询问
//按r的大小来排序，这样就可以将顺序变为[2,2],[4,4][1,10][3,10]
//博客链接： https://www.cnblogs.com/CsOH/p/5904430.html
//题目链接： https://www.lydsy.com/JudgeOnline/problem.php?id=2038
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<set>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
  
using namespace std;
typedef unsigned long long LL;
typedef pair<int, int> P;
const int maxn = 10010;
const int mod = 1e9+7;
struct node
{
    int l, r, id;
}p[50010];
int a[50010], len;
LL sum[50010], ans[50010], anss[50010];
bool cmp(node a, node b);
LL gcd(LL a, LL b);

int main()
{
    int n, m, i, j, l, r;
    LL ans1;
    while(~scanf("%d %d", &n, &m))
    {
    	//每块的长度为len
    	len = (int)sqrt(n);
	    for(i=1;i<=n;i++)
	        scanf("%d", &a[i]);
	    for(i=0;i<m;i++)
	    {
	        scanf("%d %d", &p[i].l, &p[i].r);
	        p[i].id = i;
	    }
	    sort(p, p+m, cmp);
	    memset(sum, 0, sizeof(sum));
	    ans1 = 0;
	    l = r = 1;
	    sum[a[1]]++;
	    for(i=0;i<m;i++)
	    {
	    	//滚动l,r,已知[l,r]的结果，求[p[i].l, p[i].r] 
	    	if(r < p[i].r)
	    	{
	    		while(r<p[i].r){
	    			r++;
	    			sum[a[r]]++;
					ans1 += 2*(sum[a[r]]-1);
				}
			}
			else
			{
				while(r>p[i].r){
					sum[a[r]]--;
					ans1 -= 2*sum[a[r]];
					r--;
				}
			}
	        if(l < p[i].l)
	    	{
	    		while(l<p[i].l){
	    			sum[a[l]]--;
					ans1 -= 2*sum[a[l]];
					l++;
				}
			}
			else
			{
				while(l>p[i].l){
					l--;
					sum[a[l]]++;
					ans1 += 2*(sum[a[l]]-1);
				}
			}
			if(ans1 == 0)
				ans[p[i].id] = 0, anss[p[i].id] = 1;
			else
			{
				LL tt = ((LL)p[i].r-p[i].l+1)*(p[i].r-p[i].l);
				LL gd = gcd(ans1, tt);
				ans[p[i].id] = ans1/gd, anss[p[i].id] = tt/gd;
			}
	    }
	    for(i=0;i<m;i++)
	            printf("%llu/%llu\n", ans[i], anss[i]); 
	}
    return 0;
}
 
bool cmp(node a, node b)
{
	if(a.l/len != b.l/len)return a.l<b.l;
    return a.r<b.r;
}
 
LL gcd(LL a, LL b)
{
    LL k;
    do{
        k = a % b;
        a = b;
        b = k;
    }while(k!=0);
    return a;
}
