//exkmp, kmp
//������ʵ��kmp�Ϳ������������ѵ��ҵ�ˮ�����˽�һ����չkmp
//��չkmp������Բ��������Ǹ����ͣ�exkmp��Ҫ��Ԥ�������
//һ��next���飬����ģʽ��t�ĺ�׺��t���ǰ׺�ĳ���
//(�����������next������KMP�����鲢��һ��) 
//���ͣ�https://www.cnblogs.com/dilthey/p/8620119.html 
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
//�ⲿ����ʵ��Ԥ����nex��������ݣ�����������������
//������ıȽϣ����Բ�����Ҫexnex���� 
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

//����exnext���� 
void getextend()
{
	int i=0, j, po;
	slen = strlen(s);
	while(s[i] == t[i] && i<slen && i<tlen)i++;
	exnex[0] = 0;
	po = 0;
	for(i=1;i<slen;i++)
	{
		//exnex[po]+po����ƥ�䵽������Զλ�ã�
		//nex[i-po]������t��ƥ�䵽��λ��, 
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
