# Day 5 — My Notes

## Before I start: how do I *think* a computer "decides" something?


## Explain it like I'm teaching a friend
- What does the CPU actually do when it runs an `if`?
- it compares the condition and then jumps to that code.

- In an `if` / `else if` / `else` chain, what happens when two conditions are both true?
- it is not possible for two conditions to be true because, if the first condition is true then the next else if or else statements are ignored. so it cannot happen. 

- What is short-circuiting, and how can it prevent a crash?
- short circuiting means in C++ the conditions are checked from left to right, so when the left condition is checked as soon as it completes the code doesn't check for the right side if that condition is met, so in this way some unwanted crashes could be prevented.

- Why does `if (health = 0)` compile, and what two bad things does it do?
- in that above statement we are making the health variable set to zero, so the if statement compiles and the condition becomes true and the codes go through the if statement and gives an output.

- What is switch fall-through, and when is it actually useful?
- switch fallthrough means the switch jumps to the matching condition and if there's no break condition then the switch keeps on jumping to the next condition and it doesn't stop until it hit break statement. it is actually useful when at a time two or more conditions are required to be met such a "case "A": " or "case 'a':", so in this the switch fall through is useful.

- Why can't you `switch` on a `std::string`?
- swicth only works with Whoel number types, so it doesn't work on a string.

## Ex 1 — does the order of the `if`s matter?
- Inputs that broke when "Invalid" was moved to the end:
- Why: yes, the order of the if's matter because if any of the first conditions are met the next else if and else statements are ignored automatically, so if the invalid health value checking was done at the end then it is automatically ignored if any of the above conditions were met so it is important.

## Ex 2 — the four traps
- a: warning: suggest parentheses around assignment used as truth value [-Wparentheses] / 
printed: nothing / health afterwards: 0
- b: warning: suggest braces around empty body in an 'if' statement [-Wempty-body]
printed: 50 / health afterwards = 50
- c: warning: this 'if' clause does not guard... [-Wmisleading-indentation]
printed: 50 50 
- d: warning: comparisons like 'X<=Y<=Z' do not have their mathematical meaning [-Wparentheses]
printed: 50

## Ex 3 — predictions vs. actual
| # | My prediction | Actual |
|---|---|---|
| 1 | false | false
| 2 | true  | true
| 3 | false | false
| 4 | false | false
| 5 | false | false
| 6 | false | false

## Ex 4 — short-circuit
- Safe version, gamesPlayed = 0:
- Swapped version, gamesPlayed = 0 (what happened, exit code):
- Why the order matters:
- i am very much confused with the question. so i am unable to answer this.

## Ex 5 — switch menu
- Missing `break`: what printed + warning:
- warning : this statement may fall through [-Wimplicit-fallthrough=]
- when i chose 1 it printed 1 and 2 options and in second i hade break so it stopped there.
- `std::string` switch error: expression must have integral or enum type

## Ex 6 — bad input
- Why `50abc` isn't treated as bad input: the cin reads the numbers and then at the letter a it stops taking input and it leaves out the letters and only takes the numbers.

## Ex 7 — combat turn test results
- attack vs armor 5: 
- heavy vs armor 0: 
- heavy vs armor 35:
- potion:
- `x`:
- armor `abc`:

## Bonus — which jump instruction for `health > 100`?


## What surprised me / what's still confusing

