# Day 1 — Answer Key & Revision Sheet

Use this for revising. Try to answer from memory **first**, then check here.
All code and error messages below were checked with g++ 14.2 (`-std=c++20 -Wall -Wextra`).

---

## ⚡ 60-second revision

- **CPU** — runs tiny instructions (add, compare, copy, jump), billions per second. It **cannot read C++**.
- **Memory (RAM)** — a long row of numbered boxes. Each box holds **1 byte** (0–255). The box's number is its **address**. It's *volatile*: wiped when power is off.
- **Compiler (g++)** — a program that **translates** C++ text into machine code (`.exe`). C++ needs one because the CPU only understands machine code.
- **Compile time ≠ run time.**
  ```
  COMPILE TIME:  g++ reads hello.cpp → writes hello.exe → g++ is finished
  RUN TIME:      you run hello.exe  → the CPU runs its instructions → output appears
  ```
- Every program starts at **`main()`**. Statements end with **`;`**.
- Error format: **`file:line:column: error: message`** — fix the **first** error first.
- **Editor squiggles (IntelliSense) ≠ compiler errors.** The terminal output from g++ is the real judge.

---

## Notes questions — model answers

### What does the CPU do?
The CPU (Central Processing Unit) runs **machine-code instructions**, one after another, very fast.
Each instruction is tiny: add two numbers, compare two numbers, copy a value from one
memory address to another, jump to a different instruction.

It does **not** compile your code and it can't read C++. *Both* g++ and your `hello.exe`
are programs made of machine code, so the CPU runs both — g++ first (to make the `.exe`),
then your `.exe` later.

*Bonus:* a CPU seems to do "many tasks at a time" because it has several **cores**
(each runs its own instruction stream) and the operating system switches between
programs thousands of times per second.

### What is memory?
RAM is fast, **temporary** storage the CPU uses while programs run (erased when the
power is off). Picture it as a long row of numbered boxes:
- each box holds **one byte** (a number from 0 to 255),
- each box's number is its **address**.

Everything a program works with — text, your player's health, a pixel's colour —
is stored as numbers in these boxes.

### What does a compiler do, and why does C++ need one?
A compiler **translates** C++ source code into **machine code** that the CPU can run,
and saves it as an executable file (`hello.exe`). It also checks your code and reports
errors if it can't understand it.

C++ needs one because the CPU only understands machine code, not C++ text.
C++ is compiled **ahead of time**: you translate once, and afterwards the `.exe` runs
on its own — the compiler is not involved anymore. That's part of why C++ is fast.

### What does each line of Hello World mean?
```cpp
#include <iostream>
int main()
{
    std::cout << "Hello, World!\n";
    return 0;
}
```
| Line | Meaning |
|---|---|
| `#include <iostream>` | Pastes in the standard library code for input/output, so C++ knows what `std::cout` is. |
| `int main()` | Defines the function `main`, where every C++ program **starts**. `int` = it returns a whole number when it finishes. |
| `{` … `}` | The body of `main`: everything between the braces belongs to it. |
| `std::cout << "Hello, World!\n";` | Sends the text into `std::cout` (the console). `std::` = it comes from the **standard** library. `\n` = new line. `;` ends the statement. |
| `return 0;` | Ends `main` and gives `0` to the **operating system**, meaning "success". |

> Small correction: `std` is a *namespace* (a named group of standard-library things), and
> `std::cout` means "the `cout` that lives inside `std`". We'll study namespaces later.

---

## Ex 1 — Hello, World
```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, World!\n";
    return 0;
}
```
```bash
g++ -std=c++20 -Wall -Wextra hello.cpp -o hello.exe
./hello.exe
```
No message after the compile command = it **succeeded**.

## Ex 2 — Talk about yourself
```cpp
#include <iostream>

int main()
{
    // Way 1: three statements
    std::cout << "Hi, I'm <your name>.\n";
    std::cout << "I make games in Unity.\n";
    std::cout << "I'm learning C++ to build my own engine.\n";

    // Way 2: one statement, \n for each line break
    std::cout << "Hi, I'm <your name>.\nI make games in Unity.\nI'm learning C++ to build my own engine.\n";

    return 0;
}
```

## Ex 3 — Break it on purpose (real g++ messages)

| # | Mistake | g++ says | Which tool |
|---|---|---|---|
| a | Delete `;` after the `cout` line | `error: expected ';' before 'return'` | Compiler |
| b | `cout` → `cot` | `error: 'cot' is not a member of 'std'; did you mean 'oct'?` | Compiler |
| c | Delete `#include <iostream>` | `error: 'cout' is not a member of 'std'` | Compiler |
| d | Delete the closing `"` | `error: missing terminating " character` (then follow-up errors) | Compiler |
| e | Delete the final `}` | `error: expected '}' at end of input` | Compiler |
| f | `main` → `Main` | `undefined reference to 'WinMain'` … `ld returned 1 exit status` | **Linker** (`ld`) |

**Lessons from Ex 3:**
- **a:** the error points at the line *after* the missing `;` (`before 'return'`). The compiler only
  notices something is wrong when it reaches the next thing. When an error makes no sense,
  look at the line **above**.
- **c:** without the `#include`, the code for `std::cout` never gets pasted in, so the
  compiler has never heard of it.
- **d:** one mistake → several errors. Always fix the **first** one, then recompile.
- **f:** this is the only one that is **not** a compiler error. Your code is valid C++ — a
  function called `Main` is fine. But the program's start-up code looks for `main` to call,
  can't find it, and the **linker** (the last step of building) fails. On Windows/MinGW it
  searches for `WinMain` as a fallback, which is why that name appears.
  If you see "no error" here, you probably ran the **old** `.exe` without recompiling, or only
  looked at the editor's squiggles (they don't run the linker).

## Ex 4 — Escape sequences
| Escape | Meaning |
|---|---|
| `\n` | New line |
| `\t` | Tab (jump to the next tab stop) |
| `\"` | A `"` inside a string (without ending the string) |
| `\\` | A single `\` |
| `\a` | "Alert" — makes a beep on some terminals; in VS Code you usually see/hear nothing |

```cpp
std::cout << "She said \"Level complete!\" and saved to C:\\Games\\save.dat\n";
```
Watch out: `"\n" << std::endl` ends the line **twice** → blank lines. Use one or the other.

## Ex 5 — ASCII art
```cpp
#include <iostream>

int main()
{
    std::cout << "   O\n";
    std::cout << "  /|\\\n";     // \\ prints one \ , then \n ends the line
    std::cout << "  / \\\n";
    std::cout << " PLAYER 1\n";
    return 0;
}
```
Output:
```
   O
  /|\
  / \
 PLAYER 1
```
**Gotcha:** a `\` at the very end of a line (even inside a comment) joins it with the next
line. g++ `-Wall` warns about it. That's why pasting the output with `/|\` into a comment gave a warning.

## Ex 6 — Curiosity questions
**1. Why is `hello.exe` (~64 KB) so much bigger than `hello.cpp` (~100 bytes)?**
The `.exe` holds much more than your code:
- **start-up code** that runs *before* `main` (prepares the program, then calls `main`, then
  passes its return value to the OS),
- the parts of the **standard library** needed to make `std::cout` work,
- file headers and information Windows needs to load the program.

Your own code becomes only a few dozen bytes of machine code.

**2. What happens with `return 7;`, and who gets the number?**
`echo $LASTEXITCODE` shows `7`. The return value of `main` is the program's **exit code**,
and it goes to the **operating system** (here, PowerShell, which started the program).
`0` means success; anything else usually means "something went wrong". Scripts and
build tools check this number to see if a program failed.

**3. What do the delete experiments prove?**
- No `.exe` → can't run anything: the CPU needs machine code.
- No `.cpp` but the `.exe` is still there → it still runs.

So the computer only needs the **`.exe`** to run the program. The `.cpp` is only for humans
and the compiler. **Compiling happens once, earlier; running happens later, without the compiler.**
(This is also why players of your games never need your source code.)
