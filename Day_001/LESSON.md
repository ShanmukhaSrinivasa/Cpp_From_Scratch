# Day 1 — What is a program, and your first C++ program

**Goal for today:**
1. Know what a computer actually does when it "runs a program".
2. Know why C++ needs a *compiler*.
3. Write, compile and run your first C++ program, and understand every character of it.

---

## 1. What a computer really does

Under all the windows and games, a computer has two main parts you care about:

- **CPU (processor):** a machine that can only do very simple things, very fast:
  add two numbers, compare two numbers, copy a number from one place to another,
  jump to a different instruction. That's mostly it. A modern CPU does *billions*
  of these per second.
- **Memory (RAM):** a huge row of numbered boxes. Each box holds one **byte**
  (a number from 0 to 255). The box's number is its **address**.

```
Address:   0     1     2     3     4     5   ...  16,000,000,000
         ┌─────┬─────┬─────┬─────┬─────┬─────┬──
Value:   │ 72  │ 105 │  0  │ 255 │ 12  │  7  │ ...
         └─────┴─────┴─────┴─────┴─────┴─────┴──
```

A **program** is just a list of those tiny CPU instructions stored in memory.
The CPU reads them one by one and does what they say.

Everything in a game — Mario's position, your health bar, the colour of a pixel —
is just numbers in those boxes, being changed by those tiny instructions.

## 2. Why we need a programming language and a compiler

The CPU only understands **machine code**: raw numbers like `01 C8 C3`.
Nobody wants to write that. So we write in a human-friendly language (C++), and a
program called a **compiler** translates it into machine code.

```
 hello.cpp  ──►  [ compiler: g++ ]  ──►  hello.exe  ──►  CPU runs it
 (text you      (translator)            (machine code)
  write)
```

- **C++ is compiled ahead of time.** You translate once, then the `.exe` runs directly
  on the CPU. That's why it's fast — and why game engines (Unreal, Unity's own core,
  Godot) are written in C++.
- C# in Unity works differently: it's compiled to an in-between language first and
  translated to machine code later. More convenient, less control.

## 3. Your first program

```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, World!\n";
    return 0;
}
```

Every piece, line by line:

| Code | Meaning |
|---|---|
| `#include <iostream>` | "Paste in the code that knows how to do input/output (**i**nput **o**utput **stream**)." Without it, C++ doesn't know what `std::cout` is. |
| `int main()` | Defines a **function** called `main`. Every C++ program starts running at `main` — this is the front door. `int` means it gives back a whole number when it ends. |
| `{` `}` | The **body** — everything between the braces belongs to `main`. |
| `std::cout` | "**c**haracter **out**put" — the console/terminal. `std::` means it lives in the **st**andar**d** library. |
| `<<` | "Send this into" — push the text into `cout`. |
| `"Hello, World!\n"` | A **string** (text). `\n` means "new line". |
| `;` | Ends a statement — like a full stop in a sentence. Forgetting it is the #1 beginner error. |
| `return 0;` | `main` ends and reports `0` to the operating system, meaning "everything went fine". |

## 4. Compile and run it

In the VS Code terminal, inside the `Day_001` folder:

```bash
g++ hello.cpp -o hello.exe
```
- `g++` — the compiler
- `hello.cpp` — your source code (input)
- `-o hello.exe` — **o**utput file name

Then run it:
```bash
./hello.exe
```

You should see `Hello, World!`. You just turned text into machine code and made a CPU run it. 🎉

### A better compile command (use this from now on)
```bash
g++ -std=c++20 -Wall -Wextra hello.cpp -o hello.exe
```
- `-std=c++20` — use the modern C++20 version of the language
- `-Wall -Wextra` — turn on **warnings**: the compiler points out code that is legal but probably a mistake. Professionals always keep warnings on.

## 5. Errors are your friend

When the compiler can't understand your code, it stops and tells you where:

```
hello.cpp:5:10: error: 'cot' is not a member of 'std'; did you mean 'oct'?
   ^      ^ ^
   file   line column
```

Read it like this: **file : line : column : what's wrong.** Always fix the **first**
error first — one mistake often causes a pile of follow-up errors.

---

## Key ideas to remember
- The CPU runs simple instructions; memory is a long row of numbered byte-boxes.
- A compiler translates C++ text into machine code (`.exe`).
- Every program starts at `main()`.
- Statements end with `;`.
- Compiler error format: `file:line:column: error: message` — fix the first one first.

Now go to `EXERCISES.md`.
