# 🔗
<a href="https://codeforces.com/gym/103373/problem/E"><img src="https://s2.loli.net/2022/01/14/9Ut3VzCna2kwZEG.png "></a>

# 💡
首先我们化简一下问题  
第  <img src="https://latex.codecogs.com/svg.image?\inline&space;d" title="\inline d" /> 天算法会消耗  <img src="https://latex.codecogs.com/svg.image?\inline&space;p" title="\inline p" /> ，获得  <img src="https://latex.codecogs.com/svg.image?\inline&space;qd^5" title="\inline qd^5" />   
也就是若算法可以执行，那么将获得  <img src="https://latex.codecogs.com/svg.image?\inline&space;-p+qd^5" title="\inline -p+qd^5" />  
若开始前有  <img src="https://latex.codecogs.com/svg.image?\inline&space;x" title="\inline x" /> ，执行  <img src="https://latex.codecogs.com/svg.image?\inline&space;y" title="\inline y" /> 天后会成为  <img src="https://latex.codecogs.com/svg.image?\inline&space;x-py+q\sum\limits_{i=1}^yi^5" title="\inline x-py+q\sum\limits_{i=1}^yi^5" />  
我们要让这个值  <img src="https://latex.codecogs.com/svg.image?\inline&space;\ge10^{99}" title="\inline \ge10^{99}" />  
同时要保证  <img src="https://latex.codecogs.com/svg.image?\inline&space;\forall&space;j\in[0,y],x-pj+q\sum\limits_{i=1}^ji^5\ge&space;p" title="\inline \forall&space;j\in[0,y],x-pj+q\sum\limits_{i=1}^ji^5\ge&space;p" /> ，不然就继续不了算法了，（左侧如果开始上升那么就可以保证了  
  
我们求  <img src="https://latex.codecogs.com/svg.image?\inline&space;\sum\limits_{i=1}^ji^5" title="\inline \sum\limits_{i=1}^ji^5" /> 可以用求[自然数幂和](http://www.chivas-regal.top/%E6%95%B0%E5%AD%A6/2021/11/19/%E6%8B%89%E6%A0%BC%E6%9C%97%E6%97%A5%E6%8F%92%E5%80%BC%E6%B3%95.html#%E5%BA%94%E7%94%A8%E8%87%AA%E7%84%B6%E6%95%B0%E7%9A%84%E5%B9%82%E5%92%8C)的方式进行拉格朗日插值，这里  <img src="https://latex.codecogs.com/svg.image?\inline&space;k" title="\inline k" /> 不大，所以就是常数复杂度  
我们求  <img src="https://latex.codecogs.com/svg.image?\inline&space;x" title="\inline x" /> 可以使用第二个限制进行二分  
求  <img src="https://latex.codecogs.com/svg.image?\inline&space;y" title="\inline y" /> 可以使用第一个进行二分  
  
数很大，开java的`BigInteger`

# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```cpp
public class Main{
        static int N = 100;
        static BigInteger zero = BigInteger.ZERO;
        static BigInteger one = BigInteger.ONE;
        static BigInteger two = BigInteger.valueOf(2);
        static BigInteger six = BigInteger.valueOf(6);
        static BigInteger ten = BigInteger.TEN;
        static BigInteger five = BigInteger.valueOf(5);

        static BigInteger ksm ( BigInteger a, BigInteger b ) {
                BigInteger res = one;
                while ( b.compareTo(zero) == 1 ) {
                        if ( b.mod(two).compareTo(one) == 0 ) {
                                res = res.multiply(a);
                        } a = a.multiply(a);
                        b = b.divide(two);
                } return res;
        }
        static BigInteger[] fac = new BigInteger[N];
        static BigInteger[] pre = new BigInteger[N];
        static BigInteger[] suf = new BigInteger[N];
        static BigInteger pownk ( BigInteger n, int k ) {
                BigInteger y = zero, up = zero, down = zero, res = zero;
                fac[0] = pre[0] = suf[k + 3] = one;
                for ( int i = 1; i <= k + 2; i ++ ) {
                        pre[i] = pre[i - 1].multiply(n.subtract(BigInteger.valueOf(i)));
                        fac[i] = fac[i - 1].multiply(BigInteger.valueOf(i));
                }
                for ( int i = k + 2; i >= 1; i -- ) {
                        suf[i] = suf[i + 1].multiply(n.subtract(BigInteger.valueOf(i)));
                }
                for ( int i = 1; i <= k + 2; i ++ ) {
                        y = y.add(ksm(BigInteger.valueOf(i), BigInteger.valueOf(k)));
                        up = pre[i - 1].multiply(suf[i + 1]);
                        down = fac[i - 1].multiply(fac[k + 2 - i]).multiply(((k - i) & 1) > 0 ? zero.subtract(one) : one);
                        res = res.add(y.multiply(up).divide(down));
                }
                return res;
        }
        static BigInteger q, p;
        static BigInteger x, y;

        static boolean check ( BigInteger j ) {
                BigInteger a = x.subtract(p.multiply(j)).add(q.multiply(pownk(j, 5)));
                BigInteger b = ksm(ten, BigInteger.valueOf(99));
                if ( a.compareTo(b) >= 0 ) return true;
                return false;
        }
        static boolean chk_x ( BigInteger xx ) {
                boolean flg = false;
                for ( Long i = Long.valueOf(0);; i ++ ) {
                        if ( xx.subtract(p.multiply(BigInteger.valueOf(i))).add(q.multiply(pownk(BigInteger.valueOf(i), 5))).compareTo(p) == -1 ) break;
                        if ( i > Long.valueOf(0) && xx.subtract(p.multiply(BigInteger.valueOf(i))).add(q.multiply(pownk(BigInteger.valueOf(i), 5))).compareTo(xx.subtract(p.multiply(BigInteger.valueOf(i - 1))).add(q.multiply(pownk(BigInteger.valueOf(i - 1), 5)))) == 1 ) { flg = true; break;}
                }
                return flg;
        }

        public static void main (String[] args) {
                Scanner input = new Scanner(System.in);
                p = input.nextBigInteger();
                q = input.nextBigInteger();
                x = p;
                y = zero;
                
                BigInteger l = zero, r = ksm(ten, BigInteger.valueOf(20));
                while ( l.compareTo(r) == -1 ) {
                        BigInteger mid = l.add(r).divide(two);
                        if ( chk_x(mid) ) r = mid;
                        else l = mid.add(one);
                }
                x = l;

                l = zero; r = ksm(ten, BigInteger.valueOf(30));
                while ( l.compareTo(r) == -1 ) {
                        BigInteger mid = l.add(r).divide(two);
                        if ( check(mid) ) r = mid;
                        else l = mid.add(one);
                }
                y = l;
                System.out.println(x + "\n" + y);
        }
}
```
