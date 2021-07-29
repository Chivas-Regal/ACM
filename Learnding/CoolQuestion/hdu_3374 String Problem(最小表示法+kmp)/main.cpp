//��С��ʾ��+kmp
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
		//����󴮺���С�����ֵĴ���������ABABAB���ֶ��ٴ�
		//��������ĳ��ȳ���������С���ڣ����ǳ��ֵĴ��� 
		int num = len%(len - nex[len])?1:len/(len-nex[len]);
		printf("%d %d %d %d\n", mi+1, num, mx+1, num);
	}
	return 0;
}

//��С��ʾ��
//һ������β�������ӵڼ�����ʼ���õ��Ĵ��ֵ�����С
//���������Ӧ�û�϶������ֵ�����С���Ǹ���ĸ������ж��
//��Ƚ�����Ƚϣ������ͬ����һֱ�����
//����ʾ��˼������
int getmin()
{
	//i,j����ʼ��λ�ã�k������ 
	int i=0,j=1,k=0,t;
	while(i<len && j<len && k<len)
	{
		//�Ƚϴ�i��j��ʼ��ƫ��k��λ�õ���ĸ��С 
		t = str[(i+k)%len]-str[(j+k)%len];
		//printf("%d %d %d %d\n", i, j, k, t);
		//�����ȣ���������ƫ�� 
		if(!t)k++;
		else
		{
			//t>0����i��ʼ�Ĵ���k��ʼ�Ĵ�����i����k+1
			//��ΪK���ֶ����Ѿ��ȽϹ��ˣ������С���ƫ�ƹ�ȥ�� 
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
