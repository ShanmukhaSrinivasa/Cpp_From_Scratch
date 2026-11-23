# Day 7 — Answers & Revision Sheet (Build Day: Guess the Number)

Every program and output on this page was compiled and run with
`g++ -std=c++20 -Wall -Wextra` (0 warnings) on your MinGW setup.

---

## 60-second summary

- **Build in milestones.** Write a little, compile, run, test, and only then add the next
  feature. When something breaks, it's in the last few lines you changed.
- **Fake the hard parts first.** Start with `int secret = 42;` so every run is the same and
  you can test the logic. Add randomness last.
- **Which loop does it belong in?**
  - The **generator** is created **once**, before all the loops.
  - The **secret** is picked once per **game**: inside the play-again loop, *before* the
    guess loop.
  - The **guess** is read once per **turn**, inside the guess loop.
- **Random numbers:** `random_device` (seed) → `mt19937` (generator, created once) →
  `uniform_int_distribution` (the range) → `range(generator)` (roll).
- **A seed is a starting number, not a list of stored numbers.** The generator is a formula,
  so the same start always gives the same sequence (seed `42` → first secret `38` on Normal,
  every run).
- **Binary search:** guessing the middle halves what's left. 1–100 needs at most 7 guesses
  because 2⁷ = 128 ≥ 100.
- **Distance is bigger minus smaller,** so it's never negative. Negative numbers are always
  `<= 5`, which was the "(very close!)" bug.
- **Stats live outside the play-again loop** and must **never** be reset inside it.

---

## Model answers to the NOTES.md questions

**Before I start: how would I plan a program before typing it?**
Write down what it must do (the features), list the variables and how long each one must
live (the whole program, one game, or one guess), and sketch the shape of the loops in plain
English (pseudocode). Then decide the order of milestones: the smallest version that works
first.

**Why build in small milestones instead of all at once?**
Every milestone ends with a program that compiles and works. If the next step breaks it,
the bug is in the few lines you just added, not somewhere in 150 lines. You also always
have a working version to go back to.

**Why start with `int secret = 42;` instead of a random number?**
With a known secret you can **predict** the right output (10 → too low, 90 → too high) and
check it. With a random secret, you don't know what the answer should be, so you can't tell
whether the program is right. And a bug may appear in one run but not the next.

**Which loop does each belong in, and why?**

| Thing | Where | Why |
|---|---|---|
| generator | before every loop, once | One "machine" that keeps producing new numbers for the whole program. Re-creating it is wasteful, and with a fixed seed it would give the same number every time. |
| secret | inside the play-again loop, before the guess loop | A new secret for each game, but it must **stay the same** for every guess in that game (E2 shows what happens otherwise). |
| guess | inside the guess loop | A new one every turn. |

**What is a seed? Why does the same seed give the same numbers?**
A seed is just **one starting number**. `mt19937` is a **formula**: each time you ask for a
number, it scrambles its current state to make the next one. Nothing is stored anywhere. The
same start, put through the same formula, always gives the same results. It's useful for
**testing** (a bug happens the same way every run), **replays**, **daily-challenge** levels,
multiplayer sync, and **world seeds** (Minecraft: same seed, same world).

**Why can halving always find a number from 1 to 100 in 7 guesses?**
Each wrong guess removes about half of what's left:
`100 → 50 → 25 → 12 → 6 → 3 → 1`. After 6 wrong guesses there's only 1 number left, so the
7th guess must be right. In Day 3 terms: 7 yes/no answers can tell apart 2⁷ = **128**
numbers, and 128 ≥ 100. Binary search isn't a C++ feature: it's a general strategy (like
opening a dictionary in the middle).

---

## The game: Milestones 1–6

### What went wrong in your version, and the fix (revision list)

| Bug | Why it happened | Fix |
|---|---|---|
| Every wrong guess said "(very close!)" | `x >= 5 \|\| x <= 5` is true for **every** number. Later, `secret - guess` in the "too high" branch was always **negative**, and negatives are `<= 5`. | Gap = bigger − smaller: `guess - secret` when too high, `secret - guess` when too low. |
| Secret 1: "You got it in 1 guesses" after 5 guesses | `if (guess == 1) tries = 1;` overwrote the count | Deleted it. The counting already worked. |
| Difficulty `5` / `0` accepted | Only letters were rejected, so no `case` matched, and `maxNumber` / `maxTries` were garbage | Reject `< 1` and `> 3` in the input loop |
| Final stats never printed / no "New best!" in game 2 | The stats were reset to 0 **inside** the play-again loop | Never reset session stats. They must survive between games. |
| Lost every game: `best: 0` / nothing printed | The `if` wrapped the wrong amount | Always print games and wins; only `best` goes inside `if (wins > 0)` |

### A complete solution

This version uses a `won` flag (from the lesson's plan) and the Day 6 "first value" trick
(`wins == 1 || tries < bestGuesses`), so it needs no magic `11`. Variables are created where
they're needed, inside the loop that owns them (you'll learn exactly why this is good on
Day 9: scope).

```cpp
#include <iostream>
#include <limits>
#include <random>

int main()
{
    std::random_device seed;
    std::mt19937 generator(seed());          // created ONCE

    int gamesPlayed = 0;                     // session stats: whole program
    int wins = 0;
    int bestGuesses = 0;
    char playAgain = 'n';

    std::cout << "=== GUESS THE NUMBER ===\n";

    do                                       // play-again loop
    {
        int difficulty = 0;
        do                                   // input loop: until 1, 2 or 3
        {
            std::cout << "\nChoose difficulty:\n";
            std::cout << "1. Easy   (1-50,  10 tries)\n";
            std::cout << "2. Normal (1-100,  7 tries)\n";
            std::cout << "3. Hard   (1-500,  9 tries)\n";
            std::cout << "Choose: ";
            std::cin >> difficulty;

            if (std::cin.fail())
            {
                std::cin.clear();            // reset the failed state
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // throw away the bad text
                difficulty = 0;              // make sure the loop repeats
            }
            if (difficulty < 1 || difficulty > 3)
            {
                std::cout << "Please choose 1, 2 or 3.\n";
            }
        } while (difficulty < 1 || difficulty > 3);

        int maxNumber = 0;
        int maxTries = 0;
        switch (difficulty)
        {
            case 1: maxNumber = 50;  maxTries = 10; break;
            case 2: maxNumber = 100; maxTries = 7;  break;
            case 3: maxNumber = 500; maxTries = 9;  break;
        }

        std::uniform_int_distribution<int> range(1, maxNumber);
        int secret = range(generator);       // once per GAME

        std::cout << "I'm thinking of a number from 1 to " << maxNumber
                  << ". You have " << maxTries << " tries.\n";

        int tries = 0;
        bool won = false;

        while (tries < maxTries)             // guess loop
        {
            std::cout << "Guess " << (tries + 1) << "/" << maxTries << ": ";
            int guess = 0;
            std::cin >> guess;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Numbers only! (That didn't cost a try.)\n";
                continue;
            }
            if (guess < 1 || guess > maxNumber)
            {
                std::cout << "Between 1 and " << maxNumber << ", please. (That didn't cost a try.)\n";
                continue;
            }

            tries++;                         // only valid guesses count

            if (guess == secret)
            {
                won = true;
                break;
            }

            int distance = guess - secret;   // S1: make the distance positive
            if (distance < 0)
            {
                distance = -distance;
            }

            if (guess < secret)
            {
                std::cout << "Too low!";
            }
            else
            {
                std::cout << "Too high!";
            }
            if (distance <= 5)
            {
                std::cout << " (very close!)";
            }
            std::cout << "\n";
        }

        gamesPlayed++;
        if (won)
        {
            wins++;
            std::cout << "You got it in " << tries << " guesses!\n";
            if (wins == 1 || tries < bestGuesses)   // first win, or a better one
            {
                bestGuesses = tries;
                std::cout << "New best!\n";
            }
        }
        else
        {
            std::cout << "Out of tries! The number was " << secret << ".\n";
        }

        std::cout << "Play again? (y/n): ";
        std::cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    std::cout << "\nGames: " << gamesPlayed << ", wins: " << wins;
    if (wins > 0)
    {
        std::cout << ", best: " << bestGuesses << " guesses";
    }
    std::cout << "\nThanks for playing!\n";
    return 0;
}
```

Why `while (tries < maxTries)` with `tries` starting at 0 is neat: `tries` always means
"guesses **used**", so the win message prints it directly, and the prompt shows
`tries + 1`. Your version started at 1 and used `<=`. That also works, but then `tries`
means "the guess I'm **on**", and you have to be careful which meaning you print.

### Real test run (secret fixed at 42)

```
Choose: x          → Please choose 1, 2 or 3.
Choose: 5          → Please choose 1, 2 or 3.
Choose: 2          → I'm thinking of a number from 1 to 100. You have 7 tries.
Guess 1/7: abc     → Numbers only! (That didn't cost a try.)
Guess 1/7: 101     → Between 1 and 100, please. (That didn't cost a try.)
Guess 1/7: 50      → Too high!
Guess 2/7: 25      → Too low!
Guess 3/7: 40      → Too low! (very close!)
Guess 4/7: 44      → Too high! (very close!)
Guess 5/7: 42      → You got it in 5 guesses!   New best!
Play again: y, Easy, 10 wrong guesses → Out of tries! The number was 42.
Play again: Y, Normal, 42           → You got it in 1 guesses!   New best!
Play again: n
Games: 3, wins: 2, best: 1 guesses
Thanks for playing!
```
Winning on the **7th** guess (`1 2 3 4 5 6 42`) prints `You got it in 7 guesses!`, a win,
not a loss.

**The very-close boundaries** (secret 42): 36 → `Too low!`, 37 → `Too low! (very close!)`,
47 → `Too high! (very close!)`, 48 → `Too high!`. A gap of exactly 5 counts as close
because the check is `<=`.

**Milestone 5 seed check:** with `std::mt19937 generator(42);`, choosing Normal and losing
printed `Out of tries! The number was 38.` on **both** runs. Same seed, same secret.

---

## Experiments

### E1 — The halving strategy
I checked **every** possible secret with a program that always guesses the middle:

```
1-50: worst case 6 guesses
1-100: worst case 7 guesses
1-500: worst case 9 guesses
```

| Range | Halvings | Power of 2 | Your tries |
|---|---|---|---|
| 1–50 | 50→25→12→6→3→1 | 2⁶ = 64 ≥ 50 | 10 (4 spare) |
| 1–100 | 100→50→25→12→6→3→1 | 2⁷ = 128 ≥ 100 | 7 (exactly enough) |
| 1–500 | 500→250→125→62→31→15→7→3→1 | 2⁹ = 512 ≥ 500 | 9 (exactly enough) |

The rule: the worst case is the **smallest n where 2ⁿ ≥ range size**. Doubling the range
adds only **one** guess. That's why binary search is so powerful: a million numbers need only
20 guesses (2²⁰ ≈ 1,048,576).

### E2 — The moving target
With the secret rolled **inside** the guess loop (seed 42, guessing 50 every time):

```
Guess 1/7: Too low!
Guess 2/7: Too low!
Guess 3/7: Too high!      ← same guess, opposite hint
Guess 4/7: Too low!
...
Out of tries! The number was 60.
```
The hints **contradict each other**, because each hint is about a *different* secret.
Halving can't work: what you learned from one guess is useless for the next. The revealed
"secret" is only the last one rolled. **Fix:** the generator goes before all loops (once),
and the secret goes before the guess loop (once per game).

### E3 — Forgetting clear/ignore
Without `clear()` and `ignore()` in the guess loop, typing `abc` printed
`Guess 1/7: Numbers only! (That didn't cost a try.)` over and over, **38,464 lines in 2
seconds**, until it was stopped.

Why:
1. `abc` isn't a number, so `cin` goes into the **failed state**.
2. Without `clear()`, `cin` **stays** failed, and every later `cin >> guess` does nothing
   immediately, without waiting for you.
3. Even after a `clear()`, without `ignore()` the `abc` would **still be waiting** in the
   input and would fail again.
4. `continue` goes straight back to the top, so you get an infinite loop. It's exactly Day 6
   Ex 6/7.

You need **both**: `clear()` resets the state, and `ignore()` throws away the bad text.

---

## Stretch goals

### S1 — Hot or cold
It's built into the solution above. Two correct ways to get the distance:
- one variable made positive with an `if`: `distance = guess - secret; if (distance < 0) distance = -distance;`
- or, inside each branch, subtract **bigger minus smaller** (your final version).

### S2 — The computer guesses (`Day_007/Stretch/reverse.cpp`)

```cpp
#include <iostream>

int main()
{
    int low = 1;
    int high = 100;
    int tries = 0;
    char answer = ' ';

    std::cout << "Think of a number from 1 to 100. I'll guess it!\n";

    while (true)
    {
        if (low > high)                       // no number fits all the answers
        {
            std::cout << "Hey, you cheated! That's impossible.\n";
            break;
        }
        int guess = (low + high) / 2;         // always the middle (integer division, Day 4)
        tries++;
        std::cout << "Is it " << guess << "? (h = too high, l = too low, c = correct): ";
        std::cin >> answer;

        if (answer == 'c' || answer == 'C')
        {
            std::cout << "Got it in " << tries << " guesses!\n";
            break;
        }
        else if (answer == 'h' || answer == 'H')
        {
            high = guess - 1;                 // the number is below guess
        }
        else if (answer == 'l' || answer == 'L')
        {
            low = guess + 1;                  // the number is above guess
        }
        else
        {
            std::cout << "Please type h, l or c.\n";
            tries--;                          // a typo shouldn't count
        }
    }
    return 0;
}
```
Real runs:
- Thinking of **68**, answering `l h l c`: it guessed 50, 75, 62, 68 → `Got it in 4 guesses!`
- Always answering `l`: 50, 75, 88, 94, 97, 99, 100, then `low` = 101 > `high` = 100 →
  `Hey, you cheated! That's impossible.`

Why `guess - 1` and `guess + 1`, not just `guess`: that number is already ruled out. With
plain `guess`, the range can stop shrinking (for example, `low = 99, high = 100` → middle 99
forever).

### S3 — Typing `yes`
`char playAgain` reads **one** character: `y`. So the game restarts, but `es` is still waiting
in the input. The next `cin >> difficulty` tries to read `es` as a number, fails, and you
see **one** extra `Please choose 1, 2 or 3.` before the menu works normally (the `ignore()`
threw `es` away). In your version it printed `Invalid Choice. Try again!` once.
It's the same lesson as E3: what you type stays in the input until something reads it or
throws it away.

---

## Key things to revise
1. `||` of two opposite comparisons (`x >= 5 || x <= 5`) is **always true**.
2. A distance is **bigger − smaller**, or made positive with an `if`.
3. Session stats are declared **before** the play-again loop and never reset inside it.
4. The generator is created once, the secret once per game, the guess once per turn.
5. `clear()` resets the state; `ignore()` removes the text. You need both.
