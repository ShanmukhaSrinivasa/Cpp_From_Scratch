#include <iostream>

int main()
{
    int level = 4;
    bool hasKey = true;
    bool isAdmin = false;

    std::cout << std::boolalpha;
    std::cout << (hasKey && level >= 5) << "\n";               // false (0)
    std::cout << (hasKey || level >= 5) << "\n";               // true (1)
    std::cout << (!hasKey) << "\n";                            // false (0)
    std::cout << ((hasKey && level >= 5) || isAdmin) << "\n";  // false (0)
    std::cout << (!(level > 3) || isAdmin) << "\n";            // false (0)
    std::cout << (level != 4 && hasKey) << "\n";               // false (0)

    return 0;
}