#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 

#define ordered_set tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>
#define ll long long 
#define vt vector
#define int long long 

#define all(a) a.begin(), a.end()
#define pi pair
#define rep(i, a, b) for (ll i = a; i < b; i++)
#define repr(i , n, a) for(ll i = n ; i >= a; i--)

const ll N = 2e5+1;
const ll mod = 1e9+7;
void ff() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

ll binexpo(ll a, ll n, ll m) {
    ll res = 1;
    while (n) {
        if (n & 1) res = res * a % m;
        a = a * a % m;
        n >>= 1;
    }
    return res;
}

bool cmp(pi<ll, string> a, pi<ll, string>& b){
    if(a.first == b.first){
        return a.second < b.second;
    }
    return a.first > b.first;
}

int add(int a, int b, int m){
    a = ((a % m) + (b % m) + m) % m;
    return a;
}

int mul(int a, int b, int m){
    a = (((a % m) * (b % m)) % m + m) % m;
    return a;
}

void myerase(ordered_set & t, int v){
    int rank = t.order_of_key(v);
    ordered_set::iterator it = t.find_by_order(rank);
    t.erase(it);
}

void solve(){
int n;
cin>>n;
vt<int>a(n);
rep(i , 0 , n){
    cin>>a[i];    
}
int sol = 0;
multiset<int>st;
st.insert(1e18);
repr(i , 0 , n){
    int ind = *st.lower_bound(a[i]/2);
    if(ind == 1e18){
        st.insert(a[i]);
        continue;
    }
    else {
        st.erase(st.find(ind));
        sol++;
    }
}
cout <<sol;
}

signed main() {
    // int tt;
    // cin >> tt;
    // while(tt--){
        solve();
    // }
}
