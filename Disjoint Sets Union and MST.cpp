// Disjoint Sets Union and MST
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "debug.cpp"
#else
#define dbg(...)
#endif
using ll=long long;
const int N=1e5+200;
ll vis[N];
ll visrev[N];
vector<ll> adj[N];
vector<ll> rev[N];
ll n,m1,m2;
struct ds{
    ll N;
    vector<ll> parent,sz,max1,min1;
    ll maxSize,components;
    ds(ll n){
        N=n;
        parent.resize(n+2);
        max1.resize(n+2);
        min1.resize(n+2);
        sz.resize(n+2,1);
        maxSize=1;
        components=n;
        for (int i = 1; i <=n ; ++i) {
            parent[i]=i;
            max1[i]=i;
            min1[i]=i;
        }
    }
    bool same(ll node1,ll node2){
        return find(node1)==find(node2);
    }

    ll find(ll node){
        if(node==parent[node]){
            return node;
        }
        return parent[node]=find(parent[node]);
    }
    void marge(ll node1,ll node2){
        ll x=find(node1),z=find(node2);
        if(x==z)
            return;
        if(sz[x]<sz[z]){
            swap(x,z);
        }
        max1[x]=max(max1[x],max1[z]);
        min1[x]=min(min1[x],min1[z]);
        parent[z]=x;
        sz[x]+=sz[z];
        components--;
        maxSize = max(maxSize, sz[x]);
    }

    ll getSize(ll node1){
        ll x=find(node1);
        return sz[x];
    }
    ll getMax(ll node1){
        ll x=find(node1);
        return max1[x];
    }
    ll getMin(ll node1){
        ll x=find(node1);
        return min1[x];
    }

    ll get1(){
        return components;
    }

    ll get2(){
        return maxSize;
    }
};
struct edge{
    ll src,dest,cost;
};

bool comp(edge e1,edge e2){
    return e1.cost<e2.cost;
}
void solve(ll n,ll m){
    ds d(n);
    edge edges[m];
    for (int i = 0; i < m; ++i) {
        ll a,b,c;cin>>a>>b>>c;
        a++;
        b++;
        edges[i].src=a,edges[i].dest=b,edges[i].cost=c;
    }
    sort(edges,edges+m,comp);
    ll ans=0;
    ll taken=0;
    for (int i = 0; i < m and taken<n-1; ++i) {
        edge temp=edges[i];
        if(!d.same(temp.src,temp.dest)){
            d.marge(temp.src,temp.dest);
            ans+=temp.cost;
            taken++;
        }
    }
    cout<<ans<<"\n";
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    freopen("debuging.txt", "w", stderr);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n,m;
    while(cin>>n>>m){
        if(n==0 and m==0)
            break;
        solve(n,m);
    }

    return 0;
}
