# 🔗
<a href="https://codeforces.com/gym/102900/problem/D"><img src="https://img-blog.csdnimg.cn/a8392a32b3be40949f3988e1d84496ac.png"></a>

# 💡
给定一条路，两个人的位置，两个人的速度，怎么样最快走完这条路  
  
如果考虑左左，左右，右左，右右这样会很麻烦，要根据速度还要考虑相遇点  
相遇最好，每个人都能做出贡献  
那么我们根据相遇入手  
  
首先要考虑一个人走完全程的情况  
然后是相遇点  
1.相遇完不扭头  
2.相遇完扭头  
  
相遇完不扭头很好计算，就直接对向走到头即可  
相遇完扭头我们可以二分一下 p1,p2 中间的相遇点  
对每个相遇点我们求一下两个人全部走完自己路程的最小用时  
其实有了相遇点这个就会很好求，就是每个人已经固定了要走的 l 和 r 了，在 l,r 内走需要 `(min(p-l,r-p)+(r-l))/v`  
所以在这里我们不需要考虑一个人左走还是右走，程序会用 `min` 判断  
  
我们二分一百次之后的中点就已经很确定了，每次维护一下花费时间的最小值即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
inline double LRTime ( double l, double r, double v, double p ) {
        return (min(p - l, r - p) + (r - l)) / v;
}

inline void Solve () {
        double n, p1, v1, p2, v2; 
        cin >> n >> p1 >> v1 >> p2 >> v2;

        if ( p1 > p2 ) swap(p1, p2), swap(v1, v2);

        double res = min(LRTime(0, n, v1, p1), LRTime(0, n, v2, p2));
        res = min(res, max((n - p1) / v1, p2 / v2));

        double l = p1, r = p2;
        for ( int i = 0; i < 100; i ++ ) {
                double mid = (l + r) / 2;
                double res1 = LRTime(0, mid, v1, p1);
                double res2 = LRTime(mid, n, v2, p2);

                res = min(res, max(res1, res2));
                if ( res1 > res2 ) r = mid;
                else l = mid;
        }

        printf("%.10f\n", res);
}

int main () {
        ios::sync_with_stdio(false);

        ll cass; cin >> cass; while ( cass -- ) {
                Solve();
        }
        
}
```
