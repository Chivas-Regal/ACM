//DP
//��һ��ֻ����AB�Ĵ������Ӵ���ÿ����ĸ����һ�����Ĵ���һ����
//�������Ӵ�������
//˼·���������ܵķ�������ȥ������ķ����������Է�������� 
//ABBBBB��BAAAA��AAAAAAB��BBBBBBA�����ǲ�����ļ�ȥ���Ǽ���
//��Ŀ���ӣ�https://codeforces.com/problemset/problem/1238/D 
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
const int maxn = 300100;
char str[maxn];

int main()
{
	int n, i, j, up;
	LL ans;
	scanf("%d %s", &n, str);
	ans = (LL)n*(n-1)/2;
	up = 0;
	for(i=1;i<n;i++){
		//��ȥAAAAB��BBBBA������ʽ�Ĳ����������
		//��ΪAB���������ظ���������ans��Ҫ+1 
		if(str[i] != str[i-1]){
			ans -= i-up-1;
			up = i;
		}
	}
	up = n-1;
	for(i=n-2;i>=0;i--){
		if(str[i] != str[i+1]){
			ans -= up - i;
			up = i;
		}
	}
	printf("%I64d\n", ans);
	return 0;
}
