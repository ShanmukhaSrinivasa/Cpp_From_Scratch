# Day 1 — Exercises

Work inside the `Day_001` folder, using the VS Code terminal.
**Type everything yourself.** No copy-paste — your fingers learn too.

Compile command for every exercise:
```bash
g++ -std=c++20 -Wall -Wextra FILENAME.cpp -o FILENAME.exe
```

---

## Ex 1 — Hello, World
Create `hello.cpp` with the program from the lesson. Compile it and run it.

## Ex 2 — Talk about yourself
Create `about_me.cpp` that prints:
```
Hi, I'm <your name>.
I make games in Unity.
I'm learning C++ to build my own engine.
```
Do it **two ways**:
1. Three separate `std::cout` lines.
2. One single `std::cout` statement, using `\n` for the line breaks.

## Ex 3 — Break it on purpose (the most important exercise today)
Make a copy of `hello.cpp` called `broken.cpp`. Make **one** mistake at a time, compile,
read the error, write down what the compiler said, then fix it before the next one:

| # | Mistake | What did the compiler say? |
|---|---|---|
| a | Delete the `;` after the `cout` line | |
| b | Misspell `cout` as `cot` | |
| c | Delete the `#include <iostream>` line | |
| d | Delete the closing `"` of the string | |
| e | Delete the final `}` | |
| f | Rename `main` to `Main` | |

Mistake **f** gives a very different-looking error, mentioning `ld.exe` and `undefined reference`.
That error comes from a different tool than the others. Guess why. (We'll cover it on Day 25.)

## Ex 4 — Escape sequences
Inside a string, `\` starts a special character. Try each one and describe what it does:
```cpp
std::cout << "Tab:\tafter tab\n";
std::cout << "Quote: \"Hello\"\n";
std::cout << "Backslash: \\ \n";
std::cout << "Bell: \a\n";
```
Then print this exact text, including the quotes and the backslash:
```
She said "Level complete!" and saved to C:\Games\save.dat
```

## Ex 5 — ASCII art
Print a little game character or logo using several `std::cout` lines. For example:
```
   O
  /|\
  / \
 PLAYER 1
```
(Hint: the `\` characters will cause trouble. Use what you learned in Ex 4.)

## Ex 6 — Curiosity questions (answer in NOTES.md)
1. How big is `hello.exe` in bytes? (Right-click → Properties, or run `ls -l hello.exe`.)
   Your source file is about 100 bytes. Why might the `.exe` be so much bigger?
2. Change `return 0;` to `return 7;`, recompile and run. Then type `echo $LASTEXITCODE`
   in PowerShell. What do you see? Who receives the number that `main` returns?
3. Delete the `.exe`, then try to run it. Now delete the `.cpp` but keep the `.exe` and run it.
   What does this tell you about which file the computer actually needs?

---

When you're done, fill in `NOTES.md` and tell me **"review Day 1"**.
Then, tomorrow: **"Day 2"**.
