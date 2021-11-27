# 🔗
https://codeforces.com/contest/1365/problem/F

# 💡
我们在交换数的时候，可以联想到魔方的小技巧：如何让别的点不变的情况下，只有一个点会变？  
那么这题是交换，我们研究一个例子：  
1 2 3 4 (交换a[1], a[4])  
4 2 3 1 (交换a[1 ～ 2], a[3 ～ 4])  
3 1 4 2 (交换a[1], a[4])  
2 1 4 3  
    
于是得到结论：  
以数组中间为轴  
每一个“对称数对”都能移动到同样对称的任何位置  
比如  
1 _ _ _ _ 2  
可以移动到   
_ 1 _ _ 2 _  
_ _ 1 2 _ _   
也可以交换位置  
2 _ _ _ _ 1  
_ 2 _ _ 1 _  
_ _ 2 1 _ _  
  
所以我们先判断两个数组是否可以相同
对两个数组sort一下，判断sort的结果是否相同，如果不相同就是No
然后是对n为奇数时的a和b的中心位置（因为这个位置无法移动），如果不相同就是No
然后就是在a中存“对称数对”了
接着在b中匹配就行了

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

const int N = 550;
int a[N], b[N];
int n; 

inline bool Check_Similar () { // 检查两个数组是否元素相同
        int aa[N]; for ( int i = 0; i < n; i ++ ) aa[i] = a[i]; // 复制a数组
        int bb[N]; for ( int i = 0; i < n; i ++ ) bb[i] = b[i]; // 复制b数组
        sort ( aa, aa + n ); sort ( bb, bb + n );               // 排序一下
        for ( int i = 0; i < n; i ++ ) if ( aa[i] != bb[i] ) return false; // 如果有一位不等就不一样
        return true;
}

inline void Solve () {
        cin >> n;
        for ( int i = 0; i < n; i ++ ) cin >> a[i];
        for ( int i = 0; i < n; i ++ ) cin >> b[i];

        if ( !Check_Similar() ) {
                puts("no");
                return;
        }

        map<pair<int, int>, int> mark;
        for ( int i = 0; i < n / 2; i ++ ) mark[{ a[i], a[n - i - 1] }] ++; // 对每一对排序
        for ( int i = 0; i < n / 2; i ++ ) 
                if ( !mark[{ b[i], b[n - i - 1] }] && !mark[{ b[n - i - 1], b[i] }] ) { // 如果没有
                        puts("no");
                        return;
                } else if ( mark[{ b[i], b[n - i - 1] }] ) { // 有了就删去一个
                        mark[{ b[i], b[n - i - 1] }] --; 
                } else {
                        mark[{ b[n - i - 1], b[i] }] --;
                }
        puts("yes");
}

int main () {
        int cass;
        for ( cin >> cass; cass; cass -- ) {
                Solve ();
        }
}
```
