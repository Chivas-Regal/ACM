//ǰ׺���Ի�
//һ��������[l,r]���������
//����ǰ׺���Ի�������ʹ�ÿ��ҵ�Ԫ�ص�����ʹ�ÿ���Ԫ��
//���ڵ�i��Ԫ�ص�״̬��������Ի�����ʱ��֮ǰ��Ԫ�� 
//��ֱ�ӽ���������Ի��У�����У��򽫿���ķ�������
//��������[l,r]������rʱ��״̬�������i����λ����l֮��
//�����ʹ��
//��Ŀ���ӣ�http://acm.hdu.edu.cn/showproblem.php?pid=6579 
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
const int maxn = 500100;
//a:���Ի�״̬ pos:��Ӧ���Ի�����ʱ�� 
int b[maxn], a[maxn][32], pos[maxn][32];
void upd(int row, int n);

int main()
{
	int t, n, m, lastans, l, r, i, k;
	scanf("%d", &t);
	while(t--)
	{
		lastans = 0;
		scanf("%d %d", &n, &m);
		for(i=1;i<=n;i++){
			scanf("%d", &b[i]);
			upd(i, b[i]);
		}
		lastans = 0;
		while(m--){
			scanf("%d", &k);
			if(k){
				scanf("%d", &l);
				l ^= lastans;
				n++;
				upd(n, l);
			}
			else{
				scanf("%d %d", &l, &r);
				l = (l^lastans)%n + 1;
				r = (r^lastans)%n + 1;
				if(l > r){
					int tmp=l;l=r;r=tmp;
				}
				int ans = 0;
				for(i=30;i>=0;i--)
				//(ans^a[r][i])��������ȼ��������� 
					if(pos[r][i]>=l && (ans^a[r][i]) > ans)
						ans ^= a[r][i];
				printf("%d\n", ans);
				lastans = ans;
			}
		} 
	}
	return 0;
}

void upd(int row, int n){
	int i, j=row, tmp;
	for(i=30;i>=0;i--)
		a[row][i] = a[row-1][i],pos[row][i] = pos[row-1][i];
	for(i=30;i>=0;i--)
	//��ǰλΪ1 
	if(n>>i)
	{
		//���ֹ����򽫿����Ԫ�ط������Ի���
		//���Կ�ǰ�����Ի��������� 
		if(a[row][i]){
			if(pos[row][i]<j){
				tmp=a[row][i],a[row][i]=n,n=tmp;
				tmp=pos[row][i],pos[row][i]=j,j=tmp;
			}
			n ^= a[row][i];
		}
		//δ���ֹ���ֱ�ӷ������Ի��� 
		else{
			a[row][i] = n;
			pos[row][i] = j;
			return;
		}
	}
}
