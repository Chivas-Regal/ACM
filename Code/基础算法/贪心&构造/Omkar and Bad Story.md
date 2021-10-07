# 🔗
<a href="https://codeforces.com/problemset/problem/1536/A"><img src="https://img-blog.csdnimg.cn/20210607110944101.png"><br /><img src="https://img-blog.csdnimg.cn/20210607110950427.png"></a>

# 💡
数据的迷惑性挺强的  
稍微看出来点就以为是让GCD出差值然后进行等差数列的构造  
但是数据范围只有-100 ~ 100而且如果出现负数就肯定不能用（越添加，差值越大，无法满足）  
所以我们就直接构造一个0 ~ 100的差为1的等差数列就行了  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
inline void solve(){
        _int(n); _vectorInt(a, n);
        sort(ALL(a));
        if(a[0] < 0) cout << "NO" << endl;//最小的数为负数
        else{
                cout << "YES" << endl << 101 << endl;//构造
                for(int i = 0; i <= 100; i ++) cout << i << " ";
                cout << endl;
        }
}

CHIVAS_{
        int cass;
        EACH_CASE(cass){
                solve();
        }
        _REGAL;
}
```
