# START HERE — Continue learning on any computer

Use this when you're on a new or different computer (office, laptop, a friend's PC)
or on your phone.

---

## 1. First time on a new computer (one-time setup)

**a) Get the files**
```bash
git clone https://github.com/ShanmukhaSrinivasa/Cpp_From_Scratch.git
cd Cpp_From_Scratch
```

**b) Open Claude Code in that folder.** Any of these work:
- **Claude desktop app** → **Code** tab → choose the `Cpp_From_Scratch` folder
- **Browser / phone** → **claude.ai/code** → pick the `Cpp_From_Scratch` GitHub repo (no clone needed)
- **Terminal** → `cd Cpp_From_Scratch` then `claude`

Claude reads `CLAUDE.md` in this folder automatically, so it already knows the course,
the format and the rules. You don't need to explain anything.

**c) Check you have a C++ compiler**
```bash
g++ --version
```
- Version shown → you're ready.
- "not recognized" → tell Claude: **`set up g++ on this computer`**
- Can't install anything (office laptop)? Use **onlinegdb.com** → language **C++20**.
  Copy your code into the repo afterwards so it gets saved.

---

## 2. Every time you sit down to learn

**Step 1 — Get the latest files** (always do this first, so you continue from where you left off)
```bash
git pull
```

**Step 2 — Tell Claude what you want** (see the command list below)

**Step 3 — When you finish, save your work to GitHub**
```bash
git add -A
```
```bash
git commit -m "Day 2: variables, exercises 1-6, notes"
```
```bash
git push
```
Or just tell Claude: **`commit and push my work`**

> ⚠️ **Always `git pull` before you start and `git push` when you stop.**
> If you forget to push at home, the office computer won't have your latest work.

---

## 3. Commands to give Claude

| You type | Claude does |
|---|---|
| **`where am I?`** | Reads the progress log and tells you the last completed day, anything unfinished, and what's next. Use this when you've forgotten. |
| **`Day 2`** (any number) | Creates `Day_002/` with `LESSON.md`, `EXERCISES.md` and `NOTES.md`. |
| **`review Day 2`** | Compiles and checks your exercise code and notes, explains mistakes, gives hints, and then writes `ANSWERS.md` for revision. |
| **`answers Day 2`** | Writes or updates only the `ANSWERS.md` revision sheet. |
| **`quiz me on Day 1-5`** | A quick test of 5–10 questions from those days, without looking. Good for revision. |
| **`explain <topic> again`** | A different explanation of something you didn't get, e.g. `explain pointers again`. |
| **`why does <thing> happen?`** | Ask anything. Going deep is the whole point of this course. |
| **`commit and push my work`** | Saves everything to GitHub with a clear commit message. |
| **`set up g++ on this computer`** | Helps you install a C++ compiler on a new machine. |

### Typical day
```
git pull
→ "where am I?"
→ "Day 3"
   ... read LESSON.md, do EXERCISES.md, fill NOTES.md ...
→ "review Day 3"
   ... fix what the review found ...
→ "commit and push my work"
```

---

## 4. Folder layout (so you know where things are)
```
START_HERE.md     ← this file
ROADMAP.md        full plan + progress log
CLAUDE.md         instructions Claude reads automatically (no need to touch it)
README.md         short description for GitHub
Day_001/
  LESSON.md       read first
  EXERCISES.md    then do these
  NOTES.md        explain it in your own words
  ANSWERS.md      revision sheet (after review)
  Ex_1/ Ex_2/ …   your code
```

## 5. Compile & run (reminder)
```bash
cd Day_002/Ex_1
```
```bash
g++ -std=c++20 -Wall -Wextra main.cpp -o main.exe
```
```bash
./main.exe
```
In VS Code: open the `.cpp` file → **Ctrl + Shift + B** to build.
