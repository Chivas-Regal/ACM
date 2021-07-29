//��ȡ��
//http://poj.org/problem?id=3320
//�鼮�ο�������ս������ƾ�����P149�� 
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
	//����set�Ĳ��ظ��ԣ��ж��ܹ��ж���֪ʶ�㡣 
	for(i=0;i<n;i++)
	{
		scanf("%d", &a[i]);
		s.insert(a[i]);
	}
	j = s.size();
	res = n+1;
	while(1)
	{
		//��X�����𲽼ӣ�������ȡֵ��֪�����串������֪ʶ�� 
		while(x < n && num < j)
		{
			//map����ͳ�Ƹ�֪ʶ����ִ�����num��¼֪ʶ������ 
			if(m[a[x]] == 0)
			{
				num++;
			} 
			m[a[x]]++;
			x++;
		}
		if(num < j)break;
		//�����whileѭ����������[y,x]��Ȼ��������֪ʶ��
		//��ʱx-y�������䳤�� 
		res = min(res, x-y);
		//�Ӵ������䣬������С��Χ�������С���֪ʶ��Ϊ��
		//���Ϊ0; 
		m[a[y]]--;
		if(m[a[y]] == 0)
			num--;
		y++;
	}
	printf("%d", res);
	return 0;
 } 
