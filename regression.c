#include "regression.h"

double* polynomial_fit(double* xvalues, double* yvalues, int point_number, int degree) {
    double van_row_matrix[degree + 1][point_number];
    double van_col_matrix[point_number][degree + 1];
    double dot_product1[degree + 1][degree + 1], dot_product2[degree + 1][point_number];
    double inverse_matrix[degree + 1][degree + 1];

    // 生成范德蒙德矩阵
    for (int m = 0; m < degree + 1 + 1; m++) {
        for (int n = 0; n < point_number; n++) {
            van_row_matrix[m][n] = pow(xvalues[n], m);
        }
    }

    // 转置操作
    for (int m = 0; m < point_number; m++) {
        for (int n = 0; n < degree + 1; n++) {
            van_col_matrix[m][n] = van_row_matrix[n][m];
        }
    }

    // 矩阵相乘: result = van_row_matrix * van_col_matrix
    for (int i = 0; i < degree + 1 + 1; i++) {
        for (int j = 0; j < degree + 1; j++) {
            dot_product1[i][j] = 0;  // 初始化结果矩阵
            for (int k = 0; k < point_number; k++) {
                dot_product1[i][j] += van_row_matrix[i][k] * van_col_matrix[k][j];
            }
        }
    }

    // 计算 result 矩阵的逆
    double temp[degree + 1][degree + 1];
    for (int i = 0; i < degree + 1; i++) {
        for (int j = 0; j < degree + 1; j++) {
            temp[i][j] = dot_product1[i][j];              // 复制结果矩阵
            inverse_matrix[i][j] = (i == j) ? 1.0 : 0.0;  // 初始化逆矩阵为单位矩阵
        }
    }

    for (int i = 0; i < degree + 1; i++) {
        double e = temp[i][i];

        // 如果主对角线元素为0，进行行交换
        if (e == 0) {
            for (int ii = i + 1; ii < degree + 1; ii++) {
                if (temp[ii][i] != 0) {
                    for (int j = 0; j < degree + 1; j++) {
                        double temp_value = temp[i][j];
                        temp[i][j] = temp[ii][j];
                        temp[ii][j] = temp_value;

                        temp_value = inverse_matrix[i][j];
                        inverse_matrix[i][j] = inverse_matrix[ii][j];
                        inverse_matrix[ii][j] = temp_value;
                    }
                    break;
                }
            }
            e = temp[i][i];
            if (e == 0) {
                return 0;  // 不可逆
            }
        }

        // 将当前行归一化
        for (int j = 0; j < degree + 1; j++) {
            temp[i][j] /= e;
            inverse_matrix[i][j] /= e;
        }

        // 消元
        for (int ii = 0; ii < degree + 1; ii++) {
            if (ii != i) {
                double scale = temp[ii][i];
                for (int j = 0; j < degree + 1; j++) {
                    temp[ii][j] -= scale * temp[i][j];
                    inverse_matrix[ii][j] -= scale * inverse_matrix[i][j];
                }
            }
        }
    }

    // 矩阵相乘: product = inverse * van_row_matrix
    for (int i = 0; i < degree + 1; i++) {
        for (int j = 0; j < point_number; j++) {
            dot_product2[i][j] = 0;  // 初始化乘积矩阵
            for (int k = 0; k < degree + 1; k++) {
                dot_product2[i][j] += inverse_matrix[i][k] * van_row_matrix[k][j];
            }
        }
    }

    double coeffs[degree + 1];
    for (int i = 0; i < degree + 1; i++) {
        coeffs[i] = 0;
        for (int j = 0; j < point_number; j++) {
            coeffs[i] = coeffs[i] + dot_product2[i][j] * yvalues[j];
        }
    }

    for (int i = 0; i < degree + 1; i++) {
        printf("Coefficient of x^%d: %f\n", i, coeffs[i]);
    }
}
