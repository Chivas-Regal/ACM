# 🔗
<a href="https://codeforces.com/contest/1611/problem/C"><img src="https://i.loli.net/2021/11/26/piMymS25GXldJUF.png"></a>

# 💡
a按几乎固定顺序得到b  
给定b求a  
反着求结果，那么就可以反着模拟  
  
这道题的多变就只在于最后一个元素应该放在哪  
反着模拟就是每次挑出最大的  
然后由于最后一步的变化可以得到两种情况（放左边和放右边）    
看看这两种情况能否推出来a  

如果两种都推不出来就肯定是-1  
否则的话哪种能推出来就输出哪个  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
inline bool same ( deque<int> a, deque<int> b ) { // 两个队列一样
        while ( a.size() ) {
                if ( a.back() != b.back() ) return false;
                a.pop_back(); b.pop_back();
        }
        return true;
}
 
inline bool Check ( deque<int> a, deque<int> b ) { // 看看a能否正着推出b
        deque<int> crt1, crt2;
        while ( a.size() > 1 ) {
                if ( a.front() < a.back() ) {
                        crt1.push_front(a.front());
                        crt2.push_front(a.front());
                        a.pop_front();
                } else {
                        crt1.push_back(a.back());
                        crt2.push_back(a.back());
                        a.pop_back();
                }
        }
        crt1.push_back(a.back());
        crt2.push_front(a.back());
        if ( same(crt1, b) || same(crt2, b) ) return true;
        return false;
}
 
inline void Solve () {
        int n; cin >> n;
        deque<int> dq, tmp;
        for ( int i = 0, x; i < n; i ++ ) cin >> x, dq.push_back(x), tmp.push_back(x);
        deque<int> crt1, crt2; // b反推a的两种情况
        while ( dq.size() > 1 ) {
                if ( dq.front() > dq.back() ) {
                        crt1.push_front(dq.front());
                        crt2.push_front(dq.front());
                        dq.pop_front();
                } else {
                        crt1.push_back(dq.back());
                        crt2.push_back(dq.back());
                        dq.pop_back();
                }
        }
        crt1.push_back(dq.back());
        crt2.push_front(dq.back());
        // 看看有没有可以转化成tmp
        if ( Check(crt1, tmp) ) {
                while ( crt1.size() ) cout << crt1.front() << " ", crt1.pop_front();
        } else if ( Check(crt2, tmp) ) {
                while ( crt2.size() ) cout << crt2.front() << " ", crt2.pop_front();
        } else cout << -1;
        cout << endl;
}
 
int main () {
        ios::sync_with_stdio(false);
        int cass; cin >> cass; while ( cass -- ) {
                Solve ();
        }
}
```
