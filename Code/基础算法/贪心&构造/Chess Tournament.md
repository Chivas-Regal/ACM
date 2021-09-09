# 🔗
<a href="https://codeforces.com/problemset/problem/1569/B"><img src="https://i.loli.net/2021/09/09/QUIEeWldDP6YM3f.png"></a>

# 💡
一道比较细节的贪心构造题  
首先有两种人  
1号因为不输，我们也不想影响到与他比赛的所有1号，所以直接构造成平局即可  
2号因为有赢，所以他在赢了一场之后都要把没比的设置为输，这样可以为其他的2号提供贡献  
在构造的过程中进行判断"NO"，即1号有输，2号出不来赢  
其次就是对细节的把控即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <vector>
#include <cstring>
#include <list>
using namespace std;
#define ll long long

const int N = 100;
char res[N][N]; // 答案图
int won[N]; // 第i个人赢过没

inline void solve () {
        int n; cin >> n;
        string s; cin >> s;
        memset(won, 0, sizeof won);
        memset(res, 0, sizeof res);

        for ( int i = 0; i < n; i ++ ) {
                if ( s[i] == '2' ) { // 有赢：贪法--赢过之后一直输
                        for ( int j = 0; j < n; j ++ ) {
                                if ( i == j || res[i][j] )  continue;
                                if ( s[j] == '1' ) //  有赢vs不输
                                        res[i][j] = '=', // 贪一下，这类也不让那个不输的赢，让平局
                                        res[j][i] = '=';
                                else { // 有赢vs有赢
                                        if ( !won[i] ) // 如果i没赢过，那么这把赶紧让他赢了
                                                res[i][j] = '+',
                                                res[j][i] = '-',
                                                won[i] = 1;
                                        else            // 如果赢过了，就可以贪心地后面的全让他输
                                                res[i][j] = '-',
                                                res[j][i] = '+',
                                                won[j] = 1;
                                }
                        }
                        if ( !won[i] ) { // 没赢过肯定不行
                                cout << "NO" << endl;
                                return ;
                        }
                } else { // 不输：贪法--都平局
                        for ( int j = 0; j < n; j ++ ) {  
                                if ( res[i][j] == '-' ) { // 输了肯定不行
                                        cout << "NO" << endl;
                                        return;
                                }
                                if ( i == j || res[i][j] ) continue;
                                res[i][j] = '=',
                                res[j][i] = '=';
                        }
                }
        }
        cout << "YES" << endl;
        for ( int i = 0; i < n; i ++ ) {
                for ( int j = 0; j < n; j ++ ) {
                        if ( i == j ) cout << "X";
                        else          cout << res[i][j];
                }cout << endl;
        }
}

int main () {
#ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
#endif
        int cass;
        cin >> cass;
        while ( cass -- ) {
                solve();
        }
}
```
