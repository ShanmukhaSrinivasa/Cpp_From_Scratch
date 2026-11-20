#include <iostream>

int main()
{
    // 1. using While loop

    int countdown = 10;

    while(countdown > 0)
    {
        std::cout << countdown << "\n";
        countdown -= 1;
    }

    std::cout << "Liftoff!" << "\n";

    // 2. Using for loop

    for(int i=1; i<=10; i++)
    {
        std::cout << i << " ";
    }

    std::cout << "\n";

    // 3. Even numbers using for loop

    for(int i=0; i<=20; i+=2)
    {
        std::cout << i << " ";
    }

    return 0;
}