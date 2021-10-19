# 🔗
<a href="https://acm.dingbacode.com/showproblem.php?pid=7068"><img src="https://i.loli.net/2021/10/19/JXRs2VKy6dkZmQN.png"></a>

# 💡
其实可以看作是一类分配问题  
比如第i个人想获取最低的名次，意味着分数要超过他的人需要很多  
那么一个人如果选取最小的锦标赛排名分就比第i个要大了话，他去取最大的锦标赛排名分就会造成很多浪费  
所以在这种情况下每个人要去取刚好超过第i个人的锦标赛排名分  
  
那么我们可以贪心地去遍历  
设置一个下标指针表示当前锦标赛排名分  
对于a按值从大到小遍历，b从小到大遍历（逆序    
如果当前的a[j]+b[id]<=a[i]+b[n]就让id--  
直到满足>了就停下来，如果id还可以选，那就答案++  
这样选的话可以保证每个人对加上后大于a[i]+b[n]的每个分数都充分利用了  
如果当前的a[j]选比b[id]大的只有过大于a[i]+b[n]导致浪费的情况  
如果让比b[id]小的去选，不仅会导致a[i]没法用它大于a[i]+b[n]，还可能导致剩下的id选不完  
  
如果要排名更靠前  
那么整体反转一下即可  
但要注意这时我们求的是比a[i]+b[1]小于等于的个数，最后答案是n-cnt+1  
# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const int N = 5e3 + 10;
struct node {
        int id, val;
}a[N];
int b[N];
pair<int, int> res[N];
int n;

inline void Solve () {
        cin >> n;
        for ( int i = 1; i <= n; i ++ ) 
                cin >> a[i].val,
                a[i].id = i;
        for ( int i = 1; i <= n; i ++ )
                cin >> b[i];
        sort ( a + 1, a + 1 + n, [&](node a, node b){
                return a.val < b.val;
        });
        for ( int i = 1; i <= n; i ++ ) {
                int cnt, cur;
                cnt = 0, cur = a[i].val + b[1];
                for ( int j = 1, idb = 2; j <= n && idb <= n; j ++ ) {
                        if ( j == i ) continue;
                        while ( a[j].val + b[idb] > cur && idb <= n ) idb ++;
                        if ( idb <= n ) cnt ++;
                        else break;
                        idb ++;
                }
                res[a[i].id].first = n - cnt - 1;
                cnt = 0, cur = a[i].val + b[n];
                for ( int j = n, idb = n - 1; j >= 1 && idb; j -- ) {
                        if ( j == i ) continue;
                        while ( a[j].val + b[idb] <= cur && idb ) idb --;
                        if ( idb ) cnt ++;
                        else break;
                        idb --;
                }
                res[a[i].id].second = cnt;
        }
        for ( int i = 1; i <= n; i ++ ) cout << res[i].first + 1 << " " << res[i].second + 1 << endl;
}

int main () {
        ios::sync_with_stdio(false);
        int cass; cin >> cass; while ( cass -- ) {
                Solve ();
        }
}
```
