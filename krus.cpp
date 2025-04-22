#include<iostream>
using namespace std;

#define MAX 5
#define INF 999999

int parent[MAX];

int find(int i) {
    while (i != parent[i])
        i = parent[i];
    return i;
}

void union_set(int u, int v) {
    parent[find(u)] = find(v);
}

int main() {
    int V;
    string dept[MAX];
    int G[MAX][MAX];

    cout << "Enter number of departments: ";
    cin >> V;

    cout << "Enter department names:\n";
    for (int i = 0; i < V; i++) {
        cout << "Department " << i << " : ";
        cin >> dept[i];
        parent[i] = i;  // Initialize parent
    }

    cout << "Enter distance between departments:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << "Distance between " << dept[i] << " and " << dept[j] << ": ";
            cin >> G[i][j];
        }
    }

    cout << "\nMST using Kruskal's Algorithm:\n";
    int edges = 0, total = 0;

    while (edges < V - 1) {
        int min = INF, u = 0, v = 0;

        // Find the smallest edge that doesn't form a cycle
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i != j && find(i) != find(j) && G[i][j] < min && G[i][j] != 0) {
                    min = G[i][j];
                    u = i;
                    v = j;
                }
            }
        }

        // Add the selected edge to MST
        if (find(u) != find(v)) {
            union_set(u, v);
            cout << dept[u] << " - " << dept[v] << " : " << min << endl;
            total += min;
            edges++;
        }
    }

    cout << "Total cost of MST: " << total << endl;
    return 0;
}