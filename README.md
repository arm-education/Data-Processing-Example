# Data Processing Example

##  Description

This repository is a toy data processing example for educational purposes, implemented in C++20 with two execution paths:
- Baseline generation using the C++ standard library random engine (`std::mt19937`)
- Accelerated generation using Arm Performance Libraries (APL)

The main program (`src/main.cpp`) follows a simple pipeline:
- Generates a distribution of 2D points by combining Gaussian and uniform random values
- Counts how many points fall inside a rectangular window
- Uses a basic reduction function (`min_length`) to find the point with the smallest magnitude from the origin

![Vector data output](./vector_data.png)

The repository also includes microbenchmarks for runtime comparison and a Python script for visualizing generated vector data from CSV output.

## What This Project Uses

- C++20
- CMake (build system)
- GNU C++ compiler (`g++`)
- Arm Performance Libraries (optional accelerated path)
- Python 3 + `numpy`, `pandas`, `matplotlib` for visualization

## Repository Layout

- `src/`: core implementation (`vec1d`, geometry utilities, data export, main entrypoint)
- `include/`: public headers
- `tests/`: sweep microbenchmark + visualization data generator
- `scripts/`: Python plotting/animation script
- `vector_data.csv`: sample generated dataset

## Build Commands

### 1) Baseline build (no APL)

```bash
cmake -S . -B build
cmake --build build --target main
./build/src/main
```


### 2) Build with Arm Performance Libraries (APL)

Before building, ensure [Arm Performance Libraries have been installed](https://learn.arm.com/install-guides/armpl/) and the environment module has been loaded.

```bash
cmake -S . -B build -DUSE_APL=1
cmake --build build --target main_with_apl
./build/src/main_with_apl
```

This repository also includes a small sweep microbenchmark. To build it, add `-DBUILD_TESTS=1` to the CMake configuration command.

## Visualization

Generate visualization data (baseline):

```bash
cmake -S . -B build -DBUILD_TESTS=1
cmake --build build --target generate_visualization_baseline
./build/tests/generate_visualization_baseline
```

Then render with Python:

```bash
python3 -m venv venv
source venv/bin/activate
pip install -r scripts/requirements.txt
python3 scripts/visualize_vectors.py
```

## License

This project is available under the Arm Education End User License Agreement in `LICENSE.md` (non-commercial educational use terms apply).