# Day 6 — Answer Key & Revision Sheet

Use this for revising. Try to answer from memory **first**, then check here.
All code, warnings, errors and outputs below were checked with g++ 16.1.0 (`-std=c++20 -Wall -Wextra`).

---

## ⚡ 60-second revision

- `while (cond)` checks **before** each run (may run 0 times).
  `do { } while (cond);` runs **once first**, then checks (note the `;`).
  `for (start; cond; step)` is a counting `while`.
- Something in the loop must make the condition false, or it never ends. **Ctrl + C** stops it.
- `i++` / `++i` both add 1. They only differ when the value is used in the same expression:
  `b = a++` gives `b` the **old** value; `c = ++a` gives `c` the **new** one.
- `for (int i = 0; i < n; i++)` runs exactly `n` times. `<=` runs `n + 1` (**off-by-one**).
- A variable declared in a `for`'s start part only exists inside the loop.
- To the CPU, a loop is **compare + jump backwards**. `for` and `while` compile to the
  **identical** instructions.
- `break` leaves the **innermost** loop. `continue` jumps to the next check (in a `for`,
  the step runs first; in a `do-while`, it goes to the `while (...)` check).
- Traps: stray `;` after `for`, `=` vs `==`, `unsigned` counting down past 0, `double`
  loop counters.
- Retry on bad input: `fail()` → `clear()` (reset the **state**) → `ignore(...)` (throw away
  the **text**) → `continue`. Both are needed.
- **Warning** = suspicious but still builds an `.exe`. **Error** = no `.exe` at all.

---

## Notes questions — model answers

### What's the difference between `while`, `do-while` and `for`? When would I pick each?
- `while`: checks first, so it can run **zero** times. Use it when you don't know in
  advance how many runs you need ("while the player is alive").
- `do-while`: runs the body first, checks after, so it runs **at least once**. Use it when
  something must happen before you can test it ("show the menu, then check the choice").
- `for`: a `while` with the start, condition and step in one line. Use it when you're
  **counting** ("10 times", "every column").

All three can do the same job; picking the right one just makes the intent obvious.

### What does the CPU actually do to make a loop repeat?
It compares, then does a conditional **jump backwards** to the start of the body. The
`for` loop in `sumTo` becomes `cmpl` + `jle .L3`, where `.L3` is a label **above** the
jump. When the condition is false, the jump doesn't happen and the CPU continues with the
next instruction after the loop.

### What's the difference between `i++` and `++i`, and when does it matter?
Both add 1 to `i`. The difference is the **value of the expression**:
```cpp
int i = 10;
int a = i++;   // a = 10 (old value), then i becomes 11
int b = ++i;   // i becomes 12 first, then b = 12
```
On a line by itself (`i++;`), or as a `for` step, there's no difference.

### What do `break` and `continue` each do? What does `break` do inside a nested loop?
`break` leaves the loop immediately. `continue` skips the rest of the current run and goes
to the next check. In nested loops, both only affect the **innermost** loop they're in.

### Why is `for (unsigned int u = 3; u >= 0; u--)` an infinite loop?
`u` **does** reach `0`. What it can never be is **negative**: an `unsigned` has no negative
values at all. So `u >= 0` is always true, and when `u` is `0`, `u--` wraps around (Day 3)
to the largest `unsigned int`, `4294967295`, and the loop keeps counting down from there.
g++ warns: `comparison of unsigned expression in '>= 0' is always true [-Wtype-limits]`.

### To retry bad input, why do I need **both** `clear()` and `ignore(...)`?
They fix two different problems:
1. A failed read puts `std::cin` into a **failed state**. While it's in that state, every
   `>>` fails instantly, without even looking at the input. `clear()` resets the state.
   It does **not** remove anything from the input.
2. The bad text (`abc`) is **still waiting** in the input. After `clear()`, the next `>>`
   tries to read `abc` again and fails again. `ignore(...)` throws that line away.

Leave out either one and the loop repeats forever.

---

## Ex 1 — Counting three ways
```cpp
#include <iostream>

int main()
{
    int countdown = 10;
    while (countdown > 0)
    {
        std::cout << countdown << "\n";
        countdown--;
    }
    std::cout << "Liftoff!\n";

    for (int i = 1; i <= 10; i++)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";

    for (int i = 0; i <= 20; i += 2)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";

    return 0;
}
```
The step doesn't have to be `i++`: `i += 2` jumps straight to the next even number, so no
`% 2` check is needed.

## Ex 2 — Predict, then check: how many times?
| # | Loop | Runs | Why |
|---|---|---|---|
| a | `i = 0; i < 5` | **5** | 0, 1, 2, 3, 4 |
| b | `i = 0; i <= 5` | **6** | 0 to 5: the off-by-one |
| c | `i = 10; i > 0; i -= 3` | **4** | 10, 7, 4, 1 (then -2 fails) |
| d | `while (n > 0)` with `n = 0` | **0** | checked first, false immediately |
| e | `do { } while (m > 0)` with `m = 0` | **1** | body runs before the check |
| f | `continue` at 3, `break` at 6 | **5** | counts 0, 1, 2, 4, 5 |
| g | `a = 3; b = a++; c = ++a;` | `a = 5, b = 3, c = 5` | see below |

**g step by step:** `b = a++` gives `b` the old value `3`, then `a` becomes `4`.
`c = ++a` makes `a` `5` **first**, then `c` gets `5`.

## Ex 3 — Loop traps
| # | Trap | g++ says | What happened |
|---|---|---|---|
| a | `for (...);` + indented `{ count++; }` | warning: `this 'for' clause does not guard... [-Wmisleading-indentation]` | `count` is **1** |
| b | same, no indentation | **no warning** | `count` is **1** |
| c | `while (n = 5)` | warning: `suggest parentheses around assignment used as truth value [-Wparentheses]` | prints `5` forever |
| d | `unsigned` countdown `u >= 0` | warning: `comparison of unsigned expression in '>= 0' is always true [-Wtype-limits]` | `3 2 1 0 4294967295 4294967294 ...` forever |
| e | `do { } while (x < 3)` with no `;` | **error**: `expected ';' before 'return'` | no `.exe` built |
| f | `i` used after its `for` loop | **error**: `'i' was not declared in this scope` | no `.exe` built |

- **a/b:** the `;` is the loop's (empty) body. The loop runs 3 times doing nothing, then
  the block runs **once**. The warning in **a** only exists because of the indentation,
  which is why **b** is the more dangerous version.
- **c:** `n = 5` stores 5, and the condition's value is `5`, which is true. Every time.
- **d:** the first number after `0` is `4294967295`: `0 - 1` wrapped to the biggest
  `unsigned int` (Day 3).
- **e/f** are **errors**: the compiler refuses to build anything. **a–d** are only
  **warnings**: the program builds and runs, wrongly.

## Ex 4 — Score tracker
```cpp
#include <iostream>

int main()
{
    int count = 0;
    std::cout << "How many scores? ";
    std::cin >> count;

    if (std::cin.fail() || count <= 0)
    {
        std::cout << "No scores to process.\n";
        return 0;
    }

    int total = 0;
    int highest = 0;

    for (int i = 1; i <= count; i++)
    {
        int score = 0;
        std::cout << "Score " << i << ": ";
        std::cin >> score;

        total += score;

        if (i == 1 || score > highest)
        {
            highest = score;
        }
    }

    double average = static_cast<double>(total) / count;

    std::cout << "Total: " << total << "\n";
    std::cout << "Average: " << average << "\n";
    std::cout << "Highest: " << highest << "\n";

    return 0;
}
```
| Input | Total | Average | Highest |
|---|---|---|---|
| `3` → `40 90 75` | 205 | 68.3333 | 90 |
| `2` → `-5 -8` | -13 | -6.5 | **-5** |
| `0` or `-3` | `No scores to process.` | | |

**Two edge cases worth remembering:**
- Starting `highest` at `0` breaks when every score is negative: nothing beats 0, so it
  reports a score nobody typed. Starting from the **first** score fixes it.
- The guard must be `count <= 0`, not `count == 0`. With `-3`, the loop runs 0 times and
  you'd print `0 / -3`, which shows as `-0`.
- The cast happens **before** dividing (Day 4): `static_cast<double>(total) / count`.

## Ex 5 — Draw a tile map
```cpp
#include <iostream>

int main()
{
    int width = 0, height = 0, playerX = 0, playerY = 0;
    std::cout << "Width, height, player X, player Y: ";
    std::cin >> width >> height >> playerX >> playerY;

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            if (row == 0 || row == height - 1 || col == 0 || col == width - 1)
            {
                std::cout << "#";
            }
            else if (row == playerY && col == playerX)
            {
                std::cout << "@";
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "\n";
    }

    return 0;
}
```
`8 5 3 2` gives:
```
########
#......#
#..@...#
#......#
########
```
**The border is four separate questions:** first row, last row, first **column**, last
**column**. Comparing a row with the *width* (`row == width - 1`) is the bug to avoid: it
drew a full wall in the middle of a tall map, and left out the left edge.

**Player on the border or outside:** the `@` disappears. On the border, the `#` check comes
first, and only the first true branch runs (Day 5). Outside the map, the loops never visit
that position, so `row == playerY && col == playerX` is never true. A real game would reject
or clamp those positions when they're entered.

## Ex 6 — Ask again on bad input
```cpp
#include <iostream>
#include <limits>

int main()
{
    int armor = 0;

    while (true)
    {
        std::cout << "Enemy armor (0-20): ";
        std::cin >> armor;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "That's not a number. Try again.\n";
            continue;
        }

        if (armor < 0 || armor > 20)
        {
            std::cout << "Armor must be 0 to 20. Try again.\n";
            continue;
        }

        break;
    }

    std::cout << "Armor set to " << armor << "\n";
    return 0;
}
```
`abc` → not a number; `-3` and `99` → out of range; `7` → `Armor set to 7`.

| Experiment | Result | Why |
|---|---|---|
| no `ignore(...)` | `abc` repeats the error forever | state is reset, but `abc` is still in the input and fails again |
| no `clear()` | `abc` repeats the error forever | `cin` stays failed, so every `>>` (and `ignore`) does nothing |

## Ex 7 — The game menu loop
```cpp
#include <iostream>
#include <limits>

int main()
{
    int hp = 50;
    int turns = 0;
    int choice = 0;

    do
    {
        std::cout << "=== HP: " << hp << " ===\n";
        std::cout << "1. Drink potion (+20 HP, max 100)\n";
        std::cout << "2. Fight a goblin (-15 HP)\n";
        std::cout << "3. Rest (+5 HP, max 100)\n";
        std::cout << "4. Quit\n";
        std::cout << "Choose: ";
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a number from 1 to 4.\n";
            continue;
        }

        switch (choice)
        {
            case 1:
                hp += 20;
                if (hp > 100) { hp = 100; }
                turns++;
                break;
            case 2:
                hp -= 15;
                turns++;
                break;
            case 3:
                hp += 5;
                if (hp > 100) { hp = 100; }
                turns++;
                break;
            case 4:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
        }

        if (hp <= 0)
        {
            std::cout << "You died. Game over.\n";
            break;
        }
    } while (choice != 4);

    std::cout << "Turns taken: " << turns << "\n";
    return 0;
}
```
| Test | Result |
|---|---|
| potion ×3 from 50 | 70 → 90 → **100** (capped) |
| fight ×4 from 50 | 35 → 20 → 5 → -10 → `You died. Game over.` |
| rest from 50 | **55** |
| `x` | `Please enter a number from 1 to 4.`, menu again, no turn counted |
| `9` | `Invalid choice.`, no turn counted |
| `4` | `Goodbye!` and the turn count |

**Lessons from Ex 7:**
- With `int choice`, a letter makes `cin` fail. Without the retry block, the failed state
  makes every later `>>` fail instantly: the menu printed **13,245 times in 2 seconds**.
- With `char choice`, letters can't fail, but `12` is read as **two** choices (`'1'` now,
  `'2'` next time). `int` + the retry pattern is the robust version.
- `continue` in a `do-while` jumps to the `while (choice != 4)` check. After a failed read,
  `choice` is `0`, so the menu shows again.
- The header must print the **variable** (`hp`), not the text `50`.

## Bonus — See the backward jump yourself
```bash
g++ -S -O0 asm_loop.cpp -o asm_loop.s
```
```asm
    jmp   .L2                ; jump DOWN to the check first
.L3:                         ; body
    movl  -8(%rbp), %eax
    addl  %eax, -4(%rbp)     ; total += i
    addl  $1, -8(%rbp)       ; i++
.L2:                         ; check
    movl  -8(%rbp), %eax
    cmpl  16(%rbp), %eax     ; compare i with n
    jle   .L3                ; jump UP to the body while i <= n
```
1. The jump after `cmpl` is `jle .L3`, and `.L3` is **above** it: a backward jump. (The
   `jmp .L2` near the top jumps *down* once, so the condition is checked before the first run.)
2. `i < n` gives **`jl`** (jump if less). Unlike Day 5's `if`, the jump uses **your**
   condition, not the opposite, because it's jumping *back into* the body, not skipping it.
3. Rewritten as a `while`, the `.s` file is **identical** to the `for` version (I compared
   them with `diff`: no differences). `for` is just a tidier way to write the same `while`.
