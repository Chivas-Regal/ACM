//dp
//���Խ�ԭ������һ�����Ӵ�����x(Ҳ���Բ���),����������Ӷκ�
//�����ѡ�Ĵ𰸿��Է�Ϊ���Σ�ǰ�κͺ����û�г�x�ģ��ж���
//��x�ģ������ΰ�����Ԫ�ظ���������Ϊ0��
//dp[i][0]Ϊ��i��Ԫ����Ϊǰ�β����ܵõ������ֵ
//dp[i][1]Ϊ��i��Ԫ����Ϊ�жβ����ܵõ������ֵ
//dp[i][2]Ϊ��i��Ԫ����Ϊ��β����ܵõ������ֵ
//��Ŀ���ӣ�http://codeforces.com/problemset/problem/1155/D 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<set>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 3000;
LL ans, a, dp[300100][3];

int main()
{
	int n, i, x;
	scanf("%d %d", &n, &x);
	for(i=1;i<=n;i++)
	{
		scanf("%I64d", &a);
		//��Ϊǰ��Ԫ��ֻ�迼��ͬΪǰ�εĲ��� 
		dp[i][0] = max(dp[i-1][0], 0LL)+a;
		//��Ϊ�ж�Ԫ���迼�ǽ�������Ϊǰ�Ρ������жε�ǰһ��Ԫ�� 
		dp[i][1] = max(0LL, max(dp[i-1][0], dp[i-1][1]))+a*x;
		//��Ϊ���Ԫ���迼�ǽ�ǰһ��Ԫ����Ϊǰ�β��֣��жβ��ֻ��β��� 
		dp[i][2] = max(0LL, max(dp[i-1][0], max(dp[i-1][1], dp[i-1][2])))+a;
		ans = max(ans, max(dp[i][0], max(dp[i][1], dp[i][2])));
	}
	printf("%I64d\n", ans);
	return 0;
}
