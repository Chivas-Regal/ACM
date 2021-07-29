/*******************************************
优先队列+贪心
有n个人(n是2的幂)进行比赛，每次比赛两个人中胜者晋级，继续进行下一场比赛
，直到最后剩下一个人。n个人每个人有排名，比赛排名高的一定获胜，但可以收买排名高的人，让其输掉比赛，你想让其中一人获胜，你可以安排比赛，求最少的花费
使你需要的那个人成为冠军。

思路：设让i号成为冠军，则需要考虑收买部分比i强的人。所有人中最强的人一定需要被收买，因为他与其他任何人都会比都会晋级。所以不如把他安排在决赛，让他
打倒更多比i强的人，这样他总共可以解决2^(k-1)-1个人。而半决赛，与i相对的人
则在[2^(k-2), n](2^k等于n)，因为之前的人无论怎么安排，也达不到半决赛。所以每次选则符合条件的代价最小的即可。

题目链接：https://codeforces.com/problemset/problem/1260/E
*******************************************/
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
const int maxn = 1000100;
const int mod = 1e9+7;
int a[maxn], b[maxn];

int main()
{
	priority_queue<int, vector<int>, greater<int> > que;
	int n, i, j, m=0;
	LL ans = 0;
	scanf("%d", &n);
	for(i=0;i<n;i++){
		scanf("%d", &a[i]);
	}
	//依次考虑决赛、半决赛.....
	while(n > 1)
	{
		//当取到-1时不用再考虑花费了，因为剩下的人都比他如弱
		if(a[n-1] == -1)break;
		que.push(a[n-1]);
		ans += que.top();que.pop();
		for(i=n-2;i>=n/2;i--)
		{
			if(a[i] == -1)break;
			que.push(a[i]);
		}
		if(i >= n/2)break;
		n /= 2;
	}
	printf("%I64d\n", ans);
	return 0;
}