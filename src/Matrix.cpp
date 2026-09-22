
#include "Matrix.h"
#include <iostream>
#include <sstream>
#include <cmath>

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    data.assign(rows, std::vector<double>(cols, 0.0));
}

Matrix::Matrix(const std::vector<std::vector<double>>& values) {
    rows = (int)values.size();
    cols = rows > 0 ? (int)values[0].size() : 0;
    data = values;
}

double Matrix::get(int r, int c) const {
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        throw std::out_of_range("Matrix index out of range");
    return data[r][c];
}

void Matrix::set(int r, int c, double value) {
    if (r < 0 || r >= rows || c < 0 || c >= cols)
        throw std::out_of_range("Matrix index out of range");
    data[r][c] = value;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Dimension mismatch for addition");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j] + other.data[i][j];
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Dimension mismatch for subtraction");
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[i][j] = data[i][j] - other.data[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows)
        throw std::invalid_argument("Dimension mismatch for multiplication: A.cols must equal B.rows");
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < other.cols; j++) {
            double sum = 0;
            for (int k = 0; k < cols; k++)
                sum += data[i][k] * other.data[k][j];
            result.data[i][j] = sum;
        }
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[j][i] = data[i][j];
    return result;
}

Matrix Matrix::getMinor(int skipRow, int skipCol) const {
    Matrix minor(rows - 1, cols - 1);
    int mi = 0;
    for (int i = 0; i < rows; i++) {
        if (i == skipRow) continue;
        int mj = 0;
        for (int j = 0; j < cols; j++) {
            if (j == skipCol) continue;
            minor.data[mi][mj] = data[i][j];
            mj++;
        }
        mi++;
    }
    return minor;
}

double Matrix::determinant() const {
    if (rows != cols)
        throw std::invalid_argument("Determinant requires a square matrix");
    if (rows == 1) return data[0][0];
    if (rows == 2) return data[0][0] * data[1][1] - data[0][1] * data[1][0];

    double det = 0;
    for (int col = 0; col < cols; col++) {
        Matrix minor = getMinor(0, col);
        double sign = (col % 2 == 0) ? 1.0 : -1.0;
        det += sign * data[0][col] * minor.determinant();
    }
    return det;
}

Matrix Matrix::adjoint() const {
    if (rows != cols)
        throw std::invalid_argument("Adjoint requires a square matrix");
    Matrix cofactorMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Matrix minor = getMinor(i, j);
            double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
            cofactorMatrix.data[i][j] = sign * minor.determinant();
        }
    }
    return cofactorMatrix.transpose();
}

Matrix Matrix::inverse() const {
    double det = determinant();
    if (std::fabs(det) < 1e-9)
        throw std::runtime_error("Matrix is singular; inverse does not exist");
    Matrix adj = adjoint();
    Matrix result(rows, cols);
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            result.data[i][j] = adj.data[i][j] / det;
    return result;
}

int Matrix::rank() const {
    std::vector<std::vector<double>> m = data;
    int r = rows, c = cols;
    int rank = 0;
    std::vector<bool> rowUsed(r, false);

    for (int col = 0; col < c && rank < r; col++) {
        int pivot = -1;
        for (int row = 0; row < r; row++) {
            if (!rowUsed[row] && std::fabs(m[row][col]) > 1e-9) {
                pivot = row;
                break;
            }
        }
        if (pivot == -1) continue;
        rowUsed[pivot] = true;
        rank++;
        for (int row = 0; row < r; row++) {
            if (row != pivot) {
                double factor = m[row][col] / m[pivot][col];
                for (int k = 0; k < c; k++)
                    m[row][k] -= factor * m[pivot][k];
            }
        }
    }
    return rank;
}

void Matrix::display() const {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            std::cout << data[i][j] << "\t";
        std::cout << "\n";
    }
}

std::string Matrix::toHTMLTable() const {
    std::ostringstream oss;
    oss << "<table class='matrix-table'>";
    for (int i = 0; i < rows; i++) {
        oss << "<tr>";
        for (int j = 0; j < cols; j++)
            oss << "<td>" << data[i][j] << "</td>";
        oss << "</tr>";
    }
    oss << "</table>";
    return oss.str();
}

std::string Matrix::toJSON() const {
    std::ostringstream oss;
    oss << "[";
    for (int i = 0; i < rows; i++) {
        oss << "[";
        for (int j = 0; j < cols; j++) {
            oss << data[i][j];
            if (j < cols - 1) oss << ",";
        }
        oss << "]";
        if (i < rows - 1) oss << ",";
    }
    oss << "]";
    return oss.str();
}
