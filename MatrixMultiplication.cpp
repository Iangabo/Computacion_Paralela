#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>

const int BLOCK_SIZE = 32;

// Funcion para multiplicar matrices con tres bucles anidados
std::vector<std::vector<int>> multiplyMatricesThreeLoops(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int m = A.size();
    int n = A[0].size();
    int p = B[0].size();

    std::vector<std::vector<int>> result(m, std::vector<int>(p, 0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < p; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return result;
}

// Funcion para multiplicar matrices por bloques
std::vector<std::vector<int>> multiplyMatricesBlock(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B) {
    int m = A.size();
    int n = A[0].size();
    int p = B[0].size();

    std::vector<std::vector<int>> result(m, std::vector<int>(p, 0));

    for (int i = 0; i < m; i += BLOCK_SIZE) {
        for (int j = 0; j < p; j += BLOCK_SIZE) {
            for (int k = 0; k < n; k += BLOCK_SIZE) {
                for (int ii = i; ii < std::min(i + BLOCK_SIZE, m); ++ii) {
                    for (int jj = j; jj < std::min(j + BLOCK_SIZE, p); ++jj) {
                        for (int kk = k; kk < std::min(k + BLOCK_SIZE, n); ++kk) {
                            result[ii][jj] += A[ii][kk] * B[kk][jj];
                        }
                    }
                }
            }
        }
    }

    return result;
}


int main() {

    int rowsA, colsA, rowsB, colsB;

    std::cout << "Ingrese el numero de filas de la matriz A: ";
    std::cin >> rowsA;
    std::cout << "Ingrese el numero de columnas de la matriz A: ";
    std::cin >> colsA;

    std::vector<std::vector<int>> A(rowsA, std::vector<int>(colsA));
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            A[i][j] = rand() % 9 + 1;
        }
    }

    std::cout << "Ingrese el numero de filas de la matriz B: ";
    std::cin >> rowsB;
    std::cout << "Ingrese el numero de columnas de la matriz B: ";
    std::cin >> colsB;

    std::vector<std::vector<int>> B(rowsB, std::vector<int>(colsB));
    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            B[i][j] = rand() % 9 + 1;
        }
    }

    auto start_three_loops = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> result_three_loops = multiplyMatricesThreeLoops(A, B);
    auto end_three_loops = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_milliseconds_three_loops = end_three_loops - start_three_loops;

    auto start_block = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<int>> result_block = multiplyMatricesBlock(A, B);
    auto end_block = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_milliseconds_block = end_block - start_block;

    int result_rows = result_block.size();
    int result_cols = result_block[0].size();

    std::cout << "Tiempo de ejecucion (tres bucles anidados): " << elapsed_milliseconds_three_loops.count() << " milisegundos" << std::endl;

    std::cout << "Tiempo de ejecucion (multiplicacion por bloques): " << elapsed_milliseconds_block.count() << " milisegundos" << std::endl;

    return 0;

}
