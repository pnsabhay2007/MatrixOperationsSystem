#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <string>
#include <stdexcept>

class Matrix {
private:
    int rows, cols;
    std::vector<std::vector<double>> data;

public:
    Matrix(int r, int c);
    Matrix(const std::vector<std::vector<double>>& values);

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    double get(int r, int c) const;
    void set(int r, int c, double value);

    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;

    Matrix transpose() const;
    double determinant() const;
    Matrix adjoint() const;
    Matrix inverse() const;
    int rank() const;

    Matrix getMinor(int skipRow, int skipCol) const;

    void display() const;                 // console output, used for standalone testing
    std::string toHTMLTable() const;       // used by the web layer
    std::string toJSON() const;            // used by the web layer
};

#endif
