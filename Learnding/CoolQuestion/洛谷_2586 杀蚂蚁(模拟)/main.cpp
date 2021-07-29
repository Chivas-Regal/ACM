/************************************************
模拟+计算几何
题意太长，直接读题吧

思路：大模拟。按照题目要求写就好，中间套了点计算几何。设结构体维护每个蚂蚁的信息，因为总数较少，所以删除某个点的时候直接把后面的点前移就好了。对于每个事件，写个函数就好了。注意严格按照题目说的做。
注意一些坑点，蚂蚁不动也可以拿到蛋糕。

题目链接：https://www.luogu.com.cn/problem/P2586
****************************************************/
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<vector>
#include<queue>
#include<map>
#include<iterator>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;
typedef pair<int, int> P;
const int maxn = 30;
const int mod = 998244353;
struct art{
	int t, hp, hpmax, exp, x, y, stu, upx, upy;
	art(){stu = 0;upx = upy = -1;}
	art(int a, int b, int c, int d, int e){
		t=a, exp = c, hpmax = hp = b, x = d, y = e;
		stu = 0;
		upx = upy = -1;
	}
}mayi[10];
//sig:蛋糕是否还在，num:活着的蚂蚁数量,ov:游戏是否结束
int n, m, num, sig, ov;
//a:信息素数量，c:位置是否是可行点
int x[maxn], y[maxn], a[10][10], c[10][10];
int dx[4]={0,1,0,-1}, dy[4]={1,0,-1,0};
bool internal(int x, int y);
void getdir(art &b, int t);
void UpdInfo();
void ArtDie(int i);
void Attack(int x, int y, int d, int r);
int dist(int x1, int y1, int x2, int y2);
double PointToLine(int x, int y, int a1, int b1, int a2, int b2);

int main()
{
	int t, s, d, r, i, j, k;
	int sum = 0;
	double xue = 1.1;
	num = 0, sig = 1, ov = 0;
	scanf("%d %d %d %d %d", &n, &m, &s, &d, &r);
	memset(c, 0, sizeof(c));
	for(i=0;i<s;i++)
	{
		scanf("%d %d", &x[i], &y[i]);
		c[x[i]][y[i]] = 1;
	}
	scanf("%d", &t);
	memset(a, 0, sizeof(a));
	
	for(i=1;i<=t;i++)
	{
		if(num < 6 && !c[0][0]){
			int mx = 4*xue+eps;
			mayi[num] = art(i, mx, sum/6+1, 0, 0);
			c[0][0] = 1;
			sum++, num++;
			if(sum%6 == 0)xue*=1.1;
		}
		//蚂蚁移动
		for(j=0;j<num;j++)
		{
			getdir(mayi[j], i-mayi[j].t+1);
			//判断能否拿蛋糕
			if(mayi[j].x == n && mayi[j].y == m && sig)
			{
				mayi[j].stu = 1;
				sig = 0;
				mayi[j].hp = min(mayi[j].hp+mayi[j].hpmax/2, mayi[j].hpmax);
			}
		}
		//塔台攻击
		for(j=0;j<s;j++)
			Attack(x[j], y[j], d, r);
		//清除死亡蚂蚁
		for(j=0;j<num;j++)
			if(mayi[j].hp <0){
				ArtDie(j);
				j--;
			}
		//判断蛋糕是否被运回窝
		for(j=0;j<num;j++)
			if(mayi[j].x == 0 && mayi[j].y == 0 && mayi[j].stu==1)
				ov = 1;
		if(ov)
		{
			printf("Game over after %d seconds\n", i);
			printf("%d\n", num);
			for(j=0;j<num;j++)
				printf("%d %d %d %d %d\n", i-mayi[j].t,
						mayi[j].exp, mayi[j].hp, mayi[j].x, mayi[j].y);
			break;
		}
		//更新信息素
		UpdInfo();
	}
	if(!ov)
	{
		printf("The game is going on\n");
		printf("%d\n", num);
		for(j=0;j<num;j++)
			printf("%d %d %d %d %d\n", t-mayi[j].t+1,
					mayi[j].exp, mayi[j].hp, mayi[j].x, mayi[j].y);
	}
	
	return 0;
}
//蚂蚁移动
void getdir(art &b, int t)
{
	int i, j = -1, nx, ny, mx = -1;
	//信息素更新
	if(b.stu == 1) a[b.x][b.y]+=5;
	else a[b.x][b.y] += 2;

	for(i=0;i<4;i++)
	{
		nx = b.x+dx[i], ny = b.y+dy[i];
		if(nx == b.upx && ny == b.upy)continue;
		if(internal(nx, ny) && a[nx][ny] > mx && c[nx][ny]==0)
		{
			mx = a[nx][ny];
			j = i;
		}
	}
	
	//规则4
	if(t % 5 == 0)
		for(i=1;i<=5;i++)
		{
			nx = b.x+dx[(j-i+4)%4], ny=b.y+dy[(j-i+4)%4];
			if(nx == b.upx && ny == b.upy)continue;
			if(internal(nx, ny) && c[nx][ny] == 0){
				j = (j-i+4)%4;break;
			}
		}
	if(j == -1){
		b.upx = b.x, b.upy = b.y;
		return ;
	}
	nx = b.x + dx[j], ny = b.y+dy[j];
	c[b.x][b.y] = 0, c[nx][ny] = 1;
	b.upx = b.x, b.upy = b.y;
	b.x = nx, b.y = ny;
}

bool internal(int x, int y)
{
	if(x>=0 && x<=n &&y>=0 && y<=m)return true;
	else return false;
}

//更新信息素
void UpdInfo()
{
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			if(a[i][j]>0)a[i][j]--;
}
//i号蚂蚁死亡
void ArtDie(int i)
{
	c[mayi[i].x][mayi[i].y] = 0;
	if(mayi[i].stu == 1)sig = 1;
	for(;i+1<num;i++)
		mayi[i] = mayi[i+1];
	num--;
}
//炮台攻击蚂蚁
void Attack(int x, int y, int d, int r)
{
	int i, j, k;
	LL mx = -1;
	//查找是否可以攻击背上有蛋糕的
	for(i=0;i<num;i++)
	{
		if(mayi[i].stu == 1 && dist(x,y,mayi[i].x, mayi[i].y) <= (LL)r*r)
			break;
	}
	if(i < num){
		mayi[i].hp -= d;
		j = i;
		for(i=0;i<num;i++)
		{
			if(i!=j && PointToLine(mayi[i].x, mayi[i].y,x,y,mayi[j].x,mayi[j].y)-0.5<=eps)
				mayi[i].hp -= d;
		}
		return;
	}
	//攻击能攻击到的最近的蚂蚁
	j = -1;
	for(i=0;i<num;i++)
	{
		LL dis = dist(x,y,mayi[i].x, mayi[i].y);
		if( dis <= (LL)r*r && (mx==-1 || dis < mx))
			mx = dis, j = i;
	}
	if(j == -1 || mx == -1LL)return;

	mayi[j].hp -= d;
}

int dist(int x1, int y1, int x2, int y2)
{
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
//判断点到直线距离。
double PointToLine(int x, int y, int a1, int b1, int a2, int b2)
{
	double mu = (a2-a1*1.0)*(a2-a1)+(b2-b1*1.0)*(b2-b1);
	double zi = (x-a1*1.0)*(a2-a1)+(y-b1*1.0)*(b2-b1);
	double t = zi / mu;
	double mx, my, result;
	if(t>=0 && t<=1)
	{
		mx = a1+(a2-a1)*t;
		my = b1+(b2-b1)*t;
		result = (x-mx)*(x-mx)+(y-my)*(y-my);
	}
	else
	{
		result = min((x-a1*1.0)*(x-a1*1.0)+(y-b1*1.0)*(y-b1), 
					(x-a2)*(x*1.0-a2)+(y-b2)*(y*1.0-b2));
	}
	return sqrt(result);
}