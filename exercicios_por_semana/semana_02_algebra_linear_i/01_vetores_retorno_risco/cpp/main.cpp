/*
Vetores - Retorno, risco e similaridade como operacoes vetoriais

Objetivo:
Usar produto interno, norma e projecao para comparar uma estrategia com o mercado.

Dados de partida:
- strategy = [0.012, -0.004, 0.006, 0.010, -0.008, 0.003, 0.007, -0.002]
- market   = [0.010, -0.006, 0.004, 0.011, -0.010, 0.002, 0.006, -0.003]
- risk_free_daily = 0.0002

O que fazer em C++:
1. guardar os retornos em vector<double>
2. implementar funcoes dot, norm_l2 e projection_scale
3. calcular cos(strategy_excess, market_excess)
4. calcular residual = strategy_excess - beta * market_excess
5. imprimir beta, norma do residual e cosine similarity

Saidas esperadas:
- beta/projecao da estrategia no mercado
- cosine similarity entre estrategia e mercado
- norma do residual que nao foi explicado pelo mercado
*/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

struct ExerciseMetrics {
    double primary = 0.0;
    double secondary = 0.0;
};

double mean(const std::vector<double>& values) {
    double s = 0;
    for(double v: values)
        s +=v;

    return s / values.size();
}

std::vector<double> scale_vector(double beta, const std::vector<double>& values){
    std::vector<double> sv(values.size());
    for(auto i{0uz};i<values.size();i++)
        sv[i] = beta * values[i];

    return sv;
}

std::vector<double> subtract_scalar(const std::vector<double>& values, double scalar){
    std::vector<double> sv(values.size());
    for(auto i{0uz};i<values.size();i++)
        sv[i] = values[i] - scalar;

    return sv;
}


double dot(std::vector<double> u, std::vector<double> v){
    std::vector<double> mv(u.size());
    double d = 0;
    for(auto i{0uz};i<u.size();i++)
        mv[i] = u[i] * v[i];

    for(auto i{0uz};i<u.size();i++)
        d += mv[i];

    return d;
}



double norm_l2(const std::vector<double>& u){
    return std::sqrt(dot(u,u));
}


double cosine_similarity(const std::vector<double>& u, const std::vector<double>& v){
    return dot(u, v) / (norm_l2(u) * norm_l2(v));
}

double projection_beta(const std::vector<double>& strategy_excess, const std::vector<double>& market_excess) {
    return dot(strategy_excess, market_excess) / dot(market_excess, market_excess);
}


std::vector<double> subtract_vectors(const std::vector<double>& u, const std::vector<double>& v) {
    std::vector<double> s(u.size());

    for(auto i{0uz};i<u.size();i++)
        s[i] = u[i] - v[i];

    return s;
}

std::string format_vector(const std::vector<double>& values) {
    std::ostringstream out;

    out << std::fixed << std::setprecision(6);
    out << "[";

    for (std::size_t i{0}; i < values.size(); ++i) {
        if (i > 0) {
            out << ", ";
        }

        out << values[i];
    }

    out << "]";

    return out.str();
}

void print_vector(const std::string& name, const std::vector<double>& values){
    std::cout << "Vector " << name <<  ": " << format_vector(values);
}

// Escreva as implementacoes das funcoes declaradas acima.
// A estrutura de run_exercise() abaixo mostra onde cada funcao sera usada.

ExerciseMetrics run_exercise() {
    const std::vector<double> strategy{0.012, -0.004, 0.006, 0.010, -0.008, 0.003, 0.007, -0.002};
    const std::vector<double> market{0.010, -0.006, 0.004, 0.011, -0.010, 0.002, 0.006, -0.003};
    const double risk_free_daily = 0.0002;
    
    // 1. Retorno medio da estrategia.
    const double mean_strategy = mean(strategy);

    // 2. Retorno medio do mercado.
    const double mean_market = mean(market);

    // 3. Excesso de retorno da estrategia.
    const std::vector<double> strategy_excess = subtract_scalar(strategy, risk_free_daily);

    // 4. Excesso de retorno do mercado.
    const std::vector<double> market_excess = subtract_scalar(market, risk_free_daily);

    // 5. Beta da estrategia em relacao ao mercado.
    const double beta = projection_beta(strategy_excess, market_excess);

    // 6. Cosine similarity entre estrategia e mercado.
    const double similarity = cosine_similarity(strategy_excess, market_excess);

    // 7. Vetor projetado: parte explicada pelo mercado.
    const std::vector<double> explained = scale_vector(beta, market_excess);

    // 8. Vetor residual: parte nao explicada pelo mercado.
    const std::vector<double> residual = subtract_vectors(strategy_excess, explained);

    // 9. Norma do residual.
    const double norm_explained = norm_l2(explained);
    const double norm_residual = norm_l2(residual);

    // 10. Conclusao: alpha proprio ou exposicao ao mercado?
    const std::string conclusion =
        beta > 0.8 && similarity > 0.9 && norm_residual < norm_explained
            ? "forte exposicao ao mercado; pouco alpha proprio neste exemplo"
            : "ha residual relevante; investigar se existe alpha proprio";

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "1. Retorno medio da estrategia\n";
    std::cout << "mean_strategy = " << mean_strategy << "\n\n";

    std::cout << "2. Retorno medio do mercado\n";
    std::cout << "mean_market = " << mean_market << "\n\n";

    std::cout << "3. Excesso de retorno da estrategia\n";
    print_vector("strategy_excess", strategy_excess);
    std::cout << "\n";

    std::cout << "4. Excesso de retorno do mercado\n";
    print_vector("market_excess", market_excess);
    std::cout << "\n";

    std::cout << "5. Beta da estrategia em relacao ao mercado\n";
    std::cout << "beta = " << beta << "\n\n";

    std::cout << "6. Cosine similarity entre estrategia e mercado\n";
    std::cout << "cosine_similarity = " << similarity << "\n\n";

    std::cout << "7. Vetor projetado: parte explicada pelo mercado\n";
    print_vector("explained", explained);
    std::cout << "norm_explained = " << norm_explained << "\n\n";

    std::cout << "8. Vetor residual: parte nao explicada pelo mercado\n";
    print_vector("residual", residual);
    std::cout << "\n";

    std::cout << "9. Norma do residual\n";
    std::cout << "norm_residual = " << norm_residual << "\n\n";

    std::cout << "10. Conclusao\n";
    std::cout << conclusion << "\n";

    return ExerciseMetrics{beta, norm_residual};
}

int main() {
    std::cout << "Vetores - Retorno, risco e similaridade como operacoes vetoriais\n";
    std::cout << "Siga os passos 1 a 10 do README.md.\n\n";
    run_exercise();
    return 0;
}
