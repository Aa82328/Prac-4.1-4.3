```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Структура для представления ребра графа
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Структура Union-Find (Disjoint Set Union - DSU)
class UnionFind {
private:
    vector<int> parent, rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i; // Изначально каждый элемент - корень своего множества
        }
    }

    // Найти корень множества с компрессией пути
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Рекурсивный вызов с присвоением корня
        }
        return parent[x];
    }

    // Объединить два множества по рангу
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            // Прикрепляем дерево меньшего ранга к корню дерева большего ранга
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Функция для нахождения минимального остовного дерева
pair<vector<Edge>, int> kruskalMST(int numVertices, vector<Edge>& edges) {
    // 1. Сортировка ребер по весу
    sort(edges.begin(), edges.end());

    UnionFind dsu(numVertices);
    vector<Edge> mst; // Результат: список ребер MST
    int totalWeight = 0;

    // 2. Перебор отсортированных ребер
    for (const Edge& e : edges) {
        // 3. Проверка на цикл с помощью Union-Find
        if (dsu.find(e.u) != dsu.find(e.v)) {
            // Цикла нет, добавляем ребро в MST
            mst.push_back(e);
            totalWeight += e.weight;
            // 4. Объединяем множества вершин u и v
            dsu.unite(e.u, e.v);

            // 5. Оптимизация: если MST содержит n-1 ребро, можно завершить
            if (mst.size() == numVertices - 1) {
                break;
            }
        }
    }

    return {mst, totalWeight};
}

int main() {
    // Пример входных данных: 6 вершин (0-5), 9 ребер
    int numVertices = 6;
    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 3}, {1, 2, 1}, {1, 3, 2},
        {2, 3, 4}, {2, 4, 2}, {3, 4, 3}, {3, 5, 2}, {4, 5, 6}
    };

    auto [mstEdges, totalWeight] = kruskalMST(numVertices, edges);

    cout << "Ребра минимального остовного дерева:" << endl;
    for (const Edge& e : mstEdges) {
        cout << e.u << " - " << e.v << " (вес " << e.weight << ")" << endl;
    }
    cout << "Общий вес MST: " << totalWeight << endl;

    return 0;
}
```
