# 🔗
<a href="https://codeforces.com/problemset/problem/1536/B"><img src="https://img-blog.csdnimg.cn/20210410211951223.png"></a>

# 💡
我们从上向下取数，最多能取的个数取决于：我们需要多少个跟第k个数相等的数ned、跟第k个数相等的数的个数num。  
这两个得到还是比较容易的，就考验了写码的严谨性，而这个个数明显是组合数，值为(num!) / (ned!) / ((num-ned)!)并取模  
解组合数有两种方式：  
1.杨辉三角递推法（1000*1000）的时间复杂度  
2.在结果上做运算：**求逆元**  

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
const ll mod = 1e9 + 7;
int cass;
ll n, k;

ll qpow(ll a,ll b){//ksm
    ll ans = 1;
    while(b){
        if(b&1)
            ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans%mod;
}

ll Inv(ll a,ll p){//逆元
    return qpow(a, p - 2);
}

void solve(){
    vector<ll> vec;
    cin >> n >> k;
    for (int i = 0,x; i < n; i++){
        cin >> x;
        vec.push_back(x);
    }
    sort(vec.begin(), vec.end(), greater<ll>());//合并出最大数，就要降序int cur = k;
    map<int, ll> mp;//mp[i]表i的出现次数
    for (int i = 0; i < vec.size(); i++)
    {
        if(mp[vec[i]]==0)
            mp[vec[i]] = 1;
        else
            mp[vec[i]]++;
    }
    k--;//我们从0开始存的，第k个的下标为k-1
    ll num = mp[vec[k]];//第k个数有多少个
    ll ned = 0;//我们需要多少个第k个数
    for (int i = k; i >= 0; i--){
        if(i==0||vec[i]!=vec[i-1]){
            ned = k - i + 1;
            break;
        }
    }

    //前面的小坑结束了，开始组合数取模
    ll on = 1;//分子
    for (int i = ned + 1; i <= num; i++)
        on = on * i % mod;
    ll dn = 1;//分母
    for (int i = 1; i <= num - ned; i++)
        dn = dn * i % mod;
    cout << on * Inv(dn, mod) % mod << endl;
}

int main()
{
    each_cass(cass){
        solve();
    }
    return 0;
}
```
