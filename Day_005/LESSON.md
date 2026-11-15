# Day 5 — Decisions: `if`, `else`, `switch` & Logical Operators

**Goal for today:**
1. Make programs that **choose** what to do: `if`, `else if`, `else`.
2. Combine conditions with `&&`, `||`, `!`, and understand **short-circuiting**.
3. See what a decision really is to the CPU: a **compare** and a **jump**.
4. Use `switch` for menus, and avoid its famous **fall-through** trap.
5. Finally detect the bad input from Day 4 (`"twenty"` becoming `0`).

---

## 0. Quick fixes from Day 4

Three things from your Day 4 work, all connected to today's topic:

**a) Ex 6 never tested `double`.** You wrote `int c = 5.0; int d = 0.0;`. The variable's
**type** decides what it holds (Day 2), so `c` is just the `int` `5` and `d` the `int` `0`.
You ran the *integer* test twice. Use `double c = 5.0; double d = 0.0;` and you'll see `inf`.

**b) Why you saw no output at all.** The program **crashed** at run time. On Windows, an
integer divide-by-zero kills the program with exit code `-1073741676` (= `0xC0000094`,
Windows' code for "integer divide by zero"). Check it right after running:
```bash
./div_zero.exe
echo $LASTEXITCODE
```
Even a `std::cout << "before\n";` placed *before* the division doesn't appear. `std::cout`
collects text in a buffer and writes it to the screen in batches. The crash destroyed the
buffer before it was written out.

So in your notes, *"the compiler throws an error"* isn't right. The compiler was happy
and built the `.exe`. The crash happened later, at **run time** (the Day 1 idea again:
compile time and run time are different moments).

**c) `<<` and `==`.** It's not that you "can't compare" with `<<`. The problem is
**precedence**: `<<` runs *before* `==`, so `std::cout << x == y` is grouped as
`(std::cout << x) == y`. That's nonsense, and the compiler rejects it. Parentheses force
the comparison to run first.

Also still open: the buggy (`int`) version for Ex 7 and the exact Ex 5 error message.
Finish those when you can.

---

## 1. Questions with yes/no answers

A decision needs a question whose answer is **true** or **false**, which is a `bool` (Day 3).
These **comparison operators** produce a `bool`:

| Operator | Means | `5 ? 3` gives |
|---|---|---|
| `==` | equal to | `false` |
| `!=` | not equal to | `true` |
| `<`  | less than | `false` |
| `>`  | greater than | `true` |
| `<=` | less than or equal | `false` |
| `>=` | greater than or equal | `true` |

```cpp
int health = 30;
bool isLow = health < 50;     // isLow is true
```

## 2. `if`, `else if`, `else`

```cpp
#include <iostream>

int main()
{
    int health = 0;
    std::cout << "Enter health: ";
    std::cin >> health;

    if (health <= 0)
    {
        std::cout << "You died.\n";
    }
    else if (health < 25)
    {
        std::cout << "Critical! Find a potion.\n";
    }
    else
    {
        std::cout << "You're fine.\n";
    }

    return 0;
}
```

- The conditions are checked **top to bottom**. The **first** true one runs its block,
  and all the rest are skipped, even if they would also be true.
- `else` (optional) catches everything that didn't match.
- **Order matters.** If you check `health < 100` first, then a player with `-5` HP matches
  that branch and never reaches "You died". Put the most specific checks first.

**Always use `{ }` braces,** even for one line. Section 6 shows why.

## 3. What the CPU actually does with an `if`

On Day 1 you learned the CPU only does tiny things: add, compare, copy, **jump**.
An `if` is built from exactly those. This function:

```cpp
int clampHealth(int health)
{
    if (health < 0)
        health = 0;
    return health;
}
```

compiles (with `g++ -S`) to this, trimmed slightly:

```asm
    cmpl  $0, 16(%rbp)     ; COMPARE health with 0
    jns   .L2              ; JUMP to .L2 if the result was NOT negative (health >= 0)
    movl  $0, 16(%rbp)     ; health = 0   (only reached when health < 0)
.L2:
    movl  16(%rbp), %eax   ; return health
```

So an `if` is: **compare, then jump over the code you don't want.** There's no magic
"decision" hardware. Every `if`, loop and `switch` you will ever write becomes compares and
jumps. (You'll do this yourself in the bonus exercise.)

## 4. Combining conditions: `&&`, `||`, `!`

| Operator | Name | True when |
|---|---|---|
| `a && b` | AND | **both** are true |
| `a \|\| b` | OR | **at least one** is true |
| `!a` | NOT | `a` is false |

```cpp
bool hasKey = true;
int level = 3;
bool isAdmin = false;

if ((hasKey && level >= 5) || isAdmin)
{
    std::cout << "The door opens.\n";
}
```
`&&` runs before `||` (like `*` before `+`), but use parentheses anyway, so the meaning is obvious.

### Short-circuiting: the right side might never run
C++ evaluates `&&` and `||` **left to right, and stops as soon as the answer is known**:
- `false && anything` is false, so `anything` is **never evaluated**.
- `true || anything` is true, so `anything` is **never evaluated**.

That isn't just a speed trick. It's a safety tool:

```cpp
int total = 50;
int count = 0;

if (count != 0 && total / count > 10)   // safe!
{
    std::cout << "Big average\n";
}
```
Because `count != 0` is false, `total / count` **never runs**, so there's no divide-by-zero crash.
Swap the two sides and the program crashes like your Day 4 Ex 6.

## 5. Any number can be a condition

When a number is used as a condition, **0 means false and anything else means true**:

```cpp
int lives = 3;
if (lives)                 // same as: if (lives != 0)
{
    std::cout << "Still alive\n";
}
```
That's handy, but it's also exactly what makes the first trap below possible.

## 6. Classic traps (g++ `-Wall -Wextra` warns about all of them)

**Trap 1: `=` instead of `==`**
```cpp
int health = 50;
if (health = 0)            // ASSIGNS 0, then tests 0, which is false
{
    std::cout << "Game over\n";
}
// health is now 0 !
```
```
warning: suggest parentheses around assignment used as truth value [-Wparentheses]
```
It compiles, the `if` never runs, *and* it destroys your variable. Two bugs from one character.

**Trap 2: a `;` right after `if (...)`**
```cpp
if (health <= 0);          // this ; is an EMPTY statement and IS the if's body
{
    std::cout << "You died\n";   // always runs!
}
```
```
warning: suggest braces around empty body in an 'if' statement [-Wempty-body]
```

**Trap 3: no braces, and the indentation lies**
```cpp
if (health <= 0)
    std::cout << "You died\n";
    std::cout << "Respawning...\n";   // NOT inside the if, it always runs
```
```
warning: this 'if' clause does not guard... [-Wmisleading-indentation]
```
Without braces, an `if` controls **only the next single statement**. The compiler doesn't
care about indentation; only humans do.

**Trap 4: maths-style ranges**
```cpp
int score = 75;
if (60 <= score <= 70)      // ALWAYS true!
```
```
warning: comparisons like 'X<=Y<=Z' do not have their mathematical meaning [-Wparentheses]
```
It's grouped as `(60 <= score) <= 70`. The left part becomes `true`/`false` (`1`/`0`),
and `1 <= 70` is always true. Write `score >= 60 && score <= 70`.

**Lesson:** compile with warnings on, and treat every warning as an error you must fix.

## 7. `switch`: choosing from a list of exact values

When you compare **one variable against many exact values**, `switch` is cleaner than a
long `else if` chain:

```cpp
char move = 'x';
std::cout << "Choose (a)ttack, (d)efend, (r)un: ";
std::cin >> move;

switch (move)
{
case 'a':
case 'A':                                     // stacked cases: 'a' OR 'A'
    std::cout << "You swing your sword!\n";
    break;                                    // leave the switch
case 'd':
case 'D':
    std::cout << "You raise your shield.\n";
    break;
case 'r':
case 'R':
    std::cout << "You run away...\n";
    break;
default:                                      // nothing matched
    std::cout << "You hesitate and lose your turn.\n";
    break;
}
```

### The fall-through trap
`case` labels are just **jump targets**. The switch jumps to the matching label and
then keeps running **downward until it hits `break`**, straight through the other cases:

```cpp
int choice = 1;
switch (choice)
{
case 1:
    std::cout << "Start game\n";      // forgot break!
case 2:
    std::cout << "Options\n";
    break;
}
// prints BOTH "Start game" and "Options"
```
```
warning: this statement may fall through [-Wimplicit-fallthrough=]
```
Stacked empty cases (`case 'a': case 'A':`) are the one place fall-through is wanted,
and g++ doesn't warn about those.

### `switch` only works on whole-number types
`int`, `char`, `bool` and similar types work. `double` and `std::string` don't:
```cpp
std::string cmd = "go";
switch (cmd)                   // error: switch quantity not an integer
```
Why? A switch compares exact whole numbers, which lets the compiler build a fast
**jump table**. Text and decimals can't be compared that way, so use `if` / `else if` for them.

**Rule of thumb:** use `switch` for menus, states and commands (one variable, exact values),
and `if` for ranges (`health < 25`), combined conditions, strings and decimals.

## 8. Detecting bad input: `std::cin.fail()`

On Day 4, typing `twenty` into an `int` silently gave `0`. Now you can **check** for that:

```cpp
#include <iostream>

int main()
{
    int age = 0;
    std::cout << "Enter your age: ";
    std::cin >> age;

    if (std::cin.fail())                 // true if the last >> couldn't read a number
    {
        std::cout << "That's not a number!\n";
        return 1;                         // end the program with an error code
    }

    if (age >= 18)
    {
        std::cout << "You can play the M-rated game.\n";
    }
    else
    {
        std::cout << "Sorry, too young.\n";
    }

    return 0;
}
```
- `twenty` makes `cin.fail()` true, so you see the error message and the program exits with code 1 (Day 1: the OS gets it).
- `18abc` is accepted as `18`. `>>` reads digits while it can and stops at `a`. That's
  not a failure from its point of view. Full input validation needs loops (Day 6+).

`return 1;` in the middle of `main` ends the program right there. That's often the
simplest way to handle "this can't continue".

---

## Key ideas to remember
- Comparisons (`== != < > <= >=`) produce a `bool`. `if` runs a block only when its condition is true.
- `if` / `else if` / `else` is checked top to bottom, and only the **first** true branch runs. Order matters.
- To the CPU, a decision is a **compare + jump** over the code that shouldn't run.
- `&&` = both, `||` = at least one, `!` = not. They **short-circuit**: the right side may never
  run, which you can use to guard against things like divide-by-zero.
- A number used as a condition: `0` is false, anything else is true.
- Always use braces. Watch for `=` vs `==`, a stray `;` after `if`, and `a <= x <= b`.
- `switch` works on whole-number types (`int`, `char`…). Every `case` needs a `break`,
  or it falls through. Use `default` for "anything else".
- `std::cin.fail()` tells you whether the last read failed.
- An integer divide-by-zero is a **run-time crash**, and it can also swallow output that hadn't been written to the screen yet.

**Connecting to games:** almost every game rule is a condition. *Is the player dead? Do
they have the key AND the right level? Is the enemy in range?* Unity scripts are full of
`if (health <= 0) Die();`, and game **state machines** (menu, playing, paused, game over)
are classically written as a `switch`. Day 23's `enum class` makes those switches even
better. Short-circuiting shows up in null checks like `if (target != null && target.IsAlive())`.
This is the same idea you'll use in C++ with pointers on Day 16.

Now go to `EXERCISES.md`.
