//Matrix_tree����
//Kirchhoff��������n-1���Ӿ��������ʽ�ľ���ֵ��������ͼ����������������
//Kirchhoff����Ķ����Ƕ�������-�ڽӾ���
//1��G�Ķ�������D[G]��n*n�ľ���Dii����Vi�Ķ���������Ϊ0��
//2��G���ڽӾ���A[G]��n*n�ľ��� Vi��Vj֮���б�ֱ���������� Aij=ij֮��ı���������Ϊ0��
//��Ŀ���ӣ�https://www.lydsy.com/JudgeOnline/problem.php?id=4031
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<map>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f
#define eps 1e-8

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100;
const int mod = 1e9;
int id[maxn][maxn];
LL a[maxn][maxn];
int dx[4]={0,-1,0,1}, dy[4]={-1,0,1,0};
LL det(int n);
void getgrape(int n, int m, char str[][12]);

int main()
{
	int n, m, i, j, num = 0;
	char str[12][12];
	scanf("%d %d", &n, &m);
	for(i=0;i<n;i++){
		scanf("%s", str[i]);
		for(j=0;j<m;j++)
		if(str[i][j]=='.')
			id[i][j] = num++;
	}	
	getgrape(n, m, str);
	LL ans = det(num-1);
	printf("%d", ans);
	return 0;
}

void getgrape(int n, int m, char str[][12])
{
	int i, j, k, nx, ny;
	memset(a, 0, sizeof(a));
	for(i=0;i<n;i++)
		for(j=0;j<m;j++){
			if(str[i][j] != '*'){
				for(k=0;k<4;k++){
					nx = i + dx[k];
					ny = j + dy[k];
					if(nx>=0 && nx<n && ny>=0 && ny<m && str[nx][ny]=='.'){
						a[id[i][j]][id[i][j]]++,a[id[i][j]][id[nx][ny]]--;
					}
				}
			}	
		}
}
//��˹��Ԫշת��Ԫ��
//�ɱ��⾫�����⣬��ʱ�临�Ӷ�Ϊn*n*n*log n 
LL det(int n){
	LL i, j, k, t, ret=1;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			a[i][j] %= mod;
	for(i=0;i<n;i++){
		for(j=i+1;j<n;j++)
			while(a[j][i]){
				t = a[i][i] / a[j][i];
				for(k=i;k<n;k++)
					a[i][k] = (a[i][k]-a[j][k]*t)%mod;
				swap(a[i], a[j]);
				ret = -ret;
			}
		if(a[i][i] == 0)
			return 0LL;
		ret = (ret*a[i][i]) % mod;
	}
	return (ret+mod)%mod;
}
