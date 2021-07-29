//dfs+��֦
//��Ŀ����һ��n*m�ľ�����������⽻���������
//������ɺ󰴵�һ�е�һ��Ԫ�أ���һ�еڶ���Ԫ��
//....�ڶ��е�һ��......��˳�򽫾����е�Ԫ�طŵ�һ��������
//k = min(abs(a[i]-a[i-1])),��k�����ֵ
//˼·���ܹ������16�У��������ⲻ���뵽������֮��Ĳ����С���� 
//ֵ���������Ȼ����൱��16��Ԫ��ȫ���У�������Ҫ
//����ע��ľ��ǵ�һ�������һ�е����⣬���Ҳ��ҪԤ����һ��
//��Ŀ���ӣ� http://codeforces.com/problemset/problem/1102/F
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<queue>
#include<cstring>
#include<map>
#include<iostream>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
int head, n, m, maxx, vis[20], a[20][10020], b[20][20], c[20][20];
void dfs(int step, int j, int mid);

int main()
{
	int i, j, k;
	maxx = 0;
	scanf("%d %d", &n, &m);
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			scanf("%d", &a[i][j]);
	//Ԥ��������β�е�ֵ 
	for(i=0;i<n;i++)
		for(j=0;j<i;j++)
		{
			int minn = 2147480000; 
			for(k=0;k<m;k++)
				minn = min(minn, abs(a[i][k]-a[j][k]));
			b[i][j] = b[j][i] = minn;
		}
	//Ԥ������һ�к����һ�е���� 
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(i == j)continue;
			int minn = 2147480000; 
			for(k=1;k<m;k++)
				minn = min(minn, abs(a[j][k]-a[i][k-1]));
			c[i][j] = minn;
		}
	//����ȫ���� 
	memset(vis, 0, sizeof(vis));
	for(i=0;i<n;i++)
	{
		head = i;
		vis[i] = 1;
		dfs(1, i, 2147480000);
		vis[i] = 0;
	}
	printf("%d\n", maxx);
	return 0;
}

void dfs(int step, int j, int ans)
{
	if(ans <= maxx)return;
	if(step == n)
	{
		//printf("head:%d %d\n", head, j);
		if(step>1)
		ans = min(ans, c[head][j]);
		else
		for(int i=1;i<m;i++)
			ans = min(ans, abs(a[0][i]-a[0][i-1]));
		maxx = max(ans, maxx);
		return;
	}
	for(int i=0;i<n;i++)
	{
		if(!vis[i])
		{
			vis[i] = 1;
			dfs(step+1, i, min(b[j][i], ans));
			vis[i] = 0;
		}
	}
}
