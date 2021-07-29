//hash
//有一颗多叉树，如果能将所有点重新编号，然后
//两颗树完全相同即认为两棵树同构
//此题无根树，将每个点作为根，遍历树，然后求以
//该节点作为根的Hash值，然后将所有的点的值按hash
//出的值排序，如果两个树得到的所有值都相等，即同构
//此题其实还可以通过寻找树的重心的方法对每棵树
//只进行最多两次hash。 
//题目连接：https://www.luogu.org/problemnew/show/P5043 
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
		//构造无根树 
		for(j=1;j<=n;j++)g[j].clear();
		for(j=1;j<=n;j++){
			scanf("%d", &k);
			if(k == 0)continue;
			g[k].push_back(j);
			g[j].push_back(k);
		}
		//求以每个结点为根的树的hash值 
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
//对当前子树计算hash值 
int Hash(int u, int f){
	int p[maxn], top=0, ans=7;
	for(int i=0;i<g[u].size();i++)
		if(g[u][i] != f){
			p[top] = Hash(g[u][i], u);
			top++;
		}
	sort(p, p+top);
	//此处仍以确定需要乘的值 
	for(int i=0;i<top;i++)
		ans = ans * 11 + p[i];
	return ans * 11+1;
}
