//����
//ѡq-2��λ�ã�����ͳ�Ƴ�ÿ��λ�õ�������Ȼ��
//����ö�������ˣ��������˵������ȥ��ȡ����
//������ȥ����ᳬʱ��������ҪԤ���������λ��ֻ��
//һ���˺������˵�������Ȼ����n1[r]-n1[l-1]��ʾ����
//[l,r]��ֻ��һ���������˵�����
//��Ŀ���ӣ�http://codeforces.com/contest/1132/problem/C
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
typedef long long int LL;
typedef pair<int, int> P;

int main()
{
	int n, q, i, j, res, ans, num;
	int a[5020], l[5020], r[5020], n0[5020], n1[5020], n2[5020];
	scanf("%d %d", &n, &q);
	memset(a, 0, sizeof(a));
	for(i=0;i<q;i++)
	{
		scanf("%d %d", &l[i], &r[i]);
		a[l[i]]++, a[r[i]+1]--;
	}
	j = n0[0] = n1[0] = n2[0] = num = 0;
	for(i=1;i<=n;i++)
	{
		j += a[i];
		a[i] = j;
		if(a[i])num++;
		n0[i] = n0[i-1]+(a[i]==0);
		//Ԥ������ۼӵ�i�ж��ٸ�����Ϊ1(2)������ 
		n1[i] = n1[i-1]+(a[i]==1);
		n2[i] = n2[i-1]+(a[i]==2);
	}
	res = 0;
	for(i=0;i<q;i++)
		for(j=i+1;j<q;j++)
		{
			ans = num;
			//��ȥ[l,r]��ֻ��һ�������� 
			ans -= n1[r[i]]-n1[l[i]-1];
			ans -= n1[r[j]]-n1[l[j]-1];
			//����������غϣ����ڼ�ȥ����Ϊ2������ 
			int l1 = max(l[i],l[j]), r1 = min(r[i], r[j]);
			if(l1<=r1)ans -= n2[r1]-n2[l1-1];
			res = max(res, ans);
		}
	printf("%d", res);
	return 0;
}
