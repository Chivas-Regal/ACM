//����
//��n����(����)��ÿ��λ�õ�����ֵ��[li,ri]����������λ��
//�����ĺͼ�����С�ڵ���s������Щ����λ�����Ϊ����
//��⣺�������뵽���֣�����ƽ���е㲻һ�������ڼ���� 
//ֵmid������õ�����λ�����������Ƶ������´��ڵ���mid
//����Ϊ�˷�������
//���ڼ��������룬����ÿ����mid����Ҫ�������е���������
//С������riС��mid�ģ�������Ϊ��λ������벿�֣�ֱ��
//ȡֵΪli��
//�������������ȡmid�����li>mid,��ȡmid���ȼ�����Ϊ�Ұ벿�� 
//�����ȷ������벿�ֵ�������n/2�� ��Ϊ�٣�(��Ϊ��Щ��һ��С��mid
//��������n/2������λ��ҲС��mid��)
//�����ȷ������벿�ֵ���С��n/2���򽫾����Ľ��ұߵ�ת�Ƶ�
//��벿�֣�ͬʱΪ���ܺ���С��Ӧѡli����С��
//��Ŀ���ӣ�https://codeforces.com/contest/1251/problem/D
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 200100;
const int mod = 998244353;
struct node{
	int l, r;
}p[maxn];
int b[maxn];
bool isok(LL mid, LL s, int n);

int main()
{
	int t, n, i, j;
	LL s, l, r;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%d %I64d", &n, &s);
		for(i=0;i<n;i++)
			scanf("%d %d", &p[i].l, &p[i].r);
		l = 0, r = INF;
		while(l<r)
		{
			LL mid = (l+r+1)/2;
			if(isok(mid, s, n))
				l = mid;
			else
				r = mid-1;
		}
		printf("%I64d\n", l);
	}
	return 0;
}
//�����Ƿ������λ�����ڵ���mid�ĺ����� 
bool isok(LL mid, LL s, int n)
{
	int i, j, a1=0, top = 0;
	LL sum = 0;
	for(i=0;i<n;i++)
	{
		//rС��mid����ֻ����Ϊ��벿�֣�ȡ��Сֵ���� 
		if(p[i].r < mid)
		{
			a1++;sum += p[i].l;
		}
		//������ȡ�����ڵ���mid��������Ϊ�Ұ벿�� 
		else
		{
			b[top++] = p[i].l;
			sum += max(mid, (LL)p[i].l);
		}
	}
	//С��mid��������һ�룬����λ��Ҳһ��С��mid 
	if(a1 > n/2)return false;
	sort(b, b+top);
	i = 0;
	//��һЩ�Ұ벿�ֵ���ת������벿�֣�ͬʱΪ����С��
	//sum��Ӧ��ȡli����С�� 
	while(i<top && b[i]<= mid && a1 < n/2)
	{
		sum -= mid-b[i];
		i++, a1++;
	}
	return sum <= s;
}
