//尺取法
//http://poj.org/problem?id=3320
//书籍参考：《挑战程序设计竞赛》P149。 
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>

using namespace std;
int a[1000020];

int main()
{
	set<int> s;
	map<int, int> m;
	int n, i, j, res, x=0, y=0, num=0;
	scanf("%d", &n);
	//利用set的不重复性，判断总共有多少知识点。 
	for(i=0;i<n;i++)
	{
		scanf("%d", &a[i]);
		s.insert(a[i]);
	}
	j = s.size();
	res = n+1;
	while(1)
	{
		//对X进行逐步加，逐步往后取值，知道区间覆盖所有知识点 
		while(x < n && num < j)
		{
			//map用来统计各知识点出现次数，num记录知识点种类 
			if(m[a[x]] == 0)
			{
				num++;
			} 
			m[a[x]]++;
			x++;
		}
		if(num < j)break;
		//上面的while循环结束，则[y,x]必然包含所有知识点
		//此时x-y就是区间长度 
		res = min(res, x-y);
		//加大左区间，尝试缩小范围，如果缩小后此知识点为空
		//则记为0; 
		m[a[y]]--;
		if(m[a[y]] == 0)
			num--;
		y++;
	}
	printf("%d", res);
	return 0;
 } 
