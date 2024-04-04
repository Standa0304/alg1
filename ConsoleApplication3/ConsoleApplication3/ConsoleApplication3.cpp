#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

void selectionSort(std::vector<int>& pole) {
    int min = 0;
    int pom = 0;

    for (size_t i = 0; i < pole.size() - 1; i++) {
        min = pole[i];
        for (size_t j = i + 1; j < pole.size(); j++) {
            if (pole[j] < min) {
                pom = pole[j];
                pole[j] = min;
                min = pom;
            }
            pole[i] = min;
        }
    }
}

void bubbleSort(std::vector<int>& pole) {
    int pom2 = 0;

    for (size_t i = 0; i < pole.size() - 1; i++) {
        for (size_t j = 0; j < pole.size() - 1; j++) {
            if (pole[j] > pole[j + 1]) {
                pom2 = pole[j];
                pole[j] = pole[j + 1];
                pole[j + 1] = pom2;
            }
        }
    }
}


void Leftto(std::vector<int>& pole, int& left, int& right) {
    int j = 0;
    for (int i = left; i < right - 1; i++) {
        if (pole[i] > pole[i + 1]) {
            std::swap(pole[i], pole[i + 1]);
            j = i;
        }
    }
    right = j;
}

void Rightto(std::vector<int>& pole, int& left, int& right) {
    int j = 0;
    for (int i = right; i >= left + 1; i--) {
        if (pole[i - 1] > pole[i]) {
            std::swap(pole[i - 1], pole[i]);
            j = i;
        }
    }
    left = j;
}

void shaker(std::vector<int>& pole) {
    int left = 0;
    int right = pole.size();

    while (left <= right) {
        Leftto(pole, left, right);
        if (left >= right) break;
        Rightto(pole, left, right);
        if (left >= right) break;
    }
}

std::vector<int> generate(int lenght, int minVal, int maxVal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(minVal, maxVal);

    std::vector<int> result;
    result.reserve(lenght);

    for (int i = 0; i < lenght; i++) {
        result.push_back(distribution(gen));
    }

    return result;

}

int main() {

    std::vector<int> pole = generate(10, 0, 100);

    std::cout << "před" << std::endl;
    for (int i = 0; i < pole.size(); i++) {
        std::cout << pole[i] << " ";
    }

    auto start = std::chrono::high_resolution_clock::now();
    shaker(pole);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Time: " << duration.count() << " sec" << std::endl;

    std::cout << "po" << std::endl;
    for (int i = 0; i < pole.size(); i++) {
        std::cout << pole[i] << " ";
    }

    auto star = std::chrono::high_resolution_clock::now();
    bubbleSort(pole);
    auto en = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duratio = en - star;
    std::cout << "Time: " << duratio.count() << " sec" << std::endl;

    auto sta = std::chrono::high_resolution_clock::now();
    selectionSort(pole);
    auto e = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durati = e - sta;
    std::cout << "Time: " << durati.count() << " sec" << std::endl;

    return 0;
}


// T(n) = 5T(n-1)
// T(4) = 5T(3)
// T(3) = 5*5T(2)
// T(2) = 5*5*5T(1)
// T(1) = 5*5*5*5T(0)
// T(0) = 5*5*5*5*1

//T(n) = 5^n


/*    std::cout << "před" << std::endl;
    for (int i = 0; i < pole.size(); i++) {
        std::cout << pole[i] << " ";
    }
    shaker(pole);
    std::cout << "po" << std::endl;
    for (int i = 0; i < pole.size(); i++) {
        std::cout << pole[i] << " ";
    }
    std::cout << "konec" << std::endl;*/
