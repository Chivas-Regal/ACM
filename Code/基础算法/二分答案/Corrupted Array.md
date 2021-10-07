# 🔗
<a href="https://codeforces.com/problemset/problem/1512/D在b排列中我们想舍弃一个数，然后将排列的前n个数的和等于第n+1个数，我们只需要求出整个b排列的sum，然后去寻找sum减去哪个数再/2可以在其中找到（而且不能是当前减去的那个数），删去的那个数为x，找到的那个数为b[n+1]"><img src="https://img-blog.csdnimg.cn/20210411083143257.png"></a>

# 💡
在b排列中我们想舍弃一个数，然后将排列的前n个数的和等于第n+1个数，我们只需要求出整个b排列的sum，然后去寻找sum减去哪个数再/2可以在其中找到（而且不能是当前减去的那个数），删去的那个数为x，找到的那个数为b[n+1]

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
void solve()
{
    vector<ll> b;//b排列
    ll n;
    ll sum = 0;//排列的和
    cin >> n;
    for (ll i = 0; i < n + 2; i++)
    {
        ll x;
        cin >> x;
        b.push_back(x);
        sum += x;
    }
    sort(b.begin(), b.end());//排序，方便二分
    for (ll i = 0; i < b.size(); i++)
    {
        ll cur_sum = sum - b[i];
        if (cur_sum & 1)//奇数不再操作，因为无法准确/2
            continue;
        cur_sum /= 2;
        if (!binary_search(b.begin(), b.end(), cur_sum))//找不到的就不再操作
            continue;
        int con=b[i];//记录一下删掉的是哪个，下面两行有用
        b.erase(b.begin() + i, b.begin() + i + 1);
        if (!binary_search(b.begin(), b.end(), cur_sum))//唯一一个小坑点，可能会因为找到的数是当前的数，而当前的数又被删掉了
        {
            b.insert(b.begin()+i,con);//若删掉就再放回去，这次操作不能满足，continue了
            continue;
        }
        ll id = lower_bound(b.begin(), b.end(), cur_sum) - b.begin();//寻找我们应该设为b[n+1]的数
        b.erase(b.begin() + id, b.begin() + id + 1);//删掉这个数
        for (ll j = 0; j < b.size(); j++)//此时我们就只有n个数了，就是a的排列
        {
            cout << b[j] << " ";
        }
        return;
    }
    cout << "-1" << endl;//循环完了也找不到能满足的，就"-1"
}
int main()
{
    int cass;
    each_cass(cass)
    {
        solve();
    }
    return 0;
}
```
