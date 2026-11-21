# Day 7 — Build Day: Guess the Number

Work inside `Day_007`. **Type everything yourself.**

Compile command:
```bash
g++ -std=c++20 -Wall -Wextra guess.cpp -o guess.exe
```

Today is different: instead of separate exercises, you build **one game** in one file,
`Day_007/Game/guess.cpp`, in six milestones. Each milestone adds one feature to the same
file.

**The rule for every milestone:** it must compile with **no warnings** and **work** before
you start the next one. When a milestone works, save your progress: either copy the file
(`guess_m1.cpp`, `guess_m2.cpp`…) or make a git commit. If the next milestone goes wrong,
you can always go back to something that worked.

---

## Milestone 1 — One guess
Start with a fixed secret: `int secret = 42;`.
Ask for one guess and print `Too low!`, `Too high!` or `You got it!`.

Test: `10`, `90`, `42`.

## Milestone 2 — Keep guessing
Put the guess in a loop that repeats until the player is right, counting the guesses.
When they win, print `You got it in N guesses!`.

Test: `50`, `25`, `40`, `42` should say **4** guesses. Winning on the first guess should
say **1**, not 0.

## Milestone 3 — Survive bad input
- Letters (`abc`): print a message, **don't** count it as a guess, keep going.
- Numbers outside 1–100 (`0`, `101`): same, no guess used.

Test: `abc`, `0`, `101`, `42` should say **1** guess.

## Milestone 4 — Difficulty and a limited number of tries
Before the game, show the difficulty menu from the lesson and read a choice. Use a
`switch` to set `maxNumber` and `maxTries`:

| Choice | Range | Tries |
|---|---|---|
| 1 Easy | 1–50 | 10 |
| 2 Normal | 1–100 | 7 |
| 3 Hard | 1–500 | 9 |

- Keep asking until the choice is 1, 2 or 3 (letters included).
- Show the try number: `Guess 3/7: `.
- Use `maxNumber` in your range check from Milestone 3 (no more hard-coded `100`).
- If the player runs out of tries: `Out of tries! The number was 42.`

Test: choose Normal and guess wrong 7 times. Then win on exactly the **7th** guess: it must
say you won, not that you ran out.

## Milestone 5 — A real secret
Replace `int secret = 42;` with a random number from `1` to `maxNumber`, using the four
lines from lesson §4.

- Create the `random_device` and the generator **once**, near the top of `main`.
- Create the distribution and the secret **after** you know `maxNumber`.

Test it a few times. Then **temporarily** put the fixed seed `42` in the generator, run the
game twice, and check the secret is the same both times. Put `seed()` back afterwards.

## Milestone 6 — Play again, with stats
Wrap everything (from the difficulty menu down) in a `do-while` that asks
`Play again? (y/n): ` and repeats on `y` or `Y`. Track, across all games:
- games played,
- wins,
- best score (fewest guesses in a **won** game). Day 6 Ex 4's "first value" trick is useful
  here.

Print the stats when the player quits. If they never won, don't print a best score.

**Final test:** go through the testing checklist in lesson §6.

---

## Experiments (in a separate folder, `Day_007/Experiments/`)

### E1 — Predict, then check: the halving strategy
Before playing, predict in NOTES: with the "always guess the middle" strategy, what's the
**most** guesses you could ever need for 1–50? 1–100? 1–500?
Then play your game on each difficulty using that strategy. Did you ever need more?
Explain the numbers using powers of 2 (Day 3).

### E2 — Break it on purpose: the moving target
Make a copy of your game and move the four random-number lines **inside the guess loop**,
so a new secret is rolled before every guess. Play it. Describe in NOTES what happens to the
"too high / too low" hints, and why. Which loop do the secret and the generator belong in?

### E3 — Break it on purpose: forget the cleanup
In another copy, delete the `clear()` and `ignore()` lines from the **guess** loop (keep the
`continue`). Type `abc` as a guess. What happens? (Ctrl + C to stop it.) Connect it to Day 6
Ex 6.

---

## Stretch goals (optional, pick any)

**S1 — Hot or cold.** When a guess is wrong but within 5 of the secret, add `(very close!)`
after "Too high!" / "Too low!". You'll need the **distance** between guess and secret, which
must be positive either way (you know enough to make a negative number positive with an
`if`).

**S2 — The computer guesses.** In a new file `Day_007/Stretch/reverse.cpp`, swap roles: the
player thinks of a number from 1 to 100, and the computer guesses using halving. The player
answers `h` (too high), `l` (too low) or `c` (correct). Keep two variables, `low` and `high`,
and always guess the middle. Print how many guesses it took. If the player's answers are
impossible (`low` becomes bigger than `high`), print `Hey, you cheated!`.

**S3 — Typing `yes`.** Answer `yes` to "Play again?". What happens to the next difficulty
prompt, and why? (Hint: a `char` reads one character. Where do `e` and `s` go?)

---

When you're done, fill in `NOTES.md` and tell me **"review Day 7"**.
