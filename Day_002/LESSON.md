# Day 2 — Variables: Named Boxes in Memory

**Goal for today:**
1. Understand what *actually* happens in memory when you create a variable.
2. Declare, initialize and assign variables of the basic types: `int`, `double`, `char`, `bool`, `std::string`.
3. Know the difference between **declaration**, **initialization** and **assignment** — and why an uninitialized variable is dangerous.
4. Learn the naming rules.

---

## 0. Quick fixes from Day 1

Three things from your notes to straighten out before we move on:

- **The CPU does not compile anything.** The **compiler** (g++, a program) translates your
  `.cpp` text into machine code, **once**, before you ever run the program. The **CPU**
  then just runs that machine code, super fast — it has never seen your C++ text and
  doesn't know C++ exists. Two different jobs, two different "runners": g++ runs on the
  CPU to *build* your program; your `.exe` runs on the CPU *later* to execute it.
- **Compiling and running are not the same moment.** Compiling happens once (compile
  time) and produces `hello.exe`. Running happens later (run time), any number of times,
  without the compiler. "The code compiles in the runtime" mixes the two — there is no
  compiling *during* run time.
- **Ex 3f (`main` → `Main`)** wasn't a compiler error at all — it came from the **linker**
  (`ld.exe`), a different tool that runs *after* the compiler to stitch your machine code
  together into an `.exe`. That's why the message looked so different (`undefined
  reference`, not `error:`). If you saw "no error", you likely ran the old `.exe` without
  recompiling — always re-run the compile command before judging the result.

Keep these in mind — today's topic (variables) only makes sense once "compile time" and
"run time" are separated in your head.

---

## 1. What a variable actually is

Remember Day 1: memory is a long row of numbered byte-boxes, and a program is just CPU
instructions working on numbers stored in those boxes.

A **variable** is a name *you* invent so you don't have to remember a raw address like
`0x44589ff78c`. When you write:

```cpp
int health = 100;
```

here's what really happens:

1. **Compile time:** g++ reserves enough bytes for an `int` (4 bytes) somewhere in the
   memory your program will get when it runs, and writes down, *only for its own use*:
   "whenever this code says `health`, that means the 4 bytes starting at this address."
2. Every later line that says `health` gets translated into instructions that read or
   write that address directly. The name `health` never gets compiled into the `.exe` —
   it's a bookkeeping tool for the compiler, erased once compiling is done.
3. **Run time:** the CPU has no idea a variable called `health` ever existed. It just
   sees "copy the number 100 into this address" and "read the number at this address".

This is exactly the compile-time/run-time split from the fix above: the *name* `health`
is a compile-time-only convenience; at run time there are only addresses and bytes.

Try this (the addresses will differ on your machine — that's expected, and *why* is a
Week 3 topic):

```cpp
#include <iostream>

int main()
{
    int health = 100;
    double speed = 3.14;
    char grade = 'A';
    bool isAlive = true;

    std::cout << "health is " << sizeof(health) << " bytes, at address " << &health << "\n";
    std::cout << "speed is "  << sizeof(speed)  << " bytes, at address " << &speed  << "\n";
    std::cout << "isAlive is " << sizeof(isAlive) << " bytes, at address " << &isAlive << "\n";

    return 0;
}
```

`&health` means "the address of `health`" — don't worry about the full meaning of `&`
yet (that's Day 15); for now just read it as "show me where this box lives".

The memory your program borrows to hold these local variables while a function is
running is called the **call stack** — we'll take it apart properly on Day 9. For now,
just know it exists and that it's temporary: it disappears the moment the function ends.

## 2. Declaration vs. initialization vs. assignment

These are three different things that look similar:

```cpp
int score;        // declaration only — reserves the box, puts NO known value in it
int lives = 3;     // declaration + initialization — reserves the box AND fills it
score = 10;        // assignment — changes the value of an EXISTING box, no type needed
```

An uninitialized variable isn't zero or empty — it's whatever leftover bits happen to be
sitting in that memory from whatever used it before. Reading it is a bug:

```cpp
#include <iostream>

int main()
{
    int x;
    std::cout << x << "\n";
    return 0;
}
```

Real g++ output:
```
t1.cpp: In function 'int main()':
t1.cpp:6:23: warning: 'x' is used uninitialized [-Wuninitialized]
    6 |     std::cout << x << "\n";
      |                       ^~~~
t1.cpp:5:9: note: 'x' was declared here
```
This is only a **warning**, not an error — the program still compiles and runs, and
prints some garbage number (on one test run: `32758`). `-Wall -Wextra` catches the
*obvious* cases, not all of them. **Always initialize your variables.** This is a real
difference from C#, where local variables of most types are required to be initialized
before use and the *compiler itself* refuses to compile otherwise — C++ mostly leaves it
to you (and your warnings).

You also can't declare the same name twice in the same scope:

```cpp
int score = 0;
int score = 10;   // error: redeclaration of 'int score'
```

And you can't use a name before the compiler has seen its declaration:

```cpp
std::cout << age << "\n";   // error: 'age' was not declared in this scope
int age = 20;
```

C++ reads your file top to bottom; a name only exists from its declaration onward.

## 3. The basic types you'll use starting today

A variable's **type** tells the compiler two things: how many bytes to reserve, and how
to interpret the bits sitting in those bytes. We'll open up *how* numbers become bits on
Day 3 — today, just meet the types:

| Type | Holds | Example | Typical size |
|---|---|---|---|
| `int` | whole numbers | `int health = 100;` | 4 bytes |
| `double` | decimal numbers | `double speed = 3.14;` | 8 bytes |
| `char` | one character | `char grade = 'A';` | 1 byte |
| `bool` | `true` / `false` | `bool isAlive = true;` | 1 byte |
| `std::string` | text | `std::string name = "Hero";` | (more than 1 byte — it manages its own memory; details later) |

Note `char` uses **single quotes** (`'A'`) and `std::string`/literals use **double
quotes** (`"Hero"`) — mixing these up is a compiler error.

`std::string` needs `#include <string>` — add it whenever you use one, even though on
some setups `<iostream>` happens to drag it in already. Relying on that is not portable:
your code might fail to compile on a different computer or compiler, which is exactly
the kind of thing that bites you when you move between your laptop, the office PC, and
onlinegdb.com.

You can use a variable on the right-hand side of another assignment, same as in C#:

```cpp
int score = 0;
score = score + 10;   // read old score, add 10, store back: score is now 10
score += 5;            // shorthand for score = score + 5; now 15
```

## 4. Naming rules

- Must start with a letter or `_`, then letters/digits/`_` only. **Never a digit first.**
- Case-sensitive: `health` and `Health` are different names.
- No spaces, no reserved keywords (`int`, `return`, `main`, …) as names.
- Convention in this course (matches your C# habits): `camelCase` for variables —
  `playerHealth`, `isAlive`, `moveSpeed`.
- Prefer a clear name over a short one. `int hp` is fine once you know the codebase;
  `int health` is clearer while learning. Avoid single letters except for loop counters
  (Day 6).

## 5. Bonus: a stricter way to initialize

`= value` silently allows some data loss. `double` → `int` with `=` just truncates with
no warning even under `-Wall -Wextra`:

```cpp
int x = 3.9;    // compiles clean, x becomes 3 — the .9 is silently thrown away
```

Brace initialization `{ value }` is stricter and catches this **at compile time**:

```cpp
int x{3.9};     // error: narrowing conversion of '3.9...' from 'double' to 'int'
int score{};    // declares AND zero-initializes — score is 0, never garbage
```

You don't have to switch today — `=` is what you'll see in most beginner material and
it's what we'll keep using by default for now — but keep `{}` in your back pocket for
whenever you want the compiler to double-check you.

---

## Key ideas to remember
- A variable's **name** exists only at compile time; at run time there are only
  addresses and bytes. Compiling happens once; running happens later and repeatedly.
- **Declaration** reserves a box (`int score;`); **initialization** fills it at creation
  (`int score = 0;`); **assignment** changes an existing box (`score = 5;`).
- Reading an uninitialized variable gives garbage, not zero — `-Wall -Wextra` sometimes
  warns you, but don't rely on it. Always initialize.
- You can't redeclare a name in the same scope, or use a name before its declaration.
- Today's types: `int`, `double`, `char` (single quotes), `bool`, `std::string` (double
  quotes, needs `#include <string>`).
- `{}` initialization is stricter than `=` — it rejects data-losing conversions at
  compile time.

**Connecting to games:** every `int health`, `float speed`, `bool isGrounded` you've
written in Unity C# scripts is the same idea — a named box of memory holding part of
your game's state. The syntax is nearly identical; what differs (coming in Week 3) is
*who manages that memory* — C#'s garbage collector versus you, by hand, in C++.

Now go to `EXERCISES.md`.
