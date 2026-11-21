# Day 7 — Build Day: Guess the Number

**Goal for today:**
1. Build one **complete game** using everything from Week 1, start to finish.
2. Learn how programmers build something bigger than an exercise: **plan first, then grow
   the program in small steps that each compile and work.**
3. Meet one new tool, random numbers, used as a "black box" today and explained properly on
   Day 13.
4. Discover the best guessing strategy, and why it's secretly about **binary** (Day 3).

Today's lesson is short on new ideas and long on *building*. Most of your time goes into
`EXERCISES.md`, where the game is split into milestones.

---

## 0. Quick fixes from Day 6

Two lines in your Day 6 notes are still not quite right, and both matter today:

**a) The unsigned loop.** Your note says "unsigned int never becomes zero". It **does**
become zero: your Ex 3d printed `3 2 1 0`. What an `unsigned` can never be is
**negative**. So `u >= 0` is always true, and `0 - 1` wraps around to `4294967295`.

**b) `clear()` vs `ignore()`.** Your first answer was right ("clear resets the failed
state"), but your Ex 6 note says "the clear is needed to clear the input". It isn't:
- `clear()` resets the **failed state**. The bad text is still waiting in the input.
- `ignore(...)` **throws away** that bad text.

Today's game reads input in two different places, so you'll use this pattern twice.

(Also: in Ex 4, the zero check avoids **dividing** by zero, not multiplying.)

---

## 1. What you're building

Here's a real run of the finished game (the secret was `42`):

```
=== GUESS THE NUMBER ===

Choose difficulty:
1. Easy   (1-50,  10 tries)
2. Normal (1-100,  7 tries)
3. Hard   (1-500,  9 tries)
Choose: 2
I'm thinking of a number from 1 to 100. You have 7 tries.
Guess 1/7: abc
Numbers only! (That didn't cost a try.)
Guess 1/7: 101
Between 1 and 100, please. (That didn't cost a try.)
Guess 1/7: 50
Too high!
Guess 2/7: 25
Too low!
Guess 3/7: 40
Too low! (very close!)
Guess 4/7: 44
Too high! (very close!)
Guess 5/7: 42
You got it in 5 guesses!
New best!
Play again? (y/n): n

Games: 1, wins: 1, best: 5 guesses
Thanks for playing!
```

Every piece of that uses something you already know:

| Feature | Skill | Day |
|---|---|---|
| Text on screen | `std::cout`, `"\n"` | 1 |
| Secret, tries, wins, best score | `int` variables, initialized | 2 |
| `y`/`n` answer | `char` | 3 |
| Reading guesses, counting tries | `std::cin`, `++`, comparisons | 4 |
| Too high / too low / correct | `if` / `else if` / `else` | 5 |
| Difficulty settings | `switch` | 5 |
| Letters typed instead of numbers | `cin.fail()`, `clear()`, `ignore()` | 5–6 |
| Keep guessing; play again | `while`, `do-while`, `break`, `continue` | 6 |
| A secret you can't predict | random numbers | **new (Day 13)** |

## 2. How to build something bigger than an exercise

Beginners often type the whole program at once, compile, get 30 errors, and give up.
Professionals do the opposite:

1. **Plan before you type.** Write down what the program must do, and which variables it
   needs. (§3 does this for you today; next Build Day you'll do it yourself.)
2. **Build the smallest thing that works**, compile it, run it. Then add **one** feature.
   Compile, run, test. Repeat. Every step ends with a program that **works**.
3. **Fake the hard parts at first.** You can't test "too high" if the secret is random and
   unknown. So start with `int secret = 42;` and only add randomness at the end.
4. **Test the edges**, not just the happy path: letters, `0`, `101`, the last allowed try,
   winning on the very first guess.

If something breaks, you only changed a few lines since it last worked, so you know where
to look. That's the whole trick. Game studios work exactly like this: get *something*
playable early, then grow it.

## 3. The plan

**The variables** (and when each one is created):

| Variable | Type | Lives for… | Meaning |
|---|---|---|---|
| `gamesPlayed`, `wins`, `bestGuesses` | `int` | the whole program | session stats |
| `playAgain` | `char` | the whole program | `y` or `n` |
| `difficulty`, `maxNumber`, `maxTries` | `int` | one game | settings |
| `secret` | `int` | one game | the number to guess |
| `tries` | `int` | one game | guesses used so far |
| `won` | `bool` | one game | did the player win? |
| `guess` | `int` | one guess | what was typed |

**The shape of the program:** three loops, one inside the other.

```
create the random number generator (once!)

do                                          <- "play again" loop
    ask for difficulty until it's 1, 2 or 3  <- input loop
    set maxNumber / maxTries with a switch
    pick the secret

    while tries < maxTries                   <- guess loop
        read a guess
        letters?        -> clear, ignore, continue   (no try used)
        out of range?   -> continue                  (no try used)
        tries++
        correct?        -> won = true, break
        otherwise       -> "too high" / "too low"

    update stats, print win or lose message
    ask "play again?"
while the answer is y or Y

print the final stats
```

Notice where things go. The difficulty and secret are picked **inside** the play-again
loop (a new game each time), but **outside** the guess loop (the secret must not change
between guesses!). Getting this "which loop does it belong to" question right is most of
the design work.

## 4. The one new thing: random numbers

A CPU follows instructions exactly, so it can't "pick a number" by itself. C++ gives you
tools for it in `<random>`. Today, use these lines as a **black box**: copy the pattern,
and on Day 13 we'll open the box and see how it works.

```cpp
#include <iostream>
#include <random>

int main()
{
    std::random_device seed;                            // 1. get an unpredictable starting value
    std::mt19937 generator(seed());                     // 2. create a random-number generator from it

    std::uniform_int_distribution<int> range(1, 100);   // 3. "I want whole numbers from 1 to 100"
    int secret = range(generator);                      // 4. roll!

    std::cout << secret << "\n";
    return 0;
}
```
What each line is for, in one sentence:
1. `random_device` asks the operating system for a genuinely unpredictable number, the **seed**.
2. `mt19937` is a **generator**: from one seed it produces a long stream of numbers that
   look random. Create it **once**, at the start of the program.
3. `uniform_int_distribution<int> range(1, 100)` turns those numbers into your range, all
   equally likely.
4. `range(generator)` gives you the next random number. Call it each time you need one.

I ran it three times on your setup: `23 41 55…`, `82 15 55…`, `90 27 61…`. Different every
run, as it should be.

### Seeds: why the same seed gives the same numbers
Replace `seed()` with a fixed number:
```cpp
std::mt19937 generator(42);
```
Now the program prints **the same numbers every single run** (`38 80 96 19 74` with seed 42,
on your compiler). The generator isn't truly random: it's a formula that produces the same
sequence from the same starting point. That sounds like a flaw, but games use it on
purpose. A **Minecraft world seed** is exactly this: same seed, same world. Replays,
"daily challenge" levels and multiplayer games that must stay in sync all rely on it. And
for **testing**, a fixed seed means a bug happens the same way every time you run.

## 5. The best strategy, and why it's binary

If the number is from 1 to 100, what's the smartest first guess? **50**. Whatever the
answer, you've thrown away **half** the possibilities. Then guess the middle of what's
left, and so on. This is called **binary search** (you'll study it properly in Phase 4).

How many guesses can it need, at worst? Each wrong guess halves what's left:

```
guess number:              1     2     3     4     5     6     7
numbers still possible:   100    50    25    12     6     3     1   <- the 7th guess must be it
```
That's Day 3 in disguise: 7 halvings works because **2⁷ = 128**, and 128 ≥ 100. With 7 bits
you can tell apart 128 different numbers; with 7 yes/no answers you can find one of 128.
I checked every possible secret with a small program, and the worst cases are:

| Range | Worst case with halving | Why |
|---|---|---|
| 1–50 | 6 guesses | 2⁶ = 64 ≥ 50 |
| 1–100 | 7 guesses | 2⁷ = 128 ≥ 100 |
| 1–500 | 9 guesses | 2⁹ = 512 ≥ 500 |

So the difficulty settings aren't random either: **Normal and Hard give you exactly enough
tries, if you play perfectly.** Easy gives you some spare.

## 6. Testing checklist

When you think the game is done, run through this list. Each line catches a real bug:

- [ ] Type letters for the difficulty, then `5`, then a valid choice.
- [ ] Type `abc` as a guess: no try used, the game keeps working.
- [ ] Type `0` and `101` (on Normal): no try used.
- [ ] Win on the **last** allowed try: it should count as a win, not a loss.
- [ ] Lose: the real number is revealed.
- [ ] Play 3 games: are games, wins and best score right? Does "best" only go **down**?
- [ ] Answer `Y` (capital) to "play again".
- [ ] Use the halving strategy on Normal: do you always win within 7?

---

## Key ideas to remember
- Build in **small working steps**: plan, write a little, compile, run, test, repeat.
- **Fake the hard parts first** (`int secret = 42;`) so you can test the logic.
- Decide which **loop** each line belongs to. The generator is created **once**; the secret
  once per **game**; the guess once per **turn**.
- Random numbers: `random_device` → seed → `mt19937` generator (create once) →
  `uniform_int_distribution` for the range → `range(generator)` each time you need a number.
- The same seed always gives the same sequence. Games use this for world seeds, replays and
  testing.
- Halving the range each guess (binary search) needs at most 7 guesses for 1–100, because
  2⁷ = 128 (Day 3).
- Test the edges: bad input, boundaries, the last try, repeated games.

**Connecting to games:** you just built a complete game loop: input → update → feedback,
repeated until the game ends, wrapped in a "play again" loop. A Unity game is the same idea
with graphics on top. You also met seeds, which drive procedural generation in games like
Minecraft, Spelunky and No Man's Sky. Next week (Days 8–14) you'll learn **functions**, and
you'll see how much cleaner this program gets when the repeated "read a number safely" code
becomes one reusable function.

Now go to `EXERCISES.md` and build it.
