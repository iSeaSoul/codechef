// Rain Dreamer MODEL
// Create @ 14:54 01-05 2014
// Comment - 

#include <cmath>
#include <ctime>
#include <cstdio>
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
#define RD(x) freopen (x, "r", stdin)
#define WT(x) freopen (x, "w", stdout)
#define clz(x) memset (x, 0, sizeof(x))
#define cln(x) memset (x, -1, sizeof(x))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define repf(i,a,b) for (int i = (a); i <= (b); ++i)
#define repd(i,a,b) for (int i = (a); i >= (b); --i)
#define repcase int t, Case = 1; for (scanf ("%d", &t); t; --t)
#define repeach(i,x) for (__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)

typedef long long int64;
typedef pair<int, int> pii;

int sgn(double x) { return (x > 1e-8) - (x < -1e-8); }
int count_bit(int x) { return x == 0? 0 : count_bit(x >> 1) + (x & 1); }

template<class T> inline void ckmin(T &a, const T b) { if (b < a) a = b; }
template<class T> inline void ckmax(T &a, const T b) { if (b > a) a = b; }

// Self Template Code END

const int MAXN = 100000 + 100;

int read_int() {
    char ch;
    for (ch = getchar(); !(ch >= '0' && ch <= '9'); ch = getchar());
    int res = ch - '0';
    for (ch = getchar(); ch >= '0' && ch <= '9'; ch = getchar()) {
        res = res * 10 + (ch - '0');
    }
    return res;
}

int n, a[MAXN], max_pow, dcz_cnt, dcz_a[MAXN];

void discret() {
    int pow2 = 1, max_a = *max_element(dcz_a, dcz_a + n);
    dcz_cnt = n;
    max_pow = 0;
    while (pow2 < max_a) {
        dcz_a[dcz_cnt++] = pow2;
        pow2 <<= 1;
        max_pow += 1;
    }
    dcz_a[dcz_cnt++] = pow2;
    sort (dcz_a, dcz_a + dcz_cnt);
    dcz_cnt = unique(dcz_a, dcz_a + dcz_cnt) - dcz_a;
}

int get_id(int x) {
    return lower_bound(dcz_a, dcz_a + dcz_cnt, x) - dcz_a + 1;
}

void input() {
    rep (i, n) {
        //scanf ("%d", &a[i]);
        dcz_a[i] = a[i] = read_int();
    }
    discret();
}

struct chairTree {
    struct node {
        int l, r, val, sum;
    };
    
    node n[MAXN * 20];
    int r_cnt;
    
    void init() {
        r_cnt = 0;
    }
    int build(int l, int r) {
        int curR = r_cnt++;
        n[curR].val = n[curR].sum = 0;
        if (l != r) {
            n[curR].l = build (l, (l + r) >> 1);
            n[curR].r = build (((l + r) >> 1) + 1, r);
        }
        return curR;
    }
    void update_dif(int cur_root, int root, int rel_val) {
        n[cur_root].val = n[root].val + 1;
        n[cur_root].sum = n[root].sum + rel_val;
    }
    int update(int root, int pos, int rel_val) {
        int nextR = r_cnt++;
        int resR = nextR;
        update_dif (nextR, root, rel_val);
        
        int l = 1, r = dcz_cnt;
        while (l != r) {
            int mid = (l + r) >> 1;
            if (pos <= mid) {
                n[nextR].l = r_cnt++; n[nextR].r = n[root].r;
                nextR = n[nextR].l; root = n[root].l;
                r = mid;
            } else {
                n[nextR].r = r_cnt++; n[nextR].l = n[root].l;
                nextR = n[nextR].r; root = n[root].r;
                l = mid + 1;
            }
            update_dif (nextR, root, rel_val);      
        }
        
        return resR;
    }
    pii get_num_sum(int l_root, int r_root, int pos) {
        int res = 0, cnt = 0;
        int l = 1, r = dcz_cnt;
        while (l != r) {
            int mid = (l + r) >> 1;
            if (pos <= mid) {
                l_root = n[l_root].l;
                r_root = n[r_root].l;
                r = mid;
            } else {
                res += (n[n[r_root].l].sum - n[n[l_root].l].sum);
                cnt += (n[n[r_root].l].val - n[n[l_root].l].val);
                l_root = n[l_root].r;
                r_root = n[r_root].r;
                l = mid + 1;
            }
        }
        res += n[r_root].sum - n[l_root].sum;
        cnt += n[r_root].val - n[l_root].val;
        return pii(cnt, res);
    }
    int get_kth_num_pos(int l_root, int r_root, int cnt) {
        if (n[r_root].val - n[l_root].val < cnt) {
            return -1;
        }
        
        int l = 1, r = dcz_cnt;
        while (l != r) {
            int mid = (l + r) >> 1;
            if (n[n[r_root].l].val - n[n[l_root].l].val >= cnt) {
                l_root = n[l_root].l;
                r_root = n[r_root].l;
                r = mid;
            } else {
                cnt -= n[n[r_root].l].val - n[n[l_root].l].val;
                l_root = n[l_root].r;
                r_root = n[r_root].r;
                l = mid + 1;
            }
        }
        return l;
    }
};

chairTree ct;
int treeID[MAXN];

void build() {
    ct.init();
    treeID[0] = ct.build(1, dcz_cnt);
    rep (i, n) {
        treeID[i + 1] = ct.update(treeID[i], get_id(a[i]), a[i]);
    }
}

void query() {
    repcase {
        int l, r;
        //scanf ("%d%d", &l, &r);
        l = read_int(), r = read_int();
        l -= 1;
        int pow2 = 1;
        rep (pow_cnt, max_pow + 1) {
            pii num_sum = ct.get_num_sum(treeID[l], treeID[r], get_id(pow2));
            int cur_sum = num_sum.second;
            int cur_next_num_pos = ct.get_kth_num_pos(treeID[l], treeID[r], num_sum.first + 1);
            if (cur_next_num_pos == -1 || dcz_a[cur_next_num_pos - 1] > cur_sum + 1) {
                printf ("%d\n", cur_sum + 1);
                break ;
            }
            pow2 <<= 1;
        }
    }
}

int main() {
    while (scanf ("%d", &n) != EOF) {
        input();
        build();
        query();
    }
    return 0;
}

