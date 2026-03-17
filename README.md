# Лабораторная работа №1

- Код программы: `matrix_benchmark.cpp`
- Готовый шаблон отчёта: `REPORT.md`

Быстрый старт:

```bash
g++ -std=c++17 -O2 -march=native -o matmul_O2 matrix_benchmark.cpp
g++ -std=c++17 -O3 -march=native -o matmul_O3 matrix_benchmark.cpp
./matmul_O2 cache 256 512 768 1024
./matmul_O3 cache 256 512 768 1024
```
