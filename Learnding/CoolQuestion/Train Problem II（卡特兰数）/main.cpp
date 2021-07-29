//¿¨ÌØÀ¼Êý
//http://acm.hdu.edu.cn/showproblem.php?pid=1023
// http://www.cnblogs.com/kuangbin/archive/2012/03/21/2410516.html
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

int a[110][110];
void table();

int main()
{
	int n, i, j;
	table();
	while(scanf("%d", &n)!=EOF)
	{
		for(i=a[n][0];i>0;i--)
			printf("%d", a[n][i]);
		printf("\n");
 	}
	return 0;
} 

void table()
{
	int i, j, yu, len;
	a[2][0] = 1;
	a[2][1] = 2;
	a[1][0] = 1;
	a[1][1] = 1;
	len = 1;
	for(i=3;i<101;i++)
	{
		yu = 0;
		for(j=1;j<=len;j++)
		{
			int t = (a[i-1][j]) * (4*i-2) + yu;
			yu = t / 10;
			a[i][j] = t % 10;
		}
		while(yu)
		{
			len++;
			a[i][len] = yu%10;
			yu/=10;
		}
		for(j=len;j>=1;j--)
		{
			int t = a[i][j] + yu * 10;
			a[i][j] = t / (i+1);
			yu = t % (i+1);
		}
		while(!a[i][len])
		{
			len--;
		}
		a[i][0] = len;
	}
}
