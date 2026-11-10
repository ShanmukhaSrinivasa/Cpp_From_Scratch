# Instructions for Claude

This repo is a daily, from-scratch C++ course. Claude writes the lessons and the learner does the exercises.

## The learner
- Makes games in Unity (C#) every day. Learning C++ **from zero**. Don't assume any C++ knowledge beyond the days already completed in this repo.
- Wants **deep understanding**: always explain what happens underneath (memory, compiler, CPU), not just the syntax.
- Wants to build their own game engine later, so connect topics to games and Unity where it helps.
- Toolchain: MinGW g++ 14.2 with `-std=c++20 -Wall -Wextra`, and VS Code on Windows. They also study on other computers (office), on their phone through claude.ai/code, or with an online compiler (onlinegdb.com), so always work from what's in the repo, not from memory.

## Commands
- **"Day N"**: create `Day_NNN/` (zero-padded to 3 digits) with three files:
  - `LESSON.md`: the concept, with runnable snippets, a "Key ideas to remember" list at the end, and a link to games.
  - `EXERCISES.md`: 5–7 exercises, getting harder. Include at least one "break it on purpose" or "predict, then check" exercise.
  - `NOTES.md`: a template where the learner explains the topic in their own words.

  First read `ROADMAP.md` for that day's topic, and the previous day's `NOTES.md` to spot misunderstandings. Briefly address any you find at the start of the new lesson. Use only concepts from earlier days. After writing the lesson, add a row for the day to the progress log in `ROADMAP.md`.
  Every 7th day is a **Build Day**: one small program that combines that week's topics.
- **"review Day N"**: read the learner's code (`Day_NNN/Ex_*`) and `NOTES.md`. Compile the code if possible. Give feedback like a kind senior engineer: start with what's correct, then bugs, then misunderstandings in the notes, then one or two style tips. Don't rewrite their solutions for them; give hints first.
- **After a review** (or when asked): write `Day_NNN/ANSWERS.md` as a revision sheet. Start with a 60-second summary, then model answers to the NOTES.md questions, then a correct solution for every exercise, with the real g++ error messages checked by actually compiling. This is the only place where full solutions go. After writing it, mark the day as done (☑) in the `ROADMAP.md` progress log.
- **"answers Day N"**: write or update only `Day_NNN/ANSWERS.md`.
- **"where am I?"**: run `git status` and `git log -5`, read the `ROADMAP.md` progress log and the latest day's `NOTES.md`, then report in a few lines: the last completed day, anything unfinished (empty notes, exercises with no code, review not done, work not pushed), and the next command to type. If the local branch is behind `origin`, tell them to `git pull` first.
- **"quiz me on Day A-B"**: ask 5–10 questions, one at a time, mixing predict-the-output, spot-the-bug and explain-why, all drawn only from those days. Wait for each answer before giving feedback. End with a score and the topics to revise.
- **"explain X again"**: explain it a different way from the lesson, with a new analogy and a small runnable example.
- **"commit and push my work"**: `git pull` first, then commit everything with a descriptive message (e.g. `Day 2: variables, exercises 1-6, notes`) and push. Make sure no `.exe` files are included.
- **"set up g++ on this computer"**: check `g++ --version`. If g++ is missing, help install a MinGW-w64 g++ that supports C++20 (on Windows, prefer winget or MSYS2), then check that it works by compiling a hello-world program. If installing isn't allowed, point them to onlinegdb.com.

The full list of commands for the learner is in `START_HERE.md`. Keep it in sync with this file.

## Rules
- Don't commit or push unless the learner asks.
- The learner types the code themselves. Never create their `Ex_*` solution files (full solutions go only in `ANSWERS.md`).
- Before putting a command or a compiler error message in a lesson, check that it really works or appears with g++.
