# Day 4 — Exercises

Work inside the `Day_004` folder, using the VS Code terminal.
**Type everything yourself.** No copy-paste.

Compile command for every exercise:
```bash
g++ -std=c++20 -Wall -Wextra FILENAME.cpp -o FILENAME.exe
```

---

## Ex 1 — Basic input
Create `greet.cpp`. Ask the user for their name (`std::string`) and age (`int`) using
`std::cin`, one at a time, then print a sentence using both.

## Ex 2 — Predict, then check: the one-word string trap
Create `one_word.cpp`, reading a `std::string` with `std::cin >>` and printing it back.
**Before running it**, write in `NOTES.md` what you think will happen if you type
`Hero Jones` (with a space) when the program asks for input. Then run it, type exactly
that, and record what actually printed.

## Ex 3 — Predict, then check: bad number input
Create `bad_input.cpp`, reading an `int` with `std::cin >>` and printing it back.
Predict what happens if, instead of a number, you type the word `twenty`. Then run it
and check. Does the compiler or the program show you any error or warning at all?

## Ex 4 — Division and modulo table
Create `div_mod.cpp`. Before compiling, fill in your predictions for each of these in
`NOTES.md`, then print all six and compare:
```cpp
7 / 2
-7 / 2
7 % 2
-7 % 2
7 % -2
7.0 / 2
```

## Ex 5 — Break it on purpose: precedence
Make `precedence.cpp`. First, **without running anything**, write your predicted output
for each line in `NOTES.md`:
```cpp
std::cout << 2 + 3 * 4 << "\n";
std::cout << 10 - 2 - 3 << "\n";
std::cout << 20 / 4 - 2 << "\n";
std::cout << 2 + 3 == 5 << "\n";       // try this one exactly as written first!
```
Then type them in one at a time and compile after each. The last line should fail —
read the real error message, and fix it by adding parentheses around `2 + 3 == 5`.
Record the exact error you got before the fix.

## Ex 6 — Predict, then check: division by zero
Create `div_zero.cpp` with two small experiments (comment one out while testing the
other):
1. `int a = 5, b = 0; std::cout << a / b << "\n";`
2. `double a = 5.0, b = 0.0; std::cout << a / b << "\n";`

Predict what each one does *before* running it. Then run both and record what actually
happened — including whether anything printed before any crash.

## Ex 7 — Put it together: the average-score bug, then the fix
Create `average_bug.cpp`. Read three test scores as `int` from the user (e.g. `85 90
78`). Compute and print their average **two ways**:
1. Using only `int` arithmetic (`sum / 3`) — the "buggy" version.
2. Forcing decimal division (cast the sum or `3` to `double` first) — the correct
   version.

Run it with scores that don't divide evenly (e.g. `85 90 78`) and compare the two
printed averages. In `NOTES.md`, explain in your own words why the first version is
wrong, using what you learned in §2 of today's lesson.

---

When you're done, fill in `NOTES.md` and tell me **"review Day 4"**.
