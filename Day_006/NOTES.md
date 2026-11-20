# Day 6 — My Notes

## Before I start: how do I *think* a computer repeats something?


## Explain it like I'm teaching a friend
- What's the difference between `while`, `do-while` and `for`? When would I pick each?
- All the 3 can be used as loops in C++. while loop will be used when we know the exact condition and based on that the loop will be done. do-while loop is that we should be doing the loop while the condition is true. this loop will happen at least once even if the condition is not met in that starting. For loop is used when we know the count for example from 10 to 1.

- What does the CPU actually do to make a loop repeat?
- the cpu jumps backwards to make a loop repeat instead of jumping forward.

- What's the difference between `i++` and `++i`, and when does it matter?
- i++ is post-increment and ++i is pre-increment. for ex:
i = 10;
a = i++; // here the a takes the value 10 and then i becomes 11.
b = ++i // here the i value is increased first and it becomes 11 and then b takes that value.

- What do `break` and `continue` each do? What does `break` do inside a nested loop?
- break stops and exits the loop and continue skips the current iteration in a loop and jumps to next iteration. In a nested loop the break stops the inner loop only.

- Why is `for (unsigned int u = 3; u >= 0; u--)` an infinite loop?
- because unsigned int never becomes zero, when u becomes negative the value jumps to some higher number and then condition doesn't meet of becoming zero so the loop goes on infinitely.

- To retry bad input, why do I need **both** `std::cin.clear()` and `std::cin.ignore(...)`?
- clear resets the failed state and then ignore throws away that line

## Ex 2 — predictions vs. actual
| # | My prediction | Actual |
|---|---|---|
| a | 5 | 5
| b | 6 | 6
| c | 4 | 4
| d | 0 | 0
| e | 1 | 1
| f | 5 | 5
| g | a = 5 , b = 3, c = 4 | a = 5, b = 3, c = 5

- The ones I got wrong, and why:
- here after b = a++; the value of a goes to 4 and then in th next step it becomes 5 so that is where i was confused and wrote c = 4.

## Ex 3 — loop traps
- a: warning : this 'for' clause does not guard... [-Wmisleading-indentation], the value of count is 1.
- b: no warnings, the value of count is 1.
- c: warning: suggest parentheses around assignment used as truth value [-Wparentheses], the loops goes on forever and prints 5.
- d: (first number after 0, and why), warning: comparison of unsigned expression in '>= 0' is always true [-Wtype-limits], the loop goes on forever and after zero the value would be a large number and then loop continues from that number.
- e: error: expected ';' before 'return', the program doesn't run
- f: error: 'i' was not declared in this scope, the program doesn't run.

## Ex 4 — score tracker
- Output for `40 90 75`: total 205, average 68.3333, highest 90
- What happens with `0` scores: i have added a check to see if the no of scores is zero to avoid multiplying by zero.

## Ex 5 — tile map
- What happens with the player on the border, or outside the map: the player's "@" is not shown in the tilemap.

## Ex 6 — retry input
- Without `ignore(...)`: when i enter abc the loop runs on forever.
- Without `clear()`: same happens when i enter abc the loop runs on forever.
- Why each line is needed: the clear is needed to clear the input and ignore is needed to ignore the bad input and take the new input.

## Ex 7 — game menu loop
- Test results (max HP, dying, `x`, `9`, Quit): everything is working perfectly.

## Bonus — the backward jump
1. The jump and its label (above or below?):
2. Jump instruction for `i < n`:
3. `for` vs `while` assembly:

## What surprised me / what's still confusing

