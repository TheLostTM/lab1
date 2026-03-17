# Лабораторная работа №1 — последовательное умножение матриц

## Что в репозитории
- `matrix_benchmark.cpp` — программа на C++ (алгоритмы `naive` и `cache` + замеры времени).
- `REPORT.md` — полный шаблон отчёта с формулами, таблицами и местами для скриншотов.
- `WORD_GOST_TEMPLATE.md` — требования к оформлению в Word под ГОСТ/методичку.
- `NEW_REPO_SETUP.md` — как вынести работу в отдельный новый репозиторий.

## Сборка
```bash
g++ -std=c++17 -O2 -march=native -o matmul_O2 matrix_benchmark.cpp
g++ -std=c++17 -O3 -march=native -o matmul_O3 matrix_benchmark.cpp
```

## Запуск
```bash
./matmul_O2 cache 5 256 512 768 1024
./matmul_O3 cache 5 256 512 768 1024
./matmul_O3 naive 3 256 512
```

Формат аргументов:
```bash
./matmul_<opt> <algo> <runs> <N1> <N2> ...
```
где `<algo>` = `naive` или `cache`.
