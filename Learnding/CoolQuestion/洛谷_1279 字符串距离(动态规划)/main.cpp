//DP
//�������ַ������ַ������������ⲹ���ַ���������ĸ��ո�
//�Ĵ���Ϊk����ĸ֮�����Ϊ����ĸ�Ĳ������ո�ʹ
//������Ӧ�Ĵ��ۺ���С
//��⣺���Ƕ�̬�滮��dp[i][j]�����һ�����ĵ�i���ַ���
//�ڶ������ĵ�j���ַ���Ӧ��״̬ת�ƣ� 
//dp[i][j]������dp[i-1][j]+i��Ӧ�ո�dp[i][j-1]+j��Ӧ�ո�
//dp[i-1][j-1]+i,j��Ӧ��dp[i-1][j-1]+i,j�ֱ��Ӧһ���ո�ת��
//����dp[i][j]=min{dp[i-1][j]+k,dp[i][j-1]+k
//     dp[i-1][j-1]+abs(s1[i]-s2[j]),dp[i-1][j-1]+k+k}
//��Ŀ���ӣ�https://www.luogu.org/problem/P1279 
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
const int maxn = 4020;
const int mod = 998244353;
char str1[maxn], str2[maxn];
int dp[maxn][maxn];

int main()
{
	int len1, len2, i, j, k;
	scanf(" %s %s %d", str1+1, str2+1, &k);
	memset(dp, 0x3f, sizeof(dp));
	dp[0][0] = 0;
	len1 = strlen(str1+1), len2 = strlen(str2+1);
	for(i=1;i<=len1;i++)
		dp[i][0] = dp[i-1][0]+k;
	for(i=1;i<=len2;i++)
		dp[0][i] = dp[0][i-1]+k;
	for(i=1;i<=len1;i++)
		for(j=1;j<=len2;j++)
		{
			//i��j���Կ���i,j�ֱ��Ӧ�ո�i,jͬʱ��Ӧ
			//�ո�i,j�໥��Ӧ����״̬ת�� 
			dp[i][j] = min(dp[i][j-1]+k, dp[i-1][j]+k);
			dp[i][j] = min(dp[i][j], dp[i-1][j-1]+min(2*k, abs((int)str1[i]-str2[j])));
		}
	printf("%d\n", dp[len1][len2]);
	return 0;
}
