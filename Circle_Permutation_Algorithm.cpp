/**
 * @file Circle_Permutation_Algorithm.cpp
 * @brief High-performance Circle Permutation Algorithm (Optimized Iterative Implementation)
 * * @copyright Copyright (c) 2024 [ Yusheng-Hu ]. All rights reserved.
 * @license Licensed under the MIT License.
 * * Program Details:
 * - Implements a specialized circle permutation logic with memory-copy optimizations.
 * - Features: Windows CPU Affinity (Core 2), High-precision timing (QPC), 
 * and manual pointer arithmetic for performance.
 * * Environment:
 * - Platform: Windows (Requires <windows.h>)
 * - Compiler: Recommended g++ -O3 -march=native
 */

#include <cstdio>
#include <cstring>
#include <ctime>
#include <windows.h>

// ... 剩余代码#include <cstdio>
#include <cstring>
#include <ctime>
#include <windows.h>

#define N 14
// Uncomment the following line to enable output
// #define OUTPUT 1
#define lastIndex (N - 1)
#define secondLastIndex (N - 2)
#define thirdLastIndex (N - 3)

int main()
{
  // Set thread affinity to run on a specific CPU core (core index 2, which is the 3rd core)
  DWORD_PTR mask = 1ULL << 2;  // Bitmask for CPU core 2 (0-based index)
  HANDLE thread = GetCurrentThread();
  if (SetThreadAffinityMask(thread, mask) == 0)
  {
    printf("Failed to set thread affinity: %d\n", GetLastError());
    return 1;
  }
  printf("Running on CPU core %d\n", 2);

  time_t now = time(NULL);
  struct tm *tm = localtime(&now);
  printf("Now time: %02d:%02d:%02d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);

  static int C[N] = {0};
  static int D[N][3 * N] = {0};

  // High-precision timer variables for measuring program execution time
  LARGE_INTEGER start, finish, frequency;
  double duration;
  QueryPerformanceFrequency(&frequency);  // Get high-precision timer frequency
  QueryPerformanceCounter(&start);  // Record start time

  // Define and initialize three pointers pointing to different positions in the
  // last row of D array for better performance
  int *P1 = &D[lastIndex][0];         // Point to original position
  int *P2 = &D[lastIndex][N];         // Point to position with N offset
  int *P3 = &D[lastIndex][N * 2 - 1]; // Point to position with 2N-1 offset

  // Precompute the size for memcpy operations to avoid redundant calculations
  const size_t memcpy_size = static_cast<size_t>(secondLastIndex) * sizeof(int);

  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < i; j++)
    {
      D[i][j] = j;
      D[i][j + i + 1] = j;
    }
    D[i][i] = i;
  }

  // Main loop: Generate all possible permutations
  int i = thirdLastIndex - 1;
  while (C[0] < 1)
  {
    // Copy data from D[i-1] to D[i] based on the position of C[j-1]
    for (int j = i + 1; j < lastIndex; j++)
    {
      const int* src_ptr = &D[j - 1][C[j - 1]];
      memcpy(D[j], src_ptr, static_cast<size_t>(j) * sizeof(int));
      memcpy(&D[j][j + 1], src_ptr,static_cast<size_t>(j) * sizeof(int));
    }

    // Copy N-2 integers from D[N-3][C[N-3]] to three different positions
    const int *src_ptr = &D[thirdLastIndex][C[thirdLastIndex]];
    memcpy(P1, src_ptr, memcpy_size);
    *(P1 + secondLastIndex) = secondLastIndex;
    *(P1 + lastIndex) = lastIndex;
    memcpy(P2, src_ptr, memcpy_size);
    *(P2 + secondLastIndex) = secondLastIndex;
    memcpy(P3, src_ptr, memcpy_size);

    // Triple loop for output results
    for (int circle_index = 0; circle_index < lastIndex; circle_index++)
    {
      #ifdef OUTPUT
      // Output all permutations here. Note that enabling output will significantly increase program runtime.
      for (int circlehead = circle_index; circlehead < circle_index + N; circlehead++)
      {
        for (int oneperm = circlehead; oneperm < circlehead + N; oneperm++)
        {
          printf("%d ", D[lastIndex][oneperm]);
        }
        printf("\n");
      }
      #endif

      // Update the content of the last row of D array
        D[lastIndex][lastIndex + circle_index] = D[lastIndex][N + circle_index];
        D[lastIndex][N + circle_index] = lastIndex;
    }

    // Carry handling according to factorial base
    C[thirdLastIndex]++;
    for (i = thirdLastIndex; (i > 0) && (C[i] > i); i--)
    {
      C[i] = 0;
      C[i - 1]++;
    }
  }

  QueryPerformanceCounter(&finish);
  duration = static_cast<double>(finish.QuadPart - start.QuadPart) /
             static_cast<double>(frequency.QuadPart);
  printf("\ncircle.exe\t%u\t%lf", N, duration);

  // Prevent the compiler from optimizing too much
  if (D[lastIndex][lastIndex] == 100)
  {
    printf ("rare\n");
  }
  return 0;
}