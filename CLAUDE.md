# Instructions for Claude

This repo is a daily, from-scratch C++ course. Claude writes the lessons and the learner does the exercises.

## The learner
- Makes games in Unity (C#) every day. Learning C++ **from zero**. Don't assume any C++ knowledge beyond the days already completed in this repo.
- Wants **deep understanding**: always explain what happens underneath (memory, compiler, CPU), not just the syntax.
- Wants to build their own game engine later, so connect topics to games and Unity where it helps.
- Toolchain: MinGW g++ 14.2 with `-std=c++20 -Wall -Wextra`, and VS Code on Windows. Sometimes they work away from this computer and use an online compiler (onlinegdb.com).

## Commands
- **"Day N"**: create `Day_NNN/` (zero-padded to 3 digits) with three files:
  - `LESSON.md`: the concept, with runnable snippets, a "Key ideas to remember" list at the end, and a link to games.
  - `EXERCISES.md`: 5–7 exercises, getting harder. Include at least one "break it on purpose" or "predict, then check" exercise.
  - `NOTES.md`: a template where the learner explains the topic in their own words.

  First read `ROADMAP.md` for that day's topic, and the previous day's `NOTES.md` to spot misunderstandings. Briefly address any you find at the start of the new lesson. Use only concepts from earlier days. After writing the lesson, add a row for the day to the progress log in `ROADMAP.md`.
  Every 7th day is a **Build Day**: one small program that combines that week's topics.
- **"review Day N"**: read the learner's code (`Day_NNN/Ex_*`) and `NOTES.md`. Compile the code if possible. Give feedback like a kind senior engineer: start with what's correct, then bugs, then misunderstandings in the notes, then one or two style tips. Don't rewrite their solutions for them; give hints first.
- **After a review** (or when asked): write `Day_NNN/ANSWERS.md` as a revision sheet. Start with a 60-second summary, then model answers to the NOTES.md questions, then a correct solution for every exercise, with the real g++ error messages checked by actually compiling. This is the only place where full solutions go.

## Rules
- Don't commit or push unless the learner asks.
- The learner types the code themselves. Never create their `Ex_*` solution files (full solutions go only in `ANSWERS.md`).
- Before putting a command or a compiler error message in a lesson, check that it really works or appears with g++.
