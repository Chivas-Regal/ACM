//���㼸��+����
//��֪��ά��n��������С�������е��Բ׶�����������ߺ͵���뾶
//��ΪԲ׶�Ķ���һ��x��y������һ��Ϊ0,���Կ�������z������
//����ÿ��ȷ����z���꣬����ȷ����С�İ뾶r��Ȼ����֪����
//����Сֵ���� 
//��Ŀ���ӣ�http://poj.org/problem?id=3962
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
#include<iostream>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 10100;
struct node{
	double x, y, z, r;
}p[maxn];
int a[maxn];
double isok(double z, double n, double &rr);
bool cmp(node a, node b);

int main()
{
	int n, i, j;
	double lz = 0, rz, ans, rr;
	scanf("%d", &n);
	for(i=0;i<n;i++){
		scanf("%lf %lf %lf", &p[i].x, &p[i].y, &p[i].z);
		p[i].r = sqrt(p[i].x*p[i].x+p[i].y*p[i].y);
		lz = max(lz, p[i].z);
	}
	//�����������볢���Ż�һ�£����͸��Ӷȣ�Ȼ��ûɶ��
	//˵��������ģ���˻��ܵ���һ�� 
	sort(p, p+n, cmp);
	rr = p[n-1].r;
	for(i=n-2;i>=0;i--){
		if(p[i].r < rr)
			a[i] = 1;
		else
			rr = p[i].r;
	}
	int num = 0;
	for(i=0;i<n;i++)
	if(!a[i])p[num++] = p[i];
	n = num;
	//*******************
	
	rz = 10000;
	while(fabs(lz-rz)>1e-8)
	{
		double mid = (rz-lz)/3; 
		//�����������ȷֵ�ʱ��ֵ 
		double midl = isok(lz+mid, n, rr), midr = isok(lz+2*mid, n, rr);
		//���������ȷֵ�ϴ��ֵ���� 
		if(midl > midr)
			lz = lz + mid;
		else
			rz = lz + 2*mid;
	}
	isok(lz, n, rr);
	printf("%.3f %.3f\n", lz, rr);
	return 0;
}

double isok(double z, double n, double &rr)
{
	double r=0;
	for(int i=0;i<n;i++)
	{
		//�������������Σ������뾶
		r = max(r, p[i].r/(1-p[i].z/z));
	}
	rr = r;
	return r*r*z;
}

bool cmp(node a, node b)
{
	return a.z < b.z;
}
