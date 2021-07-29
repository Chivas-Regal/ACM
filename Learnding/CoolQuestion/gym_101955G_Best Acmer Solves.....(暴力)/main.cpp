//暴力
//主要在于求离(x,y)的距离正好为根号k，设偏移量(x1,y1)
//如果x1*x1+y1*y1=k，则其离点(x,y)距离正好为k，因为
//实际上满足条件的(x1,y1)很少，所以直接暴力就好
//因为m时10^5,所以求(x1,y1)时需要预处理出来，否则复杂度
//可能变为6000*10^5
//题目链接：https://codeforces.com/gym/101955/problem/G
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
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 100100;
vector<P> g[10001000];
bool inyu(int x, int y);

int main()
{
	int t, n, m, i, j, x, y, w, k;
	for(i=0;i<=6000;i++)
		for(j=0;j<=6000;j++){
			k = i*i+j*j;
			if(k <= 10000100){
				g[k].push_back(P(i, j));
			}
		}
	scanf("%d", &t);
	for(int z=1;z<=t;z++)
	{
		//mp维护点的权值 
		map<P, int> mp;
		int op;
		LL lastans = 0;
		scanf("%d %d", &n, &m);
		for(i=0;i<n;i++)
		{
			scanf("%d %d %d", &x, &y, &w);
			mp[P(x,y)] = w;
		}
		printf("Case #%d:\n", z);
		while(m--)
		{
			scanf("%d %d %d", &op, &x, &y);
			x = (x+lastans)%6000+1, y = (y+lastans)%6000+1;
			if(op == 1){
				scanf("%d", &w);
				mp[P(x,y)] = w;
			}
			else if(op == 2){
				mp[P(x,y)] = 0;
			}
			else if(op == 3){
				scanf("%d %d", &k, &w);
				//距离的平方正好为k，求x*x+y*y=k，满足条件
				//的(x,y)有多少对就可以了 
				for(j=0;j<g[k].size();j++){
					i = g[k][j].first;
					int s2 = g[k][j].second;
					//当其中一个为0时，可能重复，所以需要去重 
					if(i == 0 && s2 == 0){
						if(inyu(x, y)){
							int &a1 = mp[P(x,y)];
							if(a1>0)a1+=w;	
						}
					}
					else if(i == 0){
						if(inyu(x, y-s2)){
							int &a1 = mp[P(x, y-s2)];
							if(a1>0)a1+=w;
						}
						if(inyu(x, y+s2)){
							int &a1 = mp[P(x, y+s2)];
							if(a1>0)a1+=w;
						}
					}
					else if(s2 == 0){
						if(inyu(x+i, y)){
							int &a1 = mp[P(x+i, y)];
							if(a1>0)a1+=w;
						}
						if(inyu(x-i, y)){
							int &a1 = mp[P(x-i, y)];
							if(a1>0)a1+=w;
						}
					}
					else{
						if(inyu(x+i, y+s2)){
							int &a1 = mp[P(x+i, y+s2)];
							if(a1>0)a1+=w;
						}
						if(inyu(x-i, y-s2)){
							int &a1 = mp[P(x-i, y-s2)];
							if(a1>0)a1+=w;
						}
						if(inyu(x+i, y-s2)){
							int &a1 = mp[P(x+i, y-s2)];
							if(a1>0)a1+=w;
						}
						if(inyu(x-i, y+s2)){
							int &a1 = mp[P(x-i, y+s2)];
							if(a1>0)a1+=w;
						}
					}
				}
			}
			else if(op == 4){
				LL ans = 0;
				scanf("%d", &k);
				//操作如同操作3，结果的和会爆int，用LL 
				for(j=0;j<g[k].size();j++){
					i = g[k][j].first;
					int s2 = g[k][j].second;
						if(i == 0 && s2 == 0){
							if(inyu(x, y)){
								int &a1 = mp[P(x,y)];
								ans += a1;
							}
						}
						else if(i == 0){
							if(inyu(x, y-s2)){
								int &a1 = mp[P(x, y-s2)];
								ans+=a1;
							}
							if(inyu(x, y+s2)){
								int &a1 = mp[P(x, y+s2)];
								ans+=a1;
							}
						}
						else if(s2 == 0){
							if(inyu(x+i, y)){
								int &a1 = mp[P(x+i, y)];
								ans+=a1;
							}
							if(inyu(x-i, y)){
								int &a1 = mp[P(x-i, y)];
								ans+=a1;
							}
						}
						else{
							if(inyu(x+i, y+s2)){
								int &a1 = mp[P(x+i, y+s2)];
								ans+=a1;
							}
							if(inyu(x-i, y-s2)){
								int &a1 = mp[P(x-i, y-s2)];
								ans+=a1;
							}
							if(inyu(x+i, y-s2)){
								int &a1 = mp[P(x+i, y-s2)];
								ans+=a1;
							}
							if(inyu(x-i, y+s2)){
								int &a1 = mp[P(x-i, y+s2)];
								ans+=a1;
							}
						}
				}
				printf("%I64d\n", ans);
				lastans = ans;
			}
		}
	}
	return 0;
}
//判断(x,y)是否在合理范围内 
bool inyu(int x, int y)
{
	if(x>=1 && x<=6000 && y>=1 && y<=6000)
		return true;
	return false;
}
