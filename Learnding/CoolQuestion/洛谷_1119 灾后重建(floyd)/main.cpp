//floyd�㷨
//��Щ���ڹ̶�ʱ�������ʹ�ã���ĳ��ʱ���������
//�����·
//��⣺��Ϊ��Ŀû��˵�̶������յ㣬����N<=200
//�������뵽floyd�������ڲ��ֽ����ܲ����ã�����
//���⿼�ľ���floyd��ϸ�����
//floyd������ѭ����������k�����Ǿ���k����ת
//�����(��һ����k��)��i��j�����i��j�ĵ�ǰ��̾��룬
//k��ѭ����������ʾ����k���Ըı�����·���Ѹ��� 
//ps��д�����߰���ģ�����ɣ�����P103 
//��Ŀ���ӣ�https://www.luogu.org/problemnew/show/P1119 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<string>
#include<ctype.h>
#include<cstring>
#include<stack>
#include<queue>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 220;
int a[maxn][maxn], tim[maxn];

int main()
{
    int n, m, q, t, i, j, k, l, r;
    scanf("%d %d", &n, &m);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
    	if(i == j)a[i][i] = 0;
    	else a[i][j] = INF;
    for(i=0;i<n;i++)
        scanf("%d", &tim[i]);
    while(m--)
    {
        scanf("%d %d %d", &i, &j, &k);
        a[i][j] = a[j][i] = k;
    }
    l = r = 0;
    scanf("%d", &q);
    while(q--)
    {
        int f, t, d;
        scanf("%d %d %d", &f, &t, &d);
        while(l<n && tim[l]<=d)l++;
        for(k=r;k<l;k++)
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                a[i][j] = min(a[i][j], a[i][k]+a[k][j]);
        if(d < tim[f] || d < tim[t] || a[f][t] == INF)
            printf("-1\n");
        else
            printf("%d\n", a[f][t]);
        r = l;
    }
    return 0;
}

