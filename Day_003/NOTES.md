# Day 3 — My Notes

## Before I start: what do I *think* a bit and a byte are?
- both bit and byte are sizes that are stored in the machine. 1 byte is 8 bits of storage.

## Explain it like I'm teaching a friend
- What is a bit, and what is a byte made of?
- a bit is a size of the storage that is required to store a value, a byte is made of 8 bits.

- Why does `int` overflow instead of showing an error?
- hte int overflows because it once it reaches the max value it wraps itself to the smallest value at runtime so this is the reason why int overflow's instead of showing an error.

- Why is `char` basically just a number underneath?
- the machine can read only numbers from 0 to 1 so that is binary values, so everything we write is converted to binary values so that the machine can read these values for example 11 can be written as 1011 in binary

- Why doesn't `0.1 + 0.2 == 0.3` in C++?
- the value is off by some value when adding the two numbers in c++ so that is the reason why it is not equal to 0.3.

## Ex 1 — binary by hand
- My by-hand conversions (`0b0110`, `0b1001`, `0b1111`):
- 0b110 = 6, 0b1001 = 9, 0b1111 = 15.
- Did the program confirm them?
-

## Ex 2 — predict, then check (int overflow)
- My prediction before compiling:
- i think if you add 1 to maximum int number, the value will be converted to the lowest value the int can hold.
- What actually happened:
- the value went to the lowest number that int can hold that is -2147483648.

## Ex 3 — the wraparound health bug
- My predicted hp values after each hit:
- my predicted values are 240, 230, 220.
- Actual hp values:
- 240, 230, 220
- Why this happened, in my own words:
- char holds upto the value 250 so reducing -10 each time didnt give any issues.

## Ex 4 — char, int, ASCII
- My predictions for `'A' + 1` (as char vs. as int):
- as a char it will output B and as an int it will output the number 66.
- What actually printed:
- my predictions were true.

## Ex 5 — float vs. precision
- My prediction (`true`/`false`):
- my prediction is that the output will be false.
- What actually happened, float vs double, and the precision(17) output:
- false, c++ loses precision a bit so the value is not exactly equalled to 0.3.

## Ex 6 — choosing types for a game character
- Which stat(s) could secretly wrap around if I'd picked a smaller type, and why I
  avoided or accepted that risk:
- i have given the answers in the .cpp file as comments.

## What surprised me / what's still confusing

