# Day 2 — My Notes

## Before I start: what do I *think* a variable is in memory?
- a variable is an object that is created to store a value or character or anything such as numbers, words, letters etc.

## Explain it like I'm teaching a friend
- What happens in memory when I write `int health = 100;`?
- in the memory a space is created with the name health and it holds the value of 100.

- What's the difference between declaration, initialization and assignment?
- declaration mean we are saying that there would be a variable named this and initializing means making that variable have a starting value such as 100 for health, and then assignment means assigning a value to the variable.

- Why is reading an uninitialized variable dangerous, instead of just "it's zero"?
- it is dangerous to read an uninitialized value because it might be a random and very big number instead of zero and while doing any calculations the program might overflow and show us an error.

- Why does `std::string` need double quotes but `char` needs single quotes?
- string stores a set of chars just like an array but for charcaters or letters, char stores a single character or letter, so in c++ to differentiate both we use double quotes for string and single quote for chars.

## Ex 2 — predict, then check
- My prediction before compiling:
- i think code will compile but it will show a warning saying the score is not initialized and it will show a very big random number.
- What g++ actually said / what the program printed:
- the output warning is 'score' is used uninitialized [-Wuninitialized]
- after running the program for 3 times, eevrytime i got a new and random number.

## Ex 3 — error messages I saw
- a: it says the variable is already previously declared.
- b: it says the variable was not declared in the scope.
- c: it says expected unqualified-id before numeric constant.
- d: it says itn was not declared in this scope; did you mean int?.
- e: it says invalid conversion from const char* to char.

## Ex 4 — sizeof and addresses
1. Biggest type / smallest type:
- biggest is double with the size of 8 bytes. and the smallest it char with 1 byte.
2. Were the addresses contiguous?
- no the addresses were not contiguos.

## Ex 5 — predict, then check (narrowing)
- My three guesses (a, b, c):
- a. the compiler will throw an error because int cannot store decimal values.
- b. i think the compiler will explicitly convert decimal values to int and show 7 as output
- c. i think the compiler will run with no errors and show output as 7
- What actually happened:
- a. didnt show any error
- b. invalid narrowing conversion from doubl to int
- c. no error

## What surprised me / what's still confusing

