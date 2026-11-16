#include <iostream>

int main()
{
    int totalScore = 0;
    std::cout << "Enter your total score: ";
    std::cin >> totalScore;

    int gamesPlayed = 0;
    std::cout << "Enter total games played: ";
    std::cin >> gamesPlayed;

    // REVIEW: CORRECT. Tested: 500/2 -> Pro player! (exit 0),
    // 100/2 -> Keep Practising (exit 0), 500/0 -> Keep Practising (exit 0, no crash).
    // The short-circuit of && is what protects the division.
    //
    // How it works, left to right with gamesPlayed = 0:
    //   1. gamesPlayed != 0   -> false
    //   2. false && (anything) is ALWAYS false, so C++ stops here.
    //      totalScore / gamesPlayed is NEVER evaluated -> no divide-by-zero.
    //
    // Then swap the two sides:
    //
    //     if (totalScore / gamesPlayed > 100 && gamesPlayed != 0)
    //
    // Now the division is on the LEFT, so it runs first, before the check
    // can protect it -> crash. In PowerShell, `echo $LASTEXITCODE` shows
    // -1073741676 (Windows' "integer divide by zero" code).
    if(gamesPlayed != 0 && totalScore/gamesPlayed > 100)
    {
        std::cout << "Pro player!" << "\n";
    }
    else
    {
        // REVIEW: FIXED. "Keep Practising" is a normal result, so the program
        // now reaches `return 0;` (success) instead of reporting a failure.
        std::cout << "Keep Practising" << "\n";
    }

    return 0;
}