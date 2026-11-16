# Day 5 — Answer Key & Revision Sheet

Use this for revising. Try to answer from memory **first**, then check here.
All code, warnings and outputs below were checked with g++ 16.1.0 (`-std=c++20 -Wall -Wextra`).

---

## ⚡ 60-second revision

- A comparison (`==`, `!=`, `<`, `>`, `<=`, `>=`) produces a `bool`.
- `if` / `else if` / `else`: conditions are checked **top to bottom**, and only the
  **first** true branch runs. Several conditions can be true; only one branch runs.
- To the CPU, an `if` is **compare, then jump**. The jump *skips* the body, so the
  compiler jumps on the **opposite** of your condition.
- `&&` and `||` **short-circuit**: `false && x` and `true || x` never evaluate `x`.
  Put the safety check **on the left**: `count != 0 && total / count > 10`.
- Four traps g++ warns about: `if (x = 0)`, `if (...);`, an `if` without braces
  guarding two lines, and `a <= x <= b`.
- `switch` jumps to the matching `case` and runs **until a `break`** (fall-through).
  Deliberate fall-through is useful for `case 'a': case 'A':`.
- `switch` only works on whole-number types (`int`, `char`, …). Not `std::string`.
- `std::cin.fail()` tells you whether the **last** `>>` worked. Check it **after**
  the read. `50abc` is not a failure: `>>` reads `50` and stops at `a`.
- Test **boundary values** (`24`, `25`, `0`, `1`…). That's where `<` vs `<=` bugs hide.

---

## Notes questions — model answers

### What does the CPU actually do when it runs an `if`?
Two instructions: a **compare** (e.g. `cmpl $0, ...`), which sets flags describing the
result, then a **conditional jump** that reads those flags. The jump goes *over* the body
when the condition is false, so the body only runs when it's true. There's no special
"decision" hardware: every `if`, loop and `switch` becomes compares and jumps.

### In an `if` / `else if` / `else` chain, what happens when two conditions are both true?
Two conditions **can** both be true. With `health = 10`, both `health < 25` and
`health < 75` are true. But only the **first** true branch runs; once a branch runs,
the rest of the chain is skipped. That's why order matters (Ex 1).

### What is short-circuiting, and how can it prevent a crash?
`&&` and `||` evaluate left to right and **stop as soon as the answer is known**:
- `false && anything` is false, so `anything` never runs.
- `true || anything` is true, so `anything` never runs.

So if the left side is a safety check, the dangerous right side only runs when it's safe:
`gamesPlayed != 0 && totalScore / gamesPlayed > 100` never divides when `gamesPlayed` is 0.

### Why does `if (health = 0)` compile, and what two bad things does it do?
`=` is assignment, and an assignment is also an expression whose value is the value
assigned. So `health = 0` stores 0 and then evaluates to `0`, which counts as `false`.
It compiles because any number can be a condition (lesson §5). The two bad things:
1. It **destroys** `health`: it's now 0, whatever it was before.
2. The condition is **always false**, so the body never runs.

(Your Ex 2a result shows both: nothing printed, and `health` was 0 afterwards.)

### What is switch fall-through, and when is it useful?
A `switch` jumps to the matching `case` label and then runs **every following line**,
through later `case` labels, until it hits a `break` (or the end of the `switch`). The
`case` labels are just jump targets, not walls. It's useful when several values should
do the same thing:
```cpp
case 'a':
case 'A':
    // runs for both 'a' and 'A'
    break;
```

### Why can't you `switch` on a `std::string`?
`switch` compares the value against **constant whole numbers** (it can even be compiled
into a jump table indexed by that number). A `std::string` isn't a single number; it's an
object holding many characters, so g++ refuses: `error: switch quantity not an integer`.
For strings, use an `if` / `else if` chain.

---

## Ex 1 — Health status
```cpp
#include <iostream>

int main()
{
    int health = 0;
    std::cout << "Enter player's health: ";
    std::cin >> health;

    if (health < 0 || health > 100)
    {
        std::cout << "Invalid health value\n";
    }
    else if (health == 0)
    {
        std::cout << "Dead\n";
    }
    else if (health <= 24)
    {
        std::cout << "Critical\n";
    }
    else if (health <= 74)
    {
        std::cout << "Hurt\n";
    }
    else
    {
        std::cout << "Healthy\n";
    }

    return 0;
}
```
| Input | -5 | 0 | 1 | 24 | 25 | 74 | 75 | 100 | 150 |
|---|---|---|---|---|---|---|---|---|---|
| Output | Invalid | Dead | Critical | Critical | Hurt | Hurt | Healthy | Healthy | Invalid |

Because "Invalid" is checked **first**, every later branch already knows health is
0–100. That's why `health <= 24` doesn't need `health >= 1` too: 0 was caught above.

**Does order matter?** Yes. If the Invalid check moves to the end, the earlier
branches see the bad values first. With the version above, `-5` passes `health <= 24`
and prints **Critical**, and `150` falls into the final `else` and prints **Healthy**.
The Invalid check is never reached. (If every branch checks both ends of its range, like
your version did, the order matters less, but that's more code and easier to get wrong.)

## Ex 2 — Four traps
| # | Trap | g++ warning | Printed |
|---|---|---|---|
| a | `if (health = 0)` | `suggest parentheses around assignment used as truth value [-Wparentheses]` | nothing; `health` is now `0` |
| b | `if (health <= 0);` then `{ }` | `suggest braces around empty body in an 'if' statement [-Wempty-body]` | `50` (the block always runs) |
| c | `if` with no braces, two indented lines | `this 'if' clause does not guard... [-Wmisleading-indentation]` | `50` `50` |
| d | `if (40 <= health <= 45)` | `comparisons like 'X<=Y<=Z' do not have their mathematical meaning [-Wparentheses]` | `50` |

- **b:** the `;` *is* the `if`'s body (an empty statement). The `{ }` block after it is
  just a normal block that always runs.
- **c:** without braces, the `if` only guards the **first** line. The second line always
  runs; the indentation is lying.
- **d:** evaluated left to right: `40 <= 50` is `true` (`1`), then `1 <= 45` is `true`.
  It's true for **every** health value. Write `health >= 40 && health <= 45`.

## Ex 3 — Logical operators
With `level = 4`, `hasKey = true`, `isAdmin = false`:

| # | Expression | Result | Why |
|---|---|---|---|
| 1 | `hasKey && level >= 5` | `false` | `4 >= 5` is false |
| 2 | `hasKey \|\| level >= 5` | `true` | `hasKey` is true; right side never checked |
| 3 | `!hasKey` | `false` | not true |
| 4 | `(hasKey && level >= 5) \|\| isAdmin` | `false` | false \|\| false |
| 5 | `!(level > 3) \|\| isAdmin` | `false` | `!(true)` is false, \|\| false |
| 6 | `level != 4 && hasKey` | `false` | `4 != 4` is false; right side never checked |

## Ex 4 — Short-circuit: a safe division
```cpp
#include <iostream>

int main()
{
    int totalScore = 0;
    int gamesPlayed = 0;

    std::cout << "Enter your total score: ";
    std::cin >> totalScore;
    std::cout << "Enter total games played: ";
    std::cin >> gamesPlayed;

    if (gamesPlayed != 0 && totalScore / gamesPlayed > 100)
    {
        std::cout << "Pro player!\n";
    }
    else
    {
        std::cout << "Keep practising\n";
    }

    return 0;
}
```
| Input | Safe version | Swapped (`totalScore / gamesPlayed > 100 && gamesPlayed != 0`) |
|---|---|---|
| `500 2` | `Pro player!` | `Pro player!` |
| `100 2` | `Keep practising` | `Keep practising` |
| `500 0` | `Keep practising`, exit `0` | **crash**, prints nothing, exit `-1073741676` |

**Why the order matters:** `&&` runs its left side first. In the safe version the left
side is `gamesPlayed != 0`, which is false for 0 games, so C++ stops and the division
never runs. Swapped, the division is the left side, so it runs first and divides by zero
before the check can help. `-1073741676` is `0xC0000094`, Windows' code for "integer
divide by zero" (Day 4).

"Keep practising" is a normal result, so the program ends with `return 0`. Exit code `1`
would tell the OS the program **failed**.

## Ex 5 — `switch`: the game menu
```cpp
#include <iostream>

int main()
{
    int choice = 0;

    std::cout << "=== MAIN MENU ===\n";
    std::cout << "1. New Game\n";
    std::cout << "2. Load Game\n";
    std::cout << "3. Options\n";
    std::cout << "4. Quit\n";
    std::cout << "Choose: ";
    std::cin >> choice;

    switch (choice)
    {
        case 1:
            std::cout << "Starting a new adventure...\n";
            break;
        case 2:
            std::cout << "Loading your save...\n";
            break;
        case 3:
            std::cout << "Opening options...\n";
            break;
        case 4:
            std::cout << "Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice\n";
            break;
    }

    return 0;
}
```
**Break it:**
1. Delete the `break` after case 1 and choose 1: it prints the case 1 **and** case 2
   messages, stopping at case 2's `break`. g++ warns:
   `warning: this statement may fall through [-Wimplicit-fallthrough=]`
2. Switch on a `std::string` with `case "1":`: g++ says
   `error: switch quantity not an integer`. ("expression must have integral or enum
   type" is VS Code's red squiggle, not the compiler.)

## Ex 6 — Catch the bad input
```cpp
#include <iostream>

int main()
{
    int health = 0;
    std::cout << "Enter player's health: ";
    std::cin >> health;

    if (std::cin.fail())
    {
        std::cout << "Please enter a number.\n";
        return 1;
    }

    // ... the same if / else if chain as Ex 1 ...

    return 0;
}
```
| Input | Result |
|---|---|
| `50` | `Hurt`, exit 0 |
| `ten` | `Please enter a number.`, exit 1 |
| `50abc` | `Hurt`, exit 0 |

**Why `50abc` isn't bad input:** `>>` reads digits as long as it can, gets `50`, and stops
at `a`. It successfully read a number, so `fail()` is false. The `abc` is left unread in
the input. Rejecting it needs extra checks (Day 6+).

## Ex 7 — One combat turn
```cpp
#include <iostream>

int main()
{
    int playerHp = 60;
    int stamina = 25;
    int enemyArmor = 0;
    char move = ' ';

    std::cout << "Enemy armor (0-20): ";
    std::cin >> enemyArmor;

    if (std::cin.fail())
    {
        std::cout << "Armor must be a number.\n";
        return 1;
    }

    if (enemyArmor < 0 || enemyArmor > 20)
    {
        std::cout << "Armor must be from 0 to 20.\n";
        return 1;
    }

    std::cout << "Move (a = attack, h = heavy, p = potion): ";
    std::cin >> move;

    int baseDamage = 0;

    switch (move)
    {
        case 'a':
        case 'A':
            baseDamage = 15;
            break;

        case 'h':
        case 'H':
            if (stamina >= 20)
            {
                baseDamage = 30;
                stamina -= 20;
            }
            else
            {
                std::cout << "Too tired!\n";
            }
            break;

        case 'p':
        case 'P':
            playerHp += 20;
            if (playerHp > 100)
            {
                playerHp = 100;
            }
            std::cout << "You drink a potion. HP is now " << playerHp << "\n";
            break;

        default:
            std::cout << "You stumble. Turn lost.\n";
            break;
    }

    if (baseDamage > 0)
    {
        int damage = baseDamage - enemyArmor;
        if (damage < 1)
        {
            damage = 1;
        }
        std::cout << "You deal " << damage << " damage!\n";
    }

    return 0;
}
```
Doing the damage maths **once, after** the `switch` (only when `baseDamage > 0`) means the
"minimum 1" rule is written once instead of copied into each attack case.

| Test | Result |
|---|---|
| attack vs armor 5 | `15 - 5` = **10** |
| attack vs armor 15 | `15 - 15 = 0` → raised to **1** (the boundary case) |
| attack vs armor 20 | `15 - 20 = -5` → raised to **1** |
| heavy vs armor 0 | **30** (stamina 25 → 5) |
| heavy vs armor 20 | `30 - 20` = **10** |
| heavy with stamina 10 | `Too tired!`, no damage |
| potion | HP `60 + 20` = **80** |
| `x` | `You stumble. Turn lost.` |
| armor `abc` | `Armor must be a number.`, exit 1 |
| armor `35` | `Armor must be from 0 to 20.`, exit 1 |

**Lessons from Ex 7:**
- `cin.fail()` reports on the **last read**, so it must come **after** `>>`. Checked before
  the read, it's always false.
- `if (damage < 0)` misses `0`. The rule is "never less than 1", so the check is `< 1`.
  The armor-15 test is exactly the boundary that catches it.

## Bonus — See the compare-and-jump yourself
```cpp
// asm_if.cpp — no main needed, we only want the assembly
int clampHealth(int health)
{
    if (health < 0)
        health = 0;
    return health;
}
```
```bash
g++ -S -O0 asm_if.cpp -o asm_if.s
```
| Condition | Compare | Jump | Meaning of the jump |
|---|---|---|---|
| `health < 0` | `cmpl $0, 16(%rbp)` | `jns .L2` | jump if **not** negative (`health >= 0`) |
| `health > 100` | `cmpl $100, 16(%rbp)` | `jle .L2` | jump if **less or equal** (`health <= 100`) |

In both cases the jump goes to `.L2`, **past** the assignment. So the compiler jumps on
the **opposite** of your condition: "if `health > 100` is false, skip the body".
`health > 100` becomes "jump if `health <= 100`", which is `jle`.
