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
├── input.csv               # Input: puzzle (81 digits), optional clue ID
├── output.csv              # Generated: clue, time_ms, backtracks, propagations
├── sudoku_batch_parallel.c # High-performance parallel batch driver
├── include/
│   └── sudoku.h            # Solver API + OpenMP threadprivate directives
├── src/                    # Core solver implementation
│   ├── sudoku.c            # Constraint + backtracking engine
│   ├── backtrack.c         # Recursive search routines
│   ├── box.c               # Box-centric elimination logic
│   ├── square.c            # Cell data structures & helpers
│   └── puzzle.c            # CSV parsing and grid builder
├── Makefile                # Preconfigured build targets
├── .github/workflows/ci.yml# Optional: performance regression tests
└── README.md               # This epic guide
```

---

## 🛠️ Quickstart: Compile & Crush It

1. **Clone & Enter**

   ```bash
   git clone https://github.com/<you>/sudoku-batch-parallel.git
   cd sudoku-batch-parallel
   ```

2. **Compile with Maximal Optimizations**

   ```bash
   make all
   # or, manually:
   gcc -std=c11 -Iinclude/ -O3 -march=native -funroll-loops -flto -pipe \  
       -DNDEBUG -fopenmp sudoku_batch_parallel.c src/*.c -lm -o solver
   ```

3. **Prepare `input.csv`**

   ```csv
   puzzle,clue
   530070000600195000098000060800060003400803001700020006060000280000419005000080079,example-001
   ...
   ```

4. **Unleash the Solver**

   ```bash
   ./solver
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

Crafted with 💡 by \Harsifat Singh • Let’s solve the unsolvable!
