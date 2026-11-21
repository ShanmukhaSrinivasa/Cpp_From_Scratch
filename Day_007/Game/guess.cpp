#include <iostream>
#include <random>
#include <limits>

int main()
{
    int guess;
    int tries = 1;
    int secret;
    char playAgain;

    // Settings
    int difficulty;
    int maxNumber;
    int maxTries;

    // Session Stats
    int gamesPlayed = 0;
    int wins = 0;
    int bestGuesses = 11;

    std::random_device seed;
    std::mt19937 generator(seed());

    do
    {
        while(true)
        {
            std::cout << "=== GUESS THE NUMBER ===" << "\n" << "\n";
            std::cout << "Choose Difficulty:" << "\n";
            std::cout << "1. Easy   (1-50,  10 tries)" << "\n";
            std::cout << "2. Normal (1-100,  7 tries)" << "\n";
            std::cout << "3. Hard   (1-500,  9 tries)" << "\n";
            std::cout << "Choose: ";
            std::cin >> difficulty;
    
            if(std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
                std::cout << "Invalid Choice. Try again!" << "\n";
                continue;
            }
            break;
        }

        switch(difficulty)
        {
            case 1:
                maxNumber = 50;
                maxTries = 10;
                break;
            
            case 2:
                maxNumber = 100;
                maxTries = 7;
                break;
                
            case 3:
                maxNumber = 500;
                maxTries = 9;
                break;

            default:
                std::cout << "Invalid Choice. Try again!" << "\n";
                break;
        }

        std::cout << "I'm thinking of a number from 1 to " << maxNumber << ". You have " << maxTries << " tries." << "\n";

        std::uniform_int_distribution<int> range(1, maxNumber);
        secret = range(generator);

        gamesPlayed++;

        while(tries <= maxTries)
        {
            std::cout << "Guess " << tries << "/" << maxTries << ": ";
            std::cin >> guess;

            if(std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Numbers only! (That didn't cost a try.)" << "\n";
                continue;
            }

            if(guess > maxNumber || guess < 1)
            {
                std::cout << "Between 1 and " << maxNumber << ", please.  (That didn't cost a try.)" << "\n";
                continue;
            }

            if(guess > secret)
            {
                if(secret - guess <= 5)
                {
                    std::cout << "Too high! (very close!)" << "\n";
                }
                else
                {
                    std::cout << "Too high!" << "\n";
                }
                tries++;
            }
            else if(guess < secret)
            {
                if(guess - secret <= 5)
                {
                    std::cout << "Too low! (very close!)" << "\n";
                }
                else
                {
                    std::cout << "Too low!" << "\n";
                }

                tries++;
            }
            else if(guess == secret)
            {
                std::cout << "You got it in " << tries << " guesses!" << "\n";

                if(tries < bestGuesses)
                {
                    bestGuesses = tries;
                    std::cout << "New best!" << "\n";
                }
                wins++;
                break;
            }
        }

        if(tries > maxTries)
        {
            std::cout << "You lost! The secret number was " << secret << "\n";
        }

        std::cout << "Play again? (y/n): ";
        std::cin >> playAgain;

        if(playAgain == 'y' || playAgain == 'Y')
        {
            tries = 1;
        }

    }while(playAgain == 'y' || playAgain == 'Y');

    if(bestGuesses == 11)
    {
        bestGuesses = 0;
    }

    std::cout << "Games: " << gamesPlayed << ", wins: " << wins << ", best: " << bestGuesses << " guesses" << "\n";
    std::cout << "Thanks for playing!" << "\n";

    gamesPlayed = 0;
    wins = 0;
    bestGuesses = 0;

    return 0;
}