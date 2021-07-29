//����ԭ�� 
//����http://www.cnblogs.com/ACShiryu/archive/2011/08/09/poj2356.html
//http://poj.org/problem?id=3370
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
typedef long long int ll;

int main()
{
	priority_queue<int, vector<int>, greater<int> > que;
	//visΪ״̬���飬ÿ�����ݽ�������λ�ó�ʼΪ-1 
	int c, n, i, j, vis[100005]; 
	ll a[100005];
	while(scanf("%d %d", &c, &n),c!=0 && n!=0)
	{
		while(que.size())
			que.pop();
		for(i=1;i<=n;i++)
			scanf("%lld", &a[i]);
		memset(vis, -1, sizeof(vis));
		long long int sum = 0;
/*!!!!���ģ�sumΪa[0]��a[i]�ĺͣ���sum%cΪ0ʱ���������ܷ�ƽ��
��sum%c��=0ʱ�����¼�µ�һ�γ��ָ�����ʱi��λ��
��sum%c������ǰ���Ѿ����ֹ���������ʱsum2-sum1������������������C��
sum2Ϊ�ڶ��γ��ָ������ĺͣ�sum1Ϊ��һ��
��ʱ��vis����vis[sum2%c]�е�j,��j+1����ʱ��i֮���������Ϳ�������C 
*/		 
		for(i=1;i<=n;i++)
		{
			sum += a[i];
			if(sum % c == 0)
			{
				for(j=1;j<=i;j++)
					que.push(j);
				break;
			}
			else if(vis[sum % c] != -1)
			{
				//�������ڶ��γ��� 
				for(j=vis[sum %c]+1;j<=i;j++)
					que.push(j);
				break;
			}
			//����һ�γ��ָ��������±��¼������ 
			vis[sum%c] = i;
		}
		if(que.size() == 0)
			printf("no sweets");
		else
		{
			i=0;
			while(que.size())
			{
				if(i)
					printf(" ");
				i++;
				int t = que.top();
				printf("%d", t);
				que.pop();
			}
		}
		printf("\n");
	 }
	return 0;
}
