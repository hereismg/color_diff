#include <bits/stdc++.h>
using namespace std;

#define inf64 INT64_MAX/2
#define inf32 INT32_MAX/2
#define ll long long
#define int ll
#define pii pair<int,int>
#define endl '\n'
#define vv vector
#define cy cout<<"Yes"<<endl
#define cn cout<<"No"<<endl
#define its(it)  it.begin() + 1,it.end()
#define minV *min_element
#define maxV *max_element

int _;

//数学公式
ll mpow(ll x, ll y, ll mod);

//最长公共子序列
struct  Longest_common_subsequence{
    vv<vv<int>>f;
    vv<vv<int>>p;
    int dp(string &s,string &ss) {
        int n = s.size();  
        int m = ss.size();
        p = f = vv<vv<int>>(n + 1, vv<int>(m + 1));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[i - 1] == ss[j - 1])
                    p[i][j] = 1, f[i][j] = f[i - 1][j - 1] + 1;
                else {
                    if (f[i][j - 1] > f[i - 1][j])
                        p[i][j] = 2;
                    else
                        p[i][j] = 3;
                    f[i][j] = max(f[i - 1][j], f[i][j - 1]);
                }
            }
            cout << "进度：" << (double) i / n * 100 << "%" << endl;
        }
        return f[n ][m ];
    }
    string get_same(string &s,string &ss) {
        int i = s.size(), j = ss.size();
        string rs;
        while (i > 0 && j > 0) {
            if (p[i][j] == 1)
                rs += s[i - 1], i--, j--;
            else if (p[i][j] == 2)
                j--;
            else
                i--;
        }
        reverse(rs.begin(), rs.end());
        return rs;
    }    
};
void solve() {
    int n, m; cin >> n >> m;
    string s, ss; cin >> s >> ss;

    Longest_common_subsequence lcs;
    cout << lcs.dp(s, ss) << endl;

    // cout << lcs.get_same(s, ss) << endl;
}
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    _ = 1;
    //cin >> _;

    while (_--) {
        solve();
    }

    return 0;
}
ll mpow(ll x, ll y, ll mod) {
    x %= mod;
    ll s = 1;
    while (y) {
        if (y & 1) {
            s *= x;
            s %= mod;
        }
        x *= x;
        x %= mod;
        y >>= 1;
    }
    return s;
}