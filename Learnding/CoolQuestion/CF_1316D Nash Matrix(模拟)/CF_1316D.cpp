/****************************************************************************
模拟

一个n*n大小的地图，地图的每个位置可以是'U','R','L','D'，分别可以移动至相邻的上、右、左、下
的位置，不能移动出地图边界；位置上也可能是'X'，代表障碍，移动至这个空间将不能再移动。从某个
位置开始，要么他会按照地图移动，直到移动至'X'不再移动，或者一直移动，不会停下。输入会给出
n*n个点的每个点的信息，如果为(x,y)则代表从该点开始移动，会停留在(x,y)，或(-1,-1)代表从该点
开始移动，会一直保持移动。求是否存在合理的地图。

思路：模拟。先考虑能停下的部分，首先需要保证停留点是不冲突，如(x1,y1)停留在(x2,y2),而(x2,y2)
停留在(x1,y1)这种不合理情况。直接从终点开始搜索，如果能到达终点，则继续搜索。然后需要判断是否
所有的终点为(x,y)的都被搜索到，如果不能，则不合理。
对于死循环的情况，则一直让他往旁边死循环的地方移动即可。如果其四个方向都没有(-1,-1)，则不合理。

题目链接：http://codeforces.com/contest/1316/problem/D
*************************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<ctype.h>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
#define dbg(x) cout<<#x<<" = "<<x<<endl;
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define eps 1e-6
 
using namespace std;
typedef long long LL;   
typedef pair<int, int> P;
const int maxn = 1020;
const int mod = 1000000007;
struct node{
    int x, y;
}p[maxn][maxn];
int n;
int dx[4]={-1,0,1,0}, dy[4]={0,-1,0,1};
char str[maxn][maxn];
bool internal(int x, int y);
void dfs(int x, int y, int kx, int ky, char ch);
 
int main()
{
    int i, j, k, sig = 1;
    scanf("%d", &n);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            scanf("%d %d", &p[i][j].x, &p[i][j].y);
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(p[i][j].x != -1){
                if(str[p[i][j].x][p[i][j].y] != 'X' && str[p[i][j].x][p[i][j].y] != 0)sig = 0;
                else dfs(p[i][j].x, p[i][j].y, p[i][j].x, p[i][j].y, 'X');
            }
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(p[i][j].x != -1 && str[i][j] == 0)
                sig = 0;
            else if(str[i][j] == 'X' && (p[i][j].x != i || p[i][j].y != j))
                sig = 0;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(p[i][j].x == -1)
            {
                for(k=0;k<4;k++)
                {
                    int nx = i+dx[k], ny = j+dy[k];
                    if(internal(nx, ny) && p[nx][ny].x == -1)
                    {
                        if(k == 0)str[i][j]='U';
                        else if(k == 1)str[i][j]='L';
                        else if(k == 2)str[i][j]='D';
                        else if(k == 3)str[i][j]='R';
                        break;
                    }
                }
                if(k == 4)sig = 0;
            }
    if(sig)
    {
        printf("VALID\n");
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
                printf("%c", str[i][j]);
            printf("\n");
        }
    }
    else 
        printf("INVALID\n");
    return 0;
}
 
void dfs(int x, int y, int kx, int ky, char ch)
{
    if(str[x][y] != 0)return ;
    str[x][y] = ch;
    for(int i=0;i<4;i++)
    {
        int nx = x + dx[i], ny = y+dy[i];
        if(internal(nx, ny) && p[nx][ny].x != -1 && p[nx][ny].x == kx && p[nx][ny].y == ky)
        {
            char ch1;
            if(i == 0)ch1 = 'D';
            else if(i == 1)ch1 = 'R';
            else if(i == 2)ch1 = 'U';
            else if(i == 3)ch1 = 'L';
            dfs(nx, ny, kx, ky, ch1);
        }
    }
}
 
bool internal(int x, int y)
{
    if(x >= 1 && x<=n && y>=1 && y<=n)return 1;
    else return 0;
}