//codeforces1186C
//有01串a,b。c为a长度与b相等的子串
//f(b,c)为两串对应位置不相等的位置数量
//如：f(00110,01100)=2,f(00110,11000)=4
//求f(b,c)为偶数的个数
//官方题解：如果b,c中1的个数同奇偶，则f(b,c)为偶数
//自行理解所谓的"易证":
//长度足够情况下，b中有d个1，c中有e个1
//设1位置对应的数量为f，则不对应的情况就有
//(d-f)+(e-f)=d+e-2f个，2f为偶数，所以需要
//d+e为偶数，所以d、e应该同奇同偶
//ps:实际上只是需要0或1数量同奇偶就行，不一定是1
//题目链接： http://codeforces.com/problemset/problem/1186/C
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<string>
#include<ctype.h>
#include<cstring>
#include<stack>
#include<queue>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1000010;
int s1[maxn], s2[maxn];
char str1[maxn], str2[maxn];

int main()
{
	int len1, len2, i, j;
	scanf("%s %s", str1+1, str2+1);
	len1 = strlen(str1+1), len2 = strlen(str2+1);
	//利用前缀和统计奇偶性
	//s1[i]=str1[1]^str1[2]^....^str1[i]
	//其中0^0=0,如果1的数量为奇数则，s1[i]=1
	//否则s[i]=0; 
	for(i=1;i<=len1;i++)
		s1[i] = (str1[i]-'0')^s1[i-1];
	for(i=1;i<=len2;i++)
		s2[i] = (str2[i]-'0')^s2[i-1];
	int ans = 0;
	for(i=len2;i<=len1;i++)
		if(!(s2[len2]^s1[i]^s1[i-len2]))++ans;
	printf("%d\n", ans);
	return 0;
}
