# 🔗
<a href="https://codeforces.com/gym/102163/problem/M"><img src="https://s2.loli.net/2022/01/06/5bLgHVQwi2m7Pry.png"></a>

# 💡
原题来看是需要计算两个指数符  
这个本身是不难的，但是我们对于  <img src="https://latex.codecogs.com/svg.image?\inline&space;1000000^{1000000}" title="\inline 1000000^{1000000}" /> 这么大的数显然是存不下的  
就算存下了，在乘和比较的时候又会要很慢  
我们可以贪一下，如果这个指数符变成加号或者乘号将会非常方便  
想一下  <img src="https://latex.codecogs.com/svg.image?\inline&space;log" title="\inline log" /> 的性质，如果前面加一个指数的相反符也就是  <img src="https://latex.codecogs.com/svg.image?\inline&space;log" title="\inline log" /> ，那么指数就可以提到前面做乘法了  
问题转化：<img src="https://latex.codecogs.com/svg.image?\inline&space;a^b?c^d\rightarrow&space;blog_{10}a?dlog_{10}d?" title="\inline " />    

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
inline void Solve () {
        int b1, p1, b2, p2; cin >> b1 >> p1 >> b2 >> p2;
        double res1 = (double)p1 * log10(b1);
        double res2 = (double)p2 * log10(b2);

        if ( b1 == 0 && b2 == 0 ) cout << "Lazy" << endl;
        else if ( fabs(res1 - res2) < 1e-8 ) cout << "Lazy" << endl;
        else if ( res1 - res2 < -1e-8 ) cout << "Congrats" << endl;
        else cout << "HaHa" << endl;
}

int main () {
        int cass; scanf("%d", &cass); while ( cass -- ) {
                Solve ();
        }
}
```
