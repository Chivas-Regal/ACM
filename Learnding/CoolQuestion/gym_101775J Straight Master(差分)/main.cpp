//差分
//1~n的牌各有ai个，每次能消除3~5个连续的数，能否正好所有的消除完
//可以发现一段连续的数，只要大于等于3，都能删除
//因为6=3+3，7=3+4......
//可以对数进行差分，得到新的序列b，对于bi，如果bi>0
//则代表需要以i为开头消除bi次，如果bi<0则代表以i为结尾
//消除bi次(不删除i位置)，所以遍历bi，对于bi大于0，一直 
//将其与后面为负值的bj匹配，进行min(bi,bj)次消除(代表的
//的意义为以i为开头到j之前的位置都消除min(bi,bj)次)
//直到bi等于0。注意如果i，j之间小于三个数，则不能删除 
//题目链接：https://codeforces.com/gym/101775/problem/J
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
		//差分，在序列最后补个0 
		for(i=1;i<=n;i++)
		{
			scanf("%I64d", &a[i]);
			b[i] = a[i] - a[i-1];
		} 
		b[n+1] = -a[n];
		
		j = 4;
		for(i=1;i<=n+1;i++)
		{
			//对于b[i]>0，找到以i开头的序列b[i]次 
			while(b[i] > 0 && sig && j<=n+1)
			{
				//找到合理的bj,并消除，代表进行以
				//i为开头，j为末尾，消除min(b[i],b[j])次 
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
