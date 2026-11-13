# Day 4 — Answer Key & Revision Sheet

Use this for revising. Try to answer from memory **first**, then check here.
All code and error messages below were checked with g++ 16.1.0 (`-std=c++20 -Wall -Wextra`).

---

## ⚡ 60-second revision

- `std::cin >> x` reads one **whitespace-separated** chunk and converts it to `x`'s type.
- `std::cin >> someString` stops at the first space: `Hero Jones` → `Hero`.
- Bad input (`twenty` into an `int`) silently gives `0`. No error, no warning.
- `%` works only on whole-number types. On `double` it's a compile error.
- Integer division **truncates toward zero**: `7/2 = 3`, `-7/2 = -3`. The sign of `%`
  follows the left operand: `-7%2 = -1`, `7%-2 = 1`.
- If **either** operand of `/` is a `double`, the division is done in decimal.
- `*` `/` `%` run before `+` `-`; same level runs left to right.
- `<<` binds tighter than `==`, so always write `std::cout << (a == b)`.
- `int / 0` → **run-time** crash (undefined behavior; the compiler says nothing).
  `double / 0.0` → `inf`.
- The **type of the variable** decides what happens, not the literal you wrote:
  `int d = 0.0;` is an `int` holding `0`, so dividing by it is integer division.

---

## Notes questions — model answers

### How does `std::cin >> someInt` know when to stop reading?
It skips any leading whitespace (spaces, tabs, Enter), then reads characters as long as
they can still be part of an `int` (digits, an optional leading `-`). It stops at the
first character that can't be, usually whitespace. That leftover character stays in the
input, waiting for the next read.

### Why does `std::cin >> someString` only grab one word?
`>>` treats whitespace as the separator between values, for every type, `std::string`
included. So it reads up to the first space and stops. Reading a whole line needs
`std::getline` (Day 11).

### Why does integer division truncate instead of round?
An `int` result has no room for a fractional part, so something has to be dropped. C++
defines that the fraction is simply discarded (rounded **toward zero**). This also
matches what the CPU's integer-divide instruction produces: a whole-number quotient plus
a remainder, which is exactly what `/` and `%` give you.

### Why does `std::cout << (x == y)` need parentheses?
**Precedence.** `<<` binds tighter than `==`. Without parentheses,
`std::cout << 2 + 3 == 5 << "\n"` is grouped as `(std::cout << (2 + 3)) == (5 << "\n")`.
The compiler rejects `5 << "\n"`. Parentheses make the comparison happen first, then its
result (`1` or `0`) is printed.

### Why does `5 / 0` behave differently from `5.0 / 0.0`?
Both compile without complaint. The difference shows up at **run time**:
- `int` division by zero has no defined result in C++ (undefined behavior). On most
  systems the CPU raises a hardware fault and the program crashes.
- `double` follows the IEEE 754 standard, which reserves special bit patterns for
  infinity. So `5.0 / 0.0` produces `inf` and the program keeps running.

---

## Ex 1 — Basic input
```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name;
    int age;

    std::cout << "Enter your name: ";
    std::cin >> name;
    std::cout << "Enter your age: ";
    std::cin >> age;

    std::cout << "Hello, " << name << "! You are " << age << " years old.\n";
    return 0;
}
```

## Ex 2 — The one-word string trap
```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name;
    std::cout << "Enter a name: ";
    std::cin >> name;
    std::cout << "Your name is: " << name << "\n";
    return 0;
}
```
Typing `Hero Jones` prints `Your name is: Hero`. `Jones` is still sitting in the input,
unread.

## Ex 3 — Bad number input
```cpp
#include <iostream>

int main()
{
    int num;
    std::cout << "Enter a number: ";
    std::cin >> num;
    std::cout << "You have entered: " << num << "\n";
    return 0;
}
```
Typing `twenty` prints `0`. No compiler warning (the compiler can't know what you'll
type), and no run-time error message either. The read silently failed.

## Ex 4 — Division and modulo table
| Expression | Result | Why |
|---|---|---|
| `7 / 2` | `3` | integer division, `.5` dropped |
| `-7 / 2` | `-3` | truncates **toward zero**, not down to `-4` |
| `7 % 2` | `1` | `7 = 2×3 + 1` |
| `-7 % 2` | `-1` | `-7 = 2×(-3) + (-1)`; sign follows the left operand |
| `7 % -2` | `1` | `7 = (-2)×(-3) + 1`; sign follows the left operand |
| `7.0 / 2` | `3.5` | one `double` operand → decimal division |

Rule that ties `/` and `%` together: `(a / b) * b + (a % b) == a`, always.

## Ex 5 — Precedence
```cpp
std::cout << 2 + 3 * 4 << "\n";     // 14   (3*4 first)
std::cout << 10 - 2 - 3 << "\n";    // 5    ((10-2)-3, left to right)
std::cout << 20 / 4 - 2 << "\n";    // 3    (20/4 first, then -2)
std::cout << (2 + 3 == 5) << "\n";  // 1    (true prints as 1)
```
Without the parentheses, the last line gives:
```
error: invalid operands of types 'int' and 'const char [2]' to binary 'operator<<'
    7 |     std::cout << 2 + 3 == 5 << "\n";
      |                           ~ ^~ ~~~~
      |                           |    |
      |                           int  const char [2]
```
The arrows point at `5 << "\n"`. That's the piece the compiler built because `<<`
grabbed its operands before `==` could.

## Ex 6 — Division by zero
```cpp
#include <iostream>

int main()
{
    // Experiment 1: int
    // int a = 5, b = 0;
    // std::cout << a / b << "\n";   // crashes at run time, prints nothing

    // Experiment 2: double
    double c = 5.0, d = 0.0;
    std::cout << c / d << "\n";      // prints: inf

    return 0;
}
```
**The trap:** `int c = 5.0; int d = 0.0;` looks like the double experiment, but the
variables are `int`. The `=` silently converts `5.0` → `5` and `0.0` → `0` (Day 2 §5,
no warning even with `-Wall -Wextra`), so `c / d` is still **integer** division by zero
and the program crashes with no output. The literal's type doesn't matter once it's
stored; the variable's type does.

## Ex 7 — The average-score bug, then the fix
```cpp
#include <iostream>

int main()
{
    int s1, s2, s3;
    std::cout << "Enter three scores: ";
    std::cin >> s1 >> s2 >> s3;

    int sum = s1 + s2 + s3;

    std::cout << "Buggy average: " << sum / 3 << "\n";                        // 84
    std::cout << "Fixed average: " << static_cast<double>(sum) / 3 << "\n";   // 84.3333

    return 0;
}
```
With `85 90 78`: sum is `253`. `253 / 3` is `int / int`, so the result is truncated to
`84`. Casting `sum` to `double` first makes it `253.0 / 3`, which is decimal division:
`84.3333`.

Note: the cast must happen **before** the division. `static_cast<double>(sum / 3)` is
still `84`: the integer division already threw the fraction away, and the cast just
turns `84` into `84.0`.
