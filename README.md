# ⚡️ Lightning-Fast Parallel Sudoku Batch Solver ⚡️

> Blast through **thousands** of puzzles in seconds—maximize your CPU’s potential with our battle-tested, ultra-optimized C/OpenMP engine.

---

## 🚀 What Makes This Solver Unstoppable?

* **True Multicore Mastery**

  * Auto-detects and saturates **all CPU cores** via OpenMP (`omp_get_num_procs()`).
  * **Dynamic work-stealing**: evenly distributes puzzles at runtime for zero thread idling.

* **In-Memory Superqueue**

  * Load **entire datasets** upfront to eliminate disk I/O stalls during computation.
  * Scales to **hundreds of thousands** of puzzles with minimal memory overhead.

* **Cutting-Edge Hybrid Algorithm**

  * **Constraint Propagation**: lightning-fast elimination of impossible candidates (naked singles, hidden singles, box-line interactions).
  * **Depth-First Backtracking**: kicks in only when needed, guaranteeing every puzzle finds its solution.

* **Granular Performance Telemetry**

  * **Precise solve time** measurement down to microseconds per puzzle.
  * Detailed **operation counts**: track propagation vs. backtracking to tune heuristics.
  * Output-ready **CSV logs** for integration with BI tools and dashboards.

* **Zero Dependencies Beyond C99 + OpenMP**

  * No external libs: lightning compile times, rock-solid portability on macOS, Linux, Windows (MSYS2).
  * Standard library only—easy integration into any CI/CD pipeline.

---

## 📁 Repository Blueprint

```text
sudoku-batch-parallel/
├── data
│   ├── input_shortened.csv
│   ├── output_average.csv
│   └── output.csv
├── include
│   └── sudoku.h
├── makefile
├── README.md
├── src
│   ├── backtrack.c
│   ├── box.c
│   ├── puzzle.c
│   ├── square.c
│   └── sudoku.c
├── sudoku_batch_parallel.c
├── Sudoku-Solver-Testing
│   ├── datahandle.py
│   └── plot.py
└── tls_vars.c
```

---

## 🛠️ Quickstart: Compile & Crush It

1. **Clone & Enter**

   ```bash
   git clone https://github.com/<you>/Sudoku-Solver-Parallel.git
   cd Sudoku-Solver-Parallel
   ```

2. **Compile with Maximal Optimizations**

   ```bash
   make all
   # or, manually:
   gcc-14 -std=c11 \
    -DBATCH_BUILD \
    -Iinclude/ \
    -O3 -Ofast -march=native -funroll-loops -flto -pipe -DNDEBUG \
    -fopenmp \
    sudoku_batch_parallel.c \
    src/sudoku.c src/backtrack.c src/box.c src/square.c src/puzzle.c \
    -lm -o sudoku_batch_parallel

   ```

3. **Prepare `input.csv`**

   ```csv
   puzzle,clue
   530070000600195000098000060800060003400803001700020006060000280000419005000080079,example-001
   ...
   ```

4. **Unleash the Solver**

   ```bash
   ./sudoku_batch_parallel
   ```

   Watch as `output.csv` fills with:

   ```csv
   clue,time_ms,backtracks,propagations
   example-001,0.045,0,210
   ...
   ```

---

## 📊 Benchmark & Visualize

* **Hyperfine** for rapid, statistical benchmarks across difficulty tiers.
* **CI Integration**: track mean solve time across commits with GitHub Actions.
* **Data Science Ready**: import `output.csv` into Python/R/Excel to chart solver performance trends.

---

## 🤝 Contribute & Collaborate

We welcome all improvements:

* Smarter propagation heuristics
* Alternative scheduling policies
* GPU offload prototypes
* 🛠️ Cross-platform CI workflows

Fork, tweak, and send a PR—let’s push the boundaries of Sudoku performance together!

---

## 📝 License & Credits

Distributed under the **MIT License**. See [LICENSE](LICENSE) for details.

Crafted with 💡 by Harsifat Singh • Let’s solve the unsolvable!
