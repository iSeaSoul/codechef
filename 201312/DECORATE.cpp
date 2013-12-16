// New Ryan
// Create @ 17:07 12-10 2013
// Comment - 

#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bitset>
#include <queue>
#include <map>
#include <set>

using namespace std;

// Self Template Code BGEIN

#define sz(x) ((int)((x).size()))
#define out(x) printf(#x" %d\n", x)
#define all(x) (x).begin(), (x).end()
#define clz(x) memset (x, 0, sizeof(x))
#define read(x) freopen (x, "r", stdin)
#define wrte(x) freopen (x, "w", stdout)
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define repf(i,a,b) for (int i = (a); i <= (b); ++i)
#define repd(i,a,b) for (int i = (a); i >= (b); --i)
#define repcase int t, Case = 1; for (scanf ("%d", &t); t; --t)
#define repeach(i,x) for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)

typedef long long int64;
typedef pair<int, int> pii;
typedef pair<int64, int64> pll;
typedef pair<double, double> pdd;

int sgn(double x) { return (x > 1e-8) - (x < -1e-8); }
int count_bit(int x) { return x == 0? 0 : count_bit(x >> 1) + (x & 1); }

template<class T> inline void ckmin(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void ckmax(T &a, const T b) { if (b > a) a = b; }

// Self Template Code END

#define MAXN 9999
#define MAXSIZE 10
#define DLEN 4

class BigNum
{ 
private: 
    int a[1000];    //可以控制大数的位数 
    int len;       //大数长度
public: 
    BigNum(){ len = 1;memset(a,0,sizeof(a)); }   //构造函数
    BigNum(const int);       //将一个int类型的变量转化为大数
    BigNum(const char*);     //将一个字符串类型的变量转化为大数
    BigNum(const BigNum &);  //拷贝构造函数
    BigNum &operator=(const BigNum &);   //重载赋值运算符，大数之间进行赋值运算

    BigNum operator+(const BigNum &) const;   //重载加法运算符，两个大数之间的相加运算 
    BigNum operator*(const BigNum &) const;   //重载乘法运算符，两个大数之间的相乘运算 
    BigNum operator/(const int   &) const;    //重载除法运算符，大数对一个整数进行相除运算

    BigNum operator^(const int  &) const;    //大数的n次方运算
    void print();       //输出大数
}; 
BigNum::BigNum(const int b)     //将一个int类型的变量转化为大数
{ 
    int c,d = b;
    len = 0;
    memset(a,0,sizeof(a));
    while(d > MAXN)
    {
        c = d - (d / (MAXN + 1)) * (MAXN + 1); 
        d = d / (MAXN + 1);
        a[len++] = c;
    }
    a[len++] = d;
}
BigNum::BigNum(const BigNum & T) : len(T.len)  //拷贝构造函数
{ 
    int i; 
    memset(a,0,sizeof(a)); 
    for(i = 0 ; i < len ; i++)
        a[i] = T.a[i]; 
} 
BigNum & BigNum::operator=(const BigNum & n)   //重载赋值运算符，大数之间进行赋值运算
{
    int i;
    len = n.len;
    memset(a,0,sizeof(a)); 
    for(i = 0 ; i < len ; i++) 
        a[i] = n.a[i]; 
    return *this; 
}
BigNum BigNum::operator+(const BigNum & T) const   //两个大数之间的相加运算
{
    BigNum t(*this);
    int i,big;      //位数   
    big = T.len > len ? T.len : len; 
    for(i = 0 ; i < big ; i++) 
    { 
        t.a[i] +=T.a[i]; 
        if(t.a[i] > MAXN) 
        { 
            t.a[i + 1]++; 
            t.a[i] -=MAXN+1; 
        } 
    } 
    if(t.a[big] != 0)
        t.len = big + 1; 
    else
        t.len = big;   
    return t;
}
BigNum BigNum::operator*(const BigNum & T) const   //两个大数之间的相乘运算 
{ 
    BigNum ret; 
    int i,j,up; 
    int temp,temp1;   
    for(i = 0 ; i < len ; i++)
    { 
        up = 0; 
        for(j = 0 ; j < T.len ; j++)
        { 
            temp = a[i] * T.a[j] + ret.a[i + j] + up; 
            if(temp > MAXN)
            { 
                temp1 = temp - temp / (MAXN + 1) * (MAXN + 1); 
                up = temp / (MAXN + 1); 
                ret.a[i + j] = temp1; 
            } 
            else
            { 
                up = 0; 
                ret.a[i + j] = temp; 
            } 
        } 
        if(up != 0) 
            ret.a[i + j] = up; 
    } 
    ret.len = i + j; 
    while(ret.a[ret.len - 1] == 0 && ret.len > 1)
        ret.len--; 
    return ret; 
} 
BigNum BigNum::operator/(const int & b) const   //大数对一个整数进行相除运算
{ 
    BigNum ret; 
    int i,down = 0;   
    for(i = len - 1 ; i >= 0 ; i--)
    { 
        ret.a[i] = (a[i] + down * (MAXN + 1)) / b; 
        down = a[i] + down * (MAXN + 1) - ret.a[i] * b; 
    } 
    ret.len = len; 
    while(ret.a[ret.len - 1] == 0 && ret.len > 1)
        ret.len--; 
    return ret; 
}
BigNum BigNum::operator^(const int & n) const    //大数的n次方运算
{
    BigNum t,ret(1);
    int i;
    assert (n>=0);
        //exit(-1);
    if(n==0)
        return 1;
    if(n==1)
        return *this;
    int m=n;
    while(m>1)
    {
        t=*this;
        for( i=1;i<<1<=m;i<<=1)
        {
            t=t*t;
        }
        m-=i;
        ret=ret*t;
        if(m==1)
            ret=ret*(*this);
    }
    return ret;
}
void BigNum::print()    //输出大数
{ 
    int i;   
    cout << a[len - 1]; 
    for(i = len - 2 ; i >= 0 ; i--)
    { 
        cout.width(DLEN); 
        cout.fill('0'); 
        cout << a[i]; 
    } 
    cout << endl;
}

//namespace DifferentSymmetricSubstring {
    const int maxn = 400000 + 10;

    int r[maxn];
    int sa[maxn], t[maxn], t2[maxn], c[maxn];
    int rank[maxn], height[maxn];
    //char str[maxn];
    int rmp[maxn][50], pre_log2[maxn];

    void init()
    {
        int num = 0, tot = 1;
        while(tot < maxn)
        {
            for(int i = tot; i < tot * 2 && i < maxn; ++i)
                pre_log2[i] = num;
            num++; tot *= 2;
        }
    }

    void build_sa(int * s, int n, int m)
    {
        int i, * x = t, * y = t2, * t;
        for(i = 0; i < m; ++i) c[i] = 0;
        for(i = 0; i < n; ++i) c[x[i] = s[i]]++;
        for(i = 1; i < m; ++i) c[i] += c[i - 1];
        for(i = n - 1; i >= 0; --i) sa[--c[x[i]]] = i;
        for(int k = 1; k <= n; k <<= 1)
        {
            int p = 0;
            for(i = n - k; i < n; ++i) y[p++] = i;
            for(i = 0; i < n; ++i) if(sa[i] >= k) y[p++] = sa[i] - k;
            for(i = 0; i < m; ++i) c[i] = 0;
            for(i = 0; i < n; ++i) c[x[y[i]]]++;
            for(i = 1; i < m; ++i) c[i] += c[i - 1];
            for(i = n - 1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
            t = x; x = y; y = t;
            p = 1; x[sa[0]] = 0;
            for(i = 1; i < n; ++i)
                x[sa[i]] = (y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k]) ? p - 1 : p++;
            if(p >= n) break;
            m = p;
        }
    }

    void get_heigth(int * s, int n)
    {
        int i, j, k = 0;
        for(i = 1; i <= n; ++i) rank[sa[i]] = i;
        for(i = 0; i < n; ++i)
        {
            if(k) k--;
            j = sa[rank[i] - 1];
            while(s[i + k] == s[j + k]) k++;
            height[rank[i]] = k;
        }
    }

    void rmp_init(int n)
    {
        for(int i = 1; i <= n; ++i) rmp[i][0] = height[i];
        for(int j = 1; (1 << j) <= n; ++j)
            for(int i = 1; i + j - 1 <= n; ++i)
                rmp[i][j] = rmp[i][j - 1] < rmp[i + (1 << (j - 1))][j - 1] ? rmp[i][j - 1] : rmp[i + (1 << (j - 1))][j - 1];
    }

    int get_rmp(int l, int r)
    {
        int k = pre_log2[r - l + 1];
        return rmp[l][k] < rmp[r - (1 << k) + 1][k] ? rmp[l][k] : rmp[r - (1 << k) + 1][k];
    }

    int apply(char* str) 
    {
        int n = 0, len = strlen(str);
        for(int i = 0; i < len; ++i) r[n++] = str[i] - 'a' + 1;
        r[n++] = 28;
        for(int i = len - 1; i >= 0; --i) r[n++] = str[i] - 'a' + 1;
        r[n] = 0;
        build_sa(r, n + 1, 30); get_heigth(r, n);
        rmp_init(n);
        int res = 0, cnt = 0;
        for(int i = 1; i < n; ++i)
        {
            cnt = (cnt > height[i]) ? height[i] : cnt;
            if(sa[i] < len)
            {
                int other = 2 * len - sa[i];
                int tem = get_rmp(min(i, rank[other]) + 1, max(i, rank[other]));
                if(tem > cnt)
                {
                    res += (tem - cnt);
                    cnt = tem;
                }
            }
        }
        cnt = 0;
        for(int i = 1; i < n; ++i)
        {
            cnt = (cnt > height[i]) ? height[i] : cnt;
            if(!sa[i]) continue;
            if(sa[i] < len)
            {
                int other = 2 * len - sa[i] + 1;
                int tem = get_rmp(min(i, rank[other]) + 1, max(i, rank[other]));
                if(tem > cnt)
                {
                    res += tem - cnt;
                    cnt = tem;
                }
            }
        }
        return res;
    }
//};

//namespace PolyaCalcWays {
    int get_eular(int x)
    {
        int sum = 1;
        for (int i = 2; i * i <= x; ++i)
        {
            if (x % i == 0)
            {
                sum *= (i - 1); x /= i;
                while (x % i == 0)
                {
                    sum *= i; x /= i;
                }
            }
        }
        if (x != 1)
        {
            sum *= (x - 1);
        }
        return sum;
    }

    BigNum mul(BigNum x, int p)
    {
        return (x ^ p);
    }

    BigNum calc(int numberOfColors, int numberOfPearls) 
    {
        assert (numberOfColors != 0 && numberOfPearls != 0);

        BigNum sum = BigNum(0);
        for (int i = 1; i * i <= numberOfPearls; ++i)
        {
            if (numberOfPearls % i == 0)
            {
                sum = sum + mul(numberOfColors, numberOfPearls / i) * get_eular(i);
                if (i * i != numberOfPearls)
                {
                    sum = sum + mul(numberOfColors, i) * get_eular(numberOfPearls / i);
                }
            }
        }
        if (numberOfPearls & 1)
        {
            sum = sum + mul(numberOfColors, (numberOfPearls + 1) >> 1) * numberOfPearls;
        }
        else
        {
            sum = sum + mul(numberOfColors, numberOfPearls >> 1) * (numberOfPearls >> 1);
            sum = sum + mul(numberOfColors, (numberOfPearls >> 1) + 1) * (numberOfPearls >> 1);
        }

        sum = sum / (2 * numberOfPearls);
        return sum;
    }
//};

//const int maxn = 1000000 + 10;

char parentStr[maxn];
int length;

int main() {
    init();

    while (scanf ("%s", parentStr) != EOF) {
        scanf ("%d", &length);
        calc(apply(parentStr), length).print();
    }
    
    return 0;
}
