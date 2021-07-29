//差分数组
//数组仅保存其与前一个元素的差，以做到区间更新
//信阳省赛的那道题也是这样的思路，
//唯一的坑点就是判断a,b是否重复出现
//不过此题貌似有错误
//5 5 6 3
// 1 6
// 1 5
// 1 4
//得到的数据明显不对
//题目链接：https://www.luogu.org/problemnew/show/P2879 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 440;
int a[10010];
map<int,int> mp[10010];

int main()
{
	int n, i, h, r, j, k;
	memset(a, 0, sizeof(a));
	scanf("%d %d %d %d", &n, &i, &h, &r);
	while(r--){
		scanf("%d %d", &j, &k);
		if(j > k){
			int t=j;j=k;k=t;
		}
		if(mp[j][k] == 0)
			mp[j][k] = 1;
		else
			continue;
		if(j+1 < k)
		a[j+1]--, a[k]++;
	}
	j = 0;
	for(i=1;i<=n;i++)
	{
		j += a[i];
		printf("%d\n", h+j);
	}
	return 0;
}
