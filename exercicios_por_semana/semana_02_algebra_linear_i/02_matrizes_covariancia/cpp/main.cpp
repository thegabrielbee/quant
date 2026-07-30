/*
Matrizes - Matriz de covariancia e risco de portfolio

Este arquivo segue a mesma ordem da secao "Formulas por exercicio" do README.md.
Implemente as funcoes declaradas abaixo para treinar C++.
*/

#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

struct ExerciseMetrics {
    double portfolio_variance = 0.0;
    double daily_vol = 0.0;
    double annual_vol = 0.0;
};

void validate_rectangular(const std::vector<std::vector<double>>& matrix);
void validate_matmul_dimensions(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b);

std::vector<double> column_means(const std::vector<std::vector<double>>& matrix) {
    validate_rectangular(matrix);

    std::vector<double> means(matrix[0].size(), 0.0);
    for (const auto& row : matrix) {
        for (std::size_t j = 0; j < row.size(); ++j) {
            means[j] += row[j];
        }
    }

    for (double& mean : means) {
        mean /= static_cast<double>(matrix.size());
    }
    return means;
}

std::vector<std::vector<double>> center_matrix(const std::vector<std::vector<double>>& matrix, const std::vector<double>& means) {
    validate_rectangular(matrix);
    if (means.size() != matrix[0].size()) {
        throw std::invalid_argument("means must have one value for each matrix column");
    }

    std::vector<std::vector<double>> centered(matrix.size(), std::vector<double>(matrix[0].size(), 0.0));
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        for (std::size_t j = 0; j < matrix[0].size(); ++j) {
            centered[i][j] = matrix[i][j] - means[j];
        }
    }
    return centered;
}

std::vector<std::vector<double>> transpose(const std::vector<std::vector<double>>& matrix) {
    validate_rectangular(matrix);

    std::vector<std::vector<double>> t(matrix[0].size(), std::vector<double>(matrix.size(), 0.0));
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        for (std::size_t j = 0; j < matrix[0].size(); ++j) {
            t[j][i] = matrix[i][j];
        }
    }
    return t;
}

std::pair<std::size_t, std::size_t> matrix_shape(const std::vector<std::vector<double>>& matrix) {
    validate_rectangular(matrix);
    return {matrix.size(), matrix[0].size()};
}

void validate_rectangular(const std::vector<std::vector<double>>& matrix) {
    if (matrix.empty()) {
        throw std::invalid_argument("matrix must not be empty");
    }
    if (matrix[0].empty()) {
        throw std::invalid_argument("matrix rows must not be empty");
    }

    const std::size_t cols = matrix[0].size();
    for (const auto& row : matrix) {
        if (row.size() != cols) {
            throw std::invalid_argument("matrix must be rectangular");
        }
    }
}

void validate_matmul_dimensions(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b) {
    validate_rectangular(a);
    validate_rectangular(b);
    if (a[0].size() != b.size()) {
        throw std::invalid_argument("a columns must match b rows");
    }
}

std::vector<std::vector<double>> matmul(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b) {
    validate_matmul_dimensions(a, b);

    std::vector<std::vector<double>> m(a.size(), std::vector<double>(b[0].size(), 0.0));
    for (std::size_t i = 0; i < a.size(); ++i) {
        for (std::size_t j = 0; j < b[0].size(); ++j) {
            for (std::size_t k = 0; k < a[0].size(); ++k) {
                m[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return m;
}

std::vector<double> matvec(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector) {
    validate_rectangular(matrix);
    if (matrix[0].size() != vector.size()) {
        throw std::invalid_argument("matrix columns must match vector length");
    }

    std::vector<double> mv(matrix.size(), 0.0);
    for (std::size_t i = 0; i < matrix.size(); ++i) {
        for (std::size_t j = 0; j < matrix[0].size(); ++j) {
            mv[i] += matrix[i][j] * vector[j];
        }
    }
    return mv;
}

std::vector<std::vector<double>> covariance_matrix(const std::vector<std::vector<double>>& centered) {
    validate_rectangular(centered);
    if (centered.size() < 2) {
        throw std::invalid_argument("sample covariance needs at least two rows");
    }

    auto m = matmul(transpose(centered), centered);
    auto c = std::vector<std::vector<double>>(m.size(), std::vector<double>(m[0].size(), 0.0));
    const double denominator = static_cast<double>(centered.size() - 1);
    for (std::size_t i = 0; i < m.size(); ++i) {
        for (std::size_t j = 0; j < m[0].size(); ++j) {
            c[i][j] = m[i][j] / denominator;
        }
    }
    return c;
}

double dot(const std::vector<double>& u, const std::vector<double>& v) {
    if (u.size() != v.size()) {
        throw std::invalid_argument("vectors must have the same length");
    }

    double d = 0.0;
    for (std::size_t i = 0; i < u.size(); ++i) {
        d += u[i] * v[i];
    }
    return d;
}

void print_vector(const std::string& name, const std::vector<double>& values) {
    std::cout << name << " = [";
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << values[i];
    }
    std::cout << "]\n";
}

void print_matrix(const std::string& name, const std::vector<std::vector<double>>& matrix) {
    std::cout << name << " = [\n";
    for (const auto& row : matrix) {
        std::cout << "    [";
        for (std::size_t j = 0; j < row.size(); ++j) {
            if (j > 0) {
                std::cout << ", ";
            }
            std::cout << row[j];
        }
        std::cout << "],\n";
    }
    std::cout << "]\n";
}

// Escreva as implementacoes das funcoes declaradas acima.
// A estrutura de run_exercise() abaixo mostra onde cada funcao sera usada.

ExerciseMetrics run_exercise() {
    const std::vector<std::vector<double>> returns{
        {0.010, 0.004, -0.002},
        {0.006, 0.002, 0.001},
        {-0.012, -0.006, 0.003},
        {0.015, 0.008, -0.004},
        {-0.004, -0.001, 0.002},
        {0.009, 0.005, -0.001},
    };

    const std::vector<double> weights{0.50, 0.30, 0.20};
    const int periods_per_year = 252;

    // 1. Media de retorno de cada ativo.
    const std::vector<double> means = column_means(returns);

    // 2. Matriz de retornos centralizados.
    const std::vector<std::vector<double>> centered = center_matrix(returns, means);

    // 3. Matriz transposta Xc'.
    const std::vector<std::vector<double>> centered_t = transpose(centered);

    // 4. Matriz de covariancia amostral.
    const std::vector<std::vector<double>> covariance = covariance_matrix(centered);

    // 5. Vetor intermediario Cw.
    const std::vector<double> cw = matvec(covariance, weights);

    // 6. Variancia diaria do portfolio.
    const double portfolio_variance = dot(weights, cw);

    // 7. Volatilidade diaria do portfolio.
    const double daily_vol = std::sqrt(portfolio_variance);

    // 8. Volatilidade anualizada do portfolio.
    const double annual_vol = daily_vol * std::sqrt(periods_per_year);

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
