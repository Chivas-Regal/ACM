//���
//1~n���Ƹ���ai����ÿ��������3~5�������������ܷ��������е�������
//���Է���һ������������ֻҪ���ڵ���3������ɾ��
//��Ϊ6=3+3��7=3+4......
//���Զ������в�֣��õ��µ�����b������bi�����bi>0
//�������Ҫ��iΪ��ͷ����bi�Σ����bi<0�������iΪ��β
//����bi��(��ɾ��iλ��)�����Ա���bi������bi����0��һֱ 
//���������Ϊ��ֵ��bjƥ�䣬����min(bi,bj)������(�����
//������Ϊ��iΪ��ͷ��j֮ǰ��λ�ö�����min(bi,bj)��)
//ֱ��bi����0��ע�����i��j֮��С��������������ɾ�� 
//��Ŀ���ӣ�https://codeforces.com/gym/101775/problem/J
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
LL a[maxn], b[maxn];

int main()
{
	int t, n, i, j, sig;
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		sig = 1;
		scanf("%d", &n);
		b[0] = a[0] = 0;
		//��֣���������󲹸�0 
		for(i=1;i<=n;i++)
		{
			scanf("%I64d", &a[i]);
			b[i] = a[i] - a[i-1];
		} 
		b[n+1] = -a[n];
		
		j = 4;
		for(i=1;i<=n+1;i++)
		{
			//����b[i]>0���ҵ���i��ͷ������b[i]�� 
			while(b[i] > 0 && sig && j<=n+1)
			{
				//�ҵ������bj,�����������������
				//iΪ��ͷ��jΪĩβ������min(b[i],b[j])�� 
				for(;j<=n+1;j++)
				if(b[j] < 0)
				{
					if(j-i<3){
						sig = 0;break;
					}
					else{
						if(b[j]+b[i]>=0)b[i]+=b[j], b[j]=0;
						else b[j]+=b[i], b[i]=0;
						break;
					}
				}
			}
			if(j>n+1 || b[i] != 0)sig = 0;
		}
		if(sig)
			printf("Case #%d: Yes\n", z);
		else
			printf("Case #%d: No\n", z);
	}
	return 0;
}
