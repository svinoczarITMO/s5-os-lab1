#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

double calculateEMA(const std::vector<double>& data, double alpha) {
    double ema = data[0]; // Начальное значение
    for (size_t i = 1; i < data.size(); ++i) {
        ema = alpha * data[i] + (1 - alpha) * ema;
    }
    return ema;
}

void emaSearchStr(int repetitions) {
    std::vector<double> data;
    // Генерация случайных значений
    for (int i = 0; i < 1000; ++i) {
        data.push_back(static_cast<double>(rand()) / RAND_MAX);
    }

    for (int i = 0; i < repetitions; ++i) {
        double result = calculateEMA(data, 0.1); // alpha = 0.1
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Использование: " << argv[0] << " <количество повторений>" << std::endl;
        return 1;
    }

    int repetitions = std::stoi(argv[1]);

    clock_t start = clock();
    emaSearchStr(repetitions);
    clock_t end = clock();

    double elapsed_time = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Время выполнения ema-search-str: " << elapsed_time << " секунд" << std::endl;

    return 0;
}