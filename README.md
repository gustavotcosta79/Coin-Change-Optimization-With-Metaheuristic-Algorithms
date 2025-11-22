# Coin-Change-Optimization-with-metaheuristic-algorithms

**Course:** Artificial Intelligence (IIA)  
**Academic Year:** 2024/2025  

## 👥 Authors
- **Duarte Santos** — 2022149622  
- **Gustavo Costa** — 2023145800  

---

## 📋 Description
This project implements an **Evolutionary Algorithm (Genetic Algorithm)** to solve the *coin selection problem*, combined with a **local optimization technique** (Hill Climbing).

---

## 🎯 Objective
The goal is to find the best combination of coins that **minimizes the total cost**, while respecting a **constraint on the target value (V)**.

---

## 🏗️ Project Structure
```
├── TP2_IIA/ # Source code
│ ├── main.c # Main entry point
│ ├── algoritmo.c/h # Evolutionary algorithm implementation
│ ├── funcao.c/h # Evaluation/fitness functions
│ └── utils.c/h # Helpers and utility functions
├── docs/
│ ├── enunciado/ # Problem statement
│ └── relatorio/ # Report and results
├── CMakeLists.txt # CMake configuration
└── README.md # This file
```
---

## 🔧 Compilation

### 📦 Requirements
- **CMake 3.26+**
- **C compiler** with C11 support  
- GCC or Clang (Windows: MinGW or MSVC)

### 🏗️ Build Instructions

#### Using Terminal
```sh
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Compile
cmake --build .

Using CLion default build directory
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug

Basic run (2 runs by default)
./TP2_IIA <input_file>

Specify number of runs
./TP2_IIA <input_file> <num_runs>
Example:
./TP2_IIA file1.txt 10
```
⚙️ Algorithm Parameters

The algorithm parameters can be modified in main.c:
```
EA_param.popsize = 100;         // Population size
EA_param.numGenerations = 2500; // Number of generations
EA_param.pr = 0.7;              // Crossover probability
EA_param.pm = 0.001;            // Mutation probability
EA_param.crossover_type = 1;    // Crossover: (1 = 1-point, 2 = uniform)
EA_param.mutation_type = 1;     // Mutation: (1 = simple, 2 = swap)
EA_param.tsize = 2;             // Tournament size
```
