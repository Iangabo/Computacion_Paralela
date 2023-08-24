#include <iostream>
#include <chrono>

const int MAX = 10;

int main() {
    double A[MAX][MAX], x[MAX], y[MAX];
    int i, j;

    /* Initialize A and x, assign y = 0 */
    for (i = 0; i < MAX; i++) {
        x[i] = i + 1;  // Initialize x with some values
        y[i] = 0;      // Initialize y to 0

        for (j = 0; j < MAX; j++) {
            A[i][j] = i * j;  // Initialize A with some values
        }
    }

    /* First pair of loops with time measurement */
    auto start1 = std::chrono::high_resolution_clock::now();
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed1 = end1 - start1;

    /* Print the result after the first pair of loops */
    std::cout << "Result after the first pair of loops:" << std::endl;
    for (i = 0; i < MAX; i++) {
        std::cout << "y[" << i << "] = " << y[i] << std::endl;
    }
    std::cout << "Time elapsed for the first pair of loops: " << elapsed1.count() << " seconds" << std::endl;

    /* Assign y = 0 */
    for (i = 0; i < MAX; i++) {
        y[i] = 0;
    }

    /* Second pair of loops with time measurement */
    auto start2 = std::chrono::high_resolution_clock::now();
    for (j = 0; j < MAX; j++) {
        for (i = 0; i < MAX; i++) {
            y[i] += A[i][j] * x[j];
        }
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed2 = end2 - start2;

    /* Print the result after the second pair of loops */
    std::cout << "\nResult after the second pair of loops:" << std::endl;
    for (i = 0; i < MAX; i++) {
        std::cout << "y[" << i << "] = " << y[i] << std::endl;
    }
    std::cout << "Time elapsed for the second pair of loops: " << elapsed2.count() << " seconds" << std::endl;

    return 0;
}
