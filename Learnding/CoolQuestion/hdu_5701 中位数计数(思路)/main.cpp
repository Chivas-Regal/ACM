//˼·�� 
//��ÿ�����ڰ���������������λ����������
//����ÿ��������Ҫ��������ж��ٸ�������������
//���ٸ�С�����������ұ�ͬ����������ĳ��λ��
//i���ұ�ĳ��λ��j�����Ǵ��ڸ�������������С�ڸ���
//���������������Լ�1
//��Ŀ���ӣ�http://acm.hdu.edu.cn/showproblem.php?pid=5701
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
const int maxn = 8020;
int a[maxn], add[2*maxn];

int main()
{
	int n, i, j, k;
	LL ans;
	while(~scanf("%d", &n))
	{
		for(i=0;i<n;i++)
			scanf("%d", &a[i]);
		for(i=0;i<n;i++)
		{
			ans = 1;
			//ͳ���������״̬ 
			memset(add, 0, sizeof(add)); 
			j=1, k=0;
			add[n]++;
			while(i-j>=0)
			{
				//���ڸ�Ԫ�أ�k++;С��,k--
				if(a[i-j] > a[i])k++;
				else k--;
				if(k == 0)ans++;
				//ͳ��״̬���ִ��� 
				add[n+k]++;
				j++;
			}
			j=1, k=0;
			while(i+j<n)
			{
				if(a[i+j] > a[i])k++;
				else k--;
				//����������״̬k������������ߵ�-k��״̬�� 
				ans += add[n-k];
				j++;
			}
			if(i)printf(" ");
			printf("%lld", ans);
		}
		printf("\n");
	}
	return 0;
}
/*
5
1 4 3 2 5
*/
