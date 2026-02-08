/**
 * @file Ring_Cascade_Permutation_Algorithm.cpp
 * @brief High-performanceRing-Cascade-Permutation-Algorithm (Strictly Preserved Logic)
 * @copyright Copyright (c) 2026 [ Yusheng-Hu ]. All rights reserved.
 * @license Licensed under the MIT License.
 */

#include <cstdio>
#include <cstring>
#include <ctime>
#include <chrono>
#include <cstdlib>

#ifdef __linux__
#include <sched.h>
#include <pthread.h>
#endif

#define N 5
#define lastIndex (N - 1)
#define secondLastIndex (N - 2)
#define thirdLastIndex (N - 3)

int main(int argc, char* argv[]) {
    // Permutations will be printed only if N <= LITTLE_NUMBER
    const int LITTLE_NUMBER = 5;

    int n_val = N;
    if (argc > 1) {
        n_val = std::atoi(argv[1]);
    }
    const int current_n = n_val;
    const int curr_last = current_n - 1;
    const int curr_2nd_last = current_n - 2;
    const int curr_3rd_last = current_n - 3;

// #ifdef __linux__
//     cpu_set_t cpuset;
//     CPU_ZERO(&cpuset);
//     CPU_SET(0, &cpuset); 
//     pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
//     printf("Running on CPU core 0\n");
// #else
//     printf("Running on CPU core 2\n");
// #endif

    printf("PARAM_N: %d\n", current_n);

    int* C = (int*)std::calloc(current_n, sizeof(int));
    int* D_flat = (int*)std::calloc(current_n * (3 * current_n), sizeof(int));
    
    // Macro for dynamic D[i][j] access
    #define D_PTR(i, j) (D_flat + (i) * (3 * current_n) + (j))

    auto start_point = std::chrono::high_resolution_clock::now();

    // --- START OF ORIGINAL PRESERVED LOGIC ---
    int *P1 = D_PTR(curr_last, 0);
    int *P2 = D_PTR(curr_last, current_n);
    int *P3 = D_PTR(curr_last, current_n * 2 - 1);

    const size_t memcpy_size = static_cast<size_t>(curr_2nd_last) * sizeof(int);

    for (int i = 0; i < current_n; i++) {
        for (int j = 0; j < i; j++) {
            *D_PTR(i, j) = j;
            *D_PTR(i, j + i + 1) = j;
        }
        *D_PTR(i, i) = i;
    }

    int i_loop = curr_3rd_last - 1;
    while (C[0] < 1) {
        for (int j = i_loop + 1; j < curr_last; j++) {
            const int* src_ptr = D_PTR(j - 1, C[j - 1]);
            std::memcpy(D_PTR(j, 0), src_ptr, static_cast<size_t>(j) * sizeof(int));
            std::memcpy(D_PTR(j, j + 1), src_ptr, static_cast<size_t>(j) * sizeof(int));
        }

        const int *src_ptr = D_PTR(curr_3rd_last, C[curr_3rd_last]);
        std::memcpy(P1, src_ptr, memcpy_size);
        *(P1 + curr_2nd_last) = curr_2nd_last;
        *(P1 + curr_last) = curr_last;
        std::memcpy(P2, src_ptr, memcpy_size);
        *(P2 + curr_2nd_last) = curr_2nd_last;
        std::memcpy(P3, src_ptr, memcpy_size);

        for (int circle_index = 0; circle_index < curr_last; circle_index++) {
            // Check and print permutations for small N
            if (current_n <= LITTLE_NUMBER) {
                for (int circlehead = circle_index; circlehead < circle_index + current_n; circlehead++) {
                    for (int oneperm = circlehead; oneperm < circlehead + current_n; oneperm++) {
                        printf("%d ", *D_PTR(curr_last, oneperm));
                    }
                    printf("\n");
                }
            }

            *D_PTR(curr_last, curr_last + circle_index) = *D_PTR(curr_last, current_n + circle_index);
            *D_PTR(curr_last, current_n + circle_index) = curr_last;
        }

        C[curr_3rd_last]++;
        for (i_loop = curr_3rd_last; (i_loop > 0) && (C[i_loop] > i_loop); i_loop--) {
            C[i_loop] = 0;
            C[i_loop - 1]++;
        }
    }
    // --- END OF ORIGINAL PRESERVED LOGIC ---

    auto end_point = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end_point - start_point;
    double duration = diff.count();

    printf("\n[METRIC_START]\n");
    printf("N_VALUE: %d\n", current_n);
    printf("TIME_SEC: %lf\n", duration);
    printf("[METRIC_END]\n");
    
    std::free(C);
    std::free(D_flat);

    return 0;
}
