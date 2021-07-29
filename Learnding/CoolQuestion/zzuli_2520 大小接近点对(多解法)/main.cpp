//�֮ⷨһ����ϯ��
//��������׷���һ���ڵ�Ŀ�����������������ӽڵ������ĺ�
//���ϴ˽ڵ����ӽڵ��д�С�ӽ�������
//dfs���������������[l,r]�У���ֵ��[b[i]-m,b[i]+m]֮��
//����������������ͨ����ϯ��������
//��Ŀ���ӣ�http://202.196.1.136/problem.php?id=2520
#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100010;
struct node
{
	int l, r, sum;
}p[maxn*20];
int n, m, num, num1, root[maxn], a[maxn], b[maxn], c[maxn];
LL dp[100100];
vector<int> g[100100];
int update(int la, int l, int r, int x);
int creat(int l, int r);
void query(int ql, int qr, int l, int r, int ll, int rr, LL &ans);
void dfs(int u);
 
int main()
{
    int i, j;
    num = num1 = 1;
    scanf("%d %d", &n, &m);
    for(i=1;i<=n;i++)
    {
    	scanf("%d", &b[i]);
    	a[i] = b[i];
	}
    sort(a+1, a+1+n);
    root[0] = creat(1, n);
    for(i=2;i<=n;i++)
    {
        scanf("%d", &j);
        g[j].push_back(i);
    }
    dfs(1);
    for(i=1;i<=n;i++)
        printf("%lld\n", dp[i]);
    return 0;
}
 
void dfs(int u)
{
    int i, j, k, l=num, r;
    LL ans = 0;
    for(i=0;i<g[u].size();i++)
    {
        dfs(g[u][i]);
        ans += dp[g[u][i]];
    }
    //���£���b[u]��������r-1���߶����� 
    r = ++num;
    int ins = lower_bound(a+1, a+1+n, b[u])-a;
    root[r-1] = update(root[r-2], 1, n, ins);
    int ql = lower_bound(a+1, a+1+n, b[u]-m)-a;
    int qr = upper_bound(a+1, a+1+n, b[u]+m)-a;
    query(root[l-1], root[r-1], 1, n, ql, qr-1, ans);
    dp[u] = ans;
}
//����ԭʼ���߶���(����) 
int creat(int l, int r)
{
	int ts = ++num1;
	p[ts].sum = 0;
	if(l == r)return ts;
	int mid = (l+r)>>1;
	p[ts].l = creat(l, mid);
	p[ts].r = creat(mid+1, r);
	return ts;
}
//��������x������ʱ������������ص���
int update(int la, int l, int r, int x)
{
	int now = ++num1;
	p[now] = p[la];
	if(l == r){
		p[now].sum++;return now;
	}
	int mid=(l+r)>>1;
	if(x<=mid)
		p[now].l = update(p[la].l, l, mid, x);
	else
		p[now].r = update(p[la].r, mid+1, r, x);
	p[now].sum++;
	return now;
}
//��ѯ[l,r]֮�䣬��ֵ��[ll,rr]֮������ܹ��ж��ٸ� 
void query(int ql, int qr, int l, int r, int ll, int rr, LL &ans)
{
	if(l == ll && r == rr)
	{
		ans += p[qr].sum - p[ql].sum;
		return;
	}
	int mid = (l+r)>>1;
	if(rr<=mid)
		query(p[ql].l, p[qr].l, l, mid, ll, rr, ans);
	else if(ll>mid)
		query(p[ql].r, p[qr].r, mid+1, r, ll, rr, ans);
	else
	{
		query(p[ql].l, p[qr].l, l, mid, ll, mid, ans);
		query(p[ql].r, p[qr].r, mid+1, r, mid+1, rr, ans);
	}
}
