# 🔗
<a href="https://acm.dingbacode.com/showproblem.php?pid=7018"><img src="https://i.loli.net/2021/10/14/6FSnKb9sGhPZLE5.png"></a>

# 💡
首先看最大费用  
就是不仅很坦诚地造出来一个n阶方块  
同时还要每个都从最高的位置往下落  
那么就是  
<img src="https://latex.codecogs.com/svg.image?\sum\limits_{x=1}^n\sum\limits_{y=1}^n[xy^2]nn=\frac{(1&plus;n)n}{2}\frac{n(1&plus;n)(1&plus;2n)}{6}nn" title="\sum\limits_{x=1}^n\sum\limits_{y=1}^n[xy^2]nn=\frac{(1+n)n}{2}\frac{n(1+n)(1+2n)}{6}nn" />
  
再看看最小费用  
每一个都是刚好放上去而不让它落下，然后能缺的就缺  
下面的一层正常放  
画一个二阶发现最划算的是在x=1和y=1的两侧构造一面墙  
同时交界处不放方块  
那么就是  
<img src="https://latex.codecogs.com/svg.image?\begin{aligned}\sum\limits_{x=1}^n\sum\limits_{y=1}^n[xy^2]&plus;\sum\limits_{x=2}^n\sum\limits_{z=2}^n[xz]&plus;\sum\limits_{y=2}^n\sum\limits_{z=2}^n[y^2z]=\frac{(1&plus;n)n}{2}\frac{n(1&plus;n)(1&plus;2n)}{6}&plus;\frac{(2&plus;n)(n-1)}{2}\frac{(2&plus;n)(n-1)}{2}&plus;\frac{(2&plus;n)(n-1)}{2}[\frac{n(1&plus;n)(1&plus;2n)}{6}-1]\end{aligned}" title="\begin{aligned}\sum\limits_{x=1}^n\sum\limits_{y=1}^n[xy^2]+\sum\limits_{x=2}^n\sum\limits_{z=2}^n[xz]+\sum\limits_{y=2}^n\sum\limits_{z=2}^n[y^2z]=\frac{(1+n)n}{2}\frac{n(1+n)(1+2n)}{6}+\frac{(2+n)(n-1)}{2}\frac{(2+n)(n-1)}{2}+\frac{(2+n)(n-1)}{2}[\frac{n(1+n)(1+2n)}{6}-1]\end{aligned}" />
  
数很大还要取模，直接开`BigInteger`
# <img src="https://img-blog.csdnimg.cn/20210713144601841.png" >
```java
public class Main {
        static BigInteger m = BigInteger.valueOf(1000000007);
        static BigInteger one = BigInteger.ONE;
        static BigInteger two = BigInteger.valueOf(2);
        static BigInteger zero = BigInteger.ZERO;
        static BigInteger six = BigInteger.valueOf(6);
        static BigInteger ksm ( BigInteger a, BigInteger b ) {
                BigInteger res = BigInteger.ONE;
                while ( b.compareTo(BigInteger.ZERO) == 1 ) {
                        if ( b.mod(two).compareTo(BigInteger.ONE) == 0 ) res = res.multiply(a).mod(m);
                        a = a.multiply(a).mod(m);
                        b = b.divide(two);
                }
                return res;
        }
        public static void main ( String[] args ) {
                boolean flag = true;
                Scanner input = new Scanner(System.in);
                int cass = input.nextInt(); while ( cass -- > 0 ) {
                        BigInteger n = input.nextBigInteger();
                        
                        BigInteger resBig = n.multiply(n).multiply(n).multiply(n);
                        resBig = resBig.multiply(n.add(one)).multiply(n.add(one));
                        resBig = resBig.multiply(n.multiply(two).add(one));
                        resBig = resBig.divide(six).divide(two).mod(m);
                        
                        BigInteger resSml = n.multiply(n);
                        resSml = resSml.multiply(n.add(one)).multiply(n.add(one));
                        resSml = resSml.multiply(n.multiply(two).add(one));
                        resSml = resSml.divide(six).divide(two).mod(m);
                        BigInteger tmp1 = two.add(n).multiply(n.subtract(one)).divide(two);
                        BigInteger tmp2 = n.multiply(n.add(one)).multiply(n.multiply(two).add(one)).divide(six).subtract(one);
                        tmp2 = tmp2.multiply(tmp1);
                        tmp1 = tmp1.multiply(tmp1);
                        resSml = resSml.add(tmp2).add(tmp1).mod(m);

                        System.out.println(resSml);
                        System.out.println(resBig);
                        flag = false;
                }
                input.close();
        }
}
```
