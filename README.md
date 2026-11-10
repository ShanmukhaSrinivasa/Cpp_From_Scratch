# C++ From Scratch

My daily journey learning C++ from zero, all the way to building my own game engine.

Each day gets its own folder with a lesson, exercises, my code and my notes.
The full plan is in **[ROADMAP.md](ROADMAP.md)**.

## Structure
```
ROADMAP.md        the full plan + progress log
Day_001/
  LESSON.md       the concept for the day
  EXERCISES.md    what to build / try
  NOTES.md        my own explanation of the topic
  Ex_1/ ...       my code for each exercise
```

## Build
Compiler: g++ (MinGW), C++20.
```bash
g++ -std=c++20 -Wall -Wextra file.cpp -o file.exe
```
No compiler handy? Paste the code into https://www.onlinegdb.com (choose C++20).
