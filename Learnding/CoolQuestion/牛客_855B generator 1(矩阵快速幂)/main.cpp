//矩阵快速幂
//模板题，唯一思路清奇的地方就是与普通的对二进制
//不同，此题数据是10^(10^6),可以对10进制进行快速幂
//题目链接： https://ac.nowcoder.com/acm/contest/885/B
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
#define dbg(x) printf("debug:%d\n", x);
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<LL, int> P;
const int maxn = 1000100;
int mod;
char str[maxn];
struct matrix{
	int n;
	LL a[2][2];
	matrix(){}
	matrix(int e, int b, int c, int d){
		n = 2;
		a[0][0] = e, a[0][1] = b;
		a[1][0] = c, a[1][1] = d;
	}
};
matrix mul(matrix A, matrix B);
matrix Pow(matrix a, LL b);

int main()
{
	int i, x0, x1, a, b, len;
	matrix A, B(1,0,0,1); 
	scanf("%d %d %d %d", &x0, &x1, &a, &b);
	A.n = B.n = 2, A.a[0][0] = a, A.a[0][1] = b;
	A.a[1][0] = 1, A.a[1][1] = 0;
	scanf(" %s %d", str, &mod);
	len = strlen(str);
	for(i=len-1;i>=0;i--){
		matrix C = Pow(A, str[i]-'0');
		B = mul(B, C);
		A = Pow(A, 10);
	}
	printf("%lld\n", (B.a[1][0]*x1+B.a[1][1]*x0)%mod);
	return 0;
}

matrix mul(matrix A, matrix B){
	matrix C(1,0,0,1);
	memset(C.a, 0, sizeof(C.a));
	for(int i=0;i<A.n;i++)
		for(int j=0;j<B.n;j++){
			//这里如果多此累加不会爆的话，尽量
			//少做取余操作 
			C.a[i][j] = 0;
			for(int k=0;k<A.n;k++)
				C.a[i][j] += A.a[i][k]*B.a[k][j];
			C.a[i][j] %= mod; 
		}
		
	return C;
}

matrix Pow(matrix A, LL b)
{
	matrix C(1,0,0,1);
	while(b > 0){
		if(b&1) C = mul(C, A);
		A = mul(A, A);
		b >>= 1;
	}
	return C; 
}
