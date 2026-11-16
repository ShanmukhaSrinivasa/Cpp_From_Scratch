#include <iostream>

int main()
{
    int health;
    std::cout << "Enter player's health: ";
    std::cin >> health;

    if(health < 0 || health > 100)
    {
        std::cout << "Invalid health value." << "\n";
    }
    else if(health == 0)
    {
        std::cout << "Player is Dead." << "\n";
    }
    else if(health >= 1 && health <= 24)
    {
        std::cout << "Player health is Critical." << "\n";
    }
    else if(health >= 25 && health <= 74)
    {
        std::cout << "Player is hurt." << "\n";
    }
    else
    {
        std::cout << "Player is Healthy." << "\n";
    }

    return 0;
}