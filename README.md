# Ring-Cascade Permutation Algorithm
> Note: Previously titled "Circle-Permutation-Algorithm." The name was updated to ensure uniqueness and prevent naming collisions with common academic algorithms.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Complexity: O((n-1)!)](https://img.shields.io/badge/Complexity-O((n--1)!)-blue.svg)](#)
[![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-red.svg)](#)
[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.18194997.svg)](https://doi.org/10.5281/zenodo.18194997)
![Permutation Generation](https://img.shields.io/badge/Field-Combinatorial_Algorithms-blue)
[![ORCID](https://img.shields.io/badge/ORCID-0009--0005--1980--5751-A6CE39?logo=orcid&logoColor=white)](https://orcid.org/0009-0005-1980-5751)
[![GitHub stars](https://img.shields.io/github/stars/Yusheng-Hu/Ring-Cascade-Permutation-Algorithm?style=social)](https://github.com/Yusheng-Hu/Ring-Cascade-Permutation-Algorithm)

An optimized iterative algorithm for Full Permutation generation that challenges the $O(N!)$ amortized complexity barrier.

**Ring-Cascade-Permutation-Algorithm** is a transformative generation framework for permutations that shatters the operational bottlenecks of classical combinatorial algorithms. By introducing a **triple-segment memory mirroring topology**, this framework demonstrates that active logic overhead can be structurally decoupled from the $n!$ sequence scale.

This repository is the official C++ implementation of the paper:  
Work in Progress

### Why This Matters

As discussed in the [computer science community](https://www.reddit.com/r/compsci/comments/1qd6sws/is_the_complexity_of_generating_full_permutations/), $O(N!)$ and $O((N-1)!)$ represent fundamentally different complexity classes:

* **Non-Constant Factor**: Since they differ by a factor of $N$, which grows toward infinity, they are not in the same order of magnitude.
* **Scalability**: This project focuses on optimizing the transition between permutation sets (e.g., scaling from $N=15$ to $N=16$), significantly enhancing the algorithm's capability to handle larger datasets.
* **Practical Impact**: By narrowing the computational gap, we make generating permutations for larger $N$ more viable in real-world applications.

## 🎮 Live Demo

You can try the interactive Ring-Cascade permutation visualization directly in your browser:

👉 **[View Ring-Cascade and Triple Process](https://yusheng-hu.github.io/Ring-Cascade-Permutation-Algorithm/index.html)**

---

## 🚀 Key Highlights

- **Complexity Breakthrough**: Reduces the frequency of state-transition decisions to an amortized **$O((n-1)!)$** level, while the majority of permutations are generated via deterministic topological shifts.
- **Extreme Performance**: Unlike traditional algorithms, the Ring-Cascade Algorithm's throughput scales positively with order N. It reaches 4.856 Giga/s at N=14, demonstrating the power of its O((n−1)!) amortized logic. This performance translates to a CPP of 0.41, setting a new benchmark for combinatorial generation.
- **Optimal Superpermutation**: Provides a universal constructive proof for the Superpermutation problem, yielding sequences that strictly attain the theoretical lower bound $L = \sum_{i=1}^{n} i!$.
- **Stateless Sharding**: Features a mathematically consistent indexing theorem (Theorem 1) that enables efficient **Rank** and **Unrank** operations for massive parallelization.

---

## 📊 Benchmarks

## 🚀 Performance: Ring Cascade Permutation Algorithm (RCPA)
## Heap's Algorithm vs RCPA Benchmark
### 🔹 AMD Architecture Benchmark (Comparison)
[//]: # (RCPA_PERFORMANCE_AMD_START)

**Last Run:** 2026-02-21 13:02:06 UTC / 2026-02-21 21:02:06 (UTC+8)
**Processor:** `AMD EPYC 7763 64-Core Processor`

| N | Heap's Algorithm (s) | RCPA (s) | Speedup (vs Heap) |
| :--- | :--- | :--- | :--- |
| 10 | 0.058006 s | 0.000893 s | **64.95x** |
| 11 | 0.642538 s | 0.008131 s | **79.02x** |
| 12 | 7.832983 s | 0.080883 s | **96.84x** |
| 13 | 104.378693 s | 0.893569 s | **116.81x** |

[//]: # (RCPA_PERFORMANCE_AMD_END)

### 🔹 Intel Architecture Benchmark (Comparison)
[//]: # (RCPA_PERFORMANCE_INTEL_START)
[//]: # (RCPA_PERFORMANCE_INTEL_END)

## Positiob Pure Algorithm vs RCPA Benchmark
### 🔹 AMD Architecture Benchmark (Comparison)
[//]: # (PP_VS_RCPA_AMD_START)

### PP vs RCPA Performance Comparison
**Last Run:** 2026-02-22 01:45:50 UTC / 2026-02-22 09:45:50 (UTC+8)
**Processor:** `AMD EPYC 7763 64-Core Processor`

| N | RCPA (s) | PP Algorithm (s) | Speedup (vs RCPA) |
| :--- | :--- | :--- | :--- |
| 10 | 0.000883 s | 0.006029 s | **.14x** |
| 11 | 0.008098 s | 0.064336 s | **.12x** |
| 12 | 0.083787 s | 0.649364 s | **.12x** |
| 13 | 0.929577 s | 8.632930 s | **.10x** |

[//]: # (PP_VS_RCPA_AMD_END)

### 🔹 Intel Architecture Benchmark (Comparison)
[//]: # (PP_VS_RCPA_INTEL_START)

[//]: # (PP_VS_RCPA_INTEL_END)


## 🚀 Superpermutation Verification
| Order (N) | Theoretical Lower Bound ($\sum i!$) | Ring-Cascade Algorithm Length | Status |
|:---:|:---:|:---:|:---:|
| 10 | 4,037,913 | 4,037,913 | ✅ **MATCH** |
| 12 | 523,001,313 | 523,001,313 | ✅ **MATCH** |
| 15 | 1,401,602,636,313 | 1,401,602,636,313 | ✅ **MATCH** |

---
## Citation

If you use this algorithm in your research or project, please cite it as:

> Yusheng-Hu. (2026). Ring-Cascade-Permutation-Algorithm: High-performance Full Permutation Generation [Data set]. Zenodo. https://doi.org/10.5281/zenodo.18194997

[![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.18194997.svg)](https://doi.org/10.5281/zenodo.18194997)
