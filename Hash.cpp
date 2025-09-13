
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Multibase parameters
const int BASE1 = 31, MOD1 = 1e9 + 7;
const int BASE2 = 37, MOD2 = 1e9 + 9;

// Fast power
ll fastpow(ll num, ll p, ll MOD) {
    if (p == 0) return 1;
    if (p % 2) return (num % MOD * fastpow(num, p - 1, MOD)) % MOD;
    ll a = fastpow(num, p / 2, MOD);
    return (a * a) % MOD;
}

// Hash operations using pair for multibase
pair<ll,ll> shiftLeft(pair<ll,ll> code) {
    return {(code.first * BASE1) % MOD1, (code.second * BASE2) % MOD2};
}

pair<ll,ll> addAt(pair<ll,ll> code, int idx, int v) {
    return {(code.first + v * fastpow(BASE1, idx, MOD1)) % MOD1,
            (code.second + v * fastpow(BASE2, idx, MOD2)) % MOD2};
}

pair<ll,ll> removeAt(pair<ll,ll> code, int idx, int v) {
    return {(code.first - v * fastpow(BASE1, idx, MOD1) + MOD1) % MOD1,
            (code.second - v * fastpow(BASE2, idx, MOD2) + MOD2) % MOD2};
}

// Character value
int val(char c) { return c - 'a' + 1; }

// Pattern search using multibase
void pattern_search(string main, string pat) {
    int n = pat.size();
    pair<ll,ll> patCode = {0,0};
    for(int i=0;i<n;i++){
        patCode = shiftLeft(patCode);
        patCode = addAt(patCode, 0, val(pat[i]));
    }

    pair<ll,ll> subCode = {0,0};
    for(int i=0;i<(int)main.size();i++){
        if(i - n >= 0) subCode = removeAt(subCode, n-1, val(main[i-n]));
        subCode = shiftLeft(subCode);
        subCode = addAt(subCode, 0, val(main[i]));
        if(subCode == patCode){
            cout << "Found match at index " << i-n+1 << "!\n";
        }
    }
}

// Longest suffix palindrome using multibase
int longestSuffixPalindrome(string str) {
    int n = str.size();
    pair<ll,ll> code = {0,0};
    pair<ll,ll> codeRev = {0,0};
    int len = 0, ans = 0;

    for(int i=n-1;i>=0;i--){
        code = shiftLeft(code);
        code = addAt(code,0,val(str[i]));

        codeRev = addAt(codeRev,len,val(str[i]));

        len++;
        if(code == codeRev) ans = len;
    }
    return ans;
}


