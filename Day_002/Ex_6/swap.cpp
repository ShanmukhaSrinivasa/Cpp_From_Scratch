#include <iostream>

int main()
{
    int a = 9;
    int b = 18;
    int c = 0;

    std::cout << "Before Swap: A = " << a << ", B = " << b << std::endl;

    c = a;
    a = b;
    b = c;

    std::cout << "After Swap: A = " << a << ", B = " << b << std::endl;

    return 0;
}