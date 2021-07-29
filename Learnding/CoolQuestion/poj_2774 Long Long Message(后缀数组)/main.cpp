//��׺����
//�����⣬�������ַ�����������Ӵ�
//����ͨ����������������һ��Ȼ�����׺���飬�����Ӵ�
//��ô�ں�׺����������Ͽ϶��������ģ����Կ���ͨ����
//height���������������ڵ��������������ǰ׺��height���
//���Ǹ����ǽ����������Ҫע��һ��sa[i-1]��sa[i]��Ҫԭ����
//������ͬ�Ĵ�
//PS���ո�����ƴ���������ַ���û�ӷָ���
//Ȼ���ֱ�ӹ��ˣ���������̫ˮ��
//���ӷָ���������������ֻ��ͬһ����ĸ�Ĵ����޷��õ���ȷ�����
//��Ŀ���ӣ�http://poj.org/problem?id=2774 
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
//N�Ǵ��ĳ��ȣ�M��Ͱ����Ͱ�ĸ���
//tmp:Ͱ����������,
//tp  :�ڶ��ؼ�������Ϊi���±�,Ͱ����ڶ��ؼ���
//sa  ������Ϊi����ʼ�±� 
//rank: ��iΪ��׺������ 
//heg ��sa[i]��sa[i-1]�������ǰ׺ 
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
//��sa 
void binary_sa()
{
	N = strlen(s1+1);
	M = 200;
	for(int i=1;i<=N;i++)rank[i] = s1[i], tp[i] = i;
	QSORT();
	for(int w=1,q=0;q<N;w<<=1, M=q)
	{
		q = 0;
		//����w�Ľ������2*w 
		//���ĺ�w���ַ�û���ַ������0������������С 
		for(int i=1;i<=w;i++)tp[++q] = N-w+i;
		//��С�������ǰw����ĸ��С�ģ� 
		for(int i=1;i<=N;i++)if(sa[i]>w)tp[++q] = sa[i] - w;
		QSORT();
		//��ԭ����rank���Ƶ�tp���������������rank
		//����ʵ���Ͽ��Ի��������Ǿ��
		//strcpy(tp, rank, sizeof(tp)); 
		swap(tp, rank);
		rank[sa[1]] = q = 1;
		for(int i=2;i<=N;i++)
			rank[sa[i]] = (tp[sa[i]] == tp[sa[i-1]] && tp[sa[i]+w] == tp[sa[i-1]+w])?q:++q; 
	}
}
//Ͱ���� 
void QSORT()
{
	for(int i=0;i<=M;i++)tmp[i] = 0;
	for(int i=1;i<=N;i++)tmp[rank[i]]++;
	for(int i=1;i<=M;i++)tmp[i] += tmp[i-1];
	for(int i=N;i>=1;i--)sa[tmp[rank[tp[i]]]--] = tp[i];
} 

//���������ڵ��������������ǰ׺ 
//ps:����һ�ûŪ������ô���£����Ժ�Ū���ˣ���
//�������������ٽ��Ͱ� 
void GetHeight() {
    int j, k = 0;
    for(int i = 1; i < N; i++) {
        if(k) k--;
        int j = sa[rank[i] - 1];
        while(s1[i + k] == s1[j + k]) k++;
        heg[rank[i]] = k;
    }
}
