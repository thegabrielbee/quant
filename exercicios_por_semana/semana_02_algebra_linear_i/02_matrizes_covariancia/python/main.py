"""
Matrizes - Matriz de covariancia e risco de portfolio

Este arquivo segue a mesma ordem da secao "Formulas por exercicio" do README.md.
Implemente de cima para baixo, passos 1 a 9.
"""

from __future__ import annotations

from math import sqrt


RETURNS = [
    [0.010, 0.004, -0.002],
    [0.006, 0.002, 0.001],
    [-0.012, -0.006, 0.003],
    [0.015, 0.008, -0.004],
    [-0.004, -0.001, 0.002],
    [0.009, 0.005, -0.001],
]

WEIGHTS = [0.50, 0.30, 0.20]
PERIODS_PER_YEAR = 252


def column_means(matrix: list[list[float]]) -> list[float]:
    m = [0]*len(matrix[0])
    for i, l in enumerate(matrix):
        for j, vl in enumerate(l):
            m[j] += vl

    m = [v/len(matrix) for v in m] 
    return m

def center_matrix(matrix: list[list[float]], means: list[float]) -> list[list[float]]:
    c = [[[0] for _ in range(len(matrix[0]))] for _ in range(len(matrix))]
    for i, l in enumerate(matrix):
        for j, vc in enumerate(l):
            c[i][j] = vc - means[j]
    return c

def transpose(matrix: list[list[float]]) -> list[list[float]]:
    t = [[0 for _ in range(len(matrix))] for _ in range(len(matrix[0]))]
    for i in range(len(matrix)):
        for j in range(len(matrix[0])):
            t[j][i] = matrix[i][j]
    return t

def matrix_shape(matrix: list[list[float]]) -> tuple[int, int]:
    raise NotImplementedError


def validate_rectangular(matrix: list[list[float]]) -> None:
    raise NotImplementedError


def validate_matmul_dimensions(a: list[list[float]], b: list[list[float]]) -> None:
    raise NotImplementedError


def matmul(a: list[list[float]], b: list[list[float]]) -> list[list[float]]:
    m = [[0 for _ in range(len(b[0]))] for _ in range(len(a))]
    for i in range(len(a)):
        for j in range(len(b[0])):
            v = 0
            for k in range(len(a[0])):
                v += a[i][k] * b[k][j]
            m[i][j] = v
    return m
    

def matvec(matrix: list[list[float]], vector: list[float]) -> list[float]:
    cw = [0 for _ in range(len(matrix[0]))]
    for i in range(len(matrix)):
        v = 0
        for j in range(len(matrix[0])):
            v += matrix[i][j]*vector[j]
        cw[i] = v
    return cw

def covariance_matrix(centered: list[list[float]]) -> list[list[float]]:
    m = matmul(transpose(centered), centered)
    n = len(centered)-1
    for i in range(len(m)):
        for j in range(len(m[0])):
            m[i][j] = m[i][j] / n 
    return m

def dot(u: list[float], v: list[float]) -> float:
    return sum(x * y for x, y in zip(u, v))


def quadratic_form(weights: list[float], cw: list[float]) -> float:
    return dot(weights, cw)


def daily_volatility(portfolio_variance: float) -> float:
    return sqrt(portfolio_variance)


def annualized_volatility(daily_vol: float, periods_per_year: int) -> float:
    return daily_vol * sqrt(periods_per_year)


def print_vector(name: str, values: list[float]) -> None:
    formatted = ", ".join(f"{value:.6f}" for value in values)
    print(f"{name} = [{formatted}]")


def print_matrix(name: str, matrix: list[list[float]]) -> None:
    print(f"{name} = [")
    for row in matrix:
        formatted = ", ".join(f"{value:.6f}" for value in row)
        print(f"    [{formatted}],")
    print("]")


def run_exercise() -> dict[str, float]:
    """Executa os 9 passos do README.md."""

    # 1. Media de retorno de cada ativo.
    means = column_means(RETURNS)

    # 2. Matriz de retornos centralizados.
    centered = center_matrix(RETURNS, means)

    # 3. Matriz transposta Xc'.
    centered_t = transpose(centered)

    # 4. Matriz de covariancia amostral.
    covariance = covariance_matrix(centered)

    # 5. Vetor intermediario Cw.
    cw = matvec(covariance, WEIGHTS)

    # 6. Variancia diaria do portfolio.
    portfolio_variance = quadratic_form(WEIGHTS, cw)

    # 7. Volatilidade diaria do portfolio.
    daily_vol = daily_volatility(portfolio_variance)

    # 8. Volatilidade anualizada do portfolio.
    annual_vol = annualized_volatility(daily_vol, PERIODS_PER_YEAR)

    # 9. Conclusao sobre diversificacao.
    conclusion = "preencha depois de analisar a matriz de covariancia"

    print("1. Media de retorno de cada ativo")
    print_vector("means", means)
    print()

    print("2. Matriz de retornos centralizados")
    print_matrix("centered", centered)
    print()

    print("3. Matriz transposta Xc'")
    print_matrix("centered_t", centered_t)
    print()

    print("4. Matriz de covariancia amostral")
    print_matrix("covariance", covariance)
    print()

    print("5. Vetor intermediario Cw")
    print_vector("cw", cw)
    print()

    print("6. Variancia diaria do portfolio")
    print(f"portfolio_variance = {portfolio_variance:.6f}")
    print()

    print("7. Volatilidade diaria do portfolio")
    print(f"daily_vol = {daily_vol:.6f}")
    print()

    print("8. Volatilidade anualizada do portfolio")
    print(f"annual_vol = {annual_vol:.6f}")
    print()

    print("9. Conclusao")
    print(conclusion)

    return {
        "portfolio_variance": portfolio_variance,
        "daily_vol": daily_vol,
        "annual_vol": annual_vol,
    }


def main() -> None:
    print("Matrizes - Matriz de covariancia e risco de portfolio")
    print("Siga os passos 1 a 9 do README.md.")
    print()
    run_exercise()


if __name__ == "__main__":
    main()
