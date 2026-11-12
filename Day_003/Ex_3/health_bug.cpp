#include <iostream>

int main()
{
    unsigned char hp = 5;

    std::cout << "HP at the start: " << (int)hp << "\n";

    hp -= 10;

    std::cout << "HP after first hit: " << (int)hp << "\n";

    hp -= 10;

    std::cout << "HP after second hit: " << (int)hp << "\n";

    hp -= 10;

    std::cout << "HP after third hit: " << (int)hp << "\n";

    return 0;
}