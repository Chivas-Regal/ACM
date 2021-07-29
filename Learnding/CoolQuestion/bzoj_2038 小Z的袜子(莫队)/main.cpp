//����Ī���㷨
//��n��������[l,r]��ȡ������������������ͬ�ĸ��� 
//Ī���㷨���ţ���m������ѯ��
//���֪��[l,r],��ô����ͨ���ƶ�һ��l��r��[l-1,r]
//[l+1,r],[l,r-1],[l,r+1]������ϸ���l��������
//����[1,10][2,2][3,10][4,4]���ֻ���������ȫ����������
//Ī���㷨���ǽ�����n���ֳɿ飬����l��ͬһ�������ѯ��
//��r�Ĵ�С�����������Ϳ��Խ�˳���Ϊ[2,2],[4,4][1,10][3,10]
//�������ӣ� https://www.cnblogs.com/CsOH/p/5904430.html
//��Ŀ���ӣ� https://www.lydsy.com/JudgeOnline/problem.php?id=2038
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
typedef unsigned long long LL;
typedef pair<int, int> P;
const int maxn = 10010;
const int mod = 1e9+7;
struct node
{
    int l, r, id;
}p[50010];
int a[50010], len;
LL sum[50010], ans[50010], anss[50010];
bool cmp(node a, node b);
LL gcd(LL a, LL b);

int main()
{
    int n, m, i, j, l, r;
    LL ans1;
    while(~scanf("%d %d", &n, &m))
    {
    	//ÿ��ĳ���Ϊlen
    	len = (int)sqrt(n);
	    for(i=1;i<=n;i++)
	        scanf("%d", &a[i]);
	    for(i=0;i<m;i++)
	    {
	        scanf("%d %d", &p[i].l, &p[i].r);
	        p[i].id = i;
	    }
	    sort(p, p+m, cmp);
	    memset(sum, 0, sizeof(sum));
	    ans1 = 0;
	    l = r = 1;
	    sum[a[1]]++;
	    for(i=0;i<m;i++)
	    {
	    	//����l,r,��֪[l,r]�Ľ������[p[i].l, p[i].r] 
	    	if(r < p[i].r)
	    	{
	    		while(r<p[i].r){
	    			r++;
	    			sum[a[r]]++;
					ans1 += 2*(sum[a[r]]-1);
				}
			}
			else
			{
				while(r>p[i].r){
					sum[a[r]]--;
					ans1 -= 2*sum[a[r]];
					r--;
				}
			}
	        if(l < p[i].l)
	    	{
	    		while(l<p[i].l){
	    			sum[a[l]]--;
					ans1 -= 2*sum[a[l]];
					l++;
				}
			}
			else
			{
				while(l>p[i].l){
					l--;
					sum[a[l]]++;
					ans1 += 2*(sum[a[l]]-1);
				}
			}
			if(ans1 == 0)
				ans[p[i].id] = 0, anss[p[i].id] = 1;
			else
			{
				LL tt = ((LL)p[i].r-p[i].l+1)*(p[i].r-p[i].l);
				LL gd = gcd(ans1, tt);
				ans[p[i].id] = ans1/gd, anss[p[i].id] = tt/gd;
			}
	    }
	    for(i=0;i<m;i++)
	            printf("%llu/%llu\n", ans[i], anss[i]); 
	}
    return 0;
}
 
bool cmp(node a, node b)
{
	if(a.l/len != b.l/len)return a.l<b.l;
    return a.r<b.r;
}
 
LL gcd(LL a, LL b)
{
    LL k;
    do{
        k = a % b;
        a = b;
        b = k;
    }while(k!=0);
    return a;
}
