#include <iostream>

int main()
{
    char choice;
    int players_health = 60;
    int enemys_armor;
    int stamina = 25;
    int attack_damage = 15;
    int heavy_damage = 30;
    int final_damage;
    // REVIEW: FIXED. Both attacks now print final_damage (warning gone).
    //
    // Style: the course uses camelCase (playerHealth, enemyArmor, finalDamage)
    // like your earlier days, not snake_case.

    std::cout << " === COMBAT TURN GAME === " << "\n";
    std::cout << "Enter Enemy's Armor amount (from 0-20): ";

    std::cin >> enemys_armor;

    // REVIEW: Fixed! fail() now runs AFTER the read, so it can see whether
    // the read worked. Typing "abc" now prints this message.
    if(std::cin.fail())
    {
        std::cout << "That's not a valid number for Armor.";
        return 1;
    }

    // REVIEW: FIXED. Armor 0 is accepted now.
    if(enemys_armor < 0 || enemys_armor > 20)
    {
        std::cout << "Enemy's Armor amount should be from 0-20 only.";
        return 1;
    }

    std::cout << "The Choices are: " << "\n";
    std::cout << "A. Attack on Enemy." << "\n";
    std::cout << "H. Heavy Attack on Enemy (Uses 20 Stamina)." << "\n";
    std::cout << "P. Potion (Heal Player)" << "\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch(choice)
    {
        case 'a':
        case 'A':
            final_damage = attack_damage - enemys_armor;
            // REVIEW: CORRECT. `< 1` catches both 0 and negatives.
            // Tested: armor 5 -> 10, armor 15 -> 1 (the edge case), armor 20 -> 1.
            if(final_damage < 1)
            {
                final_damage = 1;
            }
            std::cout << "You have dealt " << attack_damage << " damage to the enemy, and the final damage dealt is: " << final_damage << "\n";
            break;

        case 'h':
        case 'H':
            if(stamina >= 20)
            {
                final_damage = heavy_damage - enemys_armor;
                // REVIEW: CORRECT. With stamina 25: heavy vs armor 0 -> 30,
                // heavy vs armor 20 -> 10. (Tiny typo in the message: ". ,")
                if(final_damage < 1)
                {
                    final_damage = 1;
                }
                stamina -= 20;
                std::cout << "You have dealt " << heavy_damage << " damage to the enemy. , and the final damage dealt is: " << final_damage << "\n";
            }
            else
            {
                std::cout << "Too Tired!" << "\n";
                std::cout << "You have dealt ZERO damage to the enemy." << "\n";
            }
            break;

        case 'p':
        case 'P':
            players_health += 20;
            if(players_health > 100)
            {
                players_health = 100;
            }
            std::cout << "You have used a Health Potion and healed for 20 health, Your health is now: " << players_health << "\n";
            break;

        default:
            std::cout << "You stumble. Turn lost." << "\n";
            break;    
    }

    return 0;
}