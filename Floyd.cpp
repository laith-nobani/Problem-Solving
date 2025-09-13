#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "debug.cpp"
#else
#define dbg(...)
#endif
const int N = 1010;
const int inf = 1e9;
int dist[N][N];

void Floyd() {
    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = inf;
        }
    }

    for (int i = 0; i < m; i++) {
        int x, z, c;
        cin >> x >> z >> c;
        dist[x][z] = dist[z][x] = c;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] < inf && dist[k][j] < inf) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        if (dist[1][i] == inf) {
            cout << -1 << "\n";
        } else {
            cout << dist[1][i] << "\n";
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

    Floyd();

    return 0;
}
