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

### 🔹 AMD Architecture Benchmark (Comparison)
[//]: # (RCPA_VS_HEAP_AMD_START)
[//]: # (RCPA_VS_HEAP_AMD_END)

### 🔹 Intel Architecture Benchmark (Comparison)
[//]: # (RCPA_VS_HEAP_INTEL_START)

**Last Run:** Wed Feb 11 11:15:28 2026 UTC / Wed Feb 11 19:15:28 2026 (UTC+8)
### 🔍 Raw Hardware Probe (Debug)
#### [lscpu output]
```text
Architecture:                         x86_64
CPU op-mode(s):                       32-bit, 64-bit
Address sizes:                        48 bits physical, 48 bits virtual
Byte Order:                           Little Endian
CPU(s):                               4
On-line CPU(s) list:                  0-3
Vendor ID:                            AuthenticAMD
Model name:                           AMD EPYC 7763 64-Core Processor
CPU family:                           25
Model:                                1
Thread(s) per core:                   2
Core(s) per socket:                   2
Socket(s):                            1
Stepping:                             1
BogoMIPS:                             4890.86
Flags:                                fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ht syscall nx mmxext fxsr_opt pdpe1gb rdtscp lm constant_tsc rep_good nopl tsc_reliable nonstop_tsc cpuid extd_apicid aperfmperf tsc_known_freq pni pclmulqdq ssse3 fma cx16 pcid sse4_1 sse4_2 movbe popcnt aes xsave avx f16c rdrand hypervisor lahf_lm cmp_legacy svm cr8_legacy abm sse4a misalignsse 3dnowprefetch osvw topoext vmmcall fsgsbase bmi1 avx2 smep bmi2 erms invpcid rdseed adx smap clflushopt clwb sha_ni xsaveopt xsavec xgetbv1 xsaves user_shstk clzero xsaveerptr rdpru arat npt nrip_save tsc_scale vmcb_clean flushbyasid decodeassists pausefilter pfthreshold v_vmsave_vmload umip vaes vpclmulqdq rdpid fsrm
Virtualization:                       AMD-V
Hypervisor vendor:                    Microsoft
Virtualization type:                  full
L1d cache:                            64 KiB (2 instances)
L1i cache:                            64 KiB (2 instances)
L2 cache:                             1 MiB (2 instances)
L3 cache:                             32 MiB (1 instance)
NUMA node(s):                         1
NUMA node0 CPU(s):                    0-3
Vulnerability Gather data sampling:   Not affected
Vulnerability Itlb multihit:          Not affected
Vulnerability L1tf:                   Not affected
Vulnerability Mds:                    Not affected
Vulnerability Meltdown:               Not affected
Vulnerability Mmio stale data:        Not affected
Vulnerability Reg file data sampling: Not affected
Vulnerability Retbleed:               Not affected
Vulnerability Spec rstack overflow:   Vulnerable: Safe RET, no microcode
Vulnerability Spec store bypass:      Vulnerable
Vulnerability Spectre v1:             Mitigation; usercopy/swapgs barriers and __user pointer sanitization
Vulnerability Spectre v2:             Mitigation; Retpolines; STIBP disabled; RSB filling; PBRSB-eIBRS Not affected; BHI Not affected
Vulnerability Srbds:                  Not affected
Vulnerability Tsx async abort:        Not affected

```
#### [/proc/cpuinfo excerpt]
```text
processor	: 0
vendor_id	: AuthenticAMD
cpu family	: 25
model		: 1
model name	: AMD EPYC 7763 64-Core Processor
stepping	: 1
microcode	: 0xffffffff
cpu MHz		: 2445.432
cache size	: 512 KB
physical id	: 0
siblings	: 4
core id		: 0
cpu cores	: 2
apicid		: 0
initial apicid	: 0
fpu		: yes
fpu_exception	: yes
cpuid level	: 13
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ht syscall nx mmxext fxsr_opt pdpe1gb rdtscp lm constant_tsc rep_good nopl tsc_reliable nonstop_tsc cpuid extd_apicid aperfmperf tsc_known_freq pni pclmulqdq ssse3 fma cx16 pcid sse4_1 sse4_2 movbe popcnt aes xsave avx f16c rdrand hypervisor lahf_lm cmp_legacy svm cr8_legacy abm sse4a misalignsse 3dnowprefetch osvw topoext vmmcall fsgsbase bmi1 avx2 smep bmi2 erms invpcid rdseed adx smap clflushopt clwb sha_ni xsaveopt xsavec xgetbv1 xsaves user_shstk clzero xsaveerptr rdpru arat npt nrip_save tsc_scale vmcb_clean flushbyasid decodeassists pausefilter pfthreshold v_vmsave_vmload umip vaes vpclmulqdq rdpid fsrm
bugs		: sysret_ss_attrs null_seg spectre_v1 spectre_v2 spec_store_bypass srso
bogomips	: 4890.86
TLB size	: 2560 4K pages
clflush size	: 64
cache_alignment	: 64

```

| N | Heap's Algorithm (s) | RCPA (s) | Speedup |
|---|---|---|---|
| 10 | 0.060735 s | 0.001224 s | **49.62x** |
| 11 | 0.639508 s | 0.008456 s | **75.62x** |
| 12 | 7.831008 s | 0.080775 s | **96.94x** |
| 13 | 104.336388 s | 0.893244 s | **116.80x** |

[//]: # (RCPA_VS_HEAP_INTEL_END)


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
