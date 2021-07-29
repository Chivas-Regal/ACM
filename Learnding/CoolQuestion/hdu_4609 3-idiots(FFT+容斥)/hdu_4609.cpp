//FFT+容斥思想
//有n条边，求任取三条边组成三角形的概率
//如果想直接求出有多少种可以组成三角形会有些困难
//可以先枚举两条边可以组成的长(使用FFT，注意去重),
//然后枚举第三条边，假设当前边最长，可以知道两条
//边和大于第三条边就可以组成三角形，但需要减去
//使用当前边和另一条边，一条大于一条小于当前边
// 两条大于当前边的情况，减完后就是结果 
//参考博客：https://www.cnblogs.com/kuangbin/archive/2013/07/24/3210565.html
//题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=4609
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
		//len之前是2的整次幂可能很大，后面都是0
		//实际上最多只到2*a[n-1] 
		len = 2*a[n-1];
		sum[0] = 0;
		for(i=1;i<=len;i++){
			q[i] /= 2;
			sum[i] = sum[i-1]+q[i];
		}
		au = 0;
		//假设当前边作为最大边，能得到的数量 
		for(i=0;i<n;i++){
			//可以选择两边之和大于a[i]的，但存在
			//其他情况，需减去 
			au += sum[len]-sum[a[i]];
			//减去一大一小的， 
			au -= (LL)(n-1LL-i)*i;
			//减去其自身 
			au -= n-1;
			//减去两个都大于它的 
			au -= (LL)(n-1-i)*(n-i-2)/2;
		}
		ad = (LL)n*(n-1)*(n-2)/6;
		printf("%.7lf\n", au*1.0/ad);
	}
	return 0;
}
