#include <iostream>
#include <vector>

using namespace std;

struct Run {
    int value;
    int count;
};

vector<Run> pack(const int arr[], int n) {
    vector<Run> result;
    if (n == 0) return result;

    int current = arr[0];
    int count = 1;

    for (int i = 1; i < n; ++i) {
        if (arr[i] == current) {
            count++;
        }
        else {
            result.push_back({ current, count });
            current = arr[i];
            count = 1;
        }
    }
    result.push_back({ current, count });
    return result;
}

void unpack(const vector<Run>& packed, int arr[], int& n) {
    int index = 0;
    for (const auto& run : packed) {
        for (int i = 0; i < run.count; ++i) {
            arr[index++] = run.value;
        }
    }
    n = index;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    const int N = 10000;
    int* originalArray = new int[N];

    int index = 0;
    for (int value = 0; value <= 17 && index < N; ++value) {
        int repeatCount = (value + 1) * 30;
        if (index + repeatCount > N) repeatCount = N - index;

        for (int j = 0; j < repeatCount; ++j) {
            originalArray[index++] = value;
        }
    }

    vector<Run> packed = pack(originalArray, N);

    cout << "Исходный размер: " << N << " элементов\n";
    cout << "Размер после упаковки: " << packed.size() << " серий\n";
    cout << "Сжатие: " << (double)(N * sizeof(int)) / (packed.size() * sizeof(Run)) << "x\n\n";

    int* restoredArray = new int[N];
    int restoredSize;
    unpack(packed, restoredArray, restoredSize);

    bool match = true;
    for (int i = 0; i < N; ++i) {
        if (originalArray[i] != restoredArray[i]) {
            match = false;
            break;
        }
    }

    cout << (match ? "Массивы совпадают!\n" : "Массивы не совпадают!\n");

    delete[] originalArray;
    delete[] restoredArray;

    return 0;
}