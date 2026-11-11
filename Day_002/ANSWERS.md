# Day 2 — Answer Key & Revision Sheet

Use this for revising. Try to answer from memory **first**, then check here.
All code and error messages below were checked with g++ 16.1.0 (`-std=c++20 -Wall -Wextra`).

---

## ⚡ 60-second revision

- A variable's **name** is compile-time-only bookkeeping. At run time there is no
  `health`, only an address and the bytes at it. Compiling happens once; running
  happens later, repeatedly, without the compiler.
- **Declaration** reserves a box (`int score;`), **initialization** fills it at creation
  (`int score = 0;`), **assignment** changes an *existing* box (`score = 5;`, no type).
- An uninitialized variable holds **leftover garbage**, not zero — and reading it
  usually gives **no error at all**, just a silently wrong number. That silence is the
  danger, not a crash.
- You can't redeclare a name in the same scope, or use a name before its declaration.
- Today's types: `int`, `double`, `char` (single quotes `'A'`), `bool`, `std::string`
  (double quotes `"text"`, needs `#include <string>`).
- `=` silently truncates on data loss (`int x = 3.9;` → `3`, no warning). `{}` is
  stricter and **refuses to compile** on the same data loss (`int x{3.9};` → error).
- `std::cout << somePointer` prints the address in hex — **except** for `char*`, which
  it prints as text (reads bytes until a `0`). Cast to `(void*)` to see a `char`'s real
  address.

---

## Notes questions — model answers

### What happens in memory when I write `int health = 100;`?
At compile time, g++ reserves 4 bytes somewhere in the memory your program will use
while it runs, and privately notes "`health` means the box at this address" — purely for
its own translation purposes. Every later use of `health` becomes a direct read/write of
that address. Once compiling is done, the *name* `health` is gone; `hello.exe` contains
no trace of the word "health", only addresses and raw instructions. At run time the CPU
just moves the number `100` into that address — it has never heard of "health".

### What's the difference between declaration, initialization and assignment?
```cpp
int score;       // declaration only: reserves the box, leaves garbage inside
int lives = 3;   // declaration + initialization: reserves it AND fills it immediately
score = 10;      // assignment: changes an EXISTING box's value, no type needed
```
Declaration can happen without initialization (`int score;`) — that's when uninitialized
reads become possible.

### Why is reading an uninitialized variable dangerous, instead of just "it's zero"?
Because C++ does **not** clear memory for you — an uninitialized variable holds whatever
bits were already sitting at that address from whatever used it before. Crucially, this
is usually **not an error**: the program compiles, runs, and prints a plausible-looking
but wrong number, with nothing telling you something's off. (`-Wall -Wextra` catches some
obvious cases like this one, but not all — never rely on the warning showing up.) The
danger is the *silence*, not a crash.

### Why does `std::string` need double quotes but `char` needs single quotes?
`char` holds exactly **one** character, so single quotes (`'A'`) mark a single-character
literal. `std::string` holds a sequence of characters (text), so double quotes (`"Hero"`)
mark a string literal. Mixing them up is a compile error — see Ex 3e below.

---

## Ex 1 — Character sheet
```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name = "Hero";
    int health = 100;
    double moveSpeed = 5.5;
    char rank = 'A';
    bool isAlive = true;

    std::cout << name << "\n";
    std::cout << health << "\n";
    std::cout << moveSpeed << "\n";
    std::cout << rank << "\n";
    std::cout << isAlive << "\n";

    return 0;
}
```
Note: `std::cout << isAlive` prints `1` or `0`, not the words `true`/`false` — `bool`
printing as text (`std::boolalpha`) is a later topic.

## Ex 2 — Predict, then check: uninitialized
```cpp
#include <iostream>

int main()
{
    int score;
    std::cout << score << "\n";
    return 0;
}
```
Real g++ output:
```
uninitialized.cpp: In function 'int main()':
uninitialized.cpp:6:18: warning: 'score' is used uninitialized [-Wuninitialized]
    6 |     std::cout << score << std::endl;
      |                  ^~~~~
uninitialized.cpp:4:9: note: 'score' was declared here
```
It still compiles and runs (warnings don't block a build) and prints a different
"garbage" number on different runs — e.g. `32758` one time, something else the next. The
leftover bits in that memory depend on what the computer was doing right before.

## Ex 3 — Break it on purpose (real g++ messages)

| # | Mistake | g++ says |
|---|---|---|
| a | Declare `name` twice with different values | `error: redeclaration of 'std::string name'` |
| b | Use `name` in `cout` before its declaration | `error: 'name' was not declared in this scope` |
| c | `int 2ndHealth = 101;` | `error: expected unqualified-id before numeric constant` |
| d | `itn health1 = 99;` | `error: 'itn' was not declared in this scope; did you mean 'int'?` |
| e | `char value = "B";` | `error: invalid conversion from 'const char*' to 'char' [-fpermissive]` |

**Lessons from Ex 3:**
- **a** and **b** are the same underlying rule from two directions: a name only exists
  from its declaration onward, and only once, in a given scope.
- **d:** g++ is often smart enough to suggest the fix (`did you mean 'int'?`) when a typo
  is close to a real keyword — read the *whole* error, not just the first line.
- **e:** the compiler doesn't guess what you meant; `"B"` and `'B'` are genuinely
  different types (`const char*` vs `char`), and it reports exactly that type mismatch.

## Ex 4 — sizeof and addresses
```cpp
#include <iostream>

int main()
{
    int num1 = 100;
    double num2 = 3.14;
    char val1 = 'S';
    bool isNum = true;

    std::cout << "int: "    << sizeof(num1) << " bytes, " << &num1 << "\n";
    std::cout << "double: " << sizeof(num2) << " bytes, " << &num2 << "\n";
    std::cout << "char: "   << sizeof(val1) << " bytes, " << (void*)&val1 << "\n";
    std::cout << "bool: "   << sizeof(isNum) << " bytes, " << &isNum << "\n";

    return 0;
}
```
1. **Biggest / smallest:** `double` (8 bytes) is biggest; `char` and `bool` (1 byte
   each) are smallest.
2. **Contiguous?** Not exactly back-to-back — there are small gaps. That's **alignment
   padding**, which we'll cover properly when we look at memory layout in Week 3; for
   now just notice it exists.
3. **The `char` gotcha:** `std::cout << &val1` (without the `(void*)` cast) does **not**
   print an address — `char*` is special-cased by `<<` to mean "a string," so it prints
   characters starting at that address until it happens to hit a `0` byte:
   ```cpp
   std::cout << &val1;         // e.g. "Sp\xxx\xxxn3" — reads neighboring memory, UB
   std::cout << (void*)&val1;  // e.g. "0x336efff8cf" — the actual address
   ```
   This is undefined behavior (reading memory you never asked for) that happens to
   "work" often enough to be a classic beginner trap. Always cast to `(void*)` when you
   want to print a `char`'s address.

## Ex 5 — Predict, then check: narrowing
```cpp
int a = 7.8;    // a
int b{7.8};     // b
int c{7};       // c
```
| | Guess it right? | What g++ actually does |
|---|---|---|
| a | — | Compiles **clean**, no warning even with `-Wall -Wextra`. `a` becomes `7` (the `.8` is silently thrown away). |
| b | — | **`error: narrowing conversion of '7.7999999999999998e+0' from 'double' to 'int'`** — refuses to compile. |
| c | — | Compiles clean, `c` becomes `7` — no data is lost, so there's nothing to warn about. |

The takeaway: `=` trusts you completely, even when data is silently lost; `{}` double-
checks and refuses when a conversion could lose data. Neither is "wrong" — they're
different trade-offs, and this is exactly why some codebases prefer `{}` by default.

## Ex 6 — Swap two variables
```cpp
#include <iostream>

int main()
{
    int a = 9;
    int b = 18;

    std::cout << "Before: a=" << a << " b=" << b << "\n";

    int temp = a;   // save a's value before it's overwritten
    a = b;          // a now has b's old value
    b = temp;       // b now has a's original value

    std::cout << "After: a=" << a << " b=" << b << "\n";

    return 0;
}
```
Why `a = b; b = a;` alone fails: the first line overwrites `a`'s original value for
good — by the second line, `a` and `b` already hold the *same* value, so both end up
equal to whatever `b` originally was. You need somewhere to park one value before it's
overwritten — that's what the extra (`temp`) variable is for.

## Ex 7 — Simple score tracker
```cpp
#include <iostream>

int main()
{
    int score = 0;
    std::cout << "Score: " << score << "\n";

    score += 10;    // killed an enemy
    std::cout << "Score: " << score << "\n";

    score += 25;    // completed objective
    std::cout << "Score: " << score << "\n";

    score -= 5;     // took a penalty
    std::cout << "Score: " << score << "\n";

    double celsius = 37.0;
    double fahrenheit = celsius * 9.0 / 5.0 + 32.0;
    std::cout << celsius << "C = " << fahrenheit << "F\n";

    return 0;
}
```
Final score: `0 → 10 → 35 → 30`. `37.0°C = 98.6°F`. Writing `+ 32` instead of `+ 32.0`
also works fine here — C++ automatically promotes the `int` `32` to `double` in a mixed
expression — but spelling out `32.0` makes the intent ("this is a decimal calculation")
obvious to a reader.
