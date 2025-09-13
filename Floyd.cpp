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
int next[N][N];

vector<int> get_path(int u, int v) {
    if (next[u][v] == -1) return {}; 
    vector<int> path;
    path.push_back(u);
    
    while (u != v) {
        u = next[u][v];
        path.push_back(u);
    }
    
    return path;
}
void Floyd() {
    int n, m;
    cin >> n >> m;

      for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dist[i][j] = 0;
                next[i][j] = i;
            } else {
                dist[i][j] = inf;
                next[i][j] = -1;
            }
        }
    }


    for (int i = 0; i < m; i++) {
        int x, z, c;
        cin >> x >> z >> c;
        dist[x][z] = dist[z][x] = c;
        next[x][z] = z;
        next[z][x] = x;
    }

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
               if (dist[i][k] < inf && dist[k][j] < inf) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
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
    
    for (int j = 2; j <= n; j++) {
        vector<int> path = get_path(1, j);
        if (path.empty()) {
            cout << "No path from 1 to " << j << "\n";
        } else {
            cout << "Path from 1 to " << j << " (distance: " << dist[1][j] << "): ";
            for (int node : path) {
                cout << node;
                if (node != j) cout << " -> ";
            }
            cout << "\n";
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
