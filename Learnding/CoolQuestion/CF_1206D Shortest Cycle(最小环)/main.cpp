//floyd����С��
//��n���������ai & aj != 0 ,��i��j֮���бߣ�����С�� 
//n�ķ�ΧΪ100000�����ֱ�ӽ����бߵĻ���Ȼ�ᳬ�����Է���
//���ĳ��������λΪ1�����д��ڵ���3�������������Ϳ���ֱ��
//�γ�һ�������������n>64*2,�Ϳ���ֱ�����3��
//����n<=64*2�ģ�n�ķ�Χ���󣬿��Կ�����floyd����С��
//����ԭͼ������ÿ��·��i->j�����i��j����k������������һ����
//����С�ľͺ���
//��Ŀ���ӣ�https://codeforces.com/problemset/problem/1206/D 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 210;
LL res;
LL b[100100], a[maxn][maxn], c[maxn][maxn];
void floyd(int n);

int main()
{
	int n, i, j, k =1;
	scanf("%d", &n);
	for(i=1;i<=n;i++){
		LL x;
		scanf("%I64d", &x);
		if(x)b[k++] = x;
	}
	n = k-1;
	if(n >= 64*3)
		printf("3\n");
	else{
		res = INF;
		for(i=1;i<=n;i++){
			for(j=1;j<=n;j++)
				if(b[i] & b[j])a[i][j] = c[i][j] = 1;
				else a[i][j] = c[i][j] = INF;
			a[i][i] = c[i][i] = 0;
		}
		floyd(n);
		if(res == INF)
			printf("-1\n");
		else
			printf("%d\n", res);
	}
	return 0;
}

void floyd(int n)
{
	int i, j, k;
	for(k=1;k<=n;k++)
	{
		//����С��
		//dis[i][j]��Ϊ���·��Ȼ��i�㣬j�㶼������k��ԭʼ��
		//��Ϊһ���� 
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			if(i != j && i!=k && j!=k){
				res = min(res, c[i][k]+c[k][j]+a[i][j]);
			}
				
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
			if(a[i][j] > a[i][k]+a[k][j])
				a[i][j] = a[i][k]+a[k][j];
	}
}
