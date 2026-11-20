# Day 6 — Exercises

Work inside the `Day_006` folder, using the VS Code terminal.
**Type everything yourself.** No copy-paste.

Compile command for every exercise:
```bash
g++ -std=c++20 -Wall -Wextra FILENAME.cpp -o FILENAME.exe
```
Put each exercise in its own folder (`Ex_1/`, `Ex_2/` …) like before.

> Today you **will** write infinite loops, some on purpose. If a program never ends,
> press **Ctrl + C** in the terminal to stop it.

---

## Ex 1 — Counting three ways
Write `counting.cpp` that prints:
1. A countdown from `10` to `1` using a **`while`** loop, then `Liftoff!`.
2. The numbers `1` to `10` on one line using a **`for`** loop.
3. The even numbers from `0` to `20` on one line using a `for` loop that steps by `2`
   (hint: the step part doesn't have to be `i++`).

## Ex 2 — Predict, then check: how many times?
**Before running anything**, write in NOTES how many times each loop body runs (and for
**g**, the three values). Then put them all in `predict.cpp`, count with an `int count`
variable (reset it to `0` before each loop), print each count, and compare.
```cpp
// a
for (int i = 0; i < 5; i++) { count++; }
// b
for (int i = 0; i <= 5; i++) { count++; }
// c
for (int i = 10; i > 0; i -= 3) { count++; }
// d
int n = 0;
while (n > 0) { count++; n--; }
// e
int m = 0;
do { count++; } while (m > 0);
// f
for (int i = 0; i < 10; i++)
{
    if (i == 3) { continue; }
    if (i == 6) { break; }
    count++;
}
// g — what are a, b and c at the end?
int a = 3;
int b = a++;
int c = ++a;
```
For any you got wrong, explain in NOTES what actually happened.

## Ex 3 — Break it on purpose: loop traps
Create `traps.cpp`. Try each one **on its own** (comment out the others). For each, write
down the exact **warning or error** (or "no warning") and what the program did:

| # | Trap | Warning / error | What happened |
|---|---|---|---|
| a | `for (int i = 0; i < 3; i++);` then an **indented** `{ count++; }` block, then print `count` | | |
| b | Same as **a**, but write `count++;` with **no** indentation and no braces | | |
| c | `int n = 3; while (n = 5) { std::cout << n << "\n"; }` (stop it with Ctrl + C) | | |
| d | `for (unsigned int u = 3; u >= 0; u--) { std::cout << u << "\n"; }` (Ctrl + C) | | |
| e | A `do { ... } while (x < 3)` with the `;` missing at the end | | |
| f | Print `i` on the line **after** a `for (int i = 0; ...)` loop ends | | |

For **d**: what was the first number printed after `0`, and why? (Think Day 3.)

## Ex 4 — Score tracker
Write `scores.cpp`. Ask how many scores the player wants to enter (`int`). Then use a
`for` loop to read that many scores, one at a time (`Score 1: `, `Score 2: `…). At the
end print:
- the **total**,
- the **average** as a decimal (Day 4: careful with integer division!),
- the **highest** score.

Test with `3` scores: `40 90 75`. Then test with `0` scores. What should happen, and does
your program avoid dividing by zero (Day 5)?

Hint for "highest": keep a variable `highest` and update it inside the loop whenever the
new score is bigger.

## Ex 5 — Draw a tile map
Write `tilemap.cpp`. Read a `width`, a `height`, and the player's position `playerX`,
`playerY`. Use **nested `for` loops** to draw the map:
- `#` on the border (first/last row, first/last column),
- `@` at the player's position,
- `.` everywhere else.

Example with width `8`, height `5`, player at `3 2` (counting from `0`, top-left corner):
```
########
#......#
#..@...#
#......#
########
```
Test with a few sizes. What happens if you put the player **on** the border, or outside the
map? (You don't have to fix it, just describe it in NOTES.)

## Ex 6 — Ask again on bad input
Write `retry.cpp`: ask for an enemy armor value from `0` to `20`. Keep asking until the
user types a valid number **in range**, then print `Armor set to N`. Use the pattern from
lesson §9 (`fail()`, `clear()`, `ignore(...)`, `continue`, `break`). Type it from memory as
much as you can.

Test with: `abc`, `-3`, `99`, `7`. Then, as an experiment:
1. Delete the `std::cin.ignore(...)` line, recompile, and type `abc`. What happens?
2. Put it back, delete the `std::cin.clear();` line instead, and try `abc` again.

Explain in NOTES why **each** of the two lines is needed.

## Ex 7 — Put it together: the game menu loop
Write `game_menu.cpp`. The player starts with `hp = 50`. Show this menu **again and again**
(use a `do-while`) until the player chooses Quit:
```
=== HP: 50 ===
1. Drink potion (+20 HP, max 100)
2. Fight a goblin (-15 HP)
3. Rest (+5 HP, max 100)
4. Quit
Choose:
```
- Use a `switch` for the choice (Day 5), and the retry pattern from Ex 6 so letters don't
  break the menu.
- If `hp` drops to `0` or below after a fight, print `You died. Game over.` and end the
  loop, even though the player didn't choose Quit.
- When the loop ends, print how many **turns** (menu choices) the player took.

Test: drink until max HP (does it stop at 100?), fight until you die, type `x`, type `9`,
and Quit.

---

## Bonus — See the backward jump yourself
Save the `sumTo` function from lesson §5 in `asm_loop.cpp` (no `main` needed) and run:
```bash
g++ -S -O0 asm_loop.cpp -o asm_loop.s
```
1. Open `asm_loop.s`, find the `cmpl`, and the jump right after it. Which label does it jump
   to? Is that label **above** or **below** the jump?
2. Change `i <= n` to `i < n` and rebuild. Which jump instruction is used now?
3. Rewrite `sumTo` with a `while` loop instead of `for` (same logic), build it into a
   second `.s` file, and compare the two. What do you notice?

---

When you're done, fill in `NOTES.md` and tell me **"review Day 6"**.
