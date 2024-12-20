#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <queue>
#include <limits>
#include <utility>
#include <functional> // для std::bind

using namespace std;

double calculateEMA(const std::vector<double>& data, double alpha) {
    double ema = data[0]; 
    for (size_t i = 1; i < data.size(); ++i) {
        ema = alpha * data[i] + (1 - alpha) * ema;
    }
    return ema;
}

void emaSearchStr(int repetitions) {
    std::vector<double> data;
    for (int i = 0; i < 1000; ++i) {
        data.push_back(static_cast<double>(rand()) / RAND_MAX);
    }

    for (int i = 0; i < repetitions; ++i) {
        double result = calculateEMA(data, 0.1); // alpha = 0.1
    }
}

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
        dijkstra(graph, 0); // Запускаем алгоритм Дейкстры от вершины 0
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Использование: " << argv[0] << " <количество повторений ema> <количество повторений sp>" << std::endl;
        return 1;
    }

    int emaRepetitions = std::stoi(argv[1]);
    int spRepetitions = std::stoi(argv[2]);

    clock_t start = clock();

    std::thread emaThread(emaSearchStr, emaRepetitions);
    std::thread spThread(shortPath, spRepetitions);

    emaThread.join();
    spThread.join();

    clock_t end = clock();

    double elapsed_time = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Общее время выполнения: " << elapsed_time << " секунд" << std::endl;

    return 0;
}