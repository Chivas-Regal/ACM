//�������
//�������������ǰһ��Ԫ�صĲ�������������
//����ʡ�����ǵ���Ҳ��������˼·��
//Ψһ�Ŀӵ�����ж�a,b�Ƿ��ظ�����
//��������ò���д���
//5 5 6 3
// 1 6
// 1 5
// 1 4
//�õ����������Բ���
//��Ŀ���ӣ�https://www.luogu.org/problemnew/show/P2879 
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<queue>
#include<map>
#include<iostream>
#include<iterator>
#define INF 0x3f3f3f3f

using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 440;
int a[10010];
map<int,int> mp[10010];

int main()
{
	int n, i, h, r, j, k;
	memset(a, 0, sizeof(a));
	scanf("%d %d %d %d", &n, &i, &h, &r);
	while(r--){
		scanf("%d %d", &j, &k);
		if(j > k){
			int t=j;j=k;k=t;
		}
		if(mp[j][k] == 0)
			mp[j][k] = 1;
		else
			continue;
		if(j+1 < k)
		a[j+1]--, a[k]++;
	}
	j = 0;
	for(i=1;i<=n;i++)
	{
		j += a[i];
		printf("%d\n", h+j);
	}
	return 0;
}
