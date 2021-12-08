#include <algorithm>
#include <vector>
#include <numeric>
#include <iostream>
#include <climits>
 
using namespace std;
 
class Graph {
private:
    vector<vector<int>> graph_matrix;
    int vertices_amount;
    bool graph_type;
 
public:
    Graph(int n, bool type) {
        graph_type = type;
 
        vertices_amount = n+1;
        graph_matrix.resize(vertices_amount);
        for (int i = 0; i < vertices_amount; ++i) {
            graph_matrix[i].resize(vertices_amount, 0);
        }
    }
 
    void add_edge(int u, int v, int weight) {
        if (graph_type) {
            graph_matrix[u][v] = weight;
            graph_matrix[v][u] = weight;
        } else {
            graph_matrix[u][v] = weight;
        }
    }
 
    void print() {
        for (int i = 0; i < vertices_amount; ++i) {
            for (int j = 0; j < vertices_amount; ++j) {
                if (i == 0 && j == 0) {
                    cout << "  ";
                } else if (i == 0) {
                    cout << j << " ";
                } else if (j == 0) {
                    cout << i << " ";
                } else {
                    cout << graph_matrix[i][j] << " ";
                }
            }
            cout << "\n";
        }
    }
 
    void dijkstra(int s, int to) {
        vector<int> used(vertices_amount, false), paths_len(vertices_amount, INT_MAX), parents(vertices_amount, -1);
        paths_len[s] = 0;
        int v;
 
        for (int i = 1; i < vertices_amount; ++i) {
            v = -1;
            for (int j = 1; j < vertices_amount; ++j) {
                if (!used[j] && (v == -1 || paths_len[j] < paths_len[v])) {
                    v = j;
                }
            }
            if (paths_len[v] == INT_MAX) {
                break;
            }
            used[v] = true;
            for (int e = 1; e < vertices_amount; ++e) {
                if (graph_matrix[v][e] != 0) {
                    if (paths_len[v] + graph_matrix[v][e] < paths_len[e]) {
                        paths_len[e] = paths_len[v] + graph_matrix[v][e];
                        parents[e] = v;
                    }
                }
            }
        }
 
        if (paths_len[to] == INT_MAX) {
            cout << "Нет пути между двумя заданными вершинами.\n";
            return;
        }
 
        vector<int> path;
 
        int i = to;
        path.push_back(i);
 
        while (parents[i] != -1) {
            i = parents[i];
            path.push_back(i);
        }
        reverse(path.begin(), path.end());
 
        cout << "Длина крайтчашего пути между заданнами вершинами: " << paths_len[to] << "\n";
        cout << "Путь: ";
        for (auto& c : path) {
            cout << c << " ";
        }
        cout << "\n";
    }
 
    void dfs(int s, vector<int>& visited) {
        visited[s] = true;
 
        for (int v = 1; v < vertices_amount; ++v) {
            if (graph_matrix[s][v] && !visited[v]) {
                dfs(v, visited);
            }
        }
    }
 
    void is_connected() {
        vector<int> visited(vertices_amount, false);
 
        dfs(1, visited);
 
        int count = accumulate(visited.begin(), visited.end(), 0);
        if (vertices_amount-1 == count) {
            cout << "Граф связный.\n";
        } else {
            cout << "Граф связный.\n";
        }
    }
 
};
 
 
void menu() {
    cout << "1. Добавить ребра\n";
    cout << "2. Вывести граф\n";
    cout << "3. Найти кратчайший путь от одной вершины до другой\n";
    cout << "4. Проверка на связность\n";
    cout << "0. Выход\n";
    cout << "~\n";
}
 
int main() {
    bool type;
    int n;
    cout << "Введите 1, если граф неориентированный и 0 иначе:\n";
    cin >> type;
    cout << "Введите количество вершин:\n";
    cin >> n;
    Graph g(n, type);
    int op = -1;
    int u, v, weight;
    while (op != 0) {
        menu();
        cin >> op;
        if (op == 1) {
            int count;
            cout << "Введите количество ребер:\n";
            cin >> count;
            cout << "Введите начальную вершину, конечную и вес ребра:\n";
            for (int i = 0; i < count; ++i) {
                cin >> u >> v >> weight;
                g.add_edge(u, v, weight);
            }
        } else if (op == 2) {
            g.print();
        } else if (op == 3) {
            cout << "Введите начальную и конечную вершины:\n";
            cin >> u >> v;
            g.dijkstra(u, v);
 
        } else if (op == 4) {
            g.is_connected();
        }
    }
}
