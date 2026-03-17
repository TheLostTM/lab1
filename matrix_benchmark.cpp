#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

using Matrix = std::vector<double>;

inline double &at(Matrix &m, std::size_t n, std::size_t r, std::size_t c) {
    return m[r * n + c];
}

inline double at(const Matrix &m, std::size_t n, std::size_t r, std::size_t c) {
    return m[r * n + c];
}

Matrix random_matrix(std::size_t n, std::uint32_t seed) {
    std::mt19937 gen(seed);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    Matrix m(n * n);
    for (double &x : m) {
        x = dist(gen);
    }
    return m;
}

Matrix multiply_naive(const Matrix &a, const Matrix &b, std::size_t n) {
    Matrix c(n * n, 0.0);
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            double sum = 0.0;
            for (std::size_t k = 0; k < n; ++k) {
                sum += at(a, n, i, k) * at(b, n, k, j);
            }
            at(c, n, i, j) = sum;
        }
    }
    return c;
}

Matrix transpose(const Matrix &m, std::size_t n) {
    Matrix t(n * n);
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            at(t, n, j, i) = at(m, n, i, j);
        }
    }
    return t;
}

Matrix multiply_cache_friendly(const Matrix &a, const Matrix &b, std::size_t n) {
    Matrix bt = transpose(b, n);
    Matrix c(n * n, 0.0);

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            const std::size_t a_row = i * n;
            const std::size_t bt_row = j * n;
            double sum = 0.0;
            for (std::size_t k = 0; k < n; ++k) {
                sum += a[a_row + k] * bt[bt_row + k];
            }
            c[a_row + j] = sum;
        }
    }
    return c;
}

double checksum(const Matrix &m) {
    double s = 0.0;
    for (double x : m) {
        s += x;
    }
    return s;
}

int main(int argc, char **argv) {
    std::vector<std::size_t> sizes = {256, 512, 768, 1024};
    std::string algo = "cache";

    if (argc >= 2) {
        algo = argv[1];
    }

    if (argc >= 3) {
        sizes.clear();
        for (int i = 2; i < argc; ++i) {
            long n = std::strtol(argv[i], nullptr, 10);
            if (n <= 0) {
                throw std::invalid_argument("Размер матрицы должен быть положительным");
            }
            sizes.push_back(static_cast<std::size_t>(n));
        }
    }

    std::cout << "Алгоритм: " << algo << "\n";
    std::cout << std::left << std::setw(12) << "N"
              << std::setw(16) << "time_sec"
              << std::setw(16) << "checksum" << '\n';

    for (std::size_t n : sizes) {
        Matrix a = random_matrix(n, 42u);
        Matrix b = random_matrix(n, 1337u);

        auto start = std::chrono::steady_clock::now();
        Matrix c;
        if (algo == "naive") {
            c = multiply_naive(a, b, n);
        } else if (algo == "cache") {
            c = multiply_cache_friendly(a, b, n);
        } else {
            throw std::invalid_argument("Неизвестный алгоритм: используйте naive или cache");
        }
        auto end = std::chrono::steady_clock::now();

        std::chrono::duration<double> elapsed = end - start;
        std::cout << std::left << std::setw(12) << n
                  << std::setw(16) << std::fixed << std::setprecision(6) << elapsed.count()
                  << std::setw(16) << std::setprecision(4) << checksum(c) << '\n';
    }

    return 0;
}
