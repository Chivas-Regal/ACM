//���Ի�����kСֵ
//�����Ի����ÿ������������ÿһλͨ�������Ի���
//���������������ʹ��ֻ�����λΪ1��
//http://acm.hdu.edu.cn/showproblem.php?pid=3949
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<set>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
const int maxn = 110;
LL maxx, ans, sig, kk, a[10020], b[66];
void insert(LL n);

int main()
{
    int t, n, i, j, k, q;
    scanf("%d", &t);
    for(int z=1;z<=t;z++)
    {
        sig = 1;
        scanf("%d", &n);
        memset(b, 0, sizeof(b));
        for(i=0;i<n;i++)
        {
            scanf("%lld", &a[i]);
            insert(a[i]);
        }
        //��ÿ����������Ϊֻ�����λΪ1 
        for(i=0;i<=62;i++)
            if(b[i])
            for(j=i-1;j>=0;j--)
                if((b[i]>>j)&1 == 1)b[i]^=b[j];
        vector<LL> g;
        for(i=0;i<=62;i++)
        if(b[i])g.push_back(b[i]);
        scanf("%d", &q);
        printf("Case #%d:\n", z);
        //����ɲ�ͬ����������Ϊ2^g.size() 
        maxx = 1LL<<g.size();
        while(q--)
        {
            scanf("%lld", &kk);
            if(!sig)kk--;
            if(maxx<=kk)
                printf("-1\n");
            else
            {
                ans = i = 0;
                while(kk>0)
                {
                    if(kk%2)ans ^= g[i];
                    i++;
                    kk /= 2;
                }
                printf("%lld\n", ans);
            }
        }
    }
    return 0;
}
//�������Ի�����n�����Ϊ1��λΪ��sλ�����
//"����"���д��ڵ�sλΪ1��������n�������򣬲�
//�����ظ��˲�������������ڵ�sλΪ1�����������n
//���˳�ѭ�� 
void insert(LL n)
{
    for(int i=62;i>=0;i--)
    {
        if((n>>i)&1 == 1)
        {
            if(!b[i]){
                b[i] = n;break;
            }
            else
                n ^= b[i];
        }
        if(n == 0)
        {
            sig = 0;
            break;
        }
    }
}
