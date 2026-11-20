#include <iostream>
#include <limits>

int main()
{
    int enemy_armor;

    while(true)
    {
        std::cout << "Enter enemy's armor value: ";
        std::cin >> enemy_armor;

        if(std::cin.fail() || enemy_armor < 0 || enemy_armor > 20)
        {
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

            std::cout << "Not a valid number or Armor should be between 0-20. Try again!" << "\n";
            continue;
        }

        break;
    }

    std::cout << "Enemy Armor set to: " << enemy_armor << "\n";

    return 0;
}