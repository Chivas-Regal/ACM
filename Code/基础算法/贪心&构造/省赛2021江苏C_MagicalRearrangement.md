# 🔗
<a href="https://codeforces.com/gym/103495/problem/C"><img src="https://s2.loli.net/2022/01/08/CZuNVcvkGoeqSAW.png"></a>

# 💡
这种按字典序选数的策略：从前往后构造，对于这一位，从可以保证能顺利构造的字符中选取最小的字符  
保证顺利构造：  
在选中的字符的数量  <img src="https://latex.codecogs.com/svg.image?\inline&space;-1" title="\inline -1" /> 的情况下，设出现数量最多的字符为  <img src="https://latex.codecogs.com/svg.image?\inline&space;c" title="\inline maxc" /> ，数量为  <img src="https://latex.codecogs.com/svg.image?\inline&space;v" title="\inline maxv" /> ，总数量为  <img src="https://latex.codecogs.com/svg.image?\inline&space;cnt" title="\inline cnt" />  
如果最多的是当前选中的字符，满足要求要保证  <img src="https://latex.codecogs.com/svg.image?\inline&space;v\times2\le&space;cnt" title="\inline maxv\times2\le&space;cnt" /> 即  <img src="https://latex.codecogs.com/svg.image?\inline&space;...\_c\_c\_c....\_c" title="\inline \_c\_c\_c....\_c" /> 这样  
如果最多的不是选中的字符，满足要求要保证  <img src="https://latex.codecogs.com/svg.image?\inline&space;v\times2\le&space;cnt+1" title="\inline v\times2\le&space;cnt+1" /> ，即  <img src="https://latex.codecogs.com/svg.image?\inline&space;...c\_c\_c...\_c" title="\inline ...c\_c\_c...\_c" /> 这样  
>这里有个小技巧，就是如果  <img src="https://latex.codecogs.com/svg.image?\inline&space;c" title="\inline c" /> 和当前选中的字符一样，我们可以看看有没有数量一样多的但是不是  <img src="https://latex.codecogs.com/svg.image?\inline&space;c" title="\inline c" /> 的，这样就能满足更多情况了  

对于每一位，我们都从可以选择的数里面扫一下，最小的也就是第一个扫到的就让他做这一位的字符，就能保证字典序最小了  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
vector<pair<char, int> > vec; // 可选字符集
int cnt; // 剩余字符数量

inline bool check (char c) {
        pair<char, int> mx = {0, 0};
        for ( int i = 0; i < vec.size(); i ++ ) {
                char a = vec[i].first; int b = vec[i].second;
                if ( a == c ) b --;
                if ( b > mx.second ) mx = {a, b};
        }

        int tmpcnt = cnt; tmpcnt --;
        
        if ( mx.first == c ) { // 看看有没有数量一样的但不是 c 的
                for ( int i = 0; i < vec.size(); i ++ ) {
                        char a = vec[i].first; int b = vec[i].second;
                        if ( a == c ) b --;
                        if ( a != mx.first && b == mx.second ) {
                                mx = vec[i];
                                break;
                        }
                }
        }

        if ( mx.first == c ) {
                if ( mx.second * 2 > tmpcnt ) return false;
        } else {
                if ( mx.second * 2 > tmpcnt + 1 ) return false;
        }
        return true;
}

inline void Solve () {
        vec.clear(); cnt = 0;
        for ( int i = 0; i < 10; i ++ ) {
                int x; cin >> x;
                if ( x ) vec.push_back({i + '0', x});
                cnt += x;
        }
        if ( cnt == 1 && vec[0].first == '0' ) { // 特判是不是只有一个 0
                cout << "0" << endl;
                return;
        }
        string res;
        while ( vec.size() ) {
                bool flag = false;
                for ( int i = 0; i < vec.size(); i ++ ) {
                        if ( !res.size() && vec[i].first == '0' ) continue; // 第一位不能为0
                        if ( res.size() && res.back() == vec[i].first ) continue; // 不能和上一个一样
                        if ( check(vec[i].first) ) {
                                res += vec[i].first;
                                cnt --;
                                vec[i].second --;
                                if ( vec[i].second == 0 ) vec.erase(vec.begin() + i, vec.begin() + i + 1);
                                flag = true;
                                break;
                        }
                }
                if ( !flag ) {
                        cout << "-1" << endl;
                        return;
                }
        }
        if ( !res.size() ) cout << "-1" << endl;
        else cout << res << endl;
}

int main () {
        ios::sync_with_stdio(false);
        int cass; cin >> cass; while ( cass -- ) {
                Solve ();
        }
}
```
