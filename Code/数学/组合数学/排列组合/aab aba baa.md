# 🔗
<a href="https://atcoder.jp/contests/abc202/tasks/abc202_d?lang=en"><img src="https://img-blog.csdnimg.cn/20210526235513656.png"></a>

# 💡
拿到这道题  
刚开始我其实是想转化为二进制看变化的  
因为如果把'a'视作1，'b'视作0，每次向后推一个字典序其实就是减去一个数  
但是有很多处理地方不知道怎么办  
放弃了，虽然不对，但不得不说确实是一种好的思维拓展方向  
  
正解来了：  
操作数过大的时候我们考虑跳步  
分析字典序性质  
发现每个位置都有两种存放方式：  
要么存a要么存b  
这取决于k的剩余值  
  
  
这个位置放a是对k没有影响的  
因为k是寻找第几个字典序最小的  
  
而放b的话我们要知道我们跳了几步也就是减了多少个k  
确定方式是假设这里放a（比放b小1）我们后面能构造出的字符串数量  
一想这不是组合数吗？  
我们想在剩下的（a + b - 1）个位置随意放置（a - 1）个'a'  
所以跳的步数是C(a + b - 1, a - 1)  
  
流程：
在k>1时（因为我们字典序从头开始找的，所以要少用一个k）：  
	如果k > C(a + b - 1, a - 1)，那么这一步是可以放'b'来跳步的  
	否则，不能跳步，老老实实放'a'吧  
在最后，我们构造出后面没有构造的最小字符串：先放完a，再放完b  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
ll c[65][35];

inline void get_C(){//杨辉三角构建组合数
        for(int i = 0; i < 65; i ++) c[i][0] = 1;
        for(int i = 0; i < 65; i ++){
                for(int j = 1; j <= i && j < 35; j ++){
                        c[i][j] = c[i - 1][j] + c[i - 1][j - 1];
                }
        }
}


inline void solve(){get_C();
        _ll(a); _ll(b); _ll(k);
        string res;
        while(k > 1){
                if(k > c[b + a - 1][a - 1]){ k -= c[b + a - 1][a - 1]; //可以跳步
                        b --; //放了'b'，b的数量就减1
                        res += "b";
                }else{
                        a --;//放了'a'，a的数量就减1
                        res += "a";
                }
        }
        for(int i = 0; i < a; i ++) res += "a";
        for(int i = 0; i < b; i ++) res += "b";
        cout << res << endl;
}

CHIVAS{
        solve();
        _REGAL;
}
```
