#include <iostream>
#include <limits>   // FIX: needed for std::numeric_limits below

int main()
{
    int player_hp = 50;
    int turns = 0;
    int choice = 0;   // FIX: start at 0 so it never holds a garbage value (Day 2)

    do
    {
        std::cout << "=== HP: " << player_hp << " ===" << "\n";
        std::cout << "1. Drink potion (+20 HP, max 100)" << "\n";
        std::cout << "2. Fight a goblin (-15 HP)" << "\n";
        std::cout << "3. Rest (+5 HP, max 100)" << "\n";
        std::cout << "4. Quit" << "\n";
        std::cout << "Choose: ";
        std::cin >> choice;

        // FIX: typing a letter like `x` used to print the menu forever.
        // A failed read puts cin into a "failed" state, and every later >>
        // then fails instantly without waiting for you (your Ex 6 experiment).
        // Same retry pattern as Ex 6:
        //   clear()  -> reset the failed state
        //   ignore() -> throw away the bad text still waiting in the input
        //   continue -> jump to the loop's check, showing the menu again.
        // In a do-while, `continue` goes to `while(choice != 4)`. choice is 0
        // after a failed read, so the loop keeps going, and no turn is counted.
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a number from 1 to 4." << "\n";
            continue;
        }

        switch(choice)
        {
            case 1:
                player_hp += 20;

                if(player_hp > 100)
                {
                    player_hp = 100;
                }
                std::cout << "Player used potion and the health is: " << player_hp << "\n";
                turns++;
                break;
            
            case 2:
                turns++;
                std::cout << "Player took a fight with Goblin! and lost 15 HP." << "\n";
                player_hp -= 15;
                std::cout << "Player's current health is: " << player_hp << "\n";
                break;

            case 3:
                turns++;
                std::cout << "Player took a nap and recovered 5 HP." << "\n";
                player_hp += 5;
                if(player_hp > 100)
                {
                    player_hp = 100;
                }
                std::cout << "Player's current health is: " << player_hp << "\n";
                break;

            case 4:
                std::cout << "Exiting the Game!! " << "\n";
                break;

            default:
                std::cout << "Invalid Choice!! Try again!" << "\n";
                break;
        }

        if(player_hp <= 0)
        {
            std::cout << "You Died. Game over." << "\n";
            break;
        }


    }while(choice != 4);

    std::cout << "No.of Turns: " << turns << "\n";

    return 0;
}