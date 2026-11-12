#include <iostream>

int main()
{
    int health = 100; // we can use integer variable for health as it can hold both neg and pos numbers and also large values which are sufficient enough for health

    char slot = 'A'; // we can char for a single inventory slot letter because char because char takes very less space and also satisfies the need of holding a single letter.

    float walkingSpeed = 4.5f; // we can use float for the walking speed value because it can hold decimal values.

    bool isStunned = true; // we can use a boolean variable for this because we only need to two states that is: is the player stunned or not stunned so if the player is stunned we can use true and if not we can use false. so for this reason we can use a boolean variable.

    std::cout << "Health: " << health << "\n";
    std::cout << "Inventory Slot: " << slot << "\n";
    std::cout << "Walking Speed: " << walkingSpeed << "\n";
    std::cout << "Is the player Stunned: " << isStunned << "\n";

    return 0;
}