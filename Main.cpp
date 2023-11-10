#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
    Graph(int vertices);
    void addEdge(int from, int to);
    void findBridges();

private:
    int vertices;
    vector<vector<int>> adj;
    vector<int> disc; 
    vector<int> low;  
    vector<int> parent; 
    int time;

    void DFS(int v);
};

Graph::Graph(int vertices) {
    this->vertices = vertices;
    adj.resize(vertices);
    disc.resize(vertices, -1);
    low.resize(vertices, -1);
    parent.resize(vertices, -1);
    time = 0;
}

void Graph::addEdge(int from, int to) {
    adj[from].push_back(to);
    adj[to].push_back(from);
}

void Graph::DFS(int v) {
    disc[v] = low[v] = ++time;

    for (int neighbor : adj[v]) {
        if (disc[neighbor] == -1) {
            parent[neighbor] = v;
            DFS(neighbor);
            low[v] = min(low[v], low[neighbor]);

            if (low[neighbor] > disc[v]) {
                cout << "Bridge: " << v << " - " << neighbor << endl;
            }
        }
        else if (neighbor != parent[v]) {
            low[v] = min(low[v], disc[neighbor]);
        }
    }
}

void Graph::findBridges() {
    for (int i = 0; i < vertices; ++i) {
        if (disc[i] == -1) {
            DFS(i);
        }
    }
}

int main() {
    int vertices = 9;
    Graph g(vertices);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 3);
    g.addEdge(5, 6);
    g.addEdge(6, 7);
    g.addEdge(7, 8);
    g.addEdge(8, 6);

    cout << "Bridges in the graph:\n";
    g.findBridges();

    return 0;
}
