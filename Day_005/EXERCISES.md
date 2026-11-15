# Day 5 — Exercises

Work inside the `Day_005` folder, using the VS Code terminal.
**Type everything yourself.** No copy-paste.

Compile command for every exercise:
```bash
g++ -std=c++20 -Wall -Wextra FILENAME.cpp -o FILENAME.exe
```
Put each exercise in its own folder (`Ex_1/`, `Ex_2/` …) like before.

---

## Ex 1 — Health status
Write `health_status.cpp`. Read the player's health (an `int`) and print **one** message:

| Health | Message |
|---|---|
| less than 0, or more than 100 | `Invalid health value` |
| exactly 0 | `Dead` |
| 1 – 24 | `Critical` |
| 25 – 74 | `Hurt` |
| 75 – 100 | `Healthy` |

Test it with **all** of these: `-5`, `0`, `1`, `24`, `25`, `74`, `75`, `100`, `150`.
Testing the values right at each boundary is how professionals find bugs.

Then answer in NOTES: does the **order** of your `if`s matter? Move the "Invalid" check to the end. Which inputs break?

## Ex 2 — Break it on purpose: four traps
Create `traps.cpp` with `int health = 50;` and try each trap from the lesson **one at a time**.
For each one, write down the exact **warning** and the **actual output**:

| # | Trap | Warning (copy it exactly) | What printed |
|---|---|---|---|
| a | `if (health = 0)` | | |
| b | `if (health <= 0);` followed by a `{ }` block | | |
| c | `if` without braces, with two indented lines under it | | |
| d | `if (40 <= health <= 45)` | | |

For **a**, also print `health` after the `if`. What is it now, and why?

## Ex 3 — Predict, then check: logical operators
Write down your prediction (`true` / `false`) for each line **before** running.
Use `std::boolalpha` (Day 3) so it prints words:
```cpp
int level = 4;
bool hasKey = true;
bool isAdmin = false;

std::cout << std::boolalpha;
std::cout << (hasKey && level >= 5) << "\n";               // 1
std::cout << (hasKey || level >= 5) << "\n";               // 2
std::cout << (!hasKey) << "\n";                            // 3
std::cout << ((hasKey && level >= 5) || isAdmin) << "\n";  // 4
std::cout << (!(level > 3) || isAdmin) << "\n";            // 5
std::cout << (level != 4 && hasKey) << "\n";               // 6
```

## Ex 4 — Short-circuit: a safe division
Write `safe_average.cpp`. Read `totalScore` and `gamesPlayed` (both `int`).
Print `Pro player!` if the average per game is **greater than 100**, and `Keep practising` otherwise.

1. Write the condition so it's **safe when `gamesPlayed` is 0**, using one `if` with `&&`
   (no nested `if`). Test with `gamesPlayed = 0`.
2. Now **swap** the two sides of the `&&`, recompile and test with `0` again. What happens?
   What's the exit code (`echo $LASTEXITCODE`)? Explain in NOTES why the order matters.

## Ex 5 — `switch`: the game menu
Write `menu.cpp`. Print this menu, read an `int`, and use a `switch` to respond:
```
=== MAIN MENU ===
1. New Game
2. Load Game
3. Options
4. Quit
Choose:
```
- 1–4 each print a different message (e.g. `Starting a new adventure...`).
- Anything else prints `Invalid choice`.

Then **break it**, one at a time, and note what happens:
1. Delete the `break` after case 1. Choose 1. What prints? What's the warning?
2. Change the menu variable to a `std::string` (and the cases to `"1"`, `"2"`…). What's the error?

## Ex 6 — Catch the bad input
Take your Ex 1 program and make it safe: if the user types something that isn't a
number (like `ten`), print `Please enter a number.` and end the program with exit code `1`.
Test with: `50`, `ten`, `50abc`. Explain in NOTES why `50abc` doesn't count as bad input.

## Ex 7 — Put it together: one combat turn
Write `combat_turn.cpp`. A simple turn-based fight:

1. Ask for the **enemy's armor** (`int`, 0–20) and the player's move as a `char`:
   `a` = attack, `h` = heavy attack, `p` = potion. Accept capital letters too.
2. Use a `switch` on the move:
   - **attack:** base damage `15`
   - **heavy:** base damage `30`, but only if the player has `stamina >= 20`
     (start with `int stamina = 25;`). Otherwise print `Too tired!` and the damage is `0`.
   - **potion:** heal the player by `20`. The player's HP starts at `60` and can't go above `100`.
   - anything else: `You stumble. Turn lost.`
3. Final damage = base damage − armor, but if damage was dealt, it can never be **less than 1**.
4. Print what happened (damage dealt, or the player's new HP).
5. If the user types letters for the armor, use `cin.fail()` to stop with an error.

Test at least: attack vs armor 5, heavy vs armor 0, heavy vs armor 35, potion, `x`, and armor `abc`.

---

## Bonus — See the compare-and-jump yourself
Save the `clampHealth` function from lesson section 3 in `asm_if.cpp` (no `main` needed) and run:
```bash
g++ -S -O0 asm_if.cpp -o asm_if.s
```
Open `asm_if.s`, find `cmpl` and the jump right after it (`jns`, `jge`, `jl`…).
Then change the condition to `health > 100` with `health = 100;` and rebuild. Which jump instruction does it use now?

---

When you're done, fill in `NOTES.md` and tell me **"review Day 5"**.
