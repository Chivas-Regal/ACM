//dp,���ر���
//dp���������Ϊ��i����Ʒʱ����ֵΪj��i�����ʣ���� 
//����ս������ƾ�����P63
//�ο�����: http://www.hankcs.com/program/cpp/poj-1742-coins.html
//��Ŀ����: http://poj.org/problem?id=1742
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<map>
#include<iterator>
#include<queue>
#include<iostream>
#include<ctime>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
int dp[100010];

int main()
{
	int n, m, i, j, k, a[120], b[120];
	LL sum;
	while(scanf("%d %d", &n, &m), n||m)
	{
		memset(dp, -1, sizeof(dp));
		sum = 0;
		dp[0] = 1;
		for(i=0;i<n;++i)scanf("%d", &a[i]);
		for(i=0;i<n;++i)scanf("%d", &b[i]);
		for(i=0;i<n;++i)
		{
			for(j=0;j<=m;j++)
			{
				//���dp[j]>=0�����֮ǰ�Ѿ�����
				//�ﵽ����ֵ�����Կ���ʣ��b[i]�� 
				if(dp[j]>=0)
				{
					dp[j] = b[i];
				}
				//���a[i]̫���ˣ�����j-a[i]��������֮ǰ 
				//��״̬�г��֣���jҲ�޷����� 
				else if(j<a[i] || dp[j-a[i]]<=0)
				{
					dp[j] = -1;
				}
				//���֮ǰû�е������״̬����Ҳ������������
				//��i����������һ�� 
				else 
					dp[j] = dp[j-a[i]]-1;
			}
		}
		for(i=1;i<=m;i++)if(dp[i]>=0)sum++;
		printf("%d\n", sum);
	}
	return 0;
}
