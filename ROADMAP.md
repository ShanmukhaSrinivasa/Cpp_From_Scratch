# Daily C++ — From Zero to Building Your Own Game Engine

We start from the very beginning: what a program is, how a computer runs it,
your first line of C++. No prior C++ knowledge assumed.

The difference from a typical tutorial: every topic answers **"how does this actually
work underneath?"** — what the compiler does, where the data lives in memory, what the
CPU executes. That's what turns "I can write code" into "I understand code".

---

## How a day works (~60–90 min)

| Block | Time | What you do |
|---|---|---|
| 1. Recall | 10 min | Without looking, write 3 things you remember from yesterday. |
| 2. Concept | 25 min | Read the day's `LESSON.md`. Run every snippet yourself. |
| 3. Code | 30–45 min | Do the exercises in `EXERCISES.md`. Type everything — no copy/paste. |
| 4. Explain | 5–10 min | Fill in `NOTES.md`: explain the topic as if teaching a friend. If you can't explain it, you don't know it yet. |

**Every 7th day = Build Day**: a small program that uses the whole week.

### Working with me
- Say **"Day N"** → I write that day's lesson + exercises into `Day_NNN/`.
- Say **"review Day N"** → I review your code and notes (bugs, style, the "why").
- Ask "why?" anytime. Going deep on one question beats racing through topics.

---

## Phase 1 — Foundations (Weeks 1–4)

**Week 1 — First steps**
| Day | Topic |
|---|---|
| 1 | What a program is, how a computer runs it, your first C++ program |
| 2 | Variables: named boxes in memory |
| 3 | Data types: bits, bytes, binary, `int` / `float` / `char` / `bool` |
| 4 | Input, output & operators (math, precedence, integer division) |
| 5 | Decisions: `if`, `else`, `switch`, logical operators |
| 6 | Loops: `while`, `for`, `do-while`, `break` / `continue` |
| 7 | **Build Day:** number-guessing game |

**Week 2 — Organising code**
| Day | Topic |
|---|---|
| 8 | Functions: parameters, return values |
| 9 | Scope & the call stack — what happens in memory when you call a function |
| 10 | Arrays & loops over arrays |
| 11 | Strings (`std::string`) and characters |
| 12 | Using the debugger: breakpoints, stepping, watching variables |
| 13 | Random numbers, `const`, writing readable code |
| 14 | **Build Day:** text-based dungeon crawler |

**Week 3 — Memory**
| Day | Topic |
|---|---|
| 15 | Memory addresses & references |
| 16 | Pointers |
| 17 | Pass by value vs reference vs pointer |
| 18 | Stack vs heap, `new` / `delete`, memory leaks |
| 19 | `std::vector` — a growable array (and how it grows) |
| 20 | Undefined behaviour — when C++ lets you shoot yourself |
| 21 | **Build Day:** dynamic inventory system |

**Week 4 — Bigger programs**
| Day | Topic |
|---|---|
| 22 | `struct` — grouping data |
| 23 | `enum class` — named states (game states, item types) |
| 24 | Multiple files: headers & source files |
| 25 | The build pipeline in depth: preprocessor → compiler → assembler → linker |
| 26 | Reading compiler & linker errors like a pro |
| 27 | Review day — redo old exercises from memory |
| 28 | **Build Day:** multi-file turn-based battle game |

## Phase 2 — Object-Oriented C++ (Weeks 5–8)
- Classes, objects, `public` / `private`, member functions
- Constructors, initializer lists, destructors, object lifetime
- `const` member functions, `static` members
- Operator overloading — build a `Vector2` like Unity's
- Inheritance, `virtual` functions, **how vtables work**, `override`
- Copying objects — Rule of 0 / 3 / 5
- **Build Days:** RPG character system → `Vector2/Vector3` math library → enemy AI with polymorphism

## Phase 3 — Modern C++ & the Standard Library (Weeks 9–12)
- RAII — the most important idea in C++
- Smart pointers: `unique_ptr`, `shared_ptr`, `weak_ptr`
- Move semantics and rvalue references
- Lambdas, `std::function`
- Templates and `auto`, concepts (C++20)
- STL containers (`vector`, `map`, `unordered_map`, `set`…) and how they work inside
- `<algorithm>`, iterators, ranges, `optional`, `variant`, `string_view`
- **Build Days:** your own `DynamicArray<T>` → your own `UniquePtr<T>` → event system

## Phase 4 — Data Structures, Algorithms & Performance (Weeks 13–16)
- Big-O thinking, linked lists, stacks, queues, hash tables, trees, graphs
- Searching & sorting, pathfinding (BFS, A* — used in games)
- How the CPU sees memory: cache, why `vector` beats `list`
- Data-oriented design (the idea behind Unity DOTS), object pools, memory arenas
- CMake for real projects, profiling
- **Build Days:** A* pathfinding on a grid → object pool → benchmark experiments

## Phase 5 — Game Programming in C++ (Weeks 17–26)
- Window, input & rendering with **SDL3** (or raylib to start faster)
- The game loop: delta time, fixed timestep
- Game math: vectors, matrices, transforms
- Entity-Component-System from scratch
- Collision detection & simple physics
- Sprites, animation, audio, scenes
- **Projects:** Pong → Breakout → a small original platformer on *your own* engine

## Phase 6 — Next languages
| Language | Why |
|---|---|
| **C# (deep)** | You use it in Unity — GC, structs vs classes, Jobs/Burst. C++ makes this much easier. |
| **HLSL / GLSL** | Shaders — visuals and GPU performance in any engine. |
| **Python** | Tools, build scripts, asset pipelines, prototypes. |
| **Lua** | Embed it as a scripting language in your C++ engine. |
| **Rust** (optional) | Its ownership model vs C++ RAII deepens both. |

---

## References (use alongside the lessons)
- **learncpp.com** — free, excellent, matches this order closely.
- cppreference.com — the official-style documentation. You'll learn to read it.
- Compiler Explorer (godbolt.org) — see the machine code your C++ becomes.
- *Game Programming Patterns* (Robert Nystrom) — free online, perfect for Phase 5.

## Progress log
| Day | Topic | Done | Notes |
|---|---|---|---|
| 001 | What a program is & your first C++ program | ☑ | Reviewed. To fix in NOTES: Ex 3f, CPU vs compiler, compile time vs run time |
| 002 | Variables: named boxes in memory | ☑ | Reviewed. To fix in NOTES: "name exists in memory" vs compile-time-only, uninitialized-read danger (no error vs silent wrong value), Ex 5 `=` vs `{}` swapped |
