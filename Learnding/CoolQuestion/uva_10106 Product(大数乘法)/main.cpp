#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<set>
#include<vector>
#include<map>
#include<iostream>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
void revser(char str[], int len);
void MUlbigint(char str1[], char str2[], char str3[]);
int main()
{
	char str1[520], str2[520], str3[1020];
	while(scanf(" %s %s", str1, str2)!=EOF)
	{
		MUlbigint(str1, str2, str3);
		printf("%s\n", str3);
	} 
	return 0;
}

void MUlbigint(char str1[], char str2[], char str3[])
{
	int i, j, len1 = strlen(str1), len2 = strlen(str2), len3=0;
	revser(str1, len1), revser(str2, len2);
	for(i=0;i<len1;i++)str1[i] -= '0';
	for(i=0;i<len2;i++)str2[i] -= '0';
	//这里如果使用sizeof(str3),所初始化的大小是指针的大小
	//而不是str3整个数组的大小 
	memset(str3, 0, 1010*sizeof(int));
	for(i=0;i<len2;i++)
	{
		for(j=0;j<len1;j++)
		str3[i+j] += str1[j] * str2[i];
		len3 = max(len3, i+len1);
		for(j=0;j<len3;j++)
		if(str3[j] > 9)
			str3[j+1] += str3[j]/10,str3[j]%=10;
		while(str3[len3] > 0)len3++;
		//for(j=0;j<len3;j++)printf("%d", str3[j]);printf("\n");
	}
	i = len3-1;
	while(str3[i] == 0 && i!=0)len3--,i--;
	for(i=0;i<len3;i++)str3[i] += '0';
	revser(str3, len3);
}
void revser(char str[], int len)
{
	for(int i=0;i<=len-1-i;i++)
	{
		char ch = str[len-1-i];
		str[len-1-i] = str[i];
		str[i] = ch;
	}
}
