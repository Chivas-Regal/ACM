//前缀线性基
//一串序列求[l,r]内最大异或和
//构造前缀线性基，可以使用靠右的元素的则尽量使用靠右元素
//对于第i个元素的状态，如果线性基构建时，之前无元素 
//则直接将其放入线性基中；如果有，则将靠后的放入其中
//对于区间[l,r]，访问r时的状态，如果第i个的位置在l之后
//则可以使用
//题目链接：http://acm.hdu.edu.cn/showproblem.php?pid=6579 
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
//a:线性基状态 pos:对应线性基出现时间 
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
				//(ans^a[r][i])神奇的优先级？？！！ 
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
	//当前位为1 
	if(n>>i)
	{
		//出现过，则将靠后的元素放入线性基中
		//并对考前的线性基继续构造 
		if(a[row][i]){
			if(pos[row][i]<j){
				tmp=a[row][i],a[row][i]=n,n=tmp;
				tmp=pos[row][i],pos[row][i]=j,j=tmp;
			}
			n ^= a[row][i];
		}
		//未出现过则直接放入线性基中 
		else{
			a[row][i] = n;
			pos[row][i] = j;
			return;
		}
	}
}
