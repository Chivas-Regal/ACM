//���㼸��
//2018.icpc����D
//��������������ڳ��ڳ����һ�̣���ͷ������Ľ����غ�
//��ô�������㵽�����������һ���㣬ֻҪ��֤�Ǹ�����
//����ڼ���
//��Ҫ�����������һ���ǳ��ڳ���ʱ�Ǹ�����������ڣ������Ļ�
//��·��ȼ�Ϊ����㵽ԭ��ľ����ȥ�뾶
//����Ǹ���������ڣ�����Ը���ͶӰ�������Բ�뾶��Ȼ���ȥr 
//��Ŀ���ӣ�http://codeforces.com/gym/102028/problem/D 
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
const double pi = acos(-1.0);

int main()
{
	int t;
	double a, b, r, d, ts;
	scanf("%d", &t);
	while(t--)
	{
		scanf("%lf %lf %lf %lf", &a, &b, &r, &d);
		//��dת��Ϊ������ 
		d = d*pi / 180;
		//��Բ�ĵ������ľ��� 
		double dis = sqrt(b*b+(a+r)*(a+r));
		//�������Ҷ����������������������������ߵĻ��� 
		double cosa = (2*(a+r)*(a+r))/(2*(a+r)*dis);
		double ang = acos(cosa);
		//������ڳ���ʱ������������ڣ���ֱ�Ӽ�ȥr 
		if(ang <= d+eps){
			printf("%.6f\n", dis - r);
		}
		//������س���ʱ������������⣬����ͨ��ͶӰ���������Բ�뾶���ټ�ȥr 
		else{
			printf("%.6f\n", dis*cos(ang-d) - r);
		}
	}
	return 0;
}
