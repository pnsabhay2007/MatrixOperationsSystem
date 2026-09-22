// Standalone console test — run this FIRST, before touching the web layer.
#include "Matrix.h"
#include <iostream>

int main() {
    Matrix A({{1, 2}, {3, 4}});
    Matrix B({{5, 6}, {7, 8}});

    std::cout << "Matrix A:\n"; A.display();
    std::cout << "Matrix B:\n"; B.display();

    std::cout << "\nA + B:\n"; (A + B).display();
    std::cout << "\nA - B:\n"; (A - B).display();
    std::cout << "\nA * B:\n"; (A * B).display();
    std::cout << "\nTranspose of A:\n"; A.transpose().display();

    std::cout << "\nDeterminant of A: " << A.determinant() << "\n";
    std::cout << "Rank of A: " << A.rank() << "\n";

    std::cout << "\nInverse of A:\n"; A.inverse().display();

    // Singular matrix test — should throw, not crash
    try {
        Matrix S({{1, 2}, {2, 4}});
        S.inverse();
    } catch (const std::exception& e) {
        std::cout << "\nSingular matrix test caught correctly: " << e.what() << "\n";
    }

    return 0;
}
