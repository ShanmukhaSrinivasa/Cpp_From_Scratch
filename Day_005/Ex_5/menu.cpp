#include <iostream>

int main()
{
    int choice;

    std::cout << "=== MAIN MENU ===" << "\n";
    std::cout << "1. New Game" << "\n";
    std::cout << "2. Load Game" << "\n";
    std::cout << "3. Options" << "\n";
    std::cout << "4. Quit" << "\n";
    std::cout << "Enter your selection: ";
    std::cin >> choice;

    switch(choice)
    {
        case 1:
            std::cout << "Starting a new adventure... "    << "\n";
            break;
        
        case 2:
            std::cout << "Continuing the adventure... "    << "\n";
            break;
        
        case 3:
            std::cout << "Opening the Options menu "    << "\n";
            break;

        case 4:
            std::cout << "Qutting the application."    << "\n";
            break;

        default:
            std::cout << "Invalid Choice!" << "\n";
            break;
    }

    return 0;
}