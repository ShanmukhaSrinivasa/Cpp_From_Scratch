#include <iostream>

int main()
{
    std::cout << "ASCII code of 'A' is: " << static_cast<int>('A') << "\n";
    std::cout << "ASCII code of 'a' is: " << static_cast<int>('a') << "\n";
    std::cout << "ASCII code of '0' is: " << static_cast<int>('0') << "\n";

    std::cout << "Character code of 72 is: " << static_cast<char>(72) << "\n";
    std::cout << "Character code of 105 is: " << static_cast<char>(105) << "\n";
    std::cout << "Character code of 33 is: " << static_cast<char>(33) << "\n";

    char ch = 'A' + 1;

    std::cout << "As a char A+1 is: " << ch << "\n";

    std::cout << "As a int A+1 is: " << static_cast<int>(ch) << "\n";

    return 0;
}