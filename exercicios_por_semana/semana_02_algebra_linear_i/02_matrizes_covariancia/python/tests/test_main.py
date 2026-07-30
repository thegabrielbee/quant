import math
import sys
import unittest
from pathlib import Path


PYTHON_DIR = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PYTHON_DIR))

import main


class TestCovarianceExercise(unittest.TestCase):
    def assert_vector_almost_equal(self, actual, expected, places=12):
        self.assertEqual(len(actual), len(expected))
        for actual_value, expected_value in zip(actual, expected):
            self.assertAlmostEqual(actual_value, expected_value, places=places)

    def assert_matrix_almost_equal(self, actual, expected, places=12):
        self.assertEqual(len(actual), len(expected))
        for actual_row, expected_row in zip(actual, expected):
            self.assert_vector_almost_equal(actual_row, expected_row, places=places)

    def test_reference_results(self):
        means = main.column_means(main.RETURNS)
        centered = main.center_matrix(main.RETURNS, means)
        covariance = main.covariance_matrix(centered)
        cw = main.matvec(covariance, main.WEIGHTS)
        portfolio_variance = main.dot(main.WEIGHTS, cw)
        daily_vol = math.sqrt(portfolio_variance)
        annual_vol = daily_vol * math.sqrt(main.PERIODS_PER_YEAR)

        self.assert_vector_almost_equal(means, [0.004, 0.002, -0.00016666666666666666])
        self.assert_matrix_almost_equal(
            covariance,
            [
                [0.0001012, 0.000049, -0.0000246],
                [0.000049, 0.0000244, -0.0000122],
                [-0.0000246, -0.0000122, 0.000006966666666666667],
            ],
        )
        self.assert_vector_almost_equal(cw, [0.00006038, 0.00002938, -0.000014566666666666668])
        self.assertAlmostEqual(portfolio_variance, 0.00003609066666666667, places=15)
        self.assertAlmostEqual(daily_vol, 0.006007550804335047, places=15)
        self.assertAlmostEqual(annual_vol, 0.09536691250113952, places=15)

    def test_matrix_shape_and_rectangular_validation(self):
        self.assertEqual(main.matrix_shape([[1.0, 2.0], [3.0, 4.0]]), (2, 2))

        with self.assertRaises(ValueError):
            main.validate_rectangular([])
        with self.assertRaises(ValueError):
            main.validate_rectangular([[1.0], [2.0, 3.0]])

    def test_matmul_dimension_validation(self):
        main.validate_matmul_dimensions([[1.0, 2.0]], [[3.0], [4.0]])

        with self.assertRaises(ValueError):
            main.validate_matmul_dimensions([[1.0, 2.0]], [[3.0, 4.0]])

    def test_matmul_uses_shared_dimension_k(self):
        a = [
            [1.0, 2.0, 3.0],
            [4.0, 5.0, 6.0],
        ]
        b = [
            [7.0, 8.0],
            [9.0, 10.0],
            [11.0, 12.0],
        ]

        self.assert_matrix_almost_equal(
            main.matmul(a, b),
            [
                [58.0, 64.0],
                [139.0, 154.0],
            ],
        )

    def test_transpose_twice_returns_original(self):
        matrix = [[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]]
        self.assertEqual(main.transpose(main.transpose(matrix)), matrix)

    def test_matvec_identity(self):
        identity = [
            [1.0, 0.0, 0.0],
            [0.0, 1.0, 0.0],
            [0.0, 0.0, 1.0],
        ]
        vector = [3.0, -2.0, 5.0]
        self.assertEqual(main.matvec(identity, vector), vector)

    def test_dot_properties(self):
        u = [1.0, -2.0, 3.0]
        v = [4.0, 5.0, -6.0]
        scalar = 2.5

        self.assertAlmostEqual(main.dot(u, v), main.dot(v, u))
        self.assertAlmostEqual(
            main.dot([scalar * value for value in u], v),
            scalar * main.dot(u, v),
        )
        self.assertAlmostEqual(main.dot(u, v), -24.0)

    def test_covariance_matrix_is_symmetric(self):
        means = main.column_means(main.RETURNS)
        centered = main.center_matrix(main.RETURNS, means)
        covariance = main.covariance_matrix(centered)

        for i in range(len(covariance)):
            for j in range(len(covariance)):
                self.assertAlmostEqual(covariance[i][j], covariance[j][i], places=15)

    def test_centered_columns_sum_to_zero(self):
        means = main.column_means(main.RETURNS)
        centered = main.center_matrix(main.RETURNS, means)

        for col in range(len(centered[0])):
            self.assertAlmostEqual(sum(row[col] for row in centered), 0.0, places=15)


if __name__ == "__main__":
    unittest.main()
