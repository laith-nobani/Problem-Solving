#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "debug.cpp"
#else
#define dbg(...)
#endif
const int N = 1010;
int n, m;
char arr[N][N];
bool vis[N][N];
int dy[] = {0, 0, -1, 1};
int dx[] = {-1, 1, 0, 0};
using ll = long long;
//
struct SegmentTree {
    int sz;
    vector<ll> seg;
    vector<ll> &arr;

    SegmentTree(vector<ll> &input) : arr(input) {
        sz = 1;
        int n = arr.size();
        while (sz < n)
            sz *= 2;
        seg = vector<ll>(sz * 2, 0);
        build(0, 0, sz - 1);
    }

    void build(int node, int l, int r) {
        if (l == r) {
            if (l < arr.size()) {
                seg[node] = arr[l];
            } else {
                seg[node] = 0;
            }
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node + 1, l, mid);
        build(2 * node + 2, mid + 1, r);
        seg[node] = min(seg[2 * node + 1] , seg[2 * node + 2]);
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            seg[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) {
            update(2 * node + 1, l, mid, idx, val);
        } else {
            update(2 * node + 2, mid + 1, r, idx, val);
        }
        seg[node] = min(seg[2 * node + 1] , seg[2 * node + 2]);
    }

    ll query(int node, int l, int r, int lq, int rq) {
        if (r < lq || l > rq) {
            return LLONG_MAX;
        }
        if (lq <= l && r <= rq) {
            return seg[node];
        }
        int mid = (l + r) / 2;
        ll left = query(2 * node + 1, l, mid, lq, rq);
        ll right = query(2 * node + 2, mid + 1, r, lq, rq);
        return  min(left , right);
    }

    void solupdate(int idx, int val) {
        update(0, 0, sz - 1, idx, val);
    }

    ll solquery(int lq, int rq) {
        return query(0, 0, sz - 1, lq, rq);
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<ll> vec(n);
    for (int i = 0; i < n; ++i) {
        cin >> vec[i];
    }

    SegmentTree st(vec);

    while (m--) {
        ll op, a, b;
        cin >> op >> a >> b;
        if (op == 1) {
            st.solupdate(a, b);
        } else {
            cout << st.solquery(a, b - 1) << "\n";
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("debuging.txt", "w", stderr);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while (t--)
        solve();

    return 0;
}
