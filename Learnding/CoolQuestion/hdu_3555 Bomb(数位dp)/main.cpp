//��λdp(����) 
//�����49�����ĸ�������49��149��249��494 
//����˼·��������λdp�󲻰���49�����ĸ�����
//Ȼ����������ȥ�õ���ֵ�ټ�1���ǡ�Ҳ����ֱ�������
//49�����ĸ��� 
//http://acm.hdu.edu.cn/showproblem.php?pid=3555
//hdu 2089Ҳ��һ�������� 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<queue>
#include<cstring>
#include<vector>
#include<map>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
int a[100];
LL n, dp[100][12], z[20];
LL solve();
LL dfs(int pos, int bf, bool limit);

int main()
{
	z[0] = 1;
	for(int i=1;i<20;i++)
		z[i] = z[i-1]*10;
	int t;
	while(~scanf("%d", &t))
	{
		while(t--)
		{
			memset(dp, -1, sizeof(dp));
			scanf("%lld", &n);
			//LL ans = n-solve(n)+1;
			LL ans = solve();
			printf("%lld\n", ans);
		}
	}
	return 0;
}

LL solve()
{
	LL s = n;
	int k = 0;
	while(s>0)
	{
		a[k] = s % 10;
		k++;
		s /= 10;
	}
	LL ans = dfs(k-1, 0, 1);
	/*for(int i=0;i<k;i++)
	{
		for(int j=0;j<=9;j++)
			printf("%d ", dp[i][j]);
		printf("\n"); 
	}*/
	return ans;
}
//ֱ�������49�ĸ��� 
LL dfs(int pos, int bf, bool limit)
{
	if(pos == -1)return 0;
	if(!limit && dp[pos][bf] != -1)return dp[pos][bf];
	LL ans = 0;
	int s = limit?a[pos]:9;
	for(int i=0;i<=s;i++)
		//�������λֱ�Ӿ���49����������������������
		//����������������к������ 
		if(bf == 4 && i == 9)
			ans += limit?n%z[pos]+1:z[pos];
		else
			ans += dfs(pos-1, i, limit && i == a[pos]);
	if(!limit)
		dp[pos][bf] = ans;
	return ans;
}

/*�󲻰���49�ĸ��� 
LL dfs(int pos, int bf, bool limit)
{
	if(pos == -1)return 1;
	if(!limit && dp[pos][bf] != -1)return dp[pos][bf];
	LL ans = 0;
	int s = limit?a[pos]:9;
	for(int i=0;i<=s;i++)
		if(bf == 4 && i == 9);
		else
			ans += dfs(pos-1, i, limit && i==a[pos]);
	if(!limit)
		dp[pos][bf] = ans;
	return ans;
}
*/
