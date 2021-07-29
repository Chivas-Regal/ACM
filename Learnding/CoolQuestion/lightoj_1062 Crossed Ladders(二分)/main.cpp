//����
//��������ܵ�һ�о��Ǽ򵥵���ѧ���⣬ֻҪ�����ϵ
//���������ˣ��������󲻳�����Ȼ����Ҫ�Եױ߽��ж��֣�
//��x�����¥�Ľ���ΪA�����ұ�¥�Ľ���ΪC��y�����¥�Ľ���ΪB�����ұ�¥�Ľ���ΪD��
//x��y�Ľ���ΪE����E����������ߣ��费��ΪF��
//�����������ƣ�EF/AB=CF/CB=1-(BF/BC)=1-(EF/CD)��
//Ҳ����EF/AB=1-(EF/CD)������ͬʱ����EF
//ժ�ԣ� https://blog.csdn.net/u011644423/article/details/38380573
//��Ŀ���ӣ� http://lightoj.com/volume_showproblem.php?problem=1062
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
 
using namespace std;
typedef long long int LL;
typedef pair<int, int> P;
const int maxn = 220;

int main()
{
	int t, i, j, k, z;
	double a, b, c, l, r;
	scanf("%d", &t);
	for(z=1;z<=t;z++)
	{
		scanf("%lf %lf %lf", &a, &b, &c);
		l = 0, r = min(a, b);
		while(fabs(l-r)>1e-9)
		{
			double mid = (l+r)/2;
			//���1/EF > 1/c,��EF<c 
			if(1/sqrt(a*a-mid*mid)+1/sqrt(b*b-mid*mid)>1/c)
				r = mid;
			else
				l = mid;
		}
		printf("Case %d: %.6f\n", z, l);
	} 
	return 0;
}
