//EXBSGS
//��x^y % p = z % p ����֤gcd(x,p)==1 
//����ͨ��ת���������Ϊ����ʹ��BSGS����ʽ
//��d = gcd(x,p)
//��d!=1
//    x ^ y % p = z % p
// => x ^ y + k*p = z
// => x/d * x^(y-1) + k*p/d = z/d
//��Ȼz�����������d���޽⣬
//����һֱѭ����ȥ���Եõ�
// => xi * x^(y-num) + k*p1 = z1
// ��Ϊgcd(x,p1)==1,���Դ�ʱ�Ϳ���ʹ��BSGS�㷨�������
//��Ŀ���ӣ�http://poj.org/problem?id=3243
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
#define eps 1e-6
#define MOD 106711
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 1001000;
int hs[MOD], hd[MOD], nex[MOD], id[MOD], top;
LL EXBSGS(LL x, LL z, LL p);
LL gcd(LL a, LL b);
LL Pow(LL a, LL b, LL mod);
void Insert(LL x, LL y);
int Find(int x);

int main()
{
	LL x, z, p, ans;
	while(~scanf("%lld %lld %lld", &x, &p, &z),x||p||z)
	{
		ans = EXBSGS(x, z, p);
		if(ans == -1)
			printf("No Solution\n");
		else
			printf("%lld\n", ans);
	}
	return 0;
}
 
LL gcd(LL a, LL b)
{
	LL k;
	do{
		k = a%b;
		a = b;
		b = k;
	}while(k!=0);
	return a;
}

LL EXBSGS(LL x, LL z, LL p)
{
	x %= p, z %= p;
	if(z == 1)return x==0?-1:0;
	if(x == 0)return z>1?-1:z==0&&p>1;
	memset(hd, -1, sizeof(hd));
	top = 1;
	LL m, d, tmp1, tmp2, num = 0, xi = 1;
	//��gcd(x,p)!=1 ʱ���Թ�ʽ����ת�� 
	while((d = gcd(x, p))!= 1){
		if(z == 1)return num;
		if(z % d != 0)return -1;
		z /= d, p /= d;
		xi = x/d*xi%p, num++;
	}
	m = sqrt(p*1.0);
	tmp1 = z, tmp2 = 1;
	for(int i=1;i<=m;i++){
		tmp1 = tmp1 * x % p;
		tmp2 = tmp2 * x % p;
		Insert(tmp1, i);
	}
	tmp1 = xi;
	for(LL i=m;i<p;i+=m){
		tmp1 = tmp2 * tmp1 % p;
		if((d=Find(tmp1))>-1)
			return i+num-d;
	}
	return -1;
}
//�����ֵ��[x,y] 
void Insert(LL x, LL y)
{
	int k = x % MOD;
	hs[top] = x, id[top] = y;
	nex[top] = hd[k], hd[k] = top++;
}
//��ѯx��Ӧ�ļ�ֵ 
int Find(int x){
	int k = x%MOD;
	for(int i=hd[k];i!=-1;i=nex[i])
	{
		if(hs[i] == x)return id[i];
	}
	return -1;
}
