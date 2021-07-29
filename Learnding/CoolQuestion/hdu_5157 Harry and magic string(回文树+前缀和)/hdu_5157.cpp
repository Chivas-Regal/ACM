/***********************************************************************
回文树+前缀和

求一个字符串中不相交的回文子串的点对数。

思路：对于每个位置，求出以它为结束位置和以它为起始位置的回文子串的数量，分别即为ai,bi。
对于每个点对，已知以i为起始位置的回文子串有bi个，则回文点对有(a1+a2+..+a_i-1)*bi个。
求出所有i的和即可。
bi可以通过反向建回文树求得。
a1+a2+..+a_i-1可以通过前缀和计算。


题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=5157
*************************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 200010;
const int mod = 1000000007;
struct node{
	int len, fail, cnt, num, nex[26];
}st[maxn];
int cnt, last, len, c[maxn], b[maxn];
LL sum[maxn];
char str[maxn], s[maxn];
void init();
int creat(int x);
int getfail(int x);
int Insert(char ch);

int main()
{
	int n, i, j, k;
	while(~scanf("%s", str+1))
	{
		LL ans = 0;
		n = strlen(str+1);
		init();
		sum[0] = 0;
		for(i=1;i<=n;i++){
			b[i] = Insert(str[i]);
			sum[i] = sum[i-1] + b[i];
		}
		init();
		for(i=n;i>=1;i--){
			c[i] = Insert(str[i]);
			ans += c[i]*sum[i-1];
		}
		printf("%lld\n", ans);
	}
	return 0;
}

void init()
{
	cnt = -1;
	last = len = 0;
	str[0] = '*';
	creat(0);
	creat(-1);
	st[0].fail = 1;
}

int creat(int x)
{
	cnt++;
	st[cnt].len = x;
	memset(st[cnt].nex, 0, sizeof(st[cnt].nex));
	st[cnt].cnt = st[cnt].num = 0;
	st[cnt].fail = 0;
	return cnt;
}

int getfail(int x)
{
	while(s[len-st[x].len-1] != s[len]) x = st[x].fail;
	return x;
}

int Insert(char ch)
{
	s[++len] = ch;
	int cur = getfail(last);
	if(!st[cur].nex[ch-'a']){
		int now = creat(st[cur].len + 2);
		st[now].fail = st[getfail(st[cur].fail)].nex[ch-'a'];
		st[cur].nex[ch-'a'] = now;
		st[now].num = st[st[now].fail].num + 1;
	}
	last = st[cur].nex[ch-'a'];
	st[last].cnt++;
	return st[last].num;
}