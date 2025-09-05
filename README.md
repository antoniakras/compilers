# 🛠️ Custom Compiler (Compilers Course Project)

## 📖 About

This project implements a **compiler from scratch** for a toy programming language, developed in C as part of the *Compilers* course.  
The compiler is built step by step across five phases, covering the **full compilation pipeline** from source code to binary execution.

---

## ✨ Features & Highlights

- **Lexical Analysis (Phase 1)**
  - Implemented with **flex**.
  - Tokenizes source code into keywords, identifiers, literals, operators, and symbols.
  - Detects invalid tokens and lexical errors.

- **Syntax Analysis (Phase 2)**
  - Parses tokens according to the language grammar.
  - Validates program structure (statements, expressions, blocks).
  - Produces parse trees for further compilation steps.

- **Intermediate Representation (Phase 3)**
  - Generates an **assembly-like IR (Intermediate Representation)**.
  - Designed a symbol table for variables, functions, and scope resolution.
  - Includes jumps, labels, function calls, and system calls.
  - Simplifies translation into machine code.

- **Code Generation (Phase 4)**
  - Translates IR into **assembly/machine code instructions**.
  - Manages variables, memory layout, and registers.

- **Binary Translation (Phase 5)**
  - Produces executable **binary/machine code**.
  - End-to-end pipeline: input source → compiled binary.

---

## 🧩 Language Features

The custom toy language supports:

- **Variables & Assignments**  
  `x = 5; y = x + 3;`

- **Arithmetic Expressions**  
  Addition, subtraction, multiplication, division, precedence handling.

- **Boolean Expressions**  
  Comparisons (`==`, `!=`, `<`, `>`, etc.) and logical operators.

- **Control Flow**  
  - `if` / `if-else`  
  - `while` loops  

- **Functions**
  - Function declarations with parameters.  
  - Function calls and return values.

- **Error Handling**
  - Reports syntax and lexical errors gracefully.

---

## 🛠️ Setup & Run

1. Clone the repository:
   ```bash
   git clone https://github.com/antoniakras/compilers.git
   cd compilers
   make
   ./compiler input_file.src -o output.bin
