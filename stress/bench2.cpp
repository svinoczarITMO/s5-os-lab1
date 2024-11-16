#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <ctime>
#include <utility>

using namespace std;

void dijkstra(const vector<vector<pair<int, int> > >& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, numeric_limits<int>::max());
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push(make_pair(0, start)); 

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v)); 
            }
        }
    }
}

void shortPath(int repetitions) {
    // Создаем граф с 1000 вершинами и случайными ребрами
    int n = 1000;
    vector<vector<pair<int, int> > > graph(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 10; ++j) { // Каждая вершина соединена с 10 случайными
            int v = rand() % n;
            int weight = rand() % 10 + 1; // Вес ребра от 1 до 10
            graph[i].push_back(make_pair(v, weight));
        }
    }

    for (int i = 0; i < repetitions; ++i) {
        dijkstra(graph, 0); // 
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: " << argv[0] << " <количество повторений>" << std::endl;
        return 1;
    }

    int repetitions = std::stoi(argv[1]);

    clock_t start = clock();
    shortPath(repetitions);
    clock_t end = clock();

    double elapsed_time = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Время выполнения short-path: " << elapsed_time << " секунд" << std::endl;

    return 0;
}