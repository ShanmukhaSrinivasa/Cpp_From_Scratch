# Day 3 — Data Types: Bits, Bytes and Binary

**Goal for today:**
1. Understand what's actually sitting inside the boxes from Day 2 — bits, in binary.
2. Know why `int` has a limit, and what happens when you cross it (it's not an error!).
3. Understand that `char` is secretly just a small number, and what a "decimal point"
   really costs you in `float`/`double`.

---

## 0. Quick fixes from Day 2

Your notes still have three things to straighten out — today's topic actually resolves
all three, so pay attention as you read:

- **"A space is created with the name `health`"** — the *name* never lives in memory.
  Only the bytes do. Today you'll see exactly what sits in those bytes: not a name, just
  binary digits.
- **"Reading uninitialized memory might overflow and show us an error"** — this mixes up
  two different things. You'll see today that overflow is real, but it is almost never an
  error — it silently produces a *wrong but valid-looking* number. No message, no crash,
  just a bad value. That silence is exactly what makes both uninitialized reads and
  overflow dangerous.
- **Ex 5, `=` vs `{}`** — re-confirm this one for yourself: `int x = 7.8;` compiles clean
  and quietly becomes `7`; `int x{7.8};` refuses to compile. If that's still not settled,
  reread [Day_002/LESSON.md](../Day_002/LESSON.md) §5 before moving on.

---

## 1. Counting the only way a computer can: binary

A CPU can only tell two voltages apart: "on" and "off". So every number it stores has to
be written using only two digits: `0` and `1`. This is **binary** (base 2), compared to
the base 10 ("decimal") you count in normally.

Decimal place values are powers of 10: `present 247 = 2×100 + 4×10 + 7×1`.
Binary place values are powers of 2:

```
binary:      1   0   1   1
place value: 8   4   2   1
           = 8 + 0 + 2 + 1 = 11 (decimal)
```

One binary digit (`0` or `1`) is called a **bit**. Eight bits grouped together is a
**byte** — the same byte-boxes from Day 1's memory diagram. A byte can represent
`2^8 = 256` different patterns, so it can hold any whole number from `0` to `255`
(unsigned) or `-128` to `127` (signed — more on that below).

C++ lets you write numbers in binary directly, with a `0b` prefix, to make this concrete:

```cpp
int x = 0b1011;   // the binary pattern above
std::cout << x << "\n";   // prints 11 — same number, decimal output
```

The CPU doesn't care how *you* wrote it (`11`, `0b1011`, `0xB` are all identical bytes in
memory) — base is purely a convenience for humans reading the source code.

## 2. How `int` is really stored

An `int` is 4 bytes = 32 bits, so it can represent `2^32` (about 4 billion) different
bit patterns. By default an `int` is **signed** — it splits that range between negative
and positive numbers using a scheme called **two's complement**: the leftmost bit acts as
a sign flag (`0` = positive, `1` = negative), and negative numbers are stored as "what you'd
have to add to get back to zero". You don't need to hand-compute two's complement today —
just know it's why the signed range looks lopsided:

```cpp
#include <iostream>
#include <limits>

int main()
{
    std::cout << std::numeric_limits<int>::min() << "\n";   // -2147483648
    std::cout << std::numeric_limits<int>::max() << "\n";   //  2147483647
    return 0;
}
```

One more negative number than positive, because `0` itself uses up one of the "positive
side" slots.

## 3. Overflow: not an error, a silent wraparound

What happens if you add 1 to the biggest possible `int`? There's no bigger bit pattern to
move to — so it **wraps around** to the smallest one:

```cpp
#include <iostream>
#include <climits>

int main()
{
    int x = INT_MAX;          // 2147483647
    std::cout << x << "\n";
    x = x + 1;
    std::cout << x << "\n";   // -2147483648 !
    return 0;
}
```
Real output, no warning at all even with `-Wall -Wextra` (this happens at run time, with
a value the compiler can't predict in advance):
```
2147483647
-2147483648
```
This is **the** classic source of real game bugs — a famous (if apocryphal) one is
*Civilization*'s "Nuclear Gandhi": a trait value stored in a tiny type dropped from `1`
to `0` and then wrapped to the type's maximum, making the most peaceful leader suddenly
the most aggressive. An unsigned byte wraps the same way, just between `0` and `255`:

```cpp
unsigned char hp = 255;
hp = hp + 1;
std::cout << (int)hp << "\n";   // 0 — your "255 HP" character just died from overflow
```
(The `(int)` cast is just so `std::cout` prints a number instead of treating the byte as
a character — more on casts below.)

**Takeaway:** choosing a type isn't just "does the value fit *today*" — it's "could this
calculation ever drift outside this range while the game runs."

## 4. `char` is just a (very small) number

`char` is 1 byte, so it can only hold `0`–`255` (or `-128`–`127` signed). The "letter" you
see is just one agreed-upon mapping from numbers to printable characters, called **ASCII**:
`65` means `'A'`, `97` means `'a'`, and so on. `std::cout` prints a `char` as a letter by
default, but you can force it to show you the underlying number with a **cast**
(`static_cast<int>(...)`, "treat this value as this other type"):

```cpp
#include <iostream>

int main()
{
    char c = 'A';
    std::cout << static_cast<int>(c) << "\n";        // 65
    std::cout << static_cast<char>(97) << "\n";       // a
    return 0;
}
```

This is also why `char` arithmetic works at all — `'A' + 1` is really just `65 + 1 = 66`,
which happens to be `'B'`.

## 5. `float` and `double`: decimals are approximate

So far we've used `double` for decimals. `float` is the same idea with half the storage:

| Type | Size | ~Decimal digits of precision |
|---|---|---|
| `float` | 4 bytes | ~7 |
| `double` | 8 bytes | ~15 |

```cpp
float f = 1.0f / 3.0f;     // the f suffix means "treat this literal as float"
double d = 1.0 / 3.0;
```
`f` prints `0.3333333433...`, `d` prints `0.3333333333...` — `double` is simply more
precise. Both are still *approximations* of one-third, because binary floating-point
(like decimal) can't exactly represent every fraction, the same way `1/3` has no exact
end in decimal either. This is not a bug — it's a trade-off for storing an enormous range
of magnitudes (from tiny to astronomical) in a fixed number of bytes.

The famous consequence:
```cpp
#include <iostream>

int main()
{
    double a = 0.1;
    double b = 0.2;
    std::cout << std::boolalpha << (a + b == 0.3) << "\n";   // false !
    return 0;
}
```
`0.1` and `0.2` can't be stored exactly in binary (same way `1/3` can't be stored exactly
in decimal), so their sum is a tiny bit off from the literal `0.3`. **Never compare
`float`/`double` with `==`** — this bites everyone at least once. (The fix involves
comparing "close enough", which we'll do once we've covered functions.)

## 6. `bool`: 1 byte, but only two meaningful values

`bool` takes a full byte (not a single bit — the CPU can't address individual bits), but
only `0` (false) and `1` (true) are its "real" values. `std::cout` prints a `bool` as `0`
or `1` by default; `std::boolalpha` (used above) makes it print `true`/`false` instead.

---

## Key ideas to remember
- Everything in memory is bits (`0`/`1`); a byte is 8 bits and can hold 256 patterns.
- `int` is 4 bytes, signed by default, range roughly ±2.1 billion.
- **Overflow wraps around silently — it is not an error and rarely warns you.** This is
  the actual danger, same root cause as reading an uninitialized variable.
- `char` is just a 1-byte number interpreted as a letter via ASCII; `static_cast<int>` or
  `static_cast<char>` moves between the two views.
- `float` (4 bytes, ~7 digits) and `double` (8 bytes, ~15 digits) both store decimals as
  *approximations* — never compare them with `==`.
- `bool` is 1 byte but only means `0`/`1`; `std::boolalpha` prints the words instead.

**Connecting to games:** choosing `int` vs `float` vs a small type like `unsigned char`
for health, score or position is a real design decision, not a formality — pick wrong and
you get wraparound bugs (classic "integer overflow" exploits in real games) or precision
bugs (physics that drifts over a long play session because `float` wasn't precise enough).
We'll revisit precision trade-offs properly once we reach Phase 5's game math.

Now go to `EXERCISES.md`.
