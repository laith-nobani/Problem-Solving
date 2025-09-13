const int BASE1 = 31, MOD1 = 1e9 + 7;
const int BASE2 = 37, MOD2 = 1e9 + 9;
vector<ll> powBase1, powBase2;
void precomputePowers(int n) {
    powBase1.resize(n+1);
    powBase2.resize(n+1);
    powBase1[0] = powBase2[0] = 1;
    for(int i=1;i<=n;i++){
        powBase1[i] = (powBase1[i-1] * BASE1) % MOD1;
        powBase2[i] = (powBase2[i-1] * BASE2) % MOD2;
    }
}
int val(char c) { return c - 'a' + 1; }
pair<ll,ll> shiftLeft(pair<ll,ll> code) {
    return {(code.first * BASE1) % MOD1, (code.second * BASE2) % MOD2};
}

pair<ll,ll> addAt(pair<ll,ll> code, int idx, int v) {
    return {(code.first + v * powBase1[idx]) % MOD1,
            (code.second + v * powBase2[idx]) % MOD2};
}

pair<ll,ll> removeAt(pair<ll,ll> code, int idx, int v) {
    return {(code.first - v * powBase1[idx] + MOD1) % MOD1,
            (code.second - v * powBase2[idx] + MOD2) % MOD2};
}

ll pattern_search(const string &main, const string &pat) {
    int n = pat.size();
    pair<ll,ll> patCode = {0,0};
    for(int i=0;i<n;i++){
        patCode = shiftLeft(patCode);
        patCode = addAt(patCode,0,val(pat[i]));
    }

    pair<ll,ll> subCode = {0,0};
    ll ans = 0;
    for(int i=0;i<(int)main.size();i++){
        if(i - n >= 0) subCode = removeAt(subCode, n-1, val(main[i-n]));
        subCode = shiftLeft(subCode);
        subCode = addAt(subCode,0,val(main[i]));
        if(subCode == patCode) ans++;
    }
    return ans;
}

int longestSuffixPalindrome(string &str) {
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


void solve(){
    string st1, st2;
    cin >> st1 >> st2;
    precomputePowers(max(st1.size(), st2.size()) + 5);
    ll count = pattern_search(st1, st2);
    cout << count << "\n";
}
