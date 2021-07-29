//�߶���
//��i����ͬ��ߵ����ų�һ�ӣ���֪���Լ�ǰ�������ж��ٸ��˱��Լ���
//���Խ������˰��������Ȼ��̰�ģ���С����ÿ���˰�����������
//ǰ�ţ��������ܱ�֤�ֵ�����С
//��Ŀ���ӣ�http://acm.hdu.edu.cn/showproblem.php?pid=5493 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include<iostream>
#include<iterator>
#define dbg(x) printf("debug:%d\n", x);
#define INF 0x3f3f3f3f
#define eps 1e-8
  
using namespace std;
typedef long long LL;
typedef pair<LL, int> P;
const int maxn = 100100;
const LL mod = 998244353;
struct node{
	int x, num;
}a[maxn];
int ans[maxn], p[4*maxn];
bool cmp(node a, node b);
void creat(int l, int r, int k);
int query(int l, int r, int x, int k);
void update(int l, int r, int x, int k);


int main()
{
	int t, n, i, j, sig;
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		sig = 0;
		scanf("%d", &n);
		for(i=1;i<=n;i++)
			scanf("%d %d", &a[i].x, &a[i].num);
		sort(a+1, a+1+n, cmp);
		creat(1, n, 1);
		for(i=1;i<=n;i++){
			//�����ߵ���������ʣ�µ������Ļ�����û���� 
			if(a[i].num > n-i){
				sig = 1;break;
			}
			//a[i]���Է���a[i].num+1С����p[1]-a[i].numС��λ�� 
			int x = query(1, n, a[i].num+1, 1), y = query(1, n, p[1]-a[i].num, 1);
			ans[min(x, y)] = a[i].x;
			//��a[i]�Ž���λ�ø���Ϊ������ 
			update(1, n, min(x, y), 1);
		}
		printf("Case #%d: ", z);
		if(sig)
			printf("impossible\n");
		else{
			for(i=1;i<n;i++)
				printf("%d ", ans[i]);
			printf("%d\n", ans[n]);
		}
	}
	return 0;
}

bool cmp(node a, node b)
{
	return a.x < b.x;
}

void creat(int l, int r, int k)
{
	p[k] = (r-l+1);
	if(l == r)return;
	int mid = (l+r)/2;
	creat(l, mid, 2*k);
	creat(mid+1, r, 2*k+1);
}

void update(int l, int r, int x, int k)
{
	p[k]--;
	if(l == r)return;
	int mid = (l+r)/2;
	if(x <= mid)update(l, mid, x, 2*k);
	else update(mid+1, r, x, 2*k+1);
}

int query(int l, int r, int x, int k)
{
	if(l == r)return l;
	int mid = (l+r)/2;
	if(x <= p[2*k])return query(l, mid, x, 2*k);
	else return query(mid+1, r, x-p[2*k], 2*k+1); 
}
