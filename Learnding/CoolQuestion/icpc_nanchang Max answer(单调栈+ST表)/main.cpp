//����ջ+ST��
//һ�����У�Ŀ��ֵΪ������Сֵ������ͣ�������Ŀ��ֵ
//����ʹ�õ���ջ�����iΪ��Сֵ�ģ���������Ҷ˵�l��r 
//Ȼ���������ת��Ϊ������[l,r]�ڰ���i�����
//(��С(��Ϊa[i]����Ϊ��))�Ӷκͣ�����ͨ��st��
//�����������Ӷκ�,��Ϊ����i,���Ե�����[l,i]��
//ѡһ��λ����Ϊ����ֶκ���˵㣬��[i,r]ѡһ���Ҷ˵�
//��Ϊ������[l,r]�ĺ�Ϊsum[r]-sum[l-1]��������
//ѡȡֵʱ����˵�ʱ����Ӧ��ѡ[l-1,i-1]
//����ջ�ο����ϣ�https://blog.csdn.net/tsunagxy/article/details/87987490
//��Ŀ���ӣ� https://nanti.jisuanke.com/t/38228
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
		//����a[i]Ϊ��Сֵ���ܵõ������ֵ
		//���a[i]Ϊ������[l,r]����������
		//��sum��[i,r]�����ֵ��[l-1,i-1]����Сֵ 
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
//st��Ԥ�����ǰ׺�͵���С�����ֵ 
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
//����ջ���Ե�i��Ԫ����Ϊ��Сֵ������Զ���������� 
//ԭ��Ϊ1~n,��ǰ׺�Ϳ���Ϊ0������Ӧ����0~n��ֵ 
void instack(int n)
{
	int i, l;
	l = -1;
	for(i=1;i<=n;i++){
		//���a[i]��ջ��Ԫ�ش�����������˵�Ϊ
		//ջ�����ڵ�λ�õĺ�һ��λ�� 
		if(l==-1 || a[i]>a[sk[l]]){
			if(l == -1)
				li[i] = 1;
			else
				li[i] = sk[l]+1;
			sk[++l] = i;
		}
		//���a[i]��ջ��Ԫ��С���򵯳�ջ��Ԫ��
		//ֱ��a[i]����ջ��Ԫ�ػ�ջΪ�� 
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
