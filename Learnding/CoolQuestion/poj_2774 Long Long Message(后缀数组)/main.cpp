//后缀数组
//入门题，求两个字符串的最长公共子串
//可以通过将两个串链接在一起，然后求后缀数组，公共子串
//那么在后缀数组的排名上肯定是连续的，所以可以通过求
//height数组来求排名相邻的两个串的最长公共前缀，height最大
//的那个就是结果，不过需要注意一下sa[i-1]和sa[i]需要原属于
//两个不同的串
//PS：刚刚两个拼接起来的字符串没加分隔符
//然后就直接过了，这题数据太水了
//不加分隔符，对于两个都只有同一种字母的串，无法得到正确结果的
//题目链接：http://poj.org/problem?id=2774 
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
#define dbg(x) printf("debug:%d\n", x);
#define INF 0x3f3f3f3f
#define eps 1e-8
  
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 300200;
//N是串的长度，M是桶排序桶的个数
//tmp:桶排序辅助数组,
//tp  :第二关键字排名为i的下标,桶排序第二关键字
//sa  ：排名为i的起始下标 
//rank: 以i为后缀的排名 
//heg ：sa[i]与sa[i-1]的最长公共前缀 
int N, M, rank[maxn], tmp[maxn], tp[maxn], sa[maxn], heg[maxn];
char s1[maxn], s2[maxn];
void QSORT();
void binary_sa();
void GetHeight();

int main()
{
	while(~scanf("%s %s", s1+1, s2+1))
	{
		int ans = 0;
		int len1 = strlen(s1+1), len2 = strlen(s2+1);
		strcat(s1+1, "*");
		strcat(s1+1, s2+1);
		binary_sa();
		GetHeight();
		for(int i=1;i<N;i++)
		{
			if(sa[i]<= len1 && sa[i-1]>len1)
					ans = max(ans, heg[i]);
			else if(sa[i-1]<=len1 && sa[i]>len1)
					ans = max(ans, heg[i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
//求sa 
void binary_sa()
{
	N = strlen(s1+1);
	M = 200;
	for(int i=1;i<=N;i++)rank[i] = s1[i], tp[i] = i;
	QSORT();
	for(int w=1,q=0;q<N;w<<=1, M=q)
	{
		q = 0;
		//利用w的结果来求2*w 
		//串的后w个字符没有字符，后接0，所以排名最小 
		for(int i=1;i<=w;i++)tp[++q] = N-w+i;
		//从小到大访问前w个字母最小的， 
		for(int i=1;i<=N;i++)if(sa[i]>w)tp[++q] = sa[i] - w;
		QSORT();
		//将原来的rank复制到tp数组里，以用来更新rank
		//这里实际上可以换成下面那句的
		//strcpy(tp, rank, sizeof(tp)); 
		swap(tp, rank);
		rank[sa[1]] = q = 1;
		for(int i=2;i<=N;i++)
			rank[sa[i]] = (tp[sa[i]] == tp[sa[i-1]] && tp[sa[i]+w] == tp[sa[i-1]+w])?q:++q; 
	}
}
//桶排序 
void QSORT()
{
	for(int i=0;i<=M;i++)tmp[i] = 0;
	for(int i=1;i<=N;i++)tmp[rank[i]]++;
	for(int i=1;i<=M;i++)tmp[i] += tmp[i-1];
	for(int i=N;i>=1;i--)sa[tmp[rank[tp[i]]]--] = tp[i];
} 

//求排名相邻的两个串的最长公共前缀 
//ps:这个我还没弄懂是怎么回事，等以后弄懂了，在
//其他题的题解里再解释吧 
void GetHeight() {
    int j, k = 0;
    for(int i = 1; i < N; i++) {
        if(k) k--;
        int j = sa[rank[i] - 1];
        while(s1[i + k] == s1[j + k]) k++;
        heg[rank[i]] = k;
    }
}
