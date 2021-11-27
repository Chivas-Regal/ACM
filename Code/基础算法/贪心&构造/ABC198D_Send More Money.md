# 🔗
https://atcoder.jp/contests/abc198/tasks/abc198_d

# 💡
因为最多只有十个字符，所以在全排列之后有最多3628800种可能性，时间还可以  
所以可以直接开全排列对这些不超过十个字符一一映射一下搜索一下即可  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

#define ll long long

using namespace std;

vector<char> Char; // 存三个字符串中出现过的字符
vector<ll> Num;    // 存0～9十个数
map<char, bool> vis; // 去重
map<char, int> chg;  // 存当前排列每个字符代表什么
string s[3];

inline void Init () {
        for ( int i = 0; i < 3; i ++ ) for ( int j = 0; j < s[i].size(); j ++ ) if ( !vis[s[i][j]] ) 
                Char.push_back(s[i][j]), vis[s[i][j]] = 1;
        if ( Char.size() > 10 ) { // 超过十个数直接无解
                puts("UNSOLVABLE"); exit(0);
        }
        for ( int i = 0; i < 10; i ++ ) Num.push_back(i);
}
inline ll get ( string s ) { // 获取在当前排列下，字符串s的意思是什么
        ll res = 0;
        for ( int i = 0; i < s.size(); i ++ ) {
                res = res * 10 + chg[s[i]];
        } return res;
}

int main () {

        cin >> s[0] >> s[1] >> s[2]; Init();
        do {
                chg.clear();
                for ( int i = 0; i < Char.size(); i ++ ) chg[Char[i]] = Num[i]; // 当前排列和这些字符对应起来
                if ( !chg[s[0][0]] || !chg[s[1][0]] || !chg[s[2][0]]) continue; // 不含前导零

                ll res0 = get(s[0]), res1 = get(s[1]), res2 = get(s[2]);
                if ( res0 + res1 == res2 ) cout << res0 << endl << res1 << endl << res2, exit(0);
        } while ( next_permutation(Num.begin(), Num.end()) );
        puts("UNSOLVABLE"); // 全排列后还无解就是无解了

}
```
