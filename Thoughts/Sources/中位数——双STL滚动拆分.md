# 中位数——双STL滚动拆分  

很多时候中位数是动态插数    
此时我们可以维护两个STL，这里以优先队列为例  
   
建立一个大顶堆1和一个小顶堆2  
两个队列的左右端点都很好访问  
可以以2的堆顶为中位数  
在滚动的时候就相当于把一个队列的堆顶扔给另一个队列的堆顶  
如果插入就看在哪个队列里面插入  
删除的话就是标记一下，在之后滚动的时候就直接滚出去就行了  
  
通过这种方式拆分整个数组可以更灵活地维护插入删除  

## 例题
<a href="https://acm.dingbacode.com/showproblem.php?pid=7072">HDU2021多校9(7)_Boring data structure problem</a>  

```cpp
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
