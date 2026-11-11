# Day 2 — Exercises

Work inside the `Day_002` folder, using the VS Code terminal.
**Type everything yourself.** No copy-paste.

Compile command for every exercise:
```bash
g++ -std=c++20 -Wall -Wextra FILENAME.cpp -o FILENAME.exe
```

---

## Ex 1 — Character sheet
Create `character.cpp`. Declare and initialize these variables for a game character,
then print all of them on one line each:
- `std::string` name
- `int` health
- `double` moveSpeed
- `char` rank (a single letter grade, e.g. `'B'`)
- `bool` isAlive

## Ex 2 — Predict, then check: uninitialized
Create `uninitialized.cpp`. Declare an `int` called `score` **without** initializing it,
then print it.
1. **Before compiling**, write in `NOTES.md` what you predict will happen.
2. Compile with the warnings on. What does g++ say?
3. Run the program twice without changing the code. Does the printed number change
   between runs? Write down what you saw.

## Ex 3 — Break it on purpose
Make a copy of your Ex 1 file called `broken2.cpp`. Make **one** mistake at a time,
compile, record the exact error, then undo it before the next one:

| # | Mistake | What did the compiler say? |
|---|---|---|
| a | Declare the same variable name twice in `main` | |
| b | Use a variable in a `std::cout` line *before* its declaration | |
| c | Start a variable name with a digit, e.g. `int 2ndHealth = 5;` | |
| d | Misspell the type name, e.g. `itn health = 5;` | |
| e | Put a `char` value in double quotes instead of single, e.g. `char rank = "B";` | |

## Ex 4 — sizeof and addresses
Create `memory_layout.cpp`. Declare one variable of each type from today's lesson
(`int`, `double`, `char`, `bool`) and print, for each, its value, its `sizeof(...)`, and
its address (`&variableName`). Then answer in `NOTES.md`:
1. Which type takes the most bytes? Which takes the fewest?
2. Are the addresses right next to each other, with no gaps? (Don't worry about
   explaining *why* yet — just report what you observe.)

## Ex 5 — Predict, then check: narrowing
Before compiling, guess what each of these does — compiles clean, compiles with a
warning, or fails to compile:
```cpp
int a = 7.8;
int b{7.8};
int c{7};
```
Write your three guesses in `NOTES.md`, **then** compile all three (one at a time) and
record what g++ actually did.

## Ex 6 — Swap two variables
Create `swap.cpp`. Declare two `int` variables, `a = 5` and `b = 9`. Using **only
assignment** (no fancy tricks, and you'll need one extra variable), swap their values so
that afterwards `a` is `9` and `b` is `5`. Print both before and after the swap. Think
about why you can't just do `a = b; b = a;` directly — try it and see what happens if
you're not sure.

## Ex 7 — Put it together: simple score tracker
Create `score_tracker.cpp`. Track a player's score across three "events" using one `int`
variable, printing the running total after each event:
- Start at `0`.
- Add `10` (killed an enemy).
- Add `25` (completed objective).
- Subtract `5` (took a penalty).

Also declare a `double celsius = 37.0;` and compute `fahrenheit` from it
(`F = C * 9.0 / 5.0 + 32.0`) in a separate variable, then print both temperatures.

---

When you're done, fill in `NOTES.md` and tell me **"review Day 2"**.
