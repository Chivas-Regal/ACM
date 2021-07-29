//dfs�����仯���� 
//����ʼ�㲻ȷ������Ҫ��ÿ���㶼��Ϊ��ʼ���������
//������ɺ󽫵õ���ֵ����״̬���飬�����е�ֵ��Ϊ�Ӵ˵㿪ʼ��
//�����Ի��ж��ٲ������������㻬�����Ѹ�ֵ�ĵ㣬ֱ�ӷ��� 
//�����е�ֵ�� 
// http://poj.org/problem?id=1088
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;
typedef pair<int,int> P;
typedef long long int ll;
int m, n, a[102][102], dp[102][102];
int dx[4]={-1,0,1,0}, dy[4]={0,-1,0,1};
int dfs(int x, int y);

int main()
{
	int num, i, j, maxi, maxj, maxx = -1;
	memset(dp, -1, sizeof(dp));
	scanf("%d %d", &m, &n);
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			scanf("%d", &a[i][j]);
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
		{
			//���õ���ֵ�������� 
			dp[i][j] = dfs(i, j);
			/*for(int e=0;e<m;e++)
			{
				for(int f=0;f<n;f++)
					printf("%d ", dp[e][f]);
				printf("\n");
			}
			printf("\n");*/ 
		}
	for(i=0;i<m;i++)
		for(j=0;j<n;j++)
			maxx = max(dp[i][j], maxx);
	/*for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
			printf("%d ", dp[i][j]);
		printf("\n");
	}*/
		
	printf("%d\n", maxx);
	return 0;
}

int dfs(int x, int y)
{
	//maxx��ʼ��Ϊ1�������(x,y)���޴����ߣ�����1 
	int i, nx, ny, maxx = 1;
	//����õ��Ѿ���������ֱ�ӷ���
	if(dp[x][y] != -1)
	{
		return dp[x][y];
	}
	for(i=0;i<4;i++)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		//��������»���������(nx,ny)�����䷵�ص�ֵ��1 
		if(nx>=0 && nx<m && ny>=0 && ny<n && a[nx][ny] < a[x][y])
			maxx = max(dfs(nx,ny)+1, maxx);
	}
	return maxx;
 } 
