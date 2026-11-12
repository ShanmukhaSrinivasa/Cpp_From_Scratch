# Day 3 — Answer Key & Revision Sheet

Use this for revising. Try to answer from memory **first**, then check here.
All code and error messages below were checked with g++ 16.1.0 (`-std=c++20 -Wall -Wextra`).

---

## ⚡ 60-second revision

- A **bit** is a single binary digit (`0` or `1`) — the smallest unit of storage. A
  **byte** is 8 bits, and can represent `2^8 = 256` different patterns.
- **Place value vs. digit:** in `8 4 2 1`, those numbers are what each *position* is
  worth — the binary digits themselves are only ever `0` or `1`. `11` in binary is the
  **digit string** `1011` (`8+0+2+1`), never the string "8021".
- `int` is 4 bytes, signed, range ≈ `-2.1 billion` to `+2.1 billion`.
- **Overflow wraps around silently** — `INT_MAX + 1` becomes the smallest `int`, with no
  error and usually no warning. Same root cause as reading uninitialized memory: no
  message tells you something went wrong.
- `char` is just a 1-byte number; "letters" are an agreed mapping (ASCII) from numbers to
  printable symbols. `static_cast<int>`/`static_cast<char>` move between the two views.
- `float` (4 bytes, ~7 digits) and `double` (8 bytes, ~15 digits) both store decimals as
  **approximations** — never compare them with `==`.
- `unsigned char`'s real range is **0–255**, not whatever starting value an exercise
  happened to use.

---

## Notes questions — model answers

### What is a bit, and what is a byte made of?
A **bit** is one binary digit — `0` or `1` — the smallest possible unit of storage; a CPU
can only reliably tell two states apart (on/off), so everything ultimately comes down to
sequences of these. A **byte** is a group of 8 bits, and can represent `2^8 = 256`
distinct patterns (`0`–`255` unsigned).

### Why does `int` overflow instead of showing an error?
Because there's no bit pattern left to represent "one more than the biggest number" —
the hardware just keeps adding according to its normal rules, and the result silently
wraps to the smallest representable value. The compiler can't know in advance that a
*runtime* calculation like `x + 1` will exceed the range (it only knows `x`'s type, not
every value it might hold while running), so it has nothing to warn about ahead of time,
and the CPU itself has no concept of "this number is too big" — it just does the bit
arithmetic it's told to.

### Why is `char` basically just a number underneath?
Every value in memory is bits — a `char` reserves exactly 1 byte, same as any small
integer type. "Letters" are purely an agreed-upon **mapping** (ASCII) from numbers to the
glyphs a terminal draws: `65` is displayed as `A` only because everyone (terminals,
fonts, `std::cout`) agreed `65` means `A`. `static_cast<int>(c)` shows you the real
number underneath; `static_cast<char>(n)` goes the other way.

### Why doesn't `0.1 + 0.2 == 0.3` in C++?
`0.1` and `0.2` (and `0.3`) don't have exact representations in binary floating-point,
the same way `1/3` has no exact ending in decimal. Each is stored as the *closest*
representable value, and those tiny rounding errors don't cancel out perfectly when
added — so `0.1 + 0.2` lands a hair away from the literal `0.3`. This is inherent to how
floating-point trades exactness for an enormous representable range in a fixed number of
bytes, not a bug in your code or the compiler.

---

## Ex 1 — Binary by hand, then check
| Binary | Place values (8 4 2 1) | Decimal |
|---|---|---|
| `0b0110` | `0+4+2+0` | `6` |
| `0b1001` | `8+0+0+1` | `9` |
| `0b1111` | `8+4+2+1` | `15` |

```cpp
#include <iostream>

int main()
{
    int a = 0b0110;
    int b = 0b1001;
    int c = 0b1111;

    std::cout << a << "\n";   // 6
    std::cout << b << "\n";   // 9
    std::cout << c << "\n";   // 15

    return 0;
}
```

## Ex 2 — Predict, then check: integer overflow
```cpp
#include <iostream>
#include <climits>

int main()
{
    int a = INT_MAX;
    std::cout << a << "\n";    // 2147483647
    a += 1;
    std::cout << a << "\n";    // -2147483648
    return 0;
}
```
No warning at all, even with `-Wall -Wextra` — the overflow happens on a runtime value
the compiler can't predict ahead of time, so there's nothing for it to flag in advance.

## Ex 3 — Break it on purpose: the wraparound health bug
Starting at `250` and subtracting `10` three times never goes below zero
(`250→240→230→220`), so **this particular run doesn't actually trigger a wraparound** —
that's a gap in the exercise's chosen numbers, not something wrong in your code.

To see the real bug, cross zero:
```cpp
#include <iostream>

int main()
{
    unsigned char hp = 5;
    std::cout << "hp: " << (int)hp << "\n";
    hp -= 10;
    std::cout << "hp after -10: " << (int)hp << "\n";   // 251, not -5!
    return 0;
}
```
`unsigned char` cannot represent `-5`, so it wraps to `256 - 5 = 251` — a character at
5 HP that should be dead instead reports *near-full health*. This is exactly why health,
score, and similar stats are almost always a **signed** type even though they're never
meant to go negative in play: a signed `int` just goes to `-5` and stays there, which you
can easily check for (`if (health <= 0)`), instead of silently wrapping to a huge
positive number that looks healthy.

## Ex 4 — char, int, and ASCII
```cpp
#include <iostream>

int main()
{
    std::cout << static_cast<int>('A') << "\n";   // 65
    std::cout << static_cast<int>('a') << "\n";   // 97
    std::cout << static_cast<int>('0') << "\n";   // 48

    std::cout << static_cast<char>(72)  << "\n";  // H
    std::cout << static_cast<char>(105) << "\n";  // i
    std::cout << static_cast<char>(33)  << "\n";  // !

    char ch = 'A' + 1;
    std::cout << ch << "\n";                        // B
    std::cout << static_cast<int>(ch) << "\n";      // 66

    return 0;
}
```
`'A' + 1` is computed as `int` arithmetic (`65 + 1 = 66`) regardless of where you store
the result — storing it in a `char` just reinterprets `66` as the letter `B` when
printed; storing it in an `int` shows the raw number.

## Ex 5 — Predict, then check: float vs. precision
```cpp
#include <iostream>

int main()
{
    double a = 0.1, b = 0.2;
    std::cout << std::boolalpha << (a + b == 0.3) << "\n";   // false

    float fa = 0.1f, fb = 0.2f;
    std::cout << (fa + fb == 0.3f) << "\n";                   // also false

    std::cout.precision(17);
    std::cout << (a + b) << "\n";   // 0.30000000000000004 — the real stored value
    return 0;
}
```
Both `float` and `double` give `false` — the imprecision exists at both sizes, `float`
just rounds even more aggressively than `double` does. `precision(17)` reveals the actual
stored value is `0.30000000000000004`, not the `0.3` the source code literally says.

## Ex 6 — Choosing types for a game character
```cpp
#include <iostream>

int main()
{
    int health = 9999;          // signed: a wrong subtraction goes to -N, not wraps to a huge number (see Ex 3)
    char slot = 'A';            // 1 byte, exactly fits "a single letter"
    float walkingSpeed = 4.5f;  // decimals needed; 4 bytes is plenty of precision for a speed value
    bool isStunned = false;     // exactly two states

    std::cout << health << "\n" << slot << "\n" << walkingSpeed << "\n" << isStunned << "\n";
    return 0;
}
```
The stat most tempted toward a small unsigned type is **health** — "it's never negative,
so why not `unsigned char`?" — but that's exactly the reasoning that causes the Ex 3 bug:
the moment any calculation (damage, a bug, a debuff) pushes it below zero even briefly,
an unsigned type wraps to a huge positive number instead of going negative where you can
catch it. A signed `int` costs a few extra (cheap) bytes and avoids that failure mode
entirely.
