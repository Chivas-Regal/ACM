/***************************************
��̬�滮
����n*m�ĵ�ͼ����'.'����յأ�'R'����ʯͷ���������Ͻ�
�˿������»����ߣ�Ŀ�ĵ�Ϊ���½ǣ�������ʱ���԰�ʯͷ��
���ߵķ����ƣ��������Ƴ���ͼ�����ж����ֲ�ͬ��·�ߵ����½�
��⣺��Ȼ���Ƕ�̬�滮��dp[i][j]����i��j�����½��ж���
�ֲ�ͬ��·�������н�dp[i][j]��Ϊdx[i][j]��dy[i][j]��
�ֱ����(i,j)�����ߺ������ж����ַ�����������ʯͷ�Ļ���
��Ȼ		dx[i][j] = dx[i+1][j]+dy[i+1][j],
���(i+1,j)����ʯͷ�����»��ʯͷ���������Ƶ�λ��k��
��ʱ(i,j)���µ�(k,j)��Ȼ��(k,j)�����ߵ����ַ�����Ȼ��
���еģ���dx[i][j]����ʱ��������Щ·���������ˣ�������
��ȥ����·��������
����dy[i][j]Ҳ������������
ע�⴦��n=m=1����������д���û�����ΪR�������������
����Ĵ����Ǵ��(������Ŀ�����˰ѣ���û�����Ǿ�)
 
��Ŀ���ӣ�https://codeforces.com/contest/1247/problem/E
*****************************************/
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<deque>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 2020;
const int mod = 1000000007;
//dp[i][j][0]����dx[i][j],dp[i][j][1]����dy[i][j]
//cnt[i][j][0]�����j�д�����������i�����ж��ٸ�ʯͷ 
LL dp[maxn][maxn][2], cnt[maxn][maxn][2];
char str[maxn][maxn];

int main()
{
	int n, m, i, j;
	scanf("%d %d", &n, &m);
	for(i=0;i<n;i++)
		scanf(" %s", str[i]);
	if(n == 1 && m == 1)
		printf("1");
	else if(str[n-1][m-1] == 'R' || str[0][0] == 'R')
		printf("0");
	else
	{
		//��"ʯͷ"���׺�ͣ��Է��������ĵ�k 
		for(i=n-1;i>=0;i--)
			for(j=m-1;j>=0;j--)
			{
				cnt[i][j][0] = cnt[i+1][j][0]+(str[i][j] == 'R');
				cnt[i][j][1] = cnt[i][j+1][1]+(str[i][j] == 'R');
			}
		//�����Ե����Ϣ 
		for(i=n-2;i>=0;i--)
			if(!cnt[i][m-1][0])dp[i][m-1][0] = 1;
		for(i=m-2;i>=0;i--)
			if(!cnt[n-1][i][1])dp[n-1][i][1] = 1;
		for(i=n-2;i>=0;i--)
			for(j=m-2;j>=0;j--)
			{
				//��(i,j)����һ��������һ���ж����ֲ�ͬ��·����(n,m) 
				dp[i][j][0] = (dp[i+1][j][0]+dp[i+1][j][1])%mod;
				//�������Ϊʯͷ��ȥ���ܵ����·�� 
				if(str[i+1][j] == 'R')
					dp[i][j][0] = (dp[i][j][0]-dp[n-cnt[i+1][j][0]][j][1]+mod)%mod;
				dp[i][j][1] = (dp[i][j+1][0]+dp[i][j+1][1])%mod;
				if(str[i][j+1] == 'R')
					dp[i][j][1] = (dp[i][j][1]-dp[i][m-cnt[i][j+1][1]][0]+mod)%mod;
			}
		printf("%lld\n", (dp[0][0][0]+dp[0][0][1])%mod);
	}
	return 0;
}
