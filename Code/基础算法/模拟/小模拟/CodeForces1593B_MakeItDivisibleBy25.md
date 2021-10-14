# 🔗
<a href="https://codeforces.com/contest/1593/problem/B"><img src="https://i.loli.net/2021/10/14/MlcQW16wzOqIeDh.png"></a>

# 💡
首先逆序一下好找  
可以确定的是每次找的都是两个字符  
且答案是最后一个字符的位置-1  
那么就写一个函数，找两个字符，找到第一个之后开始第二重循环找第二个，如果找到就返回j-1，否则就是返回inf  
  
对找四种字符`'0','0'`、`'5', '2'`、`'0', '5'`、`'5', '7'`进行比较  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
inline int find ( string s, char a, char b ) {
        for ( int i = 0; i < s.size(); i ++ ) {
                if ( s[i] == a ) {
                        for ( int j = i + 1; j < s.size(); j ++ ) {
                                if ( s[j] == b ) return j - 1;
                        }
                        return 0x3f3f3f3f; // 找到第一个a再找b找不到那就没办法了
                }
        }
        return 0x3f3f3f3f; // 连a也找不到
}

inline void Solve () {
        string s; cin >> s; reverse(s.begin(), s.end());
        cout << min ( min(find(s, '0', '0'), find(s, '5', '2')), min ( find(s, '0', '5'), find(s, '5', '7')) ) << endl;
}

int main () {
        ios::sync_with_stdio(false);
        int cass; cin >> cass; while ( cass -- ) {
                Solve ();
        }
        return 0;
}
```
