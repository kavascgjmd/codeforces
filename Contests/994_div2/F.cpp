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
string tobin(int x){
    string temp = "";
    while( x > 0){
        temp = to_string(x % 2)+temp;
        x /= 2;
    }
    while(temp.size() < 61){
       temp = "0"+temp;
    }
    return temp;
}

int dp[61][2];

pi<int,int> count(int i, string &s, int I, string & K, int tough){
    int n = s.size();
    if(i == n){
       return {0, 1};
    }
    if(dp[i][tough] != -1){
        return {dp[i][tough],1};
    }
    int res = 0;
    if(tough){
       if(i >= n-I){
         if(K[i] < s[i]){
            
            pi<int,int> val = count(i+1, s, I, K , 0);
            if(val.second == 1){
                res ^= val.first^((1<<(n-1-i))*(K[i]-'0'));
            }
         } 
         else if(K[i] == s[i]){
            pi<int,int>val =  count(i +1, s, I, K, tough);
            if(val.second == 1){
                res ^= val.first^((1<<(n-1-i))*(K[i]-'0'));
            }
         }
       }
       else {
        rep(j , 0 , s[i]-'0'){
            pi<int,int>val = count(i+1, s, I, K , 0);
            if(val.second){
            res ^= val.first^((1<<(n-1-i))*j);}
        }
        pi<int,int>val = count(i +1 , s, I , K, tough);
        if(val.second == 1){
        res ^= val.first^((1<<(n-1-i))*(s[i]-'0'));}
       }
    }
    else {
       if(i >= n-I){
        pi<int,int>val = count(i+1, s, I , K ,0);
         if(val.second){
         res ^= val.first^((1<<(n-1-i))*(K[i]-'0'));}
       }
       else {
        rep(j , 0 , 2){
            pi<int,int>val = count(i+1, s, I, K, 0);
            if(val.second){
            res ^= val.first^((1<<(n-1-i))*j);}
        }
       } 
    }

    if(res != 0){
        dp[i][tough] = res;
        return {res , 1};
    }
    
    return {0, 0};
}
int dp2[61][2];
pi<int,int> calc(int i , string & s, int tough, int v){
    int n = s.size();
    if(i == n){
      cout <<v<<" ";
        return {0,1};
    }
    // if(dp2[i][tough] != -1){
    //     return {dp2[i][tough],  1};
    // }
    int res = 0;
    if(tough){
        rep(j , 0 , s[i]-'0'){
        pi<int,int>val = calc(i+1, s, 0,  v^((1<<(n-1-i))*j));
        if(val.second){    
        res ^= val.first^((1<<(n-1-i))*j);}
        }
        pi<int,int>val = calc(i+1, s, tough, v ^((1<<(n-1-i))*(s[i]-'0')) );
        if(val.second){
        res ^= val.first^((1<<(n-1-i))*(s[i]-'0'));}
    }
    else {
        rep(j , 0 , 2){
            pi<int,int>val = calc(i+1, s, 0, v ^((1<<(n-1-i))*j));
            if(val.second){
            res ^= val.first^((1<<(n-1-i))*j);}
        }
    }
    if(res == 0){return {0,0};}
    dp2[i][tough] = res;
    return {res,1};
}

void solve(){
    int l,r,i,k;
    cin>>l>>r>>i>>k;
    l -= 1;
    int res ;
    
    string s = tobin(r), t = tobin(l);
    string K = tobin(k);
   
    memset(dp, -1 , sizeof(dp));
    memset(dp2, -1 , sizeof(dp2));
    int val = count(0, s, i, K, 1).first;
    int val3 = calc(0, s, 1, 0).first;
    memset(dp, -1 , sizeof(dp));
    memset(dp2, -1 , sizeof(dp2));
    int val2 = count(0 , t, i ,K , 1).first;
    int val4 = calc(0 , t, 1, 0).first;
    val2 ^= val;
    cout << val3<< " ";
    res = val4^val3;
    cout << res<<" ";
    res ^= val2;
    cout << res<<"\n";
}

signed main() {
    int tt;
    cin >> tt;
    while(tt--){
        solve();
    }
}
