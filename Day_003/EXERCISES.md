# Day 3 — Exercises

Work inside the `Day_003` folder, using the VS Code terminal.
**Type everything yourself.** No copy-paste.

Compile command for every exercise:
```bash
g++ -std=c++20 -Wall -Wextra FILENAME.cpp -o FILENAME.exe
```

---

## Ex 1 — Binary by hand, then check
By hand (on paper or in `NOTES.md`), convert these binary patterns to decimal using
place values (`8 4 2 1` for 4 bits):
- `0b0110`
- `0b1001`
- `0b1111`

Then create `binary_check.cpp`, declare an `int` for each using the `0b` literal, print
all three, and confirm your by-hand answers were right.

## Ex 2 — Predict, then check: integer overflow
Create `overflow.cpp`. Before writing any code, predict in `NOTES.md`: if you take the
biggest possible `int` (`#include <climits>`, `INT_MAX`) and add `1` to it, what do you
expect to happen — a compiler error, a crash, or something else?

Then write the code, compile it, and run it. Record exactly what happened, including
whether g++ printed any warning.

## Ex 3 — Break it on purpose: the wraparound health bug
Create `health_bug.cpp`. Declare `unsigned char hp = 250;`. Simulate the character taking
three hits of 10 damage each (`hp = hp - 10;`, three times), printing `hp` after each hit
— **predict** the three printed values before you compile. Then compile, run, and compare
to your prediction. In `NOTES.md`, explain in your own words why this happened and why a
real game would never want this to happen silently.

## Ex 4 — char, int, and ASCII
Create `ascii_fun.cpp`:
1. Print the numeric ASCII code of `'A'`, `'a'`, and `'0'` using `static_cast<int>`.
2. Using `static_cast<char>`, print the character for the codes `72`, `105`, `33`.
3. Predict, then check: what does `'A' + 1` print if you store it straight into a `char`
   (not casting to `int` first)? What about if you store `'A' + 1` into an `int`?

## Ex 5 — Predict, then check: float vs. precision
Create `float_trap.cpp`. Before compiling, predict in `NOTES.md` whether this prints
`true` or `false`:
```cpp
double a = 0.1;
double b = 0.2;
std::cout << std::boolalpha << (a + b == 0.3) << "\n";
```
Compile and check. Then add a second comparison using `float` instead of `double` for all
three values and compare the results. Finally, print `a + b` itself with
`std::cout.precision(17);` set beforehand, and look at what the "real" stored value is.

## Ex 6 — Choosing types for a game character
Create `character_stats.cpp`. You're designing a character for a game. For each stat
below, declare a variable with a type you think fits, **and write a one-line comment
explaining why you picked that type** (size needed, whether negatives make sense, whether
decimals are needed):
- Health (can range from 0 up to 9999, never negative)
- A single inventory slot letter, like `'A'`–`'Z'` for quick-select
- Walking speed (a value like `4.5` units per second)
- Whether the character is currently stunned

Print all four. In `NOTES.md`, note any stat where you think a *small* type (like
`unsigned char`) could secretly cause the wraparound bug from Ex 3, and why you avoided
or accepted that risk.

---

When you're done, fill in `NOTES.md` and tell me **"review Day 3"**.
