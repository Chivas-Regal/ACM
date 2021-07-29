//最小表示法+kmp
//http://acm.hdu.edu.cn/showproblem.php?pid=3374
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
char str[1000010];
int len, nex[1000010];
int getmin();
int getmax();
void getnex();

int main()
{
	while(~scanf(" %s", str))
	{
		len = strlen(str);
		getnex();
		int mi = getmin();
		int mx = getmax();
		//问最大串和最小串出现的次数，比如ABABAB出现多少次
		//这个函数的长度除以他的最小周期，就是出现的次数 
		int num = len%(len - nex[len])?1:len/(len-nex[len]);
		printf("%d %d %d %d\n", mi+1, num, mx+1, num);
	}
	return 0;
}

//最小表示法
//一个串首尾相连，从第几个开始，得到的串字典序最小
//如果暴力，应该会肯定先找字典序最小的那个字母，如果有多个
//则比较往后比较，如果相同，则一直往后比
//最大表示法思想类似
int getmin()
{
	//i,j代表开始的位置，k代表长度 
	int i=0,j=1,k=0,t;
	while(i<len && j<len && k<len)
	{
		//比较从i，j开始，偏移k个位置的字母大小 
		t = str[(i+k)%len]-str[(j+k)%len];
		//printf("%d %d %d %d\n", i, j, k, t);
		//如果相等，则继续向后偏移 
		if(!t)k++;
		else
		{
			//t>0，则i开始的串比k开始的串大，则i加上k+1
			//因为K个字段内已经比较过了，如果较小早就偏移过去了 
			if(t>0)i += k+1;
			else j += k+1;
			if(i == j)j++;
			k = 0;
		}
	}
	return min(i, j);
}

int getmax()
{
	int i=0,j=1,k=0,t;
	while(i<len && j<len && k<len)
	{
		t = str[(i+k)%len]-str[(j+k)%len];
		if(!t)k++;
		else
		{
			if(t<0)i += k+1;
			else j += k+1;
			if(i == j)j++;
			k = 0;
		}
	}
	return min(i, j);
}

void getnex()
{
	int i=0, j=-1;
	nex[0] = -1;
	while(i<len)
	{
		if(j == -1 || str[i] == str[j])
			nex[++i] = ++j;
		else
			j = nex[j];
	}
}
