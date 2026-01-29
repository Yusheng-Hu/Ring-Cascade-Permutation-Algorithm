# ==========================================
# Copyright (c) 2024-2026 Yusheng-Hu
# Project: Circle-permutation-Algorithm
# Function: Universal Superpermutation Generator
# ==========================================

import sys
import os
import math

def merge_strings_without_duplicates(str1, str2):
    """
    Universal string merger: Concatenates two strings by removing the 
    longest common suffix of str1 and prefix of str2.
    """
    if str1 == str2:
        return str1
    
    max_overlap = 0
    min_len = min(len(str1), len(str2))
    
    # Check for the longest possible overlap from maximum length downwards
    for i in range(min_len, 0, -1):
        if str1[-i:] == str2[:i]:
            max_overlap = i
            break
            
    return str1 + str2[max_overlap:]

def generate_superpermutation(N):
    try:
        # ========== Array Definitions & Initialization ==========
        P = [0] * (N + 1)  # Carry tracking array
        D = [[0] * (2 * N + 2) for _ in range(N)] # Permutation matrix
        all_merged_string = ""
        
        # Initialize D array to build basic permutation logic
        for i in range(N):
            for jj in range(i):
                D[i][jj] = jj
                D[i][jj + i + 1] = jj
            D[i][i] = i
        
        # ========== Main Computation Loop (Universal Solution Path) ==========
        i = N - 3
        # Loop continues until all permutations in the sequence are covered
        while P[0] < 1:
            # Dynamic transformation of the D array
            for j in range(i + 1, N - 1):
                p_j_1 = P[j - 1]
                D[j][:j] = D[j - 1][p_j_1:p_j_1 + j]
                D[j][j + 1:j + 1 + j] = D[j - 1][p_j_1:p_j_1 + j]
            
            # Generate the current sequence segment
            next_arr = [0 for _ in range(3 * N + 3)]
            source_start = P[N - 3]
            source_end = source_start + (N - 1)
            next_arr[:N - 1] = D[N - 3][source_start:source_end]
            next_arr[N - 2] = N - 2
            next_arr[N - 1] = N - 1
            next_arr[N:N + (N - 1)] = next_arr[:N - 1]
            next_arr[N * 2 - 1:N * 2 - 1 + (N - 1)] = next_arr[:N - 1]
            
            # Core string generation and merging logic
            for ii in range(N - 1):
                for jj in range(ii, ii + N):
                    current_str = ""
                    for kk in range(jj, N + jj):
                        current_str += f"{next_arr[kk]:d}"
                    
                    # Clean the string and merge it into the main sequence
                    current_str = current_str.replace(" ", "").replace(",", "")
                    all_merged_string = merge_strings_without_duplicates(all_merged_string, current_str)
                
                # Update next_arr for the next iteration
                next_arr[N - 1 + ii] = next_arr[N + ii]
                next_arr[N + ii] = N - 1
            
            # Carry handling to navigate through permutations
            P[N - 3] += 1
            i = N - 3
            while i > 0 and P[i] > i:
                P[i] = 0
                P[i - 1] += 1
                i -= 1
        
        # ========== Output Results ==========
        # print(all_merged_string) # Uncomment to view the full sequence
        print(f"N value: {N}")
        print(f"Length of merged string: {len(all_merged_string)}")
        # OUTPUT all_merged_string
        if N <= 8:
            print(all_merged_string)
        
        # Verify result against the universal formula Σk!
        formula_val = sum(math.factorial(k) for k in range(1, N + 1))
        print(f"Formula value (sum(k!)): {formula_val}")
        print()  # Add a blank line for better readability
        
    except Exception as e:
        print(f"Error occurred for N={N}: {e}")
        import traceback
        traceback.print_exc()

def main():
    # Generate superpermutations for N=5, 6, 7
    for N in range(3, 8):
        print(f"Generating superpermutation for N={N}...")
        generate_superpermutation(N)

if __name__ == "__main__":
    main()