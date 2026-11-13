# Day 4 — My Notes

## Before I start: what do I *think* `std::cin` does differently from `std::cout`?
- cin is used to get input from the user and cout is used for ouptut to the terminal.

## Explain it like I'm teaching a friend
- How does `std::cin >> someInt` know when to stop reading?
- with the help of whitespace the cin knows when to stop.

- Why does `std::cin >> someString` only grab one word instead of a whole line?
- if the string has a whitespace, the cin only grabs whatever is available until the whitespace once it hits the whitespace the cin stops taking input. 

- Why does integer division truncate instead of round?
- int doesnt hold decimal values so it truncates the output instead of round.

- Why does `std::cout << (x == y)` need parentheses around the comparison?
- because "<<" this symbols used to represent bitwise shifter, so we cannot compare it with "==" so that is why to fix it we use parenthesis.

- Why does `5 / 0` behave differently from `5.0 / 0.0`?
- for int numns the comipler throws an undefined error but for double values, the C++ has defined a value for inifinity so it doesn't produce error.

## Ex 2 — predict, then check (one-word string trap)
- My prediction:
- if we type hero jones with std::cin it will only take Hero because of the whitespace the cin stops and doesn't read the next input.
- What actually printed:
- it printed Hero.

## Ex 3 — predict, then check (bad number input)
- My prediction:
- if we type "twenty" instead of 20, the output would be 0 with nor warnings or errors
- What actually happened — any error or warning shown?
- no warnings or errors and it shows 0 as output.

## Ex 4 — division and modulo table
- My six predictions:
- 7/2 = 3
- -7/2 = -3
- 7%2 = 1
- -7%2 = -1
- 7%-2 = 1
- 7.0/2 = 3.5
- What actually printed:
- the same as my predictions.

## Ex 5 — precedence
- My four predictions:
- 14, 5, 3, without parenthesis error, and with parenthesis output is 1.
- What actually happened, and the exact error message before the fix:
- same as my predicions.

## Ex 6 — predict, then check (division by zero)
- My two predictions:
- int divided by zero throws an error and crashes the program, for double nums divided by zero it should show an output of infinity.
- What actually happened:
- same as my predicitions but in my terminal i am not getting any output.

## Ex 7 — the average-score bug
- Buggy average vs. fixed average, for my test input:
- with int we dont get the decimal avergae it truncates the output and with double we get the decimal values too in average.
- Why the buggy version is wrong, in my own words:
- the buggy version is wrong because we don't get the decimal values and int output truncates it, but wit double we get the real average with decimal values. 

## What surprised me / what's still confusing

