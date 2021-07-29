#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<vector>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100100;
int a[maxn];
LL b[maxn];
P p[maxn];
bool cmp(P a, P b);

int main()
{
	int n, m, k, i, j;
	LL ans;
	while(~scanf("%d %d %d", &n, &k, &m))
	{
		priority_queue<int, vector<int>, greater<int> > que;
		b[0] = 0;
		for(i=1;i<=n;i++)
		{
			scanf("%d", &a[i]);
			b[i] = b[i-1] + a[i];
		}
		for(i=0;i<m;i++)
			scanf("%d %d", &p[i].first, &p[i].second);
		sort(p, p+m, cmp);
		for(i=0;i<k;i++)
			que.push(p[i].second);
		if(que.top() >= p[k-1].first)
		ans = b[que.top()]-b[p[k-1].first-1];
		else
			ans = 0;
		for(;i<m;i++)
		{
			que.push(p[i].second);
			que.pop();
			if(que.top()>=p[i].first)
			ans = max(ans, (LL)b[que.top()]-b[p[i].first-1]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}

bool cmp(P a, P b)
{
	if(a.first != b.first)
	return a.first < b.first;
	return a.second < b.second;
}
