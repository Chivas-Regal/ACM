# 🔗
<a href="https://acm.dingbacode.com/showproblem.php?pid=7072"> <img src="https://i.loli.net/2021/10/19/q7gbzUHfi8pKL6C.png"></a>

# 💡
左侧右侧进数求中位数很好操作，无非就是整个迭代器或者指针进行偏移罢了  
但是带上个删除操作，就很难保证了  
想到标记一下删除掉的数，偏移的时候如果删了就继续偏移，但是时间复杂度又该很高了（中间删除一大段然后左右横跳（雾  
  
如果能边偏移边删除就好了  
想到有两个优先队列固定值中位数的方法  
这里设两个deque来滚动拆分整个数列为两半  
让右队列的左端点表示中位数  
  
加上或删除一个数顶多也就偏移一个  
偏移的时候如果删过的就舍弃然后继续进行偏移操作嘛  
当然这里两个队列的size并不是真实的size（还有删掉的没计数呢  
我们就手写两个计数器size就行了  
然后删掉的标记一下，每一个数属于左队列还是右队列也标记一下  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <deque>

using namespace std;

#define ll long long
const int N = 1e7 + 10;

deque<int> dql, dqr; 
int szl, szr; // 左size，右size
int where[N]; // 1: lft, 2:rgt
bool isdel[N]; // 是否删掉了
int n;

inline void Init () {
        for ( int i = 0; i <= n; i ++ ) isdel[i] = where[i] = 0;
        dql.clear(), dqr.clear();
        szl = szr = 0;
}

inline void Roll () { // 滚动维护
        while ( szr > szl + 1 ) {
                if ( isdel[dqr.front()] ) { dqr.pop_front(); continue; }
                where[dqr.front()] = 1;
                dql.push_back(dqr.front()); dqr.pop_front();
                szl ++; szr --;
        }
        while ( szl > szr ) {
                if ( isdel[dql.back()] ) { dql.pop_back(); continue; }
                where[dql.back()] = 2;
                dqr.push_front(dql.back()); dql.pop_back();
                szr ++; szl --;
        }
}

inline void Solve () {
        Init();
        for ( int k = 1, i = 1; k <= n; k ++ ) {
                char op; getchar(); scanf("%c", &op); 
                if ( op == 'L' ) {
                        dql.push_front(i); szl ++; where[i] = 1;
                        Roll();
                        i ++;
                } else if ( op == 'R' ) {
                        dqr.push_back(i); szr ++; where[i] = 2;
                        Roll();
                        i ++;
                } else if ( op == 'Q' ) {
                        while ( isdel[dqr.front()] ) dqr.pop_front();
                        printf("%d\n", dqr.front());
                } else {
                        int x; scanf("%d", &x);
                        isdel[x] = 1;
                        if ( where[x] == 1 )      szl --;
                        else if ( where[x] == 2 ) szr --;
                        Roll();
                }
        }
}

int main () {
        while(scanf("%d", &n) == 1 ){
                Solve();
        }
}
```
