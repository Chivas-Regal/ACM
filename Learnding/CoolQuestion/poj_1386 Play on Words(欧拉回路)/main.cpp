//欧拉回路
//后一个单词的首字母必须等于前面那个单词的尾字母
//实际上一个单词有效部分就是首字母和尾字母
//将首字母到尾字母作为一条边，问题就能转化为欧拉回路问题
//因为是有向边，所以需要入度=出度，并判断是否是连通图
// http://poj.org/problem?id=1386
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<vector>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
int Find(int x, int a[]);

int main()
{
	int t, n, a[29], b[29][29], c[29], d[29], i, j;
	scanf("%d", &t);
	while(t--)
	{
		memset(d, 0, sizeof(d));
		memset(b, 0, sizeof(b));
		memset(c, 0, sizeof(c));
		for(i=0;i<26;i++)
			a[i] = i;
		scanf("%d", &n);
		for(i=0;i<n;i++)
		{
			char str[1020];
			scanf(" %s", str);
			int len = strlen(str);
			int s1 = str[0]-'a', s2 = str[len-1]-'a';
			d[s1]++;
			d[s2]--;
			c[s1] = c[s2] = 1;
			b[s1][s2]++;
		}
		int num = 0, numm = 0;
		//节点的个数 
		for(i=0;i<26;i++)
			if(c[i] != 0)
				numm++;
		//求图是否连通 
		for(i=0;i<26;i++)
		{
			for(j=0;j<26;j++)
			{
				if(b[i][j] == 0)continue;
				int x =Find(i, a);
				int y = Find(j, a);
				if(x != y)
				{
					a[x] = y;
					numm--;
				}
				if(numm == 1)break;
			}
			if(numm == 1)break;
		}
		//如果入度等于出度会等于0， 
		for(i=0;i<26;i++)
			num+=abs(d[i]);
		//printf("%d %d\n", num, numm);
		if(num <= 2 && numm == 1)
			printf("Ordering is possible.\n");
		else
			printf("The door cannot be opened.\n");
	}
	return 0;
}

int Find(int x, int a[])
{
	return a[x] = x == a[x]?x:Find(a[x], a);
}
