//hash
//��һ�Ŷ����������ܽ����е����±�ţ�Ȼ��
//��������ȫ��ͬ����Ϊ������ͬ��
//�����޸�������ÿ������Ϊ������������Ȼ������
//�ýڵ���Ϊ����Hashֵ��Ȼ�����еĵ��ֵ��hash
//����ֵ��������������õ�������ֵ����ȣ���ͬ��
//������ʵ������ͨ��Ѱ���������ĵķ�����ÿ����
//ֻ�����������hash�� 
//��Ŀ���ӣ�https://www.luogu.org/problemnew/show/P5043 
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
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 64;
vector<int> g[maxn];
int a[maxn][maxn], vis[maxn];
int Hash(int u, int f);

int main()
{
	int t, n, i, j, k;
	scanf("%d", &t);
	for(i=1;i<=t;i++){
		scanf("%d", &n);
		//�����޸��� 
		for(j=1;j<=n;j++)g[j].clear();
		for(j=1;j<=n;j++){
			scanf("%d", &k);
			if(k == 0)continue;
			g[k].push_back(j);
			g[j].push_back(k);
		}
		//����ÿ�����Ϊ��������hashֵ 
		for(j=1;j<=n;j++)
			a[i][j] = Hash(j, -1);
		sort(a[i]+1, a[i]+n+1);
		for(j=1;j<=i;j++){
			for(k=1;k<=n;k++)
				if(a[i][k] != a[j][k])
					break;
			if(k>n){
				printf("%d\n", j);break;
			}
		}
	}
	return 0;
}
//�Ե�ǰ��������hashֵ 
int Hash(int u, int f){
	int p[maxn], top=0, ans=7;
	for(int i=0;i<g[u].size();i++)
		if(g[u][i] != f){
			p[top] = Hash(g[u][i], u);
			top++;
		}
	sort(p, p+top);
	//�˴�����ȷ����Ҫ�˵�ֵ 
	for(int i=0;i<top;i++)
		ans = ans * 11 + p[i];
	return ans * 11+1;
}
