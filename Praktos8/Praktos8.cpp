#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <Windows.h>

class MergeSort {
public:
    void Sort(std::vector<int>& arr) {
        if (arr.size() <= 1) return;

        std::vector<int> left, right;
        for (size_t i = 0; i < arr.size(); ++i) {
            if (i < arr.size() / 2) left.push_back(arr[i]);
            else right.push_back(arr[i]);
        }

        std::thread leftThread(&MergeSort::Sort, this, std::ref(left));
        std::thread rightThread(&MergeSort::Sort, this, std::ref(right));

        leftThread.join();
        rightThread.join();

        Merge(arr, left, right);
    }

private:
    void Merge(std::vector<int>& arr, const std::vector<int>& left, const std::vector<int>& right) {
        size_t i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) arr[k++] = left[i++];
            else arr[k++] = right[j++];
        }
        while (i < left.size()) arr[k++] = left[i++];
        while (j < right.size()) arr[k++] = right[j++];
    }
};

int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    std::vector<int> numbers(10);
    std::cout << "Введите 10 целых чисел: ";
    for (int& num : numbers) std::cin >> num;

    MergeSort sorter;
    std::thread mergeSortThread(&MergeSort::Sort, &sorter, std::ref(numbers));
    mergeSortThread.join();

    std::cout << "Отсортированный массив: ";
    for (int num : numbers) std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}