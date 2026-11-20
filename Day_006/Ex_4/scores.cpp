#include <iostream>
#include <limits>

int main()
{
    int no_of_scores;
    int score;
    int total = 0;
    int highest = 0;
    double average = 0;

    while(true)
    {
        std::cout << "How many Scores do you want to enter ?";
        std::cin >> no_of_scores;

        if(std::cin.fail())
        {
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Invalid Number, Try again!" << "\n";
            continue;
        }

        break;
    }

    // FIX: was `== 0`. A negative count (like -3) slipped past it: the loop
    // below ran 0 times and then printed "Average: -0" (0 divided by -3).
    // `<= 0` catches zero AND negative counts, so we never divide by them.
    if(no_of_scores <= 0)
    {
        std::cout << "User decided to not enter any score" << "\n";
        return 0;
    }

    for(int i=1; i<=no_of_scores; i++)
    {
        std::cout << "Enter Score " << i << ": ";
        std::cin >> score;

        // FIX: was just `score > highest`, with highest starting at 0.
        // If every score is negative (-5, -8), none is bigger than 0, so it
        // reported "Highest: 0", a score nobody entered.
        // Now the FIRST score (i == 1) always becomes the highest so far, and
        // only later scores are compared. Thanks to short-circuiting (Day 5),
        // when i == 1 is true the comparison isn't even needed.
        if(i == 1 || score > highest)
        {
            highest = score;
        }

        total += score;
    }

    std::cout << "Total: " << total << "\n";
    
    average = static_cast<double>(total) / static_cast<double>(no_of_scores);
    std::cout << "Average is: " << average << "\n";
    
    std::cout << "Highest: " << highest << "\n";
    
    return 0;
}