//�����滮
//���ű��ʱ�������
//��n����Ʒ��ÿ����Ʒ�м�ֵt��������w
//����һЩ��Ʒʹt1+t2+...+tk��w1+w2+...+wk�ı�ֵ�����
//w1+w2+...+wk>= W(�Ѹ���)
//˼·�������滮�ľ���ģ�ͣ�ͬ�����ö���ö��L
//Ȼ��ÿ����ƷȨֵ�ͱ�Ϊd = t - L * w; 
//Ȼ���Ƿ�����������������ʹsimga(d)>0
//����и����½磬û��������Ͻ�
//PS����Ŀһ��ʼ����ʹ����ֱ��̰�ĵģ���dֵ��������̰��
//ȥ����d��ֱ��w�ĺʹ��ڵ���W����������ʹ���
//�����������ʱ���Ǵ��
//W = 8
//d:2 -0.1 -0.5 -1.5 
//w:4   1    2    4  
//��Ŀ���ӣ�https://www.luogu.org/problem/P4377
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
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 300;
double d[maxn], dp[1020]; 
int w[maxn], t[maxn];
bool check(double mid, int w, int n);

int main()
{
	int n, W, i, j, sum;
	double l, r;
	scanf("%d %d", &n, &W);
	for(i=1;i<=n;i++)
		scanf("%d %d", &w[i], &t[i]);
	//�����ҳ�����L 
	l = 0.0, r = 10000000.0;
	while(r-l>eps)
	{
		double mid = (l+r)/2;
		if(check(mid, W, n))	
			l = mid;
		else
			r = mid;
	}
	printf("%d\n", (int)(l*1000));
	return 0;
}
//�������LΪmidʱ���Ƿ����d�ĺʹ���0����� 
bool check(double mid, int W, int n)
{
	int i, j, k;
	for(int i=1;i<=n;i++){
		d[i] = t[i] - mid * w[i];
	}
	//��dp�����ʼ��Ϊһ����Сֵ 
	for(i=0;i<=W;i++)
		dp[i] = -INF;
	dp[0] = 0;
	for(i=1;i<=n;i++){
		for(j=W;j>=0;j--){
			//�������� 
			int k = min(W, j+w[i]);
			dp[k] = max(dp[k], dp[j]+d[i]);
		}
	}
	return dp[W] >= 0;
}
