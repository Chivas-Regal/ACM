//exkmp, kmp
//这题其实用kmp就可以做，不过难得找道水题来了解一下扩展kmp
//扩展kmp具体可以参照下面那个博客，exkmp需要先预处理出来
//一个next数组，保存模式串t的后缀与t的最长前缀的长度
//(！！！这里的next数组与KMP的数组并不一样) 
//博客：https://www.cnblogs.com/dilthey/p/8620119.html 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<queue>
#include<cstring>
#include<stack>
#include<iostream>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long int ll;
typedef pair<int, int> P;
char s[400010], t[400010];
int tlen, slen, nex[400010], exnex[400010];
void getnex();

int main()
{
	while(scanf(" %s", t)!=EOF)
	{
		stack<int> st;
		tlen = strlen(t);
		getnex();
		for(int i=0;i<tlen;i++)
			if(exnex[i]+i == tlen)st.push(exnex[i]);
		for(int i=0;i<tlen;i++)
			printf("%d ",nex[i]);
		while(!st.empty())
		{
			int s = st.top();
			st.pop();
			printf("%d ", s);
		}
		printf("\n");
	}
	return 0;
} 
//这部分其实是预处理nex数组的内容，不过此题就是这个串
//与自身的比较，所以并不需要exnex数组 
void getnex()
{
	int i, j, po;
	nex[0] = tlen;
	i=0;
	while(i+1<tlen && t[i] == t[i+1])i++;
	nex[1] = i;
	po = 1;
	for(i=2;i<tlen;i++)
	{
		if(nex[i-po]+i < nex[po] + po)
			nex[i] = nex[i-po];
		else
		{
			j = nex[po]+po-i;
			if(j<0)j = 0;
			while(i+j<tlen && t[i+j] == t[j])j++;
			nex[i] = j;
			po = i; 
		}
	}
}

//计算exnext数组 
void getextend()
{
	int i=0, j, po;
	slen = strlen(s);
	while(s[i] == t[i] && i<slen && i<tlen)i++;
	exnex[0] = 0;
	po = 0;
	for(i=1;i<slen;i++)
	{
		//exnex[po]+po代表匹配到过的最远位置，
		//nex[i-po]代表在t中匹配到的位置, 
		if(nex[i-po]+i < exnex[po]+po)
			exnex[i] = nex[i-po];
		else
		{
			j = exnex[po]+po-i;
			if(j<0)j=0;
			while(i+j<slen &&j<tlen && s[i+j] == t[j])
			j++;
			exnex[i] = j;
			po = i; 
		}
	 } 
}
