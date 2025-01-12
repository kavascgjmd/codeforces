#include<bits/stdc++.h>
using namespace std;
#define vt vector
#define pi pair
#define rep(i, a, n) for(ll i = a; i<n; i++)
#define repr(i, n, a) for(ll i = n; i>= a; i--)
#define pb push_back
#define ll long long
const ll mod = 1e9+7;
const ll mod2 = 998244353;

void ff(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

vt<vt<vt<ll>>> seg;

ll build(ll I, ll J, vt<ll>&temp) {
    ll n = temp.size();
   
    for(ll i = n; i < 2 * n; ++i) {
        seg[I][J][i] = temp[i - n]; 
    }

    for(ll i = n - 1; i > 0; --i) {
        seg[I][J][i] = min(seg[I][J][2 * i], seg[I][J][2 * i + 1]); \
    }
    return seg[I][J][1]; 
}

ll query(ll I, ll J, ll l, ll r, ll a, ll b) {
    ll n = r - l + 1;
    ll left = a + n, right = b + n;
    ll ans = 1e18;

    while(left <= right) {
        if(left % 2 == 1) ans = min(ans, seg[I][J][left++]);
        if(right % 2 == 0) ans = min(ans, seg[I][J][right--]);
        left /= 2;
        right /= 2;
    }
    return ans;
}

void solve(){
    ll n, m, k;
    cin >> n >> m >> k;
    vt<vt<vt<ll>>> nseg(n, vt<vt<ll>>(m, vt<ll>(2 * m, 1e18)));
    seg = nseg;
    vt<vt<ll>> a(n, vt<ll>(m, 0));
    
    rep(i, 0, n) {
        rep(j, 0, m) {
            cin >> a[i][j];
        }
    }


    rep(i, 0, n) {
        vt<ll> temp(m, 0);
        rep(j, 0, m) {
            temp[j] = j * k;
        }

        rep(j, 0, m) {
            rep(p, 0, m) {
                temp[p] += a[i][(p + j) % m];
            }
            build(i, j, temp);
        }
    }

    set<pi<ll, pi<ll, ll>>> st;
    vt<vt<ll>> dp(n, vt<ll>(m, 1e18));

    rep(i, 0, m) {
        ll val1 = query(0, i, 0, m - 1, 0, -1);
        ll val2 = query(0, i, 0, m - 1, 0, m - 1);
        val1 += m * k;
        if(val1 > val2) swap(val1, val2);
        st.insert({val1, {0, i}});
        dp[0][i] = val1;
    }

    while (st.size()) {
        pi<ll, pi<ll, ll>> top = *st.begin();
        st.erase(st.begin());
        ll i = top.second.first, j = top.second.second;
        ll cost = top.first;

        if (i == n - 1 && j == m - 1) {
            cout << cost << "\n";
            seg.clear();
            return;
        }

        if (i + 1 < n) {
            rep(p, 0, m - j) {
                ll val1 = query(i + 1, p, 0, m - 1, 0, j - 1);
                ll val2 = query(i + 1, p, 0, m - 1, j, m - 1);
                val1 += (-j + m) * k;
                val2 += (-j) * k;
                if (val1 > val2) swap(val1, val2);

                if (dp[i + 1][p + j] > val1 + cost) {
                    dp[i + 1][p + j] = val1 + cost;
                    st.insert({val1 + cost, {i + 1, p + j}});
                }
            }
        }
    }
}

int main(){
    ff();
    ll t;
    cin >> t;
    while (t--) {
        solve();
    }
}
