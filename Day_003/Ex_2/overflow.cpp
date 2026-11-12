#include <iostream>
#include <climits>

int main()
{
    int a = INT_MAX;
    std::cout << "Before adding +1 " << a << "\n";
    a += 1;
    std::cout << "After adding +1 " << a << "\n";
    return 0;
}