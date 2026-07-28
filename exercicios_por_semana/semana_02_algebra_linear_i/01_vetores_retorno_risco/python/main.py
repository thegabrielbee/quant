"""
Vetores - Retorno, risco e similaridade como operacoes vetoriais

Este arquivo segue a mesma ordem da secao "Formulas por exercicio" do README.md.
Implemente de cima para baixo, passos 1 a 10.
"""

from __future__ import annotations

from math import sqrt


# Dados de partida do exercicio.
STRATEGY = [0.012, -0.004, 0.006, 0.010, -0.008, 0.003, 0.007, -0.002]
MARKET = [0.010, -0.006, 0.004, 0.011, -0.010, 0.002, 0.006, -0.003]
RISK_FREE_DAILY = 0.0002


def mean(values: list[float]) -> float:
    """Media simples: soma(values) / quantidade."""
    return sum(values) / len(values)


def subtract_scalar(values: list[float], scalar: float) -> list[float]:
    """Subtrai o mesmo numero de todos os elementos do vetor."""
    return [xi-scalar for xi in values]


def dot(u: list[float], v: list[float]) -> float:
    """Produto interno: u[0]*v[0] + ... + u[n-1]*v[n-1]."""
    return sum(ui * vi for ui, vi in zip(u, v))


def norm_l2(u: list[float]) -> float:
    """Norma L2: sqrt(dot(u, u))."""
    # TODO: use dot(u, u) e sqrt.
    return sqrt(dot(u,u))
    


def cosine_similarity(u: list[float], v: list[float]) -> float:
    """Similaridade de cosseno: dot(u, v) / (norm(u) * norm(v))."""
    return dot(u, v) / (norm_l2(u) * norm_l2(v))


def projection_beta(strategy_excess: list[float], market_excess: list[float]) -> float:
    """Beta da estrategia em relacao ao mercado."""
    return dot(strategy_excess, market_excess) / dot(market_excess, market_excess)

def scale_vector(beta: float, values: list[float]) -> list[float]:
    """Multiplica todos os elementos do vetor por beta."""
    # TODO: implemente beta * values[i] para cada i.
    return [x*beta for x in values]


def subtract_vectors(u: list[float], v: list[float]) -> list[float]:
    """Subtrai dois vetores elemento a elemento: u[i] - v[i]."""
    return [ui - vi for ui, vi in zip(u, v)]



def print_vector(name: str, values: list[float]) -> None:
    formatted = ", ".join(f"{value:.6f}" for value in values)
    print(f"{name} = [{formatted}]")


def run_exercise() -> dict[str, float]:
    """Executa os 10 passos do README.md."""

    # 1. Retorno medio da estrategia.
    mean_strategy = mean(STRATEGY)

    # 2. Retorno medio do mercado.
    mean_market = mean(MARKET)

    # 3. Excesso de retorno da estrategia.
    strategy_excess = subtract_scalar(STRATEGY, RISK_FREE_DAILY)

    # 4. Excesso de retorno do mercado.
    market_excess = subtract_scalar(MARKET, RISK_FREE_DAILY)

    # 5. Beta da estrategia em relacao ao mercado.
    beta = projection_beta(strategy_excess, market_excess)

    # 6. Cosine similarity entre estrategia e mercado.
    similarity = cosine_similarity(strategy_excess, market_excess)

    # 7. Vetor projetado: parte explicada pelo mercado.
    explained = scale_vector(beta, market_excess)

    # 8. Vetor residual: parte nao explicada pelo mercado.
    residual = subtract_vectors(strategy_excess, explained)

    # 9. Norma do residual.
    norm_explained = norm_l2(explained)
    norm_residual = norm_l2(residual)

    # 10. Conclusao: alpha proprio ou exposicao ao mercado?
    if beta > 0.8 and similarity > 0.9 and norm_residual < norm_explained:
        conclusion = "forte exposicao ao mercado; pouco alpha proprio neste exemplo"
    else:
        conclusion = "ha residual relevante; investigar se existe alpha proprio"

    print("1. Retorno medio da estrategia")
    print(f"mean_strategy = {mean_strategy:.6f}")
    print()

    print("2. Retorno medio do mercado")
    print(f"mean_market = {mean_market:.6f}")
    print()

    print("3. Excesso de retorno da estrategia")
    print_vector("strategy_excess", strategy_excess)
    print()

    print("4. Excesso de retorno do mercado")
    print_vector("market_excess", market_excess)
    print()

    print("5. Beta da estrategia em relacao ao mercado")
    print(f"beta = {beta:.6f}")
    print()

    print("6. Cosine similarity entre estrategia e mercado")
    print(f"cosine_similarity = {similarity:.6f}")
    print()

    print("7. Vetor projetado: parte explicada pelo mercado")
    print_vector("explained", explained)
    print(f"norm_explained = {norm_explained:.6f}")
    print()

    print("8. Vetor residual: parte nao explicada pelo mercado")
    print_vector("residual", residual)
    print()

    print("9. Norma do residual")
    print(f"norm_residual = {norm_residual:.6f}")
    print()

    print("10. Conclusao")
    print(conclusion)

    return {
        "mean_strategy": mean_strategy,
        "mean_market": mean_market,
        "beta": beta,
        "cosine_similarity": similarity,
        "norm_explained": norm_explained,
        "norm_residual": norm_residual,
    }


def main() -> None:
    print("Vetores - Retorno, risco e similaridade como operacoes vetoriais")
    print("Siga os passos 1 a 10 do README.md.")
    print()
    run_exercise()


if __name__ == "__main__":
    main()
