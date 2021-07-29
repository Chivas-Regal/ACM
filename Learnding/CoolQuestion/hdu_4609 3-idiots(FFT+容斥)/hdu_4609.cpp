//FFT+�ݳ�˼��
//��n���ߣ�����ȡ��������������εĸ���
//�����ֱ������ж����ֿ�����������λ���Щ����
//������ö�������߿�����ɵĳ�(ʹ��FFT��ע��ȥ��),
//Ȼ��ö�ٵ������ߣ����赱ǰ���������֪������
//�ߺʹ��ڵ������߾Ϳ�����������Σ�����Ҫ��ȥ
//ʹ�õ�ǰ�ߺ���һ���ߣ�һ������һ��С�ڵ�ǰ��
// �������ڵ�ǰ�ߵ�������������ǽ�� 
//�ο����ͣ�https://www.cnblogs.com/kuangbin/archive/2013/07/24/3210565.html
//��Ŀ���ӣ�http://acm.hdu.edu.cn/showproblem.php?pid=4609
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100100;
const int mod = 1e9;
const double PI = acos(-1.0);
struct Complex{
	double x, y;
	Complex(double _x=0.0, double _y=0.0){
		x = _x;
		y = _y;
	}
	Complex operator -(const Complex &b)const{
		return Complex(x-b.x, y-b.y);
	}
	Complex operator +(const Complex &b)const{
		return Complex(x+b.x, y+b.y);
	}
	Complex operator *(const Complex &b)const{
		return Complex(x*b.x-y*b.y,x*b.y+y*b.x);
	}
};

void change(Complex y[], int len){
	int i, j, k;
	for(i=1,j=len/2;i<len-1;i++){
		if(i<j)swap(y[i], y[j]);
		k = len/2;
		while(j>=k){
			j -= k;k/=2;
		}
		if(j<k)j+=k;
	}
}

void fft(Complex y[], int len, int on)
{
	change(y, len);
	for(int h=2;h<=len;h<<=1){
		Complex wn(cos(-on*2*PI/h), sin(-on*2*PI/h));
		for(int j=0;j<len;j+=h){
			Complex w(1, 0);
			for(int k=j;k<j+h/2;k++){
				Complex u = y[k];
				Complex t = w*y[k+h/2];
				y[k] = u+t;
				y[k+h/2] = u-t;
				w = w*wn;
			}
		}
	}
	if(on == -1)
		for(int i=0;i<len;i++)
			y[i].x /= len;
}


Complex x1[8*maxn], x2[8*maxn];
int p[maxn], a[maxn];
LL sum[8*maxn], q[4*maxn];

int main(){
	int t, n, i, j, len1, len;
	scanf("%d", &t);
	while(t--){
		LL au, ad;
		scanf("%d", &n);
		len = 1;
		memset(p, 0, sizeof(p));
		for(i=0;i<n;i++){
			scanf("%d", &a[i]);
			p[a[i]]++;
		}
		sort(a, a+n);
		len1 = a[n-1]+1;
		while( len < len1*2)len<<=1;
		for(i=0;i<len1;i++)
			x1[i] = Complex(p[i], 0);
		for(i=len1;i<len;i++)
			x1[i] = Complex(0, 0);
		fft(x1, len, 1);
		for(i=0;i<len;i++)
			x1[i] = x1[i]*x1[i];
		fft(x1, len, -1);
		for(i=0;i<=len;i++)
			q[i] = (LL)(x1[i].x + 0.5);
		for(i=0;i<n;i++)
			q[a[i]+a[i]]--;
		//len֮ǰ��2�������ݿ��ܴܺ󣬺��涼��0
		//ʵ�������ֻ��2*a[n-1] 
		len = 2*a[n-1];
		sum[0] = 0;
		for(i=1;i<=len;i++){
			q[i] /= 2;
			sum[i] = sum[i-1]+q[i];
		}
		au = 0;
		//���赱ǰ����Ϊ���ߣ��ܵõ������� 
		for(i=0;i<n;i++){
			//����ѡ������֮�ʹ���a[i]�ģ�������
			//������������ȥ 
			au += sum[len]-sum[a[i]];
			//��ȥһ��һС�ģ� 
			au -= (LL)(n-1LL-i)*i;
			//��ȥ������ 
			au -= n-1;
			//��ȥ�������������� 
			au -= (LL)(n-1-i)*(n-i-2)/2;
		}
		ad = (LL)n*(n-1)*(n-2)/6;
		printf("%.7lf\n", au*1.0/ad);
	}
	return 0;
}
