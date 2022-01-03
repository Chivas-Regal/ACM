# 🔗
<a href="https://codeforces.com/gym/102900/problem/G"><img src="https://img-blog.csdnimg.cn/cfad2ab416f3422e86ca29dcbcd0cc6b.png"></a>

# 💡
fibonacci数列每第三个数一定是偶数  
那么 `n/3` 求一下偶数的个数 `eve` 
偶数和所有数相乘都是偶数 `res = eve * n` 但是不能和自己组合 `res -= eve`  
偶数内部两两组合也多加了一次，要减去 `res -= eve * (eve - 1) / 2`  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
int main () {
        ios::sync_with_stdio(false);

        ll n; cin >> n;
        ll eve = n / 3;
        ll res = eve * n - eve;
        res -= eve * (eve - 1) / 2;
        cout << res << endl;
}
```
