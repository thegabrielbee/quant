/*
Matrizes - Matriz de covariancia e risco de portfolio

Este arquivo segue a mesma ordem da secao "Formulas por exercicio" do README.md.
Implemente as funcoes declaradas abaixo para treinar C++.
*/

#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using Vector = std::vector<double>;
using Matrix = std::vector<std::vector<double>>;
using Shape = std::pair<std::size_t, std::size_t>;

struct ExerciseMetrics {
    double portfolio_variance = 0.0;
    double daily_vol = 0.0;
    double annual_vol = 0.0;
};

Vector column_means(const Matrix& matrix);
Matrix center_matrix(const Matrix& matrix, const Vector& means);
Matrix transpose(const Matrix& matrix);
Shape matrix_shape(const Matrix& matrix);
void validate_rectangular(const Matrix& matrix);
void validate_matmul_dimensions(const Matrix& a, const Matrix& b);
Matrix matmul(const Matrix& a, const Matrix& b);
Vector matvec(const Matrix& matrix, const Vector& vector);
Matrix covariance_matrix(const Matrix& centered);
double dot(const Vector& u, const Vector& v);
double quadratic_form(const Vector& weights, const Vector& cw);
double daily_volatility(double portfolio_variance);
double annualized_volatility(double daily_vol, int periods_per_year);
void print_vector(const std::string& name, const Vector& values);
void print_matrix(const std::string& name, const Matrix& matrix);

// Escreva as implementacoes das funcoes declaradas acima.
// A estrutura de run_exercise() abaixo mostra onde cada funcao sera usada.

ExerciseMetrics run_exercise() {
    const Matrix returns{
        {0.010, 0.004, -0.002},
        {0.006, 0.002, 0.001},
        {-0.012, -0.006, 0.003},
        {0.015, 0.008, -0.004},
        {-0.004, -0.001, 0.002},
        {0.009, 0.005, -0.001},
    };

    const Vector weights{0.50, 0.30, 0.20};
    const int periods_per_year = 252;

    // 1. Media de retorno de cada ativo.
    const Vector means = column_means(returns);

    // 2. Matriz de retornos centralizados.
    const Matrix centered = center_matrix(returns, means);

    // 3. Matriz transposta Xc'.
    const Matrix centered_t = transpose(centered);

    // 4. Matriz de covariancia amostral.
    const Matrix covariance = covariance_matrix(centered);

    // 5. Vetor intermediario Cw.
    const Vector cw = matvec(covariance, weights);

    // 6. Variancia diaria do portfolio.
    const double portfolio_variance = quadratic_form(weights, cw);

    // 7. Volatilidade diaria do portfolio.
    const double daily_vol = daily_volatility(portfolio_variance);

    // 8. Volatilidade anualizada do portfolio.
    const double annual_vol = annualized_volatility(daily_vol, periods_per_year);

    // 9. Conclusao sobre diversificacao.
    const std::string conclusion = "preencha depois de analisar a matriz de covariancia";

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "1. Media de retorno de cada ativo\n";
    print_vector("means", means);
    std::cout << "\n";

    std::cout << "2. Matriz de retornos centralizados\n";
    print_matrix("centered", centered);
    std::cout << "\n";

    std::cout << "3. Matriz transposta Xc'\n";
    print_matrix("centered_t", centered_t);
    std::cout << "\n";

    std::cout << "4. Matriz de covariancia amostral\n";
    print_matrix("covariance", covariance);
    std::cout << "\n";

    std::cout << "5. Vetor intermediario Cw\n";
    print_vector("cw", cw);
    std::cout << "\n";

    std::cout << "6. Variancia diaria do portfolio\n";
    std::cout << "portfolio_variance = " << portfolio_variance << "\n\n";

    std::cout << "7. Volatilidade diaria do portfolio\n";
    std::cout << "daily_vol = " << daily_vol << "\n\n";

    std::cout << "8. Volatilidade anualizada do portfolio\n";
    std::cout << "annual_vol = " << annual_vol << "\n\n";

    std::cout << "9. Conclusao\n";
    std::cout << conclusion << "\n";

    return ExerciseMetrics{portfolio_variance, daily_vol, annual_vol};
}

int main() {
    std::cout << "Matrizes - Matriz de covariancia e risco de portfolio\n";
    std::cout << "Siga os passos 1 a 9 do README.md.\n\n";
    run_exercise();
    return 0;
}
