#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int a;
    int b;
    int time;
    int cost;

    Edge(int u, int v, int t, int c) : a(u), b(v), time(t), cost(c) { }
};

bool smaller_time(const Edge&x, const Edge &y) {
    return x.time < y.time;
}

bool smaller_cost(const Edge &x, const Edge &y) {
    return x.cost < y.cost;
}

struct Graph {
    int number;
    vector<Edge> edges;

    Graph(const int n): number(n) {}

    inline void add_edge(const int &city1, const int &city2, const int &travel_time, const int &building_cost) {
        Edge e = Edge(city1, city2, travel_time, building_cost);
        edges.push_back(e);
    }

    inline void sort_cost() {
        sort(edges.begin(), edges.end(), smaller_cost);
    }

    inline void sort_time() {
        sort(edges.begin(), edges.end(), smaller_time);
    }
};

int find(vector<int> &par, int cur) {
    int shortener = cur;
    while(cur != par[cur]) {
        cur = par[cur];
    }
    while(shortener != cur) {
        int old = shortener;
        shortener = par[shortener];
        par[old] = cur;
    }
    return cur;
}

bool unite(vector<int> &par, const int a, const int b) {
    int para = find(par, a);
    int parb = find(par, b);
    if(para != parb) {
        par[para] = parb;
        return true;
    }
    return false;
}

int min_span_tree(const Graph &graph, const int cities) {
    int needed_edges = cities - 1;
    vector<int> parents(cities);
    for(int i = 0; i < cities; i++) { parents[i] = i; }
    int i = 0;
    int cost = 0;
    while(needed_edges > 0) {
        Edge edge = graph.edges[i];
        i++;
        if(unite(parents, edge.a, edge.b)) {
            cost += edge.cost;
            needed_edges--;
        }
    }
    return cost;
}

int main() {
    int n; // number of islands
    cin >> n;
    while(n--) {
        int v; // number of cities
        int e; // number of roads
        cin >> v >> e;
        Graph graph = Graph(e);
        for(int i = 0; i < e; i++) {
            int a, b; // city codes
            int t, c; // travel time and cost
            cin >> a >> b >> t >> c;
            graph.add_edge(a, b, t, c);
        }

        // find minimal spanning tree with union/find
        // for cost sorted
        graph.sort_cost();
        int cost1 = min_span_tree(graph, v);

        // for time sorted
        graph.sort_time();
        int cost2 = min_span_tree(graph, v);

        if(cost1 == cost2) {
            cout << "yes\n";
        }
        else {
            cout << "no\n";
        }
    }
}
