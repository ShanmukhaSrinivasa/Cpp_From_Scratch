# Day 5 — My Notes

## Before I start: how do I *think* a computer "decides" something?


## Explain it like I'm teaching a friend
- What does the CPU actually do when it runs an `if`?

- In an `if` / `else if` / `else` chain, what happens when two conditions are both true?

- What is short-circuiting, and how can it prevent a crash?

- Why does `if (health = 0)` compile, and what two bad things does it do?

- What is switch fall-through, and when is it actually useful?

- Why can't you `switch` on a `std::string`?


## Ex 1 — does the order of the `if`s matter?
- Inputs that broke when "Invalid" was moved to the end:
- Why:

## Ex 2 — the four traps
- a: warning: … / printed: … / health afterwards:
- b:
- c:
- d:

## Ex 3 — predictions vs. actual
| # | My prediction | Actual |
|---|---|---|
| 1 | | |
| 2 | | |
| 3 | | |
| 4 | | |
| 5 | | |
| 6 | | |

## Ex 4 — short-circuit
- Safe version, gamesPlayed = 0:
- Swapped version, gamesPlayed = 0 (what happened, exit code):
- Why the order matters:

## Ex 5 — switch menu
- Missing `break`: what printed + warning:
- `std::string` switch error:

## Ex 6 — bad input
- Why `50abc` isn't treated as bad input:

## Ex 7 — combat turn test results
- attack vs armor 5:
- heavy vs armor 0:
- heavy vs armor 35:
- potion:
- `x`:
- armor `abc`:

## Bonus — which jump instruction for `health > 100`?


## What surprised me / what's still confusing

