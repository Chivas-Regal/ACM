//单调栈+ST表
//一串序列，目标值为区间最小值乘区间和，求最大的目标值
//首先使用单调栈求出以i为最小值的，区间的左右端点l和r 
//然后问题可以转化为求区间[l,r]内包含i的最大
//(最小(因为a[i]可能为负))子段和，可以通过st表
//求区间的最大子段和,因为包含i,所以等于在[l,i]中
//选一个位置作为最大字段和左端点，在[i,r]选一个右端点
//因为求区间[l,r]的和为sum[r]-sum[l-1]，所以在
//选取值时，左端点时间上应该选[l-1,i-1]
//单调栈参考资料：https://blog.csdn.net/tsunagxy/article/details/87987490
//题目链接： https://nanti.jisuanke.com/t/38228
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
#define INF 100000000

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 500100;
int li[maxn], ri[maxn], sk[maxn];
LL b[maxn], a[maxn], res, sx[21][maxn], si[21][maxn];
void inst(int n);
void instack(int n);

int main()
{
	int n, i, j;
	scanf("%d", &n);
	for(i=1;i<=n;i++)
	{
		scanf("%lld", &a[i]);
		b[i] = b[i-1]+a[i];
	}
	a[n+1] = a[0] = -1e18;
	res = -1e18;
	instack(n);
	inst(n);
	for(i=1;i<=n;i++)
	{
		//求以a[i]为最小值，能得到的最大值
		//如果a[i]为正，则[l,r]中最大区间和
		//即sum中[i,r]的最大值，[l-1,i-1]的最小值 
		li[i] = max(li[i]-1, 0);
		int k = log(1.0*i-li[i])/log(2.0);
		LL mlx = max(sx[k][li[i]], sx[k][i-(1<<k)]);
		LL mli = min(si[k][li[i]], si[k][i-(1<<k)]);
		k = log(1.0*ri[i]-i+1)/log(2.0);
		LL mrx = max(sx[k][i], sx[k][ri[i]-(1<<k)+1]);
		LL mri = min(si[k][i], si[k][ri[i]-(1<<k)+1]);
		res = max(res, (mrx-mli)*a[i]);
		res = max(res, (mri-mlx)*a[i]);
	}
	printf("%lld\n", res);
	return 0;
}
//st表预处理出前缀和的最小和最大值 
void inst(int n)
{
	for(int i=0;i<=n;i++)
		sx[0][i] = si[0][i] = b[i];
	for(int j=1;j<=19;j++)
		for(int i=0;i<=n;i++){
			if(i+(1<<j)-1 <= n){
				sx[j][i] = max(sx[j-1][i], sx[j-1][i+(1<<(j-1))]);
				si[j][i] = min(si[j-1][i], si[j-1][i+(1<<(j-1))]);
			}
			else break;
		}
}
//单调栈求以第i个元素作为最小值，其最远的左右区间 
//原串为1~n,但前缀和可能为0，所以应该求0~n的值 
void instack(int n)
{
	int i, l;
	l = -1;
	for(i=1;i<=n;i++){
		//如果a[i]比栈顶元素大，则其左区间端点为
		//栈顶所在的位置的后一个位置 
		if(l==-1 || a[i]>a[sk[l]]){
			if(l == -1)
				li[i] = 1;
			else
				li[i] = sk[l]+1;
			sk[++l] = i;
		}
		//如果a[i]比栈顶元素小，则弹出栈顶元素
		//直到a[i]大于栈顶元素或栈为空 
		else{
			while(l>=0 && a[i]<= a[sk[l]]){
				l--;
			}
			if(l == -1)li[i] = 1;
			else li[i] = sk[l]+1;
			sk[++l] = i;
		}
	}
	l = -1;
	for(i=n;i>=1;i--){
		if(l==-1 || a[i]>a[sk[l]]){
			if(l == -1)
				ri[i] = n;
			else
				ri[i] = sk[l]-1;
			sk[++l] = i;
		}
		else{
			while(l>=0 && a[i]<= a[sk[l]]){
				l--;
			}
			if(l == -1)ri[i] = n;
			else ri[i] = sk[l]-1;
			sk[++l] = i;
		}
	}
}
