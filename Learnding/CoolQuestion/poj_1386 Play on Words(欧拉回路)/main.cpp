//ŷ����·
//��һ�����ʵ�����ĸ�������ǰ���Ǹ����ʵ�β��ĸ
//ʵ����һ��������Ч���־�������ĸ��β��ĸ
//������ĸ��β��ĸ��Ϊһ���ߣ��������ת��Ϊŷ����·����
//��Ϊ������ߣ�������Ҫ���=���ȣ����ж��Ƿ�����ͨͼ
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
		//�ڵ�ĸ��� 
		for(i=0;i<26;i++)
			if(c[i] != 0)
				numm++;
		//��ͼ�Ƿ���ͨ 
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
		//�����ȵ��ڳ��Ȼ����0�� 
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
