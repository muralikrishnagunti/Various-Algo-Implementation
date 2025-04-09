#include <bits/stdc++.h>
using namespace std;
#define ll long long int
class node
{
private:
    string id;
    ll d; // distance
    ll p; // path length
public:
    node()
    {
        id = "";
        d = INT_MAX;
        p = 0;
    }
    node(ll d_)
    {
        id = "";
        d = d_;
        p = 0;
    }

    node(string id_)
    {
        id = id_;
    }
    bool operator<(node b)
    {
        return d < b.d;
    }
    bool operator>(node b)
    {
        return d > b.d;
    }
    string get_id() { return id; }
    ll get_d() { return d; }
    ll get_p() { return p; }
    void set_d(ll x) { d = x; }
    void set_p(ll x) { p = x; }
};

template <typename t>
class min_pq
{
private:
    size_t size; // holds size of priority queue
    vector<t> v; // vector to hold entries

public:
    min_pq()
    {
        size = 0;
        v.resize(10);
    } // default constructor
    const size_t get_size() // returns size of pq;
    {
        return size;
    }
    void push(const t &x) // insert element into priority queue
    {
        if (is_full())
        {
            v.resize(2 * size + 1);
        }
        size++;
        v[size] = x;
        long long int hole = size;
        percolateup(hole);
    }
    void pop() // pop top element from priority queue
    {
        ll hole = 1;
        v[hole] = v[size];
        size--;
        percolatedown(hole);
    }
    const t &top() // returns top value
    {
        return v[1];
    }
    const bool empty() // returns true if priority queue is empty
    {
        return size == 0;
    }
    bool is_full() // returns vector is full or not used to resize vector based on its current size
    {
        return (v.size() <= size + 1);
    }
    void percolateup(ll hole) // function to percolate up hole used in push
    {
        while (hole > 1 && v[hole / 2] > v[hole])
        {
            t temp = v[hole];
            v[hole] = v[hole / 2];
            v[hole / 2] = temp;
            hole = hole / 2;
        }
    }
    void percolatedown(ll hole)
    {
        while (2 * hole <= size)
        {
            ll child1 = 2 * hole;
            ll child2 = 2 * hole + 1;
            ll min_child = child1;
            if (child2 <= size && v[child2] < v[child1]) // get min child and swap with parent
            {
                min_child = child2;
            }
            if (v[min_child] > v[hole])
            {
                break;
            }
            t temp = v[hole];
            v[hole] = v[min_child];
            v[min_child] = temp;
            hole = min_child;
        }
    }
};

class dijkstra
{
private:
    vector<node> nodes;
    map<string, vector<string>> adjlist; // adjlist for  nodes
    // map<string, node *> node_map;       //map for node id to pointers
    map<pair<string, string>, ll> weight; // map for wight of edges

public:
    dijkstra() {}
    void get_input(ll n, ll m) // get input
    {
        for (ll i = 0; i < n; ++i)
        {
            string id;
            cin >> id;
            node *n = new node(id);
            nodes.push_back(*n);
            // node_map[id] = n;
        }
        for (ll i = 0; i < m; ++i)
        {
            string u, v;
            cin >> u >> v;
            ll w;
            cin >> w;
            weight[{u, v}] = w;
            weight[{v, u}] = w;
            adjlist[u].push_back(v);
            adjlist[v].push_back(u);
        }
    }
    void get_path_len(string source, string sink) // prints even path length from source to sink using dijkjstra algm mainaing even and odd length paths seperately
    {
        map<string, vector<ll>> dist; // mpa for weight of paths from source to all other nodes accoeding to parity (odd and even paths)
        for (auto u : nodes)
        {
            dist[u.get_id()].push_back(INT_MAX);
            dist[u.get_id()].push_back(INT_MAX);
        }
        dist[source][0] = 0;
        min_pq<pair<ll, pair<string, ll>>> pq;
        pq.push({0, {source, 0}});
        while (!pq.empty())
        {
            pair<ll, pair<string, ll>> top = pq.top();
            pq.pop();
            string top_id = top.second.first;
            ll top_dist = top.first;
            ll top_parity = top.second.second;
            ll nxt_parity = abs(1 - top_parity);
            for (auto v : adjlist[top_id])
            {
                ll w = weight[{top_id, v}];
                ll new_possi_dist = top.first + w;
                if (dist[v][nxt_parity] > new_possi_dist)
                {
                    dist[v][nxt_parity] = new_possi_dist;
                    pq.push({new_possi_dist, {v, nxt_parity}});
                }
            }
        }
        if (dist[sink][0] != INT_MAX)
        {
            cout << dist[sink][0] << endl;
        }
        else
        {
            cout << -1 << endl;
        }
    }
};
int main()
{

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    dijkstra dij;
    ll n, m;
    cin >> n >> m;
    dij.get_input(n, m);
    string source, sink;
    cin >> source >> sink;
    dij.get_path_len(source, sink);
}