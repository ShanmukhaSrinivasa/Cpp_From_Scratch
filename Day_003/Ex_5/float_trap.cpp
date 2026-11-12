#include <iostream>

int main()
{
    double a = 0.1;
    double b = 0.2;

    float c = 0.1;
    float d = 0.2;

    std::cout.precision(17);
    std::cout << (a + b) << "\n";
    std::cout << std::boolalpha << (a + b == 0.3) << "\n";
    std::cout  << c + d << "\n";
    std::cout << std::boolalpha << (c + d == 0.3) << "\n";


    return 0;
}