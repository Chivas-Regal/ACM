//����
//��Ҫ��������(x,y)�ľ�������Ϊ����k����ƫ����(x1,y1)
//���x1*x1+y1*y1=k���������(x,y)��������Ϊk����Ϊ
//ʵ��������������(x1,y1)���٣�����ֱ�ӱ����ͺ�
//��Ϊmʱ10^5,������(x1,y1)ʱ��ҪԤ��������������Ӷ�
//���ܱ�Ϊ6000*10^5
//��Ŀ���ӣ�https://codeforces.com/gym/101955/problem/G
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
		//mpά�����Ȩֵ 
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
				//�����ƽ������Ϊk����x*x+y*y=k����������
				//��(x,y)�ж��ٶԾͿ����� 
				for(j=0;j<g[k].size();j++){
					i = g[k][j].first;
					int s2 = g[k][j].second;
					//������һ��Ϊ0ʱ�������ظ���������Ҫȥ�� 
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
				//������ͬ����3������ĺͻᱬint����LL 
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
//�ж�(x,y)�Ƿ��ں���Χ�� 
bool inyu(int x, int y)
{
	if(x>=1 && x<=6000 && y>=1 && y<=6000)
		return true;
	return false;
}
