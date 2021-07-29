//Matrix_Tree 
//��һ��ͼ����С������������
//���Էֽ׶����ÿ����ͨ�����ж�����ѡ�� 
//Ȼ��ÿ���׶ε�������ˣ�������С������������
//����ʹ��Kruskal�㷨��ȡ�����е�ǰȨֵ��ȵı�
//����ߵ����˲���ͬһ�����ڣ���洢�µ�ǰ�ı�
//��������б�����ɵ�һ����ͨͼ���þ��������������������������� 
//�������Ҫ����ͨ������Ϊһ���� 
//PS����������һ��࣬��¼һ���Լ��ȵĿӰ�
//1.��С������������ֻ���ڵ�ǰ��ͨ������������������ҵ�
//���бߺ�����Matrix_Tree�����
//2.�ڱ�Ȩ��ͬʱ�������ж����ͨ��������Ҫ��ÿ����ͨ����
//��������������Ϊ���������ͨ����������һ�������У�����ζ��
//�Զ����ͨ������������������Щ��ͨ����������ͨ�����Ծ�û����
//���� 
//��Ŀ���ӣ� http://acm.hdu.edu.cn/showproblem.php?pid=4408011
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
const int maxn = 1020;
struct edge{
    int f, t, p;
}p[maxn];
vector<edge> g;
vector<int> ks, craay;
int num, a[120], big[maxn], color[120], b[120][120];
LL mod;
LL det(int n);
LL getNum(int n);
int Find(int x);
bool cmp(edge a, edge b);

int main()
{
    int n, m, i, j, k;
    LL ans;
    while(scanf("%d %d %lld", &n, &m, &mod), n||m||mod)
    {
        ans = 1;
        num = 0;
        g.clear();
        for(i=1;i<=n;i++)a[i] = i;
        for(i=0;i<m;i++){
            scanf("%d %d %d", &p[i].f, &p[i].t, &p[i].p);
        }
        sort(p, p+m, cmp);
        for(i=0;i<m;)
        {
            g.clear();
            for(j=i;j<m;j++){
                if(p[j].p != p[i].p)break;
                int x = Find(p[j].f), y = Find(p[j].t);
                if(x != y)g.push_back(p[j]);
            }
            i = j;
            if(g.size())
                ans = (ans * getNum(n)) % mod;
            //printf("ans:%lld\n", ans);
            if(num == n-1)break;
        }
        if(num != n-1)
            printf("0\n");
        else
            printf("%lld\n", (ans%mod+mod) %mod);
    }
    return 0;
}

bool cmp(edge a, edge b)
{
    return a.p < b.p;
}

int Find(int x)
{
    return a[x] = x==a[x]?x:Find(a[x]);
}

LL getNum(int n)
{
    int i, j, k, sum, sk = g.size();
    LL ans = 1;
    craay.clear();
    ks.clear();
    memset(big, 0, sizeof(big));
    memset(color, -1, sizeof(color));
    //��Ҫ����ıߣ�ԭ�����ڵ���ͨ���� 
    for(i=0;i<g.size();i++)
    {
        int x = Find(g[i].f), y = Find(g[i].t);
        big[g[i].f] = x, big[g[i].t] = y;
    }
    //���������γɵ���ͨ���� 
    for(i=0;i<g.size();i++){
        int x = Find(g[i].f), y = Find(g[i].t);
        craay.push_back(x), craay.push_back(y);
        if(x != y)a[x] = y, num++;
    }
    for(i=0;i<craay.size();i++)
    if(a[craay[i]] == craay[i])ks.push_back(craay[i]);
    //��ÿ����ͨ���������������� 
    for(i=0;i<ks.size();i++){
        memset(b, 0, sizeof(b));
        sum = 0;
        for(j=0;j<g.size();j++){
            int x = Find(g[j].f);
            if(x != ks[i])continue;
            int &u = color[big[g[j].f]], &v = color[big[g[j].t]];
            if( u == -1)u = sum++;
            if( v == -1)v = sum++;
            b[u][u]++, b[v][v]++;
            b[u][v]--, b[v][u]--;
        }
        ans = ans * det(sum-1)%mod;
    }
    g.clear();
    return ans;
}

LL det(int n){
    LL i, j, k, t, ret=1;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            b[i][j] %= mod;
    for(i=0;i<n;i++){
        for(j=i+1;j<n;j++)
            while(b[j][i]){
                t = b[i][i] / b[j][i];
                for(k=i;k<n;k++)
                    b[i][k] = (b[i][k]-b[j][k]*t)%mod;
                swap(b[i], b[j]);
                ret = -ret;
            }
        if(b[i][i] == 0)
            return 0LL;
        ret = (ret*b[i][i]) % mod;
    }
    return (ret+mod)%mod;
}
/*
6 9 10000
1 2 10
2 3 10
3 1 10
4 5 8
5 6 8
6 4 8
1 4 14
5 3 14
5 1 14
*/
