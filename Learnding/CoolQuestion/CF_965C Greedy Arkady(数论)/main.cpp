//����
//��k���ˣ�n���ǣ�ÿ����������x���ǣ�֪��û��x����Ϊֹ
//����ÿ���������d�Σ�x���Ϊm�����һ��������ö��ٸ� 
//d�ķ�ΧΪ1~1000�����Կ��Ǵ�d���֣�ö��d����ö�ٵ�һ����
//���õĴ���i�����������ܹ��õĴ���Ϊ[i+(i-1)*(k-1),i*k]��
//��ÿ�ο�����[n/(i*k),n/(i+(i-1)*(k-1))]������һ����i�� 
//����������i*n/(i+(i-1)*(k-1))����������Ҫע�����ֻ�� 
//��m��������
//������Ҫע��(i-1)*(k-1)���ܱ�LL����CF������__int128,����
//��Ҫ�ж�һ��
//PS���Լ����Լ�������Ŀ����һ������Ҫ�Ϳ��������Ǹ����� 
//��Ŀ����:https://codeforces.com/problemset/problem/965/C
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<unordered_map>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6

using namespace std;
typedef unsigned long long LL;
typedef pair<int, int> P;
const int maxn = 100100;

int main()
{
	LL n, k, m, d, a, b, ans=0;
	scanf("%I64u %I64u %I64u %I64u", &n, &k, &m, &d);
	//ö�ٵ�һ��������i�� 
	for(LL i=1;i<=d;i++)
	{
		//��Ϊ(i-1)*(k-1)���ܱ�LL��������Ҫ�����ж�һ�� 
		if(i>1 && (n-1)/(i-1) <= k-1)
			a=n+1;
		else
			a = i+(i-1)*(k-1);
		b = i*k;
		if(n/a<=m)ans = max(ans, n/a*i);
		if(n/i/k<=m)ans = max(ans, n/i/k*i);
		if(m>= n/i/k && m<=n/a)ans = max(ans, m*i);
	}
	printf("%I64u\n", ans);
	return 0;
}
