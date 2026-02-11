name: RCPA-vs-Heap-Comparison-Benchmark

on:
  workflow_dispatch:

permissions:
  contents: write

jobs:
  benchmark:
    name: Benchmark (N=${{ matrix.n_factor }})
    runs-on: ubuntu-latest
    strategy:
      fail-fast: false
      matrix:
        n_factor: [10, 11, 12]

    steps:
    - name: Checkout Repository
      uses: actions/checkout@v4

    - name: Detect CPU
      id: cpu_info
      run: |
        MODEL_NAME=$(grep -m 1 "model name" /proc/cpuinfo | cut -d: -f2 | xargs)
        if [[ "$MODEL_NAME" == *"AMD"* ]]; then VENDOR="AMD"; else VENDOR="INTEL"; fi
        echo "vendor_tag=$VENDOR" >> $GITHUB_OUTPUT
        echo "CPU_MODEL=$MODEL_NAME" >> $GITHUB_ENV

    - name: Compile
      run: |
        g++ -O3 -std=c++11 -march=native -ffast-math cpp/Ring_Cascade_Permutation_Algorithm.cpp -o rcpa_test -pthread
        g++ -O3 -march=native cpp/heap_perm.cpp -o heap_test -pthread

    - name: Execute
      run: |
        H_OUT=$(./heap_test ${{ matrix.n_factor }})
        H_TIME=$(echo "$H_OUT" | grep "EXECUTION_TIME:" | awk '{print $2}')
        R_OUT=$(./rcpa_test ${{ matrix.n_factor }})
        R_TIME=$(echo "$R_OUT" | grep "EXECUTION_TIME:" | awk '{print $2}')
        SPEEDUP=$(echo "scale=2; $H_TIME / $R_TIME" | bc)
        echo "N=${{ matrix.n_factor }}|H=$H_TIME|R=$R_TIME|S=$SPEEDUP" > res_${{ matrix.n_factor }}.txt

    - name: Upload
      uses: actions/upload-artifact@v4
      with:
        name: result-${{ matrix.n_factor }}-${{ steps.cpu_info.outputs.vendor_tag }}
        path: res_${{ matrix.n_factor }}.txt

  update-readme:
    needs: benchmark
    runs-on: ubuntu-latest
    steps:
    - name: Checkout Repository
      uses: actions/checkout@v4
      with:
        fetch-depth: 0
    
    - name: Download Results
      uses: actions/download-artifact@v4
      with:
        path: raw_data
        pattern: result-*

    - name: Sync to README
      shell: python
      run: |
        import os, glob, re
        from datetime import datetime, timezone, timedelta

        # 1. Vendor Identification
        all_dirs = glob.glob("raw_data/result-*")
        vendor = "AMD" if any("-AMD" in d for d in all_dirs) else "INTEL"
        
        # 2. MARKERS (Strictly matched to your request)
        start_tag = f"[//]: # (RCPA_PERFORMANCE_{vendor}_START)"
        end_tag = f"[//]: # (RCPA_PERFORMANCE_{vendor}_END)"
        
        # 3. Environment Info
        cpu_str = os.popen("grep -m 1 'model name' /proc/cpuinfo | cut -d: -f2").read().strip()
        now_utc = datetime.now(timezone.utc)
        now_bj = now_utc + timedelta(hours=8)
        ts_header = f"**Last Run:** {now_utc.strftime('%Y-%m-%d %H:%M:%S UTC')} / {now_bj.strftime('%Y-%m-%d %H:%M:%S (UTC+8)')}"
        
        # 4. Table Construction (NO STATUS COLUMN)
        table = [
            ts_header,
            f"**Processor:** `{cpu_str}`",
            "",
            "| N | Heap's Algorithm (s) | RCPA (s) | Speedup (vs Heap) |",
            "| :--- | :--- | :--- | :--- |"
        ]
        
        # 5. Data Processing
        data_points = []
        for f_path in glob.glob("raw_data/result-*/res_*.txt"):
            with open(f_path, 'r') as f:
                content = f.read().strip()
                m = re.search(r"N=(\d+)\|H=([\d.]+)\|R=([\d.]+)\|S=([\d.]+)", content)
                if m:
                    data_points.append(m.groups())
        
        for n, h, r, s in sorted(data_points, key=lambda x: int(x[0])):
            table.append(f"| {n} | {h} s | {r} s | **{s}x** |")

        final_content = "\n".join(table)
        
        # 6. Safety Write
        with open("README.md", "r", encoding="utf-8") as f:
            readme = f.read()
            
        pattern = re.escape(start_tag) + r".*?" + re.escape(end_tag)
        if re.search(pattern, readme, re.DOTALL):
            # This replaces the old table (with Status) with the new one (without Status)
            updated_readme = re.sub(pattern, f"{start_tag}\n\n{final_content}\n\n{end_tag}", readme, flags=re.DOTALL)
            with open("README.md", "w", encoding="utf-8") as f:
                f.write(updated_readme)
        else:
            print(f"Error: Required markers {start_tag} not found.")
            exit(1)

    - name: Commit and Push
      run: |
        git config --global user.name "github-actions[bot]"
        git config --global user.email "github-actions[bot]@users.noreply.github.com"
        git add README.md
        git commit -m "docs: sync results using RCPA_PERFORMANCE tags [skip ci]" || exit 0
        git push origin main
