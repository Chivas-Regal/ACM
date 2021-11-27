# 🔗
https://codeforces.com/problemset/problem/1517/C

# 💡
既想构造满，又想连通  
那么绝对不能有一个编号在前面还没构造完时把它封闭起来  
如果我们从左上向右下遍历，那么左上是最容易确定的，只需要贴着边向下即可  
而我们后面的编号都不能很直接地向下走，那样会封住  
所以我们要贴着前面构造过的单元格继续构造  
  
总结一下就是：每个编号默认向左构造，如果左边已经有编号了就向下构造一次，然后继续判断左侧是否构造过  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>

using namespace std;

const int  N = 510;
int a[N]; // 按顺序输入的编号
int res[N][N]; // 输出的答案矩阵

int main() {
        int n; cin >> n;
        for ( int i = 1; i <= n; i ++ ) cin >> a[i]; 
        // 做个边界防止越界
        for ( int i = 1; i <= n; i ++ ) res[n + 1][i] = 1; 
        for ( int i = 1; i <= n; i ++ ) res[i][0] = 1; 

        for ( int k = 1; k <= n; k ++ ) {
                int cnt = a[k], j = k, i = k; // cnt表示还需要摆放的数量，(i, j)
                while ( cnt -- ) {
                        res[i][j] = a[k];
                        if ( !res[i][j - 1] ) j --; // 默认向左走
                        else                  i ++; // 如果被占了就向下走
                }
        }

        for ( int i = 1; i <= n; i ++ ) {
                for ( int j = 1; j <= i; j ++ ) 
                        cout << res[i][j] << " "; 
                cout << endl;
        }

        return 0;
}
```
