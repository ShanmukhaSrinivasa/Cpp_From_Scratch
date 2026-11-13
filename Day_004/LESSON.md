# Day 4 — Input, Output & Operators

**Goal for today:**
1. Read values from the keyboard with `std::cin`.
2. Use the arithmetic operators, and know exactly what integer division and `%` do.
3. Understand operator **precedence** — why `2 + 3 * 4` isn't `20` — and one nasty
   precedence trap specific to `std::cout`.
4. See why dividing by zero behaves completely differently for `int` vs. `double`.

---

## 0. Quick fix from Day 3

Your Ex 3 note still says *"char holds up to the value 250"* — small leftover wording
from before you fixed the exercise. `250` was never a limit; it was just the starting HP
you originally picked. `unsigned char`'s real range is `0`–`255`. Worth a one-line tidy
in that note when you get a chance — not urgent, just flagging it.

---

## 1. Getting input: `std::cin`

`std::cout` sends data **out** to the terminal; `std::cin` ("character in") reads data
**in** from the keyboard, using `>>` (pointing the opposite way from `<<`, which is a
handy way to remember which is which):

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter your age: ";
    int age;
    std::cin >> age;
    std::cout << "You are " << age << " years old.\n";
    return 0;
}
```

`std::cin >> age` waits for you to type something and press Enter, converts what you
typed into the type of `age` (here, `int`), and stores it. You can chain reads the same
way you chain `cout`:

```cpp
int age;
double height;
std::cin >> age >> height;   // type "25 5.9" then Enter — both get read in one go
```

**Two gotchas, both silent (no error shown) — exactly the theme from Days 2–3:**

- **`std::cin >> someString` only reads one word**, stopping at the first space —
  *not* a whole line:
  ```cpp
  std::string name;
  std::cin >> name;          // you type "Hero Jones", name becomes just "Hero"
  ```
  Reading a full line (with spaces) needs `std::getline`, which needs its own careful
  explanation — we'll get there properly on Day 11.
- **Typing letters where a number is expected doesn't error — it silently gives you
  `0`:**
  ```cpp
  int age;
  std::cin >> age;             // you type "twenty"
  std::cout << age << "\n";    // prints 0, with no warning you typed garbage
  ```
  Real games and tools check whether the read actually succeeded before trusting the
  value — a technique for later, once we've covered `if`.

## 2. Arithmetic operators

| Operator | Meaning | Works on |
|---|---|---|
| `+` | add | `int`, `double`, `char`, mixed |
| `-` | subtract | same |
| `*` | multiply | same |
| `/` | divide | same |
| `%` | remainder ("modulo") | **whole numbers only** — `int`, `char`, etc. |

`%` on `double` is flat-out not allowed — the compiler refuses it:
```cpp
double a = 7.5, b = 2.0;
a % b;   // error: invalid operands of types 'double' and 'double' to binary 'operator%'
```
"Remainder" only makes sense for whole-number division; decimals don't have a
leftover-after-dividing in the same way.

### Integer division truncates — it does not round
```cpp
std::cout << 7 / 2 << "\n";     // 3, not 3.5 — the .5 is just thrown away
std::cout << -7 / 2 << "\n";    // -3 (truncates toward zero, not toward -infinity)
std::cout << 7 % 2 << "\n";     // 1  (the leftover from 7 / 2)
std::cout << -7 % 2 << "\n";    // -1 (the remainder's sign follows the dividend, -7)
```
If **either side** is a `double`, the division happens in decimal:
```cpp
std::cout << 7.0 / 2 << "\n";   // 3.5
std::cout << 7 / 2.0 << "\n";   // 3.5 — one double in the expression is enough
```
This is the single most common beginner bug in any C-family language (C# included):
writing `average = total / count;` with two `int`s and being confused why decimals
disappeared. Fix: make at least one operand a `double` (often `total / (double)count` or
`total / static_cast<double>(count)`).

## 3. Precedence: which operator happens first

Just like normal math, `*`, `/`, `%` happen before `+`, `-`:
```cpp
std::cout << 2 + 3 * 4 << "\n";    // 14, not 20 — the 3*4 happens first
std::cout << (2 + 3) * 4 << "\n";  // 20 — parentheses force the addition first
```
Operators at the *same* precedence level run **left to right**:
```cpp
std::cout << 10 - 2 - 3 << "\n";   // 5, i.e. (10 - 2) - 3, not 10 - (2 - 3)
```
When in doubt, use parentheses — they cost nothing and remove all ambiguity, for you
*and* for whoever reads your code later.

### The `std::cout` precedence trap
`<<` was originally a bitwise shift operator, and C++ *reused* it for printing. That
reuse has a real cost: `<<` binds **tighter** than comparisons like `==`. This means you
cannot print a comparison directly without parentheses:
```cpp
std::cout << 2 + 3 == 5 << "\n";     // compile ERROR — not what you think it parses as!
std::cout << (2 + 3 == 5) << "\n";   // fix: parenthesize the comparison — prints 1
```
The first line is actually parsed as `(std::cout << (2 + 3)) == (5 << "\n")`, and
`5 << "\n"` (shifting a number by a string) makes no sense to the compiler, hence the
error. **Always wrap a comparison in `()` before sending it to `std::cout`.**

## 4. Division by zero: int vs. double behave completely differently

```cpp
int a = 5, b = 0;
std::cout << a / b << "\n";   // undefined behavior — the program crashes before printing anything
```
Integer division by zero has no defined result in C++ — on most systems it crashes the
program outright (the exact behavior depends on your OS and compiler; don't rely on a
specific error message or exit code).

```cpp
double a = 5.0, b = 0.0;
std::cout << a / b << "\n";   // prints: inf
```
`double` has a special reserved bit pattern for "infinity" (part of the same IEEE754
standard that gives floats their approximate-decimal behavior from Day 3), so dividing
by zero just produces that value instead of crashing. Same operator, same-looking code,
completely different outcome — purely because of the **type**.

## 5. Compound assignment, briefly extended

You already know `+=` and `-=` from Day 2. The same shorthand exists for every
arithmetic operator:
```cpp
int score = 10;
score *= 3;   // score = score * 3;  → 30
score /= 2;   // score = score / 2;  → 15
score %= 4;   // score = score % 4;  → 3
```

---

## Key ideas to remember
- `std::cin >> variable` reads one whitespace-separated token and converts it to that
  variable's type. Reading text into a `std::string` with `>>` stops at the first space;
  bad input (letters into a number) silently becomes `0`, no error shown.
- `%` only works on whole-number types. Integer division **truncates toward zero**
  (`-7/2 == -3`); the sign of `%`'s result follows the left-hand operand.
- If either operand of `/` is a `double`, the division is done in decimal.
- `*`, `/`, `%` run before `+`, `-`; same-precedence operators run left to right. Use
  `()` whenever you're not 100% sure, and **always** parenthesize a comparison before
  sending it into `std::cout` (`<<` binds tighter than `==`).
- Integer division by zero is undefined behavior and typically crashes; `double`
  division by zero produces `inf` instead, because of how IEEE754 floating-point is
  defined.

**Connecting to games:** every HUD stat, damage formula, and "percent complete" bar you
compute will hit integer-division truncation sooner or later (`currentXP / xpToLevel *
100` silently giving `0` for a `0.3` result is a *very* common bug). Reading player
input the way `std::cin` does here is also exactly the skeleton of a text-based menu —
which is where Build Day (Day 7) is headed.

Now go to `EXERCISES.md`.
