//��׺����+����ջ
//һ������k���������������������Ӵ�����ҳ��ȴ��ڵ���k���Ӵ��ж��ٶ�
//���������ú�׺�������height���飬Ȼ������height������������
//ps:���µĵ���ջ��д����low���������ȱ��˶�������ʮ�� 
//��Ŀ���ӣ�http://poj.org/problem?id=3415 
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
const int maxn = 300100;
const int mod = 1000000007;
struct node{
	int h, l, r, bg, ed;
	node(){
		l = r = 0;
	}
	node(int a, int b, int c, int d, int e){
		h=a, l=b, r=c, bg=d, ed=e;
	}
}sk[maxn];
int N, M, top, tp[maxn], rak[maxn], sa[maxn], tmp[maxn], heg[maxn];
char str1[maxn], str2[maxn];
void QSORT();
void binary_sa(int n);
void getHeight();
LL solve(int k, int len1);

int main()
{
	int k, i, j;
	while(scanf("%d", &k), k)
	{
		memset(tp, 0, sizeof(tp));
		scanf("%s %s", str1+1, str2+1);
		int len1 = strlen(str1+1), len2 = strlen(str2+1);
		str1[len1+1] = '<', str1[len1+2] = 0;
		strcat(str1+1, str2+1);
		str1[len1+2+len2] = 0;
		binary_sa(len1+1+len2);
		getHeight();
		LL ans = solve(k, len1);
		printf("%lld\n", ans);
	}
	return 0;
}
//���õ���ջ���� 
LL solve(int k, int len1)
{
	LL res = 0;
	int j;
	for(int i=1;i<=N;)
	{
		//������ȴ��ڵ���k����ջ 
		if(heg[i] >= k)
		{
			//���ջ��Ԫ�صĸ߶ȣ��Լ�������������������������� 
			sk[0].h = k-1;
			top = 1;
			sk[1].h = heg[i], sk[1].bg=sa[i-1], sk[1].ed = sa[i];
			sk[1].l = sk[1].r = 0;
			if(sa[i-1]>len1)sk[1].r++;
			else sk[1].l++;
			if(sa[i] > len1)sk[1].r++;
			else sk[1].l++;
			//���η��������Ĵ��ڵ���k��heg��������ջ 
			for(j=i+1;j<=N;j++){
				if(heg[j] < k)break;
				else if(heg[j]>sk[top].h){
					if(sa[j]>len1)
						sk[++top] = node(heg[j], 0, 1, sa[j], sa[j]);
					else
						sk[++top] = node(heg[j], 1, 0, sa[j], sa[j]);
				}
				else{
					//ͳ�������������ĺ�׺�ֱ��ж��ٸ� 
					int el = 0, er = 0;
					while(top && sk[top].h>heg[j]){
						int l = 0, r = 0;
						el += sk[top].l, er += sk[top].r;
						top--;
						//��ǰ��ʵ���ϻ���Ҫ�õ�ǰ��һ����׺ 
						if(top){
							if(sk[top].ed > len1)r++;
							else l++;
						}
						res += (LL) (sk[top+1].h-max(sk[top].h, heg[j]))*(el+l) *(er+r);
					}
					if(sk[top].h == heg[j]){
						sk[top].ed = sa[j], sk[top].l += el, sk[top].r+=er;;
						if(sa[j] > len1)sk[top].r++;
						else sk[top].l++;
					}
					else{
						if(sa[j] > len1)sk[++top] = node(heg[j], el, er+1, sa[j], sa[j]);
						else sk[++top] = node(heg[j], el+1, er, sa[j], sa[j]);
					}
				}
			}
			while(top){
				int l = sk[top].l, r = sk[top].r;
				top--;
				if(top){
					sk[top].l += l, sk[top].r += r;
					if(sk[top].ed > len1)r++;
					else l++;
					sk[top].ed = sk[top+1].ed;
				}
				res += (LL) (sk[top+1].h-sk[top].h)* l * r;
			}
			i = j;
		}
		else
			i++;
	}
	return res; 
}
//��׺���� 
void binary_sa(int n)
{
	N = n;
	M = 200;
	for(int i=1;i<=N;i++)
		rak[i] = str1[i], tp[i] = i;
	QSORT();
	for(int p=0,w=1;p<N;w<<=1, M=p)
	{
		p=0;
		for(int i=1;i<=w;i++)tp[++p] = N-w+i;
		for(int i=1;i<=N;i++)if(sa[i]>w)tp[++p] = sa[i]-w;
		QSORT();
		swap(tp, rak);
		rak[sa[1]] = p = 1;
		for(int i=2;i<=N;i++)
			rak[sa[i]] = (tp[sa[i-1]] == tp[sa[i]] && tp[sa[i]+w] == tp[sa[i-1]+w])?p:++p;
	}
}

void QSORT()
{
	for(int i=0;i<=M;i++)tmp[i] = 0;
	for(int i=1;i<=N;i++)tmp[rak[i]]++;
	for(int i=1;i<=M;i++)tmp[i] += tmp[i-1];
	for(int i=N;i>=1;i--)sa[tmp[rak[tp[i]]]--] = tp[i];
}

void getHeight()
{
	int j, k=0;
	for(int i=1;i<=N;i++)
	{
		if(k)k--;
		j = sa[rak[i]-1];
		while(str1[i+k] == str1[j+k])k++;
		heg[rak[i]] = k;
	 } 
}
