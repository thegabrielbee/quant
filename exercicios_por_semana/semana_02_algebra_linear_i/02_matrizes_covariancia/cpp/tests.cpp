#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#define main exercise_main
#include "main.cpp"
#undef main

void require(bool condition, const std::string& message) {
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void require_close(double actual, double expected, double tolerance, const std::string& message) {
    if (std::fabs(actual - expected) > tolerance) {
        throw std::runtime_error(message);
    }
}

void require_vector_close(
    const std::vector<double>& actual,
    const std::vector<double>& expected,
    double tolerance,
    const std::string& message
) {
    require(actual.size() == expected.size(), message + " size");
    for (std::size_t i = 0; i < actual.size(); ++i) {
        require_close(actual[i], expected[i], tolerance, message);
    }
}

void require_matrix_close(
    const std::vector<std::vector<double>>& actual,
    const std::vector<std::vector<double>>& expected,
    double tolerance,
    const std::string& message
) {
    require(actual.size() == expected.size(), message + " rows");
    for (std::size_t i = 0; i < actual.size(); ++i) {
        require_vector_close(actual[i], expected[i], tolerance, message);
    }
}

template <typename Function>
void require_throws(Function function, const std::string& message) {
    try {
        function();
    } catch (const std::invalid_argument&) {
        return;
    }
    throw std::runtime_error(message);
}

void test_reference_results() {
    const std::vector<std::vector<double>> returns{
        {0.010, 0.004, -0.002},
        {0.006, 0.002, 0.001},
        {-0.012, -0.006, 0.003},
        {0.015, 0.008, -0.004},
        {-0.004, -0.001, 0.002},
        {0.009, 0.005, -0.001},
    };
    const std::vector<double> weights{0.50, 0.30, 0.20};

    const auto means = column_means(returns);
    const auto centered = center_matrix(returns, means);
    const auto covariance = covariance_matrix(centered);
    const auto cw = matvec(covariance, weights);
    const double portfolio_variance = dot(weights, cw);
    const double daily_vol = std::sqrt(portfolio_variance);
    const double annual_vol = daily_vol * std::sqrt(252.0);

    require_vector_close(means, {0.004, 0.002, -0.00016666666666666666}, 1e-12, "means");
    require_matrix_close(
        covariance,
        {
            {0.0001012, 0.000049, -0.0000246},
            {0.000049, 0.0000244, -0.0000122},
            {-0.0000246, -0.0000122, 0.000006966666666666667},
        },
        1e-12,
        "covariance"
    );
    require_vector_close(cw, {0.00006038, 0.00002938, -0.000014566666666666668}, 1e-12, "cw");
    require_close(portfolio_variance, 0.00003609066666666667, 1e-15, "portfolio variance");
    require_close(daily_vol, 0.006007550804335047, 1e-15, "daily vol");
    require_close(annual_vol, 0.09536691250113952, 1e-15, "annual vol");
}

void test_matrix_shape_and_rectangular_validation() {
    const auto shape = matrix_shape({{1.0, 2.0}, {3.0, 4.0}});
    require(shape == std::pair<std::size_t, std::size_t>{2, 2}, "matrix_shape");

    require_throws([] { validate_rectangular({}); }, "empty matrix should throw");
    require_throws([] { validate_rectangular({{1.0}, {2.0, 3.0}}); }, "ragged matrix should throw");
}

void test_matmul_dimension_validation() {
    validate_matmul_dimensions({{1.0, 2.0}}, {{3.0}, {4.0}});

    require_throws(
        [] { validate_matmul_dimensions({{1.0, 2.0}}, {{3.0, 4.0}}); },
        "invalid matmul dimensions should throw"
    );
}

void test_matmul_uses_shared_dimension_k() {
    const std::vector<std::vector<double>> a{
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
    };
    const std::vector<std::vector<double>> b{
        {7.0, 8.0},
        {9.0, 10.0},
        {11.0, 12.0},
    };

    require_matrix_close(
        matmul(a, b),
        {
            {58.0, 64.0},
            {139.0, 154.0},
        },
        1e-12,
        "matmul"
    );
}

void test_transpose_twice_returns_original() {
    const std::vector<std::vector<double>> matrix{
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
    };
    require_matrix_close(transpose(transpose(matrix)), matrix, 1e-12, "transpose twice");
}

void test_matvec_identity() {
    const std::vector<std::vector<double>> identity{
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
    };
    const std::vector<double> vector{3.0, -2.0, 5.0};
    require_vector_close(matvec(identity, vector), vector, 1e-12, "matvec identity");
}

void test_dot_properties() {
    const std::vector<double> u{1.0, -2.0, 3.0};
    const std::vector<double> v{4.0, 5.0, -6.0};
    const double scalar = 2.5;
    std::vector<double> scaled_u{};
    scaled_u.reserve(u.size());

    for (double value : u) {
        scaled_u.push_back(scalar * value);
    }

    require_close(dot(u, v), dot(v, u), 1e-12, "dot commutativity");
    require_close(dot(scaled_u, v), scalar * dot(u, v), 1e-12, "dot linearity");
    require_close(dot(u, v), -24.0, 1e-12, "dot manual result");
}

void test_covariance_matrix_is_symmetric() {
    const std::vector<std::vector<double>> returns{
        {0.010, 0.004, -0.002},
        {0.006, 0.002, 0.001},
        {-0.012, -0.006, 0.003},
        {0.015, 0.008, -0.004},
        {-0.004, -0.001, 0.002},
        {0.009, 0.005, -0.001},
    };

    const auto centered = center_matrix(returns, column_means(returns));
    const auto covariance = covariance_matrix(centered);
    for (std::size_t i = 0; i < covariance.size(); ++i) {
        for (std::size_t j = 0; j < covariance.size(); ++j) {
            require_close(covariance[i][j], covariance[j][i], 1e-15, "covariance symmetry");
        }
    }
}

void test_centered_columns_sum_to_zero() {
    const std::vector<std::vector<double>> returns{
        {0.010, 0.004, -0.002},
        {0.006, 0.002, 0.001},
        {-0.012, -0.006, 0.003},
        {0.015, 0.008, -0.004},
        {-0.004, -0.001, 0.002},
        {0.009, 0.005, -0.001},
    };

    const auto centered = center_matrix(returns, column_means(returns));
    for (std::size_t col = 0; col < centered[0].size(); ++col) {
        double sum = 0.0;
        for (const auto& row : centered) {
            sum += row[col];
        }
        require_close(sum, 0.0, 1e-15, "centered column sum");
    }
}

int main() {
    test_reference_results();
    test_matrix_shape_and_rectangular_validation();
    test_matmul_dimension_validation();
    test_matmul_uses_shared_dimension_k();
    test_transpose_twice_returns_original();
    test_matvec_identity();
    test_dot_properties();
    test_covariance_matrix_is_symmetric();
    test_centered_columns_sum_to_zero();

    std::cout << "All C++ covariance tests passed.\n";
    return 0;
}
