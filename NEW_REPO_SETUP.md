# Как вынести эту лабораторную в новый репозиторий

## 1) Создай папку и скопируй файлы
Минимальный набор:
- `matrix_benchmark.cpp`
- `README.md`
- `REPORT.md`
- `WORD_GOST_TEMPLATE.md`
- папка `screenshots/`

## 2) Инициализация git
```bash
git init
git add .
git commit -m "Initial commit: Lab1 sequential matrix multiplication"
```

## 3) Привязка к GitHub
```bash
git branch -M main
git remote add origin https://github.com/<your_name>/<repo_name>.git
git push -u origin main
```

## 4) Рекомендуемое имя репозитория
`lab1-sequential-matrix-multiplication`
