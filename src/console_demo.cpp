// console_demo.cpp — Interactive terminal demo for viva/presentation.
// Lets you pick an operation from a menu and type matrices directly into cmd.
// This is separate from server.cpp — it does NOT touch your web app at all.

#include "Matrix.h"
#include <iostream>
#include <limits>

Matrix readMatrixFromUser(const std::string& label) {
    int r, c;
    std::cout << "\nEnter number of rows for Matrix " << label << ": ";
    std::cin >> r;
    std::cout << "Enter number of columns for Matrix " << label << ": ";
    std::cin >> c;

    Matrix m(r, c);
    std::cout << "Enter " << r * c << " values for Matrix " << label
               << " (row by row, separated by space or Enter):\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            double val;
            std::cin >> val;
            m.set(i, j, val);
        }
    }
    return m;
}

void printMatrix(const Matrix& m, const std::string& label) {
    std::cout << "\n" << label << " =\n";
    for (int i = 0; i < m.getRows(); i++) {
        std::cout << "  [ ";
        for (int j = 0; j < m.getCols(); j++) {
            std::cout << m.get(i, j);
            if (j < m.getCols() - 1) std::cout << "\t";
        }
        std::cout << " ]\n";
    }
}

void pause() {
    std::cout << "\nPress Enter to return to the menu...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void printBanner() {
    std::cout << "\n==========================================\n";
    std::cout << "   MATRIX OPERATIONS SYSTEM - CONSOLE DEMO\n";
    std::cout << "==========================================\n";
}

void printMenu() {
    std::cout << "\nSelect a module to run:\n";
    std::cout << "  1. Addition        (A + B)\n";
    std::cout << "  2. Subtraction      (A - B)\n";
    std::cout << "  3. Multiplication   (A * B)\n";
    std::cout << "  4. Transpose        (A)\n";
    std::cout << "  5. Determinant      (A)\n";
    std::cout << "  6. Adjoint          (A)\n";
    std::cout << "  7. Inverse          (A)\n";
    std::cout << "  8. Rank             (A)\n";
    std::cout << "  0. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    printBanner();
    int choice;

    while (true) {
        printMenu();
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "\nExiting. Thank you!\n";
            break;
        }

        try {
            if (choice == 1 || choice == 2 || choice == 3) {
                Matrix A = readMatrixFromUser("A");
                Matrix B = readMatrixFromUser("B");
                printMatrix(A, "Matrix A");
                printMatrix(B, "Matrix B");

                if (choice == 1) {
                    Matrix R = A + B;
                    printMatrix(R, "Result (A + B)");
                } else if (choice == 2) {
                    Matrix R = A - B;
                    printMatrix(R, "Result (A - B)");
                } else {
                    Matrix R = A * B;
                    printMatrix(R, "Result (A * B)");
                }
            }
            else if (choice == 4) {
                Matrix A = readMatrixFromUser("A");
                printMatrix(A, "Matrix A");
                printMatrix(A.transpose(), "Transpose of A");
            }
            else if (choice == 5) {
                Matrix A = readMatrixFromUser("A");
                printMatrix(A, "Matrix A");
                std::cout << "\nDeterminant of A = " << A.determinant() << "\n";
            }
            else if (choice == 6) {
                Matrix A = readMatrixFromUser("A");
                printMatrix(A, "Matrix A");
                printMatrix(A.adjoint(), "Adjoint of A");
            }
            else if (choice == 7) {
                Matrix A = readMatrixFromUser("A");
                printMatrix(A, "Matrix A");
                printMatrix(A.inverse(), "Inverse of A");
            }
            else if (choice == 8) {
                Matrix A = readMatrixFromUser("A");
                printMatrix(A, "Matrix A");
                std::cout << "\nRank of A = " << A.rank() << "\n";
            }
            else {
                std::cout << "\nInvalid choice. Please try again.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "\n[ERROR] " << e.what() << "\n";
            std::cout << "(This is the exception-handling module catching an invalid operation.)\n";
        }

        pause();
    }
    return 0;
}
