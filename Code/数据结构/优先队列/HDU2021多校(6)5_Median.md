# 🔗
<a href="https://acm.dingbacode.com/showproblem.php?pid=7029"><img src="https://i.loli.net/2021/10/14/UH6BGfpAF25b8NI.png"></a>

# 💡
首先可以想到由于每一块都是子序列  
所以顺序不必要  
每一个数都可以选取比它大的不做中位数的数的数量最多比比它小的不做中位数的数的数量多一个，至少两边相等   
那么首先是两个数两个数匹配给他们中间的一个中位数保持稳定  
那么在剩下一些数时，这一些数最多可以每一个分配一个给比他们小的中位数  
因为这些中位数右侧数的个数可以+1  
  
那么这就是一个对项相消的问题  
我们把每一个不做中位数的连续的数的数量提出  
>比如：n=5，选取3、5做中位数，那么就是剩下[1,2],[4]这两个块  
对这些块进行对项相消，贪心地让每一个块都尽量用完  
那么可以用优先队列每次消我们定义关系中大的那两个进行消除，套一个结构体两个元素分别表示这个块的数个数和这个块前面有几个中位数  
*我们定义的关系是：如果这个块前面的每个中位数都吃掉这个块内的一个元素，剩下的个数进行比较*  
  
每次优先队列提出两个块消一下，如果还有数就塞回去  
最后看一下剩下的那个块能不能被前面的中位数吃完  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
struct node { int val, op; /*个数，前面有几个中位数*/inline friend bool operator < (node a, node b) { return a.val - a.op < b.val - b.op; } };

const int N = 1e5 + 10;
int a[N], n, m;

inline void Solve () {
        scanf("%d%d", &n, &m);
        priority_queue<node> pque;
        for ( int i = 0; i < m; i ++ ) cin >> a[i];
        sort ( a, a + m );
        for ( int i = 0; i < m; i ++ ) {
                if ( i == 0     && a[i] > 1 )   pque.push({a[i] - 1, 0});
                if ( i == m - 1 && a[i] < n )   pque.push({n - a[i], m});
                if ( i && a[i] > a[i - 1] + 1 ) pque.push({a[i] - a[i - 1] - 1, i});
        }
        while ( pque.size() >= 2 ) {
                node fir = pque.top(); pque.pop();
                node sec = pque.top(); pque.pop();
                fir.val --; sec.val --;
                if ( fir.val ) pque.push(fir);
                if ( sec.val ) pque.push(sec);
        } 
        if ( !pque.size() ) puts("YES");
        else {
                node x = pque.top();
                if ( x.val - x.op > 0 ) puts("NO");
                else                    puts("YES");
        }
}

int main () {
        int cass; scanf("%d", &cass); while ( cass -- ) {
                Solve();
        }
}
```
