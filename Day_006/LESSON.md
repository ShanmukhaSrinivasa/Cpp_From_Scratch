# Day 6 — Loops: `while`, `for`, `do-while`, `break` & `continue`

**Goal for today:**
1. Make code **repeat**: `while`, `for`, `do-while`.
2. Control a loop from inside: `break` and `continue`.
3. See what a loop really is to the CPU: the same compare-and-jump from Day 5, but
   jumping **backwards**.
4. Avoid the classic loop bugs: infinite loops, off-by-one, and the Day 3 wraparound.
5. Finally make bad input **ask again** instead of quitting (the promise from Day 5).

---

## 0. Quick fixes from Day 5

Three things in your Day 5 notes, and all three matter for loops:

**a) `if (health = 0)` is never true.** Your note says the condition "becomes true". It's
the opposite: `health = 0` stores `0`, and the condition's value is that `0`, which is
**false**. Your own Ex 2a proves it: nothing printed. Today this trap gets worse:
`while (x = 0)` never runs at all, and `while (x = 5)` runs **forever**.

**b) The CPU jumps *over* code, not *to* it.** Your note says an `if` "compares the
condition and then jumps to that code". The jump goes **past** the body when the
condition is false (that's why the bonus showed `jle` for `health > 100`: the opposite
condition). Keep that picture: in §5 you'll see a loop is just a jump that goes
**backwards**.

**c) Two conditions *can* both be true.** With `health = 10`, both `health < 25` and
`health < 75` are true. What can't happen is two **branches** running: only the first
true one runs.

Your NOTES for Ex 1, Ex 4, Ex 7 and the bonus are still empty. Your *code* for those is
correct now (and `ANSWERS.md` explains it), so writing the notes in your own words is
quick and worth it.

---

## 1. Why loops?

A game is one giant loop. Every frame, Unity calls your `Update()`. Underneath, the engine
is running something like:

```cpp
while (gameIsRunning)
{
    readInput();
    updateWorld();
    drawFrame();
}
```

That's 60+ times per second until you quit. Today you learn the tool that makes that
possible: code that runs again and again until a condition says stop.

## 2. `while`: repeat while a condition is true

```cpp
#include <iostream>

int main()
{
    int countdown = 3;

    while (countdown > 0)
    {
        std::cout << countdown << "...\n";
        countdown = countdown - 1;
    }

    std::cout << "Go!\n";
    return 0;
}
```
Output:
```
3...
2...
1...
Go!
```
A `while` checks its condition **before** each run of the body:
1. Is `countdown > 0`? Yes (3), so run the body: print, then `countdown` becomes 2.
2. Check again. Yes (2): print, `countdown` becomes 1.
3. Check again. Yes (1): print, `countdown` becomes 0.
4. Check again. `0 > 0` is false, so skip the body and continue after the loop.

**Something inside the loop must eventually make the condition false.** Delete the
`countdown = countdown - 1;` line and the condition is true forever: an **infinite loop**.
The program never ends. To stop a stuck program in the VS Code terminal, press
**Ctrl + C**.

## 3. `++` and `--`: the counting shortcuts

Loops count a lot, so C++ has shortcuts:

| Code | Means |
|---|---|
| `count++;` or `++count;` | `count = count + 1;` |
| `count--;` or `--count;` | `count = count - 1;` |

On a line by themselves, `count++` and `++count` do exactly the same thing. They only
differ when you **use the value in the same expression**:

```cpp
int a = 5;
int b = a++;   // POST-increment: b gets the OLD value (5), then a becomes 6
int c = ++a;   // PRE-increment:  a becomes 7 first, then c gets the NEW value (7)
// now a = 7, b = 5, c = 7
```
Rule of thumb: keep `++` on its own (`i++` in a `for`, or `count++;` as its own line) and
you never have to think about the difference.

## 4. `for`: a counting loop in one line

Most loops count: "do this 5 times", "for every tile in a row". `for` puts the three
parts of a counting loop in one place:

```cpp
for (int i = 0; i < 5; i++)
{
    std::cout << i << " ";
}
// prints: 0 1 2 3 4
```
```
for ( start ;  condition ;  step )
      int i = 0  i < 5      i++
```
1. **start** runs once, before anything else: create `i`, set it to 0.
2. **condition** is checked before every run of the body, exactly like `while`.
3. The **body** runs.
4. **step** runs after every body run: `i++`. Then back to step 2.

It's exactly this `while`, just tidier:
```cpp
int i = 0;
while (i < 5)
{
    std::cout << i << " ";
    i++;
}
```
One real difference: a variable created in the `for`'s start part **only exists inside
the loop**. After the loop it's gone:
```cpp
for (int i = 0; i < 3; i++) { }
std::cout << i;   // error: 'i' was not declared in this scope
```
(This idea, called **scope**, gets its own day on Day 9.)

### Counting: start at 0, use `<`
`for (int i = 0; i < 10; i++)` runs **10** times (0 to 9). Programmers almost always
count from 0 like this, because that's how arrays work (Day 10). If you write `<=` by
mistake, it runs **11** times:

| Loop | Runs |
|---|---|
| `for (int i = 0; i < 10; i++)` | 10 times (0–9) |
| `for (int i = 0; i <= 10; i++)` | **11** times (0–10) |
| `for (int i = 1; i <= 10; i++)` | 10 times (1–10) |

Running one time too many or too few is so common it has a name: an **off-by-one error**.

## 5. What the CPU actually does with a loop

On Day 5 you saw an `if` become a **compare + jump forward** (over the body). A loop is
the same two instructions, with the jump going **backwards**. This function:

```cpp
int sumTo(int n)
{
    int total = 0;
    for (int i = 1; i <= n; i++)
    {
        total += i;
    }
    return total;
}
```
compiles (`g++ -S -O0`) to this, trimmed slightly:

```asm
    movl  $0, -4(%rbp)       ; total = 0
    movl  $1, -8(%rbp)       ; i = 1             (start)
    jmp   .L2                ; go check the condition first
.L3:                         ; ---- the body ----
    movl  -8(%rbp), %eax
    addl  %eax, -4(%rbp)     ; total += i
    addl  $1, -8(%rbp)       ; i++                (step)
.L2:                         ; ---- the check ----
    movl  -8(%rbp), %eax
    cmpl  16(%rbp), %eax     ; COMPARE i with n   (condition)
    jle   .L3                ; if i <= n, jump BACK UP to the body
```
`jle .L3` jumps **upwards**, to code that already ran. That's the entire secret of a loop:
a jump back to an earlier instruction. Notice this time the jump uses **your** condition
(`<=` → `jle`), not the opposite: it's not skipping code, it's going back to run it again.
When `i <= n` becomes false, the jump doesn't happen, and the CPU simply carries on to the
next instruction after the loop.

## 6. `do-while`: run first, check after

```cpp
int x = 100;
do
{
    std::cout << "do-while ran with x = " << x << "\n";
} while (x < 10);
```
This prints once, even though `x < 10` is false from the start. A `do-while` runs the
body **first** and checks afterwards, so the body always runs **at least once**. It's
perfect for "show the menu, then ask again if the choice was invalid".

Don't forget the `;` after `while (...)`. It's the only loop that needs one:
```
error: expected ';' before 'std'
    8 |     } while (x < 3)
      |                    ^
      |                    ;
```

## 7. `break` and `continue`

- `break;` leaves the loop **immediately** (you already know it from `switch`).
- `continue;` skips the **rest of this run** of the body and goes straight to the next
  check (in a `for`, the step `i++` still happens first).

```cpp
for (int i = 1; i <= 10; i++)
{
    if (i % 2 == 0)
    {
        continue;   // skip even numbers
    }
    if (i > 7)
    {
        break;      // stop the whole loop
    }
    std::cout << i << " ";
}
// prints: 1 3 5 7
```

### Loops inside loops
A loop body can contain another loop. The inner loop runs **completely** for every single
run of the outer one. That's how you walk a grid, like a tile map:

```cpp
for (int row = 0; row < 3; row++)
{
    for (int col = 0; col < 5; col++)
    {
        if (row == 1 && col == 2)
        {
            std::cout << "X";
        }
        else
        {
            std::cout << ".";
        }
    }
    std::cout << "\n";
}
```
```
.....
..X..
.....
```
A `break` inside the inner loop only leaves the **inner** loop. The outer loop carries on
with its next row.

## 8. Classic loop traps

**a) A stray `;` after the loop.**
```cpp
int count = 0;
for (int i = 0; i < 3; i++);   // <- this ; IS the loop's body (an empty one)
{
    count++;                   // just a normal block, runs ONCE after the loop
}
// count is 1, not 3
```
g++ warns `this 'for' clause does not guard... [-Wmisleading-indentation]`, but **only
because of the indentation**. Write the same code without indenting `count++;` and g++
says **nothing**: the program compiles silently and prints `1`.

**b) `=` instead of `==`**, same as Day 5, but now it decides how often the loop runs.
`while (n = 0)` never runs. `while (n = 5)` never stops. g++ warns:
`suggest parentheses around assignment used as truth value [-Wparentheses]`.

**c) Counting down with an `unsigned` type** (Day 3's wraparound, again):
```cpp
for (unsigned int u = 3; u >= 0; u--)
{
    std::cout << u << " ";
}
```
An `unsigned` can **never** be below 0, so `u >= 0` is always true. After `0`, `u--`
wraps around to `4294967295` and keeps going. g++ catches this one:
`comparison of unsigned expression in '>= 0' is always true [-Wtype-limits]`. Use `int`
for counters that count down.

**d) A `double` as the counter** (Day 3's imprecision, again):
```cpp
for (double t = 0.0; t != 1.0; t += 0.1) { ... }   // never stops!
```
Adding `0.1` ten times gives `0.99999999999999989`, not `1.0`, so `t != 1.0` stays true
forever. Even `t < 1.0` is wrong: it runs **11** times instead of 10. Count with an `int`
and calculate the decimal from it: `double t = i * 0.1;`.

## 9. Bad input: ask again instead of quitting

On Day 5 you used `std::cin.fail()` to **end** the program on bad input. A real game asks
again. That needs a loop, plus two extra steps you might not expect:

```cpp
#include <iostream>
#include <limits>

int main()
{
    int health = 0;

    while (true)
    {
        std::cout << "Enter health (0-100): ";
        std::cin >> health;

        if (std::cin.fail())
        {
            std::cin.clear();   // 1. reset the "failed" state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');   // 2. throw away the bad line
            std::cout << "That's not a number. Try again.\n";
            continue;
        }

        if (health < 0 || health > 100)
        {
            std::cout << "Out of range. Try again.\n";
            continue;
        }

        break;   // valid number: leave the loop
    }

    std::cout << "Health set to " << health << "\n";
    return 0;
}
```
Typing `abc`, then `150`, then `50`:
```
Enter health (0-100): That's not a number. Try again.
Enter health (0-100): Out of range. Try again.
Enter health (0-100): Health set to 50
```
`while (true)` loops "forever", and the only way out is the `break` at the bottom. Why
both `clear` and `ignore`?

1. When a read fails, `std::cin` switches into a **failed state** and refuses to read
   **anything** after that, even good input, until you call `std::cin.clear()`.
2. `clear()` only resets the state. The letters `abc` are **still sitting in the input**,
   so the next `>>` fails on them again. `std::cin.ignore(...)` throws away everything up
   to and including the next Enter (`'\n'`). The big first number
   (`std::numeric_limits<std::streamsize>::max()`, Day 3's `numeric_limits`) just means
   "however many characters there are".

Leave out either step and the loop prints "That's not a number" forever. I tested both:
without `clear`, or with `clear` but no `ignore`, the program never reads the `50` that
comes next.

---

## Key ideas to remember
- `while (condition)` checks **before** each run; `do { } while (condition);` runs
  **once first**, then checks. `for (start; condition; step)` is a counting `while`.
- Something in the loop must eventually make the condition false, or it's an infinite
  loop. **Ctrl + C** stops a stuck program.
- `i++` / `++i` add 1. They only differ when you use the value in the same expression.
- `for (int i = 0; i < n; i++)` runs exactly `n` times. `<=` instead of `<` is the classic
  **off-by-one** error.
- A variable declared in a `for`'s start part only exists inside the loop.
- To the CPU, a loop is a **compare + a jump backwards**.
- `break` leaves the (innermost) loop; `continue` skips to the next check.
- Traps: a stray `;` after `for`/`while`, `=` vs `==`, an `unsigned` counting down past 0,
  and a `double` loop counter.
- Retry on bad input: check `fail()`, then `clear()` **and** `ignore(...)`, then `continue`.

**Connecting to games:** the **game loop** (`while (running)`) is the heartbeat of every
engine, including the one you'll build. Unity hides it behind `Update()`, but it's there.
Nested `for` loops walk tile maps and grids, `continue` skips dead enemies in a list, and
`break` stops searching once you've found the target. Tomorrow's **Build Day** is a
number-guessing game: a `do-while` that keeps asking until the player guesses right,
using everything from this week.

Now go to `EXERCISES.md`.
